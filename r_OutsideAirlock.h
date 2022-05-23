
! ---------------------------------------------------------------------------- !
!       The OUTSIDE THE AIRLOCK. 02/18/07
!
  Room    outside_airlock "Outside the Airlock"
    with  description [;
              if (self.oairdis) {
                  self.oairdis = false;
                  print "As your eyes start to adjust,";
              } else {
                  print "As you look around,";
              }
              ma_spacesuit.noteva = false;
              print " the darkness resolves into what you've always thought of as a great
              velvet blanket, encrusted with diamonds. ";
              if (self.oairfirst) {
                  self.oairfirst = false;
                  print "(Not that you'd ever let your crewmates hear you talk like that.) ";
              }
              print "Despite your heated suit, you feel the cold of space start to creep
              in as you look the ship over in greater detail. A rail system crisscrosses
              the hull around you, designed to aid routine maintenance, while the door
              to the airlock ";
              if (os_airlock.hasopen) {
                    "stands open.";
              } else {
                  "is tightly shut.";
              }
          ],
          w_to [;
              <<Exit self>>;
          ],
          in_to [;
              <<Exit self>>;
          ],
          u_to [;
              if (bu_planet in self) move bu_planet to ontopofship;
              print "Carefully you grab the rail, making your way up the ship.^";
              return ontopofship;
          ],
          cant_go
              "As you grab the rail, your footing slips and you're barely able to stop yourself drifting
              away into space. It may look easy when the experts do it, but you're not trained for this.",
          before [;
              Listen:
                  "Only dead silence in the cold of space.";
              Exit:
                  if (os_airlock.hasopen == false) {
                      os_airlock.hasopen = true;
                      print "(first opening the airlock)^";
                  }
                  give ma_airlock ~open;
                  d_obj.&name-->5 = 'deck';
                  ma_panel.pressure = true;
                  if (blastdoor in main_airlock) remove blastdoor;
                  print "As you enter the airlock you close the door behind you, re-pressurizing the compartment.
                  You feel the pressure slowly building until it equalizes with the ship, finally allowing the
                  blast door to open.^";
                  PlayerTo(main_airlock);
                  rtrue;
          ],
          popen false,
          oairdis false,
          oairfirst true;

! 02/18/07

  RoomObj -> os_airlockobj "outside of the airlock"
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'outside' or 'room') return 0;
              w2 = NextWord();
              w3 = NextWord();
              if (w1 == 'outside' && w2 == 'of' && w3 == 'airlock') return 3;
              return 3;
          ],
          description [;
              <<Look outside_airlock>>;
          ];

! 02/18/07

  Object  -> os_airlock "airlock door"
    with  name  'airlock' 'air' 'lock' 'door' 'hatch',
          description [;
              if (self.hasopen) "This open hatch gives you access to the ship's airlock.";
              "The ship's airlock is tightly closed.";
          ],
          before [;
              Attack:
                  return PDE();
              Close:
                  if (self.hasopen == false) "That's already closed.";
                  self.hasopen = false;
                  "Typing in a code on the control pad, you close the airlock door.";
              Enter:
                  <<Exit outside_airlock>>;
              Open:
                  if (self.hasopen) "That's already open.";
                  self.hasopen = true;
                  "Typing in a code on the control pad, you open the airlock door.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          hasopen true,
    has   static scenery;

! 02/19/07

  Object  -> os_controlpad "control pad"
    with  name 'control' 'pad' 'button' 'buttons' 'numeric' 'keypad',
          description [;
              print "The control pad has a three by three numeric keypad used to ";
              if (os_airlock.hasopen) {
                  print "close";
              } else {
                  print "open";
              }
              " the airlock door.";
          ],
          before [;
              Attack:
                  return PDE();
              Push, PushDir, UseItem:
                  if (os_airlock.hasopen) <<Close os_airlock>>;
                  <<Open os_airlock>>;
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, UseItem:
                  "The control pad has no power switch; it's hard-wired into the ship's electrical system.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
          ],
          hasopen true,
    has   static scenery;

! 02/20/07

  OutRch  -> g_planet "planet"
    with  name 'blue' 'green' 'beautiful' 'planet' 'pretty',
          description
              "Clouds cover the surface of a beautiful green, blue planet.";
