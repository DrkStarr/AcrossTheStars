
! ---------------------------------------------------------------------------- !
!       The GALLEY. 04/16/06
!
  RoomShp galley "Galley"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              self.entergalley = false;
              if (self.gpland) {
                  self.pgseen = true;
                  print "The large blast-hole in the port bulkhead is now exposed to the heat of a
                  burning desert, the metal plate having fallen away. Only empty tables are left:
                  nothing was too small or unimportant for the pirates. Looking through the hole,
                  you see an utterly deserted planet. An open hatchway lies to starboard, while the
                  engineering access cover is ";
                  if (gl_eacover.panopn) "opened, giving you access to the e-tubes.";
                  "closed.";
              }
              if (self.gpboard) {
                  print "The already unsettling sight of the deserted galley has been augmented by a
                  large blast-hole in the port bulkhead. The pirates must have entered through here:
                  looking through the hole, you can see a self-sealing metal plate, and the edges of
                  a improvised suction seal which is currently all that's preventing the air from
                  bleeding into space. The robo-wash just missed getting sucked out the hole, while
                  a video game machine sits in the aft corner of the room. An open hatchway lies to
                  starboard, while the engineering access cover is ";
                  if (gl_eacover.panopn) "opened, giving you access to the e-tubes.";
                  "closed.";
              }
              galley_tables.short_name = "one of the tables";
              give galley_tables pluralname;
              if (self.gfirstime) {
                  self.gfirstime = false;
                  print "On a normal day, this place would always be bustling with your crewmates. Even between meals,
                  a few people would have stopped by for a cup of coffee. (With the long shifts, a chat in the Galley
                  helps to pass the time.) Right now, though, it's deserted. Even more alarming, the tables are littered
                  with half-eaten plates of food. Some of the food is still warm, so whatever disaster befell this place,
                  it happened very recently.";
              } else {
                  print "There's no-one here, though the tables are still littered with half-eaten plates of food.";
              }
              print " A video game machine sits in the aft corner, while an open hatchway lies to starboard.
              Also, the engineering access cover is ";
              if (gl_eacover.panopn) print "opened, giving you access to the e-tubes.^";
              else print "closed.^";
              if (robowash.working) Robotalk();
          ],
          e_to main_junction,
          w_to [;
              if (self.gpland) "You don't want to do that. You could damage your uniform on all that jagged metal.";
              if (self.gpboard) "The sealed metal plate blocks the hole.";
          ],
          in_to [;
              <<Enter gl_eacover>>;
          ],
          cant_go
              "You can go through the starboard hatchway or into the e-tube.",
          before [;
              Exit:
                  PlayerTo(main_junction);
                  rtrue;
              HideRoom:
                  "You would be in plane sight if you tried hiding under the tables.";
              Listen:
                  if (self.cleanon) "You can hear the soft purr coming from the robo-wash in the corner.";
                  if (self.workon) "The robo-wash is making quite a lot of noise as he cleans the dishes off the tables.";
              SitDown:
                  if (pattack > 2) rfalse;
                  <<Sit galley_seats>>;
          ],
          workon false,
          gpland false,
          pgseen false,
          gpboard false,
          cleanon false,
          gfirstime true,
          entergalley true;

