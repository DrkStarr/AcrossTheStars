#!/usr/bin/perl
# glk2inf.pl glk.h func.txt

# (C)opyright 1999 by John Cater
# katre@ruf.rice.edu
# Much help received from the greal guys at ifMUD 
# (http://ifmud.port4000.org:4001), especially Dan Shiovitz.

# A perl program to generate inform functions corresponding to glk functions.
# The arguments are a glk.h file and a func.txt file.  glk.h can be obtained
# from your glk library, or from http://www.eblong.com/zarf/glk.  func.txt is
# a list of the glk funcs accompanied by their selector numbers.  This list
# can be built from the glk specifiation file, at the above address, but should
# be distributed with this file.

if ($#ARGV != 1)
{
   die "Usage: glk2inf.pl glk.h func.txt";
}

$glk_file = $ARGV[0];
$func_file = $ARGV[1];

# First, read in func.txt
open (FUNC_FILE, "<$func_file") ||
   die "Can't open func.txt";

$num_funcs = 0;
$func_data = {};
$func_hash = {};

while (defined ($line = <FUNC_FILE>))
{
   #the format is 'number: func'
   if ($line =~ /\s*(0x[0-9A-Fa-f]+):\s+(\w+)/)
   {
      $number = hex($1); $name = $2;
      $func_data[$num_funcs]->{name} = $name;
      $func_data[$num_funcs]->{selector} = $number;
      $func_hash->{$name} = $num_funcs;
      $num_funcs++;
   }
}
close (FUNC_FILE);

print "Read in $num_funcs function selectors.\n";

# Next, read in glk.h (headache)
open (GLK_FILE, "<$glk_file") ||
   die "Can't open glk.h.";

$num_glk_cons = 0;
$glk_cons_data = {};
$glk_cons_hash = {};

$num_glk_funcs = 0;
$glk_func_data = {};
$glk_func_hash = {};

while (defined ($line = <GLK_FILE>))
{
   #First, check for constant #def's.
   # The format is '#define name (val)'
   if ($line =~ /#define\s+(\w+)\s+\((?:0x([0-9A-Fa-f]+)|(\d+))\)/)
   {
      $name = $1;
      if (defined($2)) # hex number
      {
         $value = "\$" . $2;
      } else # decimal number
      {
         $value = $3;
      }
      $glk_cons_data[$num_glk_cons]->{name} = $name;
      $glk_cons_data[$num_glk_cons]->{value} = $value;
      $glk_cons_hash->{$name} = $num_glk_cons;
      $num_glk_cons++;
   }

   #Second, check for functions
   # The format is 'extern ret_type name(arg_type args, ...);'
   if ($line =~ /^extern/)
   {
      my @arg_list = ();

      # See if this line is complete
      chomp $line;
      if ($line !~ /;/) # it's not over yet
      {
         #get the next line, and check it
         #no function declaration is longer than 2 lines
         $next = <GLK_FILE>;
         chomp $next;
         if ($next !~ /;/) # This is a problem
         {
            print "Warnign: Function not complete.\n";
            next;
         }
         # concatenate the two lines
         $line = $line . $next;
      } # otherwise, the line is fine

      @func = split(/[^a-zA-Z0-9_]+/,$line);
      
      do
      {
         $ret_type = shift @func;
      }
      while (($ret_type eq "extern") || ($ret_type eq "unsigned"));

      $name = shift @func;

      $num_args = 0;
      while (defined($arg = shift @func))
      {
         if ($arg eq "unsigned")
         {
            next;
         }

         if ($arg eq "void")
         {
            # check for another entry, to see if it's a func pointer
            if (@func != 0)
            {
               $arg_list[$num_args] = shift @func;
               shift @func; # gets rid of value.  very non-portable
            } else
            {
               next;
            }
         } else
         {
            $arg = shift @func;
            $arg_list[$num_args] = $arg;
         }

         $num_args++;
      }

      if ($name eq "glk_main")
      {
         next;
      }

      $glk_func_data[$num_glk_funcs]->{name} = $name;
      $glk_func_data[$num_glk_funcs]->{ret_type} = $ret_type;
      $glk_func_data[$num_glk_funcs]->{num_args} = $num_args;
      $glk_func_data[$num_glk_funcs]->{arg_list} = \@arg_list;

      $glk_func_hash->{$name} = $num_glk_funcs;
      $num_glk_funcs++;
   }
   
}
close (GLK_FILE);

print "Read in $num_glk_cons Glk Constants.\n";
print "Read in $num_glk_funcs Glk Functions.\n";

#Okay, input is done.  Time to start writing.
open (OUT_FILE, ">infglk.h") ||
   die "Can't open infglk.h.";

# Write in things like the filename, copyright info, etc.
($sec,$min,$hour,$mday,$month,$year,$wday,$yday,$isdst) = localtime(time);

$date = sprintf("%02d%02d%02d at %02d:%02d.%02d",
                 $year, $month + 1, $mday, $hour, $min, $sec);

print OUT_FILE "!-------------------------------------------------------------------------------\n";
print OUT_FILE "!  infglk.h - an Inform library to allow easy access to glk functions\n";
print OUT_FILE "!    under glulx\n";
print OUT_FILE "!  Dynamically created by glk2inf.pl on $date.\n";
print OUT_FILE "!  Send comments or suggestions to: katre\@ruf.rice.edu\n";
print OUT_FILE "!-------------------------------------------------------------------------------\n";
print OUT_FILE "System_file;\n";
print OUT_FILE "#Ifdef TARGET_GLULX;\n";
print OUT_FILE "#Ifndef infglk_h;\n";
print OUT_FILE "Constant infglk_h;\n";
print OUT_FILE "Message \"[Including <infglk>]\";\n";
print OUT_FILE "\n";
#print OUT_FILE "#Ifdef infglk_h;  ! remove \"Constant declared but not used\" warnings\n";
#print OUT_FILE "#Endif;\n";
print OUT_FILE "\n";
print OUT_FILE "Constant GLK_NULL 0;\n";
print OUT_FILE "\n";

# Now, add in the Constant definitions
print OUT_FILE "! Constant definitions from glk.h\n";
$cons_out = 0;
for ($i = 0; $i < $num_glk_cons; $i++)
{
   my $name = $glk_cons_data[$i]->{name};
   my $value = $glk_cons_data[$i]->{value};
   print OUT_FILE "Constant $name $value;\n";
   $cons_out++;
}
print "Processed $cons_out Constant declarations.\n";
print OUT_FILE "\n";

if ($num_funcs != $num_glk_funcs)
{
   print "Warning: there are unmatched functions.\n";
}

# Now, the functions
print OUT_FILE "! The actual glk functions.\n";
$num_funcs = 0;
for ($i = 0; $i < $num_glk_funcs; $i++)
{
   my $name = $glk_func_data[$i]->{name};
   my $ret_type = $glk_func_data[$i]->{ret_type};
   my $num_args = $glk_func_data[$i]->{num_args};
   my @arg_list = @{$glk_func_data[$i]->{arg_list}};
   if (!defined ($func_data[$func_hash->{$name}]->{selector}))
   {
      # This function does not have a selector.  Make a note, and skip it.
      print "Glk Function $name does not have a selector.\n";
      next;
   }
   my $selector = $func_data[$func_hash->{$name}]->{selector};

   print OUT_FILE "[ $name ",join (" ",@arg_list),"\n";
   print OUT_FILE "      ret;\n";
   print OUT_FILE "  ! Must push arguments onto the stack in reverse order\n";
   for ($j = 0; $j < $num_args; $j++)
   {
      $arg = pop @arg_list;
      print OUT_FILE "  \@copy $arg sp;\n";
   }

#   print OUT_FILE "[ $name _vararg_count ret;\n";
#   print OUT_FILE "! $name (", join (" ", @arg_list),")\n";
   print OUT_FILE "  ! And now the \@glk call\n";
#   print OUT_FILE "  \@glk $selector _vararg_count ret;\n";
   print OUT_FILE "\@glk $selector $num_args ret;\n";
   print OUT_FILE "  return ret;\n";
   print OUT_FILE "];\n";
   print OUT_FILE "\n";

   $num_funcs++;
}
print "Processed $num_funcs functions.\n";

print OUT_FILE "#Endif;\n";
print OUT_FILE "#Endif;\n";

