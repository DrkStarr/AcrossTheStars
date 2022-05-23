
! ---------------------------------------------------------------------------- !
!       The ARMORY BACKROOM. 10/23/06
!
  RoomShp armory_backroom
    with  short_name [;
              print "Armory ";
              style roman;
              print "(store room)";
              rtrue;
          ],
          description [;
              if (space_pirates in self) return PirateDeath(0);
              print "With Ensign Striker in charge, nary a speck of dust would dare move in here
              without written permission, in triplicate. The doors to the small-arms lockers should
              form a neat, gleaming row across the back wall, like soldiers on parade, but now they
              look like soldiers who've just been on their first shore leave in months; hanging off
              at crazy angles, bent and buckled, they're no longer fit to guard a water pistol. ";
              if (self.blasted) {
                  print "One of the lockers in the back has been blasted";
                  if (galley_closet has open) {
                      print ".";
                  } else {
                      print ", but still looks to be more-or-less closed.";
                  }
              } else {
                  print "Only one locker looks almost untouched in the midst of this chaos, though
                  deep scratches and blunt impacts bear mute testimony to your crewmates' last stand.";
              }
              " A broken security gate lies to starboard.";
          ],
          e_to [;
              <<Enter armory_gate>>;
          ],
          cant_go
              "You can only go out through the starboard security gate.",
          before [;
              Exit:
                  <<Enter armory_gate>>;
          ],
          pirates true,
          blasted false;

! 10/23/06

  RoomObj -> abackroomobj "back room of the armory"
    with  name 'armory' 'armoury' 'ship' 'back' 'room',
          description [;
              <<Look armory_backroom>>;
          ];

! 04/16/06

  Object  -> galley_closet
    with  name 'captain' 'captains' 'locker' 'lockers' 'cabinet' 'stainless' 'steel' 'red' 'writing' 'dent'
               'dents' 'scratch' 'scratches' 'lock' '1911ph' 'captain^s' 'small-arms' 'small' 'arms' 'slot',
          description [;
              print "The word ~Captain~ is still visible among the fresh ";
              if (armory_backroom.blasted) {
                  print "blast marks supplied by the space pirates. ";
                  if (self has open) "The door is hanging open at a crazy angle. ";
              } else {
                  print "dents and scratches supplied by frustrated crew members. ";
                  if (self has locked) print "Unlike the others, this locker's still locked. ";
              }
              if (LockerEmpty()) {
                  new_line;
                  rtrue;
              }
              if (self has open) return SearchSub(self);
              new_line;
          ],
          describe [;
              rtrue;
          ],
          short_name "locker",
          with_key ident_badge,
          before [;
              Attack:
                  return PDE();
              Close:
                  if (armory_backroom.blasted) "The lock has been blasted by a laser rifle and doesn't want to close.";
                  give self ~open;
                  "You close the Captain's locker.";
              Enter, Hide:
                  if (self has open) "You can't fit into the locker.";
                  "You'll have to open the locker first.";
              Lock:
                  if (armory_backroom.blasted) "You can't. The locker has been blasted open, now missing its lock.";
                  if (second ~= ident_badge) "Only the Captain's ident badge can lock the Captain's locker.";
              Open:
                  if (self has open) "That's already open.";
                  if (armory_backroom.blasted) {
                      give self open;
                      if (milpack in self) "You open the damaged locker, revealing a field pack. Oddly enough, the pirates didn't take it with them.";
                      "You open the damaged locker.";
                  }
                  if (self has locked) {
                      if (ident_badge in player) {
                          give self ~locked;
                          if (milpack in self) {
                              if (self.firstotime) {
                                  give self open;
                                  self.firstotime = false;
                                  if (second == ident_badge) "You unlock the Captain's locker and open it, revealing a field pack. Strangely enough, there are no small arms in the locker.";
                                  "(using the Captain's ident badge)
                                  ^You unlock the Captain's locker and open it, revealing a field pack. Strangely enough, there are no small arms in the locker.";
                              } else {
                                  if (second == ident_badge) {
                                      print "You unlock the Captain's locker.^";
                                  } else {
                                      print "(using the Captain's ident badge)
                                      ^You unlock the Captain's locker.^";
                                  }
                                  rfalse;
                              }
                          }
                          print "(using the Captain's ident badge)
                          ^You unlock the Captain's locker.^";
                          rfalse;
                      }
                      if (second == ce_badge) "It's locked, and can only be opened by the Captain's ident badge; the Chief Engineer's ident badge won't cut it.";
                      if (second == prybar) "As you try to pry open the locker, the pry bar slips away, scratching the steel.";
                      if (second == wrench) "You can't open the locker with the universal tool, only the Captain's ident badge can do that.";
                      if (ce_badge in player) "It's locked, and can only be opened by the Captain's ident badge; the Chief Engineer's ident badge won't work.";
                      "It's the Captain's personal locker, and can only be opened by the Captain's ident badge; you won't succeed where your crewmates failed.";
                  }
                  if (milpack in self) {
                      if (self.firstotime) {
                          give self open;
                          self.firstotime = false;
                          "You open the Captain's locker, revealing a field pack. Strangely enough, there are no small arms in the locker.";
                      } else {
                          rfalse;
                      }
                  }
              Read:
                  "~Captain's Locker~ is written across the two doors, in large red letters.";
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the Captain's locker.";
                  POT();
                  style fixed;
                  print "~Captain's Locker~";
                  style roman;
                  "";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Unlock:
                  if (armory_backroom.blasted) "You can't. The locker has been blasted open, now missing its lock.";
                  if (second ~= ident_badge) "Only the Captain's ident badge can unlock the Captain's locker.";
          ],
          firstotime true,
    has   lockable locked openable container static;
