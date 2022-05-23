! ==============================================================================
! SmartCantGo.h -- lists the exits from a room, more helpful than simply saying
! "You can't go that way".
!
! Version 6.1 (Apr04) by Roger Firth (roger@firthworks.com)
!
! Compatibility: for Inform 6.3 (Z-code and Glulx).
!
! Dependencies: none.
!
! License: The Creative Commons Attribution-ShareAlike License published at
! http://creativecommons.org/licenses/by-sa/1.0/ applies to this software.
! In summary: you must credit the original author(s); if you alter, transform,
! or build upon this software, you may distribute the SOURCE FORM of the
! resulting work only under a license identical to this one. Note that the
! ShareAlike clause does not affect the way in which you distribute the COMPILED
! FORM of works built upon this software.
! Copyright remains with the original author(s), from whom you must seek
! permission if you wish to vary any of the terms of this license.
! The author(s) would also welcome bug reports and enhancement suggestions.
!
! ------------------------------------------------------------------------------
! INSTALLATION
!
! Place this line anywhere after VerbLib.h:
!
!   Include "SmartCantGo";
!
! ------------------------------------------------------------------------------
! USAGE
!
! With library 6/11 and higher, you need do nothing more; the following room:
!
!   Object  Crystal_Cave "Crystal Cave"
!     with  description "A passage leads south...",
!           s_to Narrow_Passage,
!           ...;
!
! produces the message "You can go only south" if the player tries to move in
! any of the other directions.
!
! With library 6/10 and lower, you must include a reference to the SmartCantGo
! routine:
!
!   Object  Crystal_Cave "Crystal Cave"
!     with  description "A passage leads south...",
!           s_to Narrow_Passage,
!           cant_go SmartCantGo,    ! add this property
!           ...;
!
! Rather than explicitly add the 'cant_go' property to each room, it is better
! to add it to a Room class from which your actual rooms are derived:
!
!   Class   Room
!     with  cant_go SmartCantGo,    ! add this property
!     has   light;
!
! ------------------------------------------------------------------------------
! CUSTOMISATION
!
! You can change the default values of CANTGO_NOEXITS, CANTGO_PREFIX and
! CANTGO_SUFFIX. Before Including this extension, define the appropriate
! constant as a string, or as a routine which prints a string:
!
!   Constant CANTGO_NOEXITS "Looks like there's no way out.";
!
!   [ MyCANTGO_NOEXITS; "Looks like there's no way out."; ];
!   Constant CANTGO_NOEXITS MyCANTGO_NOEXITS;
!
! ------------------------------------------------------------------------------
! NOTES
!
! 1.    If the room is dark, the message is just "You can't go that way."
!       How could the player know where the exits are?
!
! 2.    SmartCantGo ignores direction properties which point to concealed
!       doors or which are strings. Therefore this code won't work quite as
!       intended in the following room:
!
!           Object  Library "Library"
!             with  description
!                       "A small wood-panelled library. An open window to the
!                        west affords a stunning view of the Tuscan coastline.",
!                   w_to
!                       "Ouch! You discover that the ~window~ is really
!                        an incredibly lifelike mural painted on the wall.",
!                   ...;
!
! 3.    SmartCantGo lists direction properties which are routines, on the
!       assumption that the routine will return something sensible. If your
!       routine returns a concealed door, you will have to do
!       something different.
!
! ------------------------------------------------------------------------------
! HISTORY
!
! Version 6.1: (Apr04) More internationalisation (thanks to DG).
! Version 6.0: (Feb04) Reworked for Inform 6.3. Self-initialises.
!              Internationalisation (thanks to SK, FR, HH, GR).
! Version 5.0: (Feb99) Minor corrections.
! Version 4.0: (Nov98) Reworked by Roger Firth for Inform 6.
! Version 3.0: (Nov95) Original by David Wagner. All rights given away.
!
! ==============================================================================

System_file;

#Ifndef LIBRARY_VERSION;
Message fatalerror "SMARTCANTGO requires library 6/11 or later";
#Endif;
#Iftrue (LIBRARY_VERSION < 611);
Message fatalerror "SMARTCANTGO requires library 6/11 or later";
#Endif;

#Ifdef SMARTCANTGO_H;
Message warning "SMARTCANTGO already Included";
#Ifnot;
Constant SMARTCANTGO_H 61;
#Ifdef DEBUG; Message "[Including SMARTCANTGO]"; #Endif;

Object  "(SmartCantGo)" LibraryExtensions
  with  ext_initialise [; ChangeDefault(cant_go, SmartCantGo); ];

! ------------------------------------------------------------------------------

#Ifdef  LIBRARY_DUTCH;
Default CANTGO_NOEXITS "Er zijn hier geen uitgangen.";
Default CANTGO_PREFIX  "U kunt alleen naar ";
#Endif;

#Ifdef  LIBRARY_FRENCH;
Default CANTGO_NOEXITS "Il n'ya a pas de sortie.";
Default CANTGO_PREFIX  "Vous pouvez aller seulement vers ";
#Endif;

#Ifdef  LIBRARY_GERMAN;
Default CANTGO_NOEXITS "Es gibt keinen Ausgang.";
Default CANTGO_PREFIX  "Du kannst nur nach ";
Default CANTGO_SUFFIX  " gehen.";
#Endif;

#Ifdef  LIBRARY_ITALIAN;
Default CANTGO_NOEXITS "Non ci sono uscite.";
Default CANTGO_PREFIX  "Puoi andare solo a ";
#Endif;

#Ifdef  LIBRARY_RUSSIAN;    ! Uses Windows Cyrillic CP 1251
Default CANTGO_NOEXITS "Здесь нет ни одного выхода.";
Default CANTGO_PREFIX  "Вы можете идти только на ";
#Endif;

#Ifdef  LIBRARY_SPANISH;
Default CANTGO_NOEXITS "No hay ninguna salida.";
Default CANTGO_PREFIX  "S@'olo puedes ir hacia el ";
#Endif;

#Ifdef  LIBRARY_SWEDISH;
Default CANTGO_NOEXITS "Det finns inga utg@oangar.";
Default CANTGO_PREFIX  "Du kan bara g@oa ";
#Endif;

Default CANTGO_NOEXITS "There are no exits.";
Default CANTGO_PREFIX  "You can go only ";
Default CANTGO_SUFFIX  ".";

! ------------------------------------------------------------------------------

[ SmartCantGo room dest dirObj dirCount;

    if (location == thedark) return L__M(##Go, 2);

    ! Find what room the player is in.

    room = location;
    while (parent(room)) room = parent(room);

    ! Count the number of exits -- if a direction property is a string or
    ! a concealed door, don't count it; if it's a routine, count it.

    dirCount = 0;
    objectloop (dirObj in compass) {
        dest = room.(dirObj.door_dir);
        if (dest ofclass Routine ||
           (dest ofclass Object && ~~(dest has door && dest has concealed)))
            dirCount++;
    }
    if (dirCount == 0) return PrintOrRunVar(CANTGO_NOEXITS);

    ! Print the exits.

    PrintOrRunVar(CANTGO_PREFIX, true);
    objectloop (dirObj in compass) {
        dest = room.(dirObj.door_dir);
        if (dest ofclass Routine ||
           (dest ofclass Object && ~~(dest has door && dest has concealed))) {
            LanguageDirection(dirObj.door_dir);
            switch (--dirCount) {
              0:       return PrintOrRunVar(CANTGO_SUFFIX);
              1:       print (string) OR__TX;
              default: print (string) COMMA__TX;
            }
        }
    }
];

#Endif; ! SMARTCANTGO_H

! ==============================================================================