! 04/16/06

  RoomObj -> galleyobj "galley"
    with  name 'galley' 'ship' 'room',
          description [;
              <<Look galley>>;
          ],
          before [;
              LookUnder:
                  "You can't do that.";
              Search:
                  L__M(##Search, 4);
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ];

! 05/24/06

  Object  -> galley_food "food"
    with  name 'food' 'germ' 'germs' 'half-eaten' 'half' 'eaten',
          description [;
              print "The food is half eaten. What ever happened here, happened fast.^";
              if (robowash.working) Robotalk();
          ],
          describe [;
              rtrue;
          ],
          before [;
              Eat:
                  print "Have you forgotten so quickly how this stuff tastes? It's better to go hungry.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder, Push, PushDir, Pull, Play:
                  print "Please don't play with the food.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove:
                  print "Why would you want to do that? ";
                  if (second == foodrep) {
                      print "Have you forgotten so quickly how this stuff tastes? It's better to go hungry.^";
                  } else {
                      print "Think of the germs!^";
                  }
                  if (robowash.working) Robotalk();
                  rtrue;
              Touch:
                  print "The plate is warm to the touch.^";
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   static;

! 05/13/08

  EACovr  -> gl_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph' 'panel',
          before [;
              Enter:
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(gl_etube);
                  rtrue;
          ],
          panopn false;

! 05/24/06

  Object  galley_tables
    with  parse_name [w1;
                  w1 = NextWord();
                  if (w1 ~= 'table' or 'tables') return 0;
                  if (w1 == 'table') {
                      self.short_name = "table";
                      give self ~pluralname;
                      return 1;
                  }
                  self.short_name = "one of the tables";
                  give self pluralname;
                  return 1;
          ],
          short_name "one of the tables",
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Enter, Sit:
                  if (pattack > 2) "You don't have any time for that right now.";
                  if (cq_head.hreport) {
                      print "Sitting won't help you get that datacard up to the bridge.^";
                      if (robowash.working) Robotalk();
                      rtrue;
                  }
                  print "You need to report for duty.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Examine, Search:
                  if (pattack > 2) "The tables are empty and even lack seats.";
                  print "The tables are covered with plates of food that are half eaten, nothing put away,
                  everything left out. It almost looks like someone just beamed the entire crew off the ship.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder:
                  print "You find nothing underneath ";
                  if (self has pluralname) {
                      print "the tables";
                  } else {
                     print "the table";
                  }
                  print ", least of which a spare cubit.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Hide:
                  print "You would be in plane sight if you tried hiding under the tables.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   supporter scenery static pluralname proper;

! 05/24/06

  Object  galley_plate "plates"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'plates' or 'plate' or 'dish' or 'dishes' or 'cleaned' or 'clean' or 'dirty') return 0;
              if (w1 == 'plates' or 'plate' or 'dish' or 'dishes') {
                  if (pattack > 2) {
                      if (robowash has open) {
                          self.cplate = true;
                          return 1;
                      }
                  } else {
                      self.cplate = false;
                      return 1;
                  }
              }
              w2 = NextWord();
              if (w1 == 'cleaned' or 'clean' && w2 == 'plates' or 'plate' or 'dish' or 'dishes') {
                  if (robowash has open) {
                      self.cplate = true;
                      return 2;
                  }
              }
              if (w1 == 'dirty' && w2 == 'plates' or 'plate' or 'dish' or 'dishes') {
                  self.cplate = false;
                  return 2;
              }
              return 0;
          ],
          description [;
              if (self.cplate) "The plates are nicely stacked inside the robo-wash.";
              print "The plates of food look like they're half eaten.^";
              if (robowash.working) Robotalk();
          ],
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove:
                  if (self.cplate && pattack > 2) "Why do you want to do that? These plates are worthless.";
                  if (self.cplate) "Thinking about eating? Have you forgotten so quickly how this stuff tastes?";
                  if (robowash.working) {
                      print "Much as you'd like to stay and help the little fellow, you've got more important things to do.^";
                  } else {
                      print "What, you're taking the place of the robo-wash?^";
                  }
                  if (robowash.working) Robotalk();
                  rtrue;
              Touch:
                  print "The plate is warm to the touch.^";
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
          cplate false,
    has   static concealed pluralname;

! 04/26/06

  Object  drinkrep "drink dispenser"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'drink' or 'drinks' or 'dispenser' or 'coffee' or 'tea' or 'water' or 'button' or 'buttons' or 'holder' or 'cup-holder' or 'jaws' or 'jaw') return 0;
              w2 = NextWord();
              if (w1 == 'drink' or 'drinks' && w2 == 'dispenser') {
                  self.mdcoffee = false;
                  self.mdtea = false;
                  self.mdwater = false;
                  return 2;
              }
              if (w1 == 'coffee' && w2 == 'button') {
                  self.mdcoffee = true;
                  self.mdtea = false;
                  self.mdwater = false;
                  return 2;
              }
              if (w1 == 'tea' && w2 == 'button') {
                  self.mdcoffee = false;
                  self.mdtea = true;
                  self.mdwater = false;
                  return 2;
              }
              if (w1 == 'water' && w2 == 'button') {
                  self.mdcoffee = false;
                  self.mdtea = false;
                  self.mdwater = true;
                  return 2;
              }
              if (w1 == 'coffee') {
                  self.mdcoffee = true;
                  self.mdtea = false;
                  self.mdwater = false;
                  return 1;
              }
              if (w1 == 'tea') {
                  self.mdcoffee = false;
                  self.mdtea = true;
                  self.mdwater = false;
                  return 1;
              }
              if (w1 == 'water') {
                  self.mdcoffee = false;
                  self.mdtea = false;
                  self.mdwater = true;
                  return 1;
              }
              self.mdcoffee = false;
              self.mdtea = false;
              self.mdwater = false;
              return 1;
          ],
          invent [;
              if (coffee_cup in self) rfalse;
              print "a drink dispenser";
              rtrue;
          ],
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Close:
                  "That's already closed.";
              Examine, Search:
                  print "It's your standard government-issue drinks dispenser, issuing standard
                  government-issue drink. There's a cup-holder at the bottom, and three
                  buttons along the top, labelled ~Coffee~, ~Tea~ and ~Water~.
                  ^^Unlike the meal synthesizer, it's working. Whatever button you press,
                  though, the results are likely to be pretty disgusting: the coffee
                  tastes like tar, the tea tastes like soap, and as for the water... Let's
                  just say that all the water on the ship is ~recycled~, and leave it at that.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder:
                  move galley_crumbs to galley;
                  print "All you can see are a few crumbs.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Open:
                  "Only the Chief refills the drink dispenser.";
              Push:
                  if (coffee_cup in player or self) <<Fill coffee_cup>>;
                  return FailFill();
              PushC:
                  if (coffee_cup in player or self) {
                      self.mdcoffee = true;
                      self.mdtea = false;
                      self.mdwater = false;
                      <<Fill coffee_cup>>;
                  }
                  return FailFill();
              PushT:
                  if (coffee_cup in player or self) {
                      self.mdcoffee = false;
                      self.mdtea = true;
                      self.mdwater = false;
                      <<Fill coffee_cup>>;
                  }
                  return FailFill();
              PushW:
                  if (coffee_cup in player or self) {
                      self.mdcoffee = false;
                      self.mdtea = false;
                      self.mdwater = true;
                      <<Fill coffee_cup>>;
                  }
                  return FailFill();
              SwFlip, SwitchOn, Use, UseItem:
                  if (coffee_cup in player or self) <<Fill coffee_cup noun>>;
                  return FailFill();
              FlipOff, SwitchOff:
                  print "The drink dispenser isn't on.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Turn, Remove, PushDir, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
          mdcoffee false,
          mdtea false,
          mdwater false,
    has   static open container;

