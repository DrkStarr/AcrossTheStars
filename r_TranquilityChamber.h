
! ---------------------------------------------------------------------------- !
!       The TRANQUILITY CHAMBER. 08/16/06
!
  Room    tranquility_chamber "Tranquility Chamber"
    with  description [;
              print "As you stand in this large circular chamber, hollowed carefully out of the rock, a feeling of peace washes over you. ";
              if (orb in tc_shrine) {
                  print "Above you, the room is entirely enclosed by a blue force field, emanating from the glowing orb on top of the shrine";
              } else {
                  print "It is open to the sky, bathed in fresh air and sunlight but somehow free of the
                  infernal heat of the desert sun. In the middle of the room is an elaborate shrine";
                  if (solace_cube in tc_shrine) {
                      print ", upon which sits a small black cube";
                  }
                  if (tc_shrine.fieldon) {
                      print ". Surrounding the shrine, a coruscating blue-green force field swirls, protecting
                      the cube from harm and putting on a beautiful lightshow";
                  } else {
                      print ". The force field has been lowered, giving you access to it";
                  }
              }
              ".
              ^^At cardinal points around the room you see the entrances to four cells, with a simple pedestal
              outside of each. A circular staircase must once have spiralled round the wall of the chamber, but
              it has long since collapsed, eroded by time, leaving only a small piece of broken stone railing at
              the top. A small passage descends northeast into the darkness.";
          ],
          u_to [;
              if (grappling_hook in tc_bsrail) {
                  if (orb in tc_shrine) "The cobalt-blue force field blocks your attempt.";
                  if (adar has general) print "~Have fun up there,~ says Captain Adar as you climb up the rope.^";
                  return view_plat;
              }
          ],
          d_to [;
              return ExitTran();
          ],
          n_to [;
              if (adar has general) {PAF(); MoveAdar(17);}
              return north_cell;
          ],
          ne_to [;
              return ExitTran();
          ],
          s_to [;
              if (adar has general) {PAF(); MoveAdar(18);}
              return south_cell;
          ],
          e_to [;
              if (adar has general) {PAF(); MoveAdar(19);}
              return east_cell;
          ],
          w_to [;
              if (adar has general) {PAF(); MoveAdar(20);}
              return west_cell;
          ],
          cant_go
              "You can only go north, northeast, south, east, and west.",
          before [;
              Exit:
                  if (adar has general) {PAF(); MoveAdar(15);}
                  PlayerTo(secret_tunnel3);
                  rtrue;
              Smell:
                  "There is nothing but fresh air on the breeze.";
          ];

! 08/16/06

  RoomObj -> tc_obj "tranquility chamber"
    with  name 'tranquility' 'hallowed' 'chamber' 'hollowed' 'tunnel' 'room',
          description [;
              <<Look tranquility_chamber>>;
          ];

