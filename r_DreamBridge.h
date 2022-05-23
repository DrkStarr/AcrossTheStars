
! ---------------------------------------------------------------------------- !
!       The DREAM BRIDGE. 04/11/06
!
  Room    dreambridge
   with   short_name "Main Bridge",
          description [;
              if (self.bridge_seen) {
                  DreamEnds(2);
              } else {
                  StartDaemon(berth_alarm);
                  self.bridge_seen = true;
                  "As the Grand Commander of the Xulthe'en Armada you have grown accustomed to your
                  place on the Main Bridge, in the eye of the storm, not to this awful silence.
                  If it wasn't for the fact that lights are still blinking on the consoles and
                  the monitors are still displaying status information, you'd swear the ship was
                  dead in space...
                  ^^Suddenly, a terrific impact on the ship's port side sends you staggering.
                  You're still trying to get your bearings when you hear the ringing sound of
                  metal-clad boots from below. A moment later, your worst fears are realized
                  as a group of space pirates swarms up the ladder to the bridge. They clearly
                  want the ship, and they've never been known to leave a man alive.";
              }
          ],
          u_to
              "You're on the highest level of the ship.",
          d_to [;
              <<Exit self>>;
          ],
          cant_go
              "The bridge isn't that big.",
          before [;
              ClimbDown, Exit, GetDown:
                  "You can't get down the ladder, there's a group of space pirates coming up it.";
              HideRoom:
                  "This is no place to hide!";
              Listen:
                  "The sound of the pirates boarding the ship, freezes you in place.";
              RunAway:
                  return DreamEnds(1);
              Sing:
                  return DreamEnds(11);
              Wake:
                  deadflag = 1;
                  "As you wake up, one of your bunkmates wants to know if you want to get something
                  to eat. Hungry, you both head down to the galley to get your fill of grub. All of
                  a sudden, from the DMC, someone shouts ~Pirates!~ Crew members fight to get out the
                  hatch, as you struggle to your duty station; but just before you make it, you're
                  transported off the ship! Space Pirates, hungry for the goods you have onboard,
                  have beamed the entire crew into their cargo hold. You're pushed against one of
                  the bulkheads, as your fellow crew members fight to open a locked hatchway.
                  Suddenly, the cargo hatch opens as you're sucked into the vacuum of space.
                  ^^Some days it just doesn't pay to wake up.";
          ],
          daemon [;
              start = start + 1;
              if (start == 1) {
                  print "^";
                  DreamEnds(3);
              }
          ],
          bridge_seen false;

! 03/08/07

  Object  -> dreamobj "main bridge"
    with  name 'main' 'bridge' 'room',
          description [;
              <<Look dreambridge>>;
          ],
          before [;
              Attack:
                  return PDE();
              Hide:
                  "This is no place to hide!";
              Search:
                  "No time!";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed;

! 04/11/06

  Object  -> dreampirates "pirates"
    with  name 'space' 'pirate' 'pirates',
          description [;
              DreamEnds(4);
          ],
          before [;
              Attack:
                  return DreamEnds(5);
              Ask, AskChar, Tell, TellTo:
                  return DreamEnds(8);
              Follow:
                  "But you're not one of them.";
              Hug, Kiss:
                  return DreamEnds(10);
              Push, PushDir, Pull, Take, Remove, Turn:
                  return DreamEnds(9);
          ],
    has   concealed animate pluralname;

! 04/11/06

  Object  -> dreamconsole "ship"
    with  name 'blinking' 'console' 'consoles' 'ship' 'monitor' 'monitors' 'xultheen' 'xulthe^en' 'command' 'carrier',
          description [;
              DreamEnds(6);
          ],
          before [;
              Attack:
                  return PDE();
              Read:
                  print "The information on the monitor is blurry and hard to read.^^";
                  return DreamEnds(6);
              Take, Remove, Turn, PushDir, Push, Pull:
                  self.drmtke = true;
                  return PAG();
          ],
          drmtke false,
    has   scenery static;

! 10/20/06

  Object  -> dreamladder "ladder"
    with  name 'ladder',
          description [;
              print "Up the ladder comes a group of space pirates.^^";
              DreamEnds(6);
          ],
          before [;
              Attack:
                  return PDE();
              Enter:
                  "The pirates are in the way.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  dreamconsole.drmtke = true;
                  return PAG();
          ],
    has   scenery static;

! 01/01/07

  Object  -> dreamvp "main viewport"
    with  name 'main' 'view' 'port' 'screen' 'viewport',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  print "The blast shield to the viewport has been tightly sealed, giving
                  you no clue as to your location.^^";
                  return DreamEnds(6);
              Take, Remove, Turn, PushDir, Push, Pull:
                  dreamconsole.drmtke = true;
                  return PAG();
          ],
    has   scenery static;

! 05/10/06

  Object  -> dreamplaque "ship's plaque"
    with  name 'ships' 'ship^s' 'plaque',
          description [;
              PSP(1);
              print "^";
              DreamEnds(6);
          ],
          before [;
              Attack:
                  return PDE();
              Read:
                  PSP(1);
                  print "^";
                  return DreamEnds(6);
              Take, Remove, Turn, PushDir, Push, Pull:
                  dreamconsole.drmtke = true;
                  return PAG();
          ],
    has   scenery static;