! 04/26/06

  Object  foodrep "meal synthesizer"
    with  name 'meal' 'synthesizer' 'soup' 'main' 'dish' 'salad' 'dessert' 'switch' 'switches',
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Close:
                  "That's already closed.";
              Examine, Search:
                  print "It's your standard government-issue meal synthesizer, issuing standard
                  government-issue food. There's a slot at the bottom, and four switches
                  along the top, labelled ~Soup~, ~Main Dish~, ~Salad~ and ~Dessert~. The
                  fresh dent in the side probably means that the machine's broken down
                  again. Given the cuisine, you're not sure whether to be annoyed or relieved.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder:
                  move galley_crumbs to galley;
                  print "All you can see are a few crumbs.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Open:
                  "Only the Chief refills the meal synthesizer.";
              Push, SwFlip, SwitchOn, Take, Use, UseItem:
                  print "You flip one of the switches, but nothing happens.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              FlipOff, SwitchOff:
                  print "The meal synthesizer isn't on.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Turn, Remove, PushDir, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   static;

! 05/24/06

  Object  galley_seats "seats"
    with  name 'seat' 'seats' 'chair' 'chairs',
          description [;
              print "The seats go unoccupied, on a ship that should be filled with people.^";
              if (robowash.working) Robotalk();
          ],
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Enter, Sit:
                  if (cq_head.hreport) {
                      print "Sitting won't help you get that datacard up to the bridge.^";
                      if (robowash.working) Robotalk();
                      rtrue;
                  }
                  print "You need to report for duty.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder:
                  return LUGalley();
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (cq_head.hreport) {
                      print "Stop playing with the seats, you need to get that datacard up to the bridge.^";
                      if (robowash.working) Robotalk();
                      rtrue;
                  }
                  print "Stop playing with the seats, you need to report for duty.^";
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   scenery static pluralname;

! 02/21/07

  Object  videogame "video game machine"
    with  name 'video' 'game' 'machine' 'console',
          description [;
              if (ma_airlock.alflowoff)
                  "The video game in the far corner fails to operate, while the words ~Ghouls & Goblins~ are
                   written across the top in dripping blood.";
              print "The video game sits in the far corner of the room, with the words ~Ghouls & Goblins~
              written across the top in dripping blood.^";
              if (robowash.working) Robotalk();
          ],
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Close:
                  "That's already closed.";
              LookBehind:
                  return PRB();
              LookUnder:
                  return LUGalley();
              Open:
                  "The Chief's the only one who services the machine, and he has a special key to open it.";
              Play, SwFlip, SwitchOn, UseItem:
                  if (ma_airlock.alflowoff) "There's no power going to the video game machine.";
                  print "It's the old-fashioned type where you have to put in money. Too bad you don't have any.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the video game machine.";
                  POT();
                  style fixed;
                  print "~Ghouls & Goblins~";
                  style roman;
                  if (robowash.working) {
                      print "^";
                      return Robotalk();
                  }
                  "";
              FlipOff, SwitchOff:
                  if (ma_airlock.alflowoff) "That's already off.";
                  print "The video game doesn't have a power switch, it's hard-wired directly into the ship.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   static scenery open container;

! 08/08/07

  Object  galley_counter "counter"
    with  name 'counter',
          before [;
              Attack:
                  PDE();
                  if (robowash.working) Robotalk();
                  rtrue;
              Examine:
                  print "The counter is made of a strong unpronounceable alloy and is minimalist in design.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              LookUnder:
                  return LUGalley();
              Sit:
                  print "People eat here, have some respect.^";
                  if (robowash.working) Robotalk();
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  PAG();
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   scenery static supporter;