! 08/16/06

  Object  -> tc_shrine
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'spectacualar' or 'shrine' or 'altar' or 'rune' or 'star') return 0;
              w2 = NextWord();
              if (w1 == 'spectacualar' && w2 == 'shrine' or 'altar') {
                  self.stlrune = false;
                  self.short_name = "shrine";
                  return 2;
              }
              if (w1 == 'star' or 'rune' && w2 == 'star' or 'rune') {
                  self.stlrune = true;
                  self.short_name = "star rune";
                  return 2;
              }
              if (w1 == 'shrine' or 'altar') {
                  self.stlrune = false;
                  self.short_name = "shrine";
                  return 1;
              }
              if (w1 == 'star' or 'rune') {
                  self.stlrune = true;
                  self.short_name = "star rune";
                  return 1;
              }
          ],
          short_name "shrine",
          describe [;
              rtrue;
          ],
          before [;
              Climb:
                   "This isn't a gymnasium.";
              Examine, Search:
                  if (self.stlrune) <<Read self>>;
                  "Sitting in the exact center of the room, the shrine is austerely simple: little more than a
                  large stone block into which an exquisitely-carved star has been set, it nonetheless speaks
                  eloquently of the sect's beliefs.";
              Read:
                  if (self.stlrune) {
                      print "The star rune is deeply engraved and looks like it has been here for a while.";
                      if (omni_trans in player or milpack) " Perhaps your OmniTrans can translate it.";
                  }
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (lc_srune.haveread) {
                      POT();
                      style fixed;
                      print "The image of the star represented the number one for the people that once
                      lived here. Depicted as 0001 using their favored binary number system, it meant
                      ~Universal God~ and embodies the concept of energy and light.";
                      style roman;
                      "";
                  }
                  return PNE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          stlrune false,
          fieldon true,
    has   supporter static;

! 09/25/06

  TCPed   -> tc_npedestal "northern pedestal"
    with  name 'north' 'northern' 'obelisk' 'pedestal' 'column' 'pillar';

! 08/16/06

  TCPed   -> tc_spedestal "southern pedestal"
    with  name 'south' 'southern' 'obelisk' 'pedestal' 'column' 'pillar';

! 08/16/06

  TCPed   -> tc_epedestal "eastern pedestal"
    with  name 'east' 'eastern' 'obelisk' 'pedestal' 'column' 'pillar';

! 08/16/06

  TCPed   -> tc_wpedestal "western pedestal"
    with  name 'west' 'western' 'obelisk' 'pedestal' 'column' 'pillar';

! 02/05/07

  Dust    -> tc_dust "dust"
    with  description
              "Looks like there's a little on each pedestal that has collected over time.";

! 02/22/07

  Object  -> tc_staircase "staircase"
    with  name 'staircase' 'stairway' 'stair' 'stairs' 'collapsed' 'circular' 'small' 'stones',
          description
              "What is left of the stairs has eroded from the wind that has blown through the
              chamber over the years. Now, small stones litter the floor and the only true signs
              that this architecture once stood is the stone railing withering away at the top.",
          before [;
              PushDir, Push, Pull:
                  "Pushing the stones around doesn't accomplish much.";
              Take, Remove:
                  "It's no use. There's no way you'll be able to clear the small stones one at a time.";
          ],
    has   concealed static;

! 02/22/07

  ORchSe  -> tc_bsrail "broken stone railing"
    with  name 'broken' 'stone' 'rail' 'railing',
          description [;
              print "A small piece of broken stone railing is left at the top of the opening ";
              if (grappling_hook in self) "with the makeshift grappling hook attached to it, hanging down into this chamber.";
              print "after the destruction, which shattered the entire staircase";
              if (view_plat.seenplat) ".";
              print ". You might be able to get up there, ";
              if (grappling_hook in player || (grappling_hook in milpack && ((milpack in player or uniform) || (parent(milpack) == parent(player))))) "using the makeshift grappling hook.";
              "if you only had a grav-belt.";
          ],
          describe [;
              if (grappling_hook in self) "^Attached to the broken stone railing, the makeshift grappling hook leads up to a platform.";
              rtrue;
          ],
          before [;
              Grapple:
                  if (grappling_hook in player || (grappling_hook in milpack && ((milpack in player or uniform) || (parent(milpack) == parent(player))))) return PGrpHk(2);
          ],
    has   supporter;

! 03/07/07

  Object  -> tc_bgffield "blue green force field"
    with  name 'blue' 'green' 'blue-green' 'force' 'field',
          description [;
              if (solace_cube in tc_shrine) "A blue green force field swirls around the shrine, protecting the small black cube that rests atop it.";
              "A blue green force field swirls around the shrine protecting it.";
          ],
          before [;
              Attack, Kick, Take, Remove, Turn, Touch, Transfer, PushDir, Push, Pull:
                  "The force field sparks as you try to touch it, stinging you with a sharp pain.";
          ],
    has   concealed static;

! 08/01/07

  Object  -> tc_sunlight "sunlight"
    with  name 'sun' 'light' 'sunlight',
          before [;
              Examine, Search:
                  if (orb in tc_shrine) "You can't see the sun with the force field in place.";
                  "The sun pours into the room, as if the tribe worshiped it.";
          ],
    has   concealed static open container;

! 08/14/07

  Object  -> tc_cell "cells"
    with  parse_name [ w1;
              w1 == NextWord();
              if (w1 ~= 'cell' or 'cells' or 'rooms') return 0;
              if (w1 == 'cell') return 3;
              return 1;
          ],
          before [;
              Enter:
                  "Try going NORTH, SOUTH, EAST, or WEST.";
              Examine:
                  "There are four cells, each at a cardinal point, used as small studies for the priests that once lived here.";
              Search:
                  "You need to enter one of the rooms to do that.";
          ],
    has   concealed static pluralname;

! 03/07/07

  Object -> tc_robe
    with  name 'tattered' 'robe' 'robes' 'outside' 'the' '8378ph' 'cell',
          description
              "Worn with time, the tattered robe looks like it's going to fall apart.",
          short_name "tattered robe",
          before [;
              Take, Remove:
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  move rope to player;
                  remove self;
                  "As you pick up the robe it crumbles to dust, leaving you with a three meter length of rope that once made up the belt.";
              Wear, Use, UseItem:
                  return PYC();
          ];
