
! -------------------------------------------------------------------------------------------- !
!       The SECRET TUNNEL (1). 04/26/06
!       Binary Puzzle: Lizard = 0101, Man = 1001, Woman = 1010, Sandworm = 0110
!
  Room    secret_tunnel1 "Tunnel"
    with  description [;
              print "This tunnel is narrow and low, starting at a stone door to the west and turning
              towards the southeast here. A small alcove has been carved out of the southern wall,
              just large enough to contain four obelisk-like structures, similar in design to the
              pedestal that opened the door. Above the obelisks, you can see a carving of a ";
              switch (ancientrune) {
                  1: print "lizard";
                  2: print "man";
                     rune_ancient.&name-->0 = 'man';
                  3: print "woman";
                     rune_ancient.&name-->0 = 'woman';
                  4: print "large worm";
                     rune_ancient.&name-->0 = 'large';
                     rune_ancient.&name-->3 = 'worm';
              }
              if (ancientrune == 1) print ".";
              else print ", similar to the one in the ralckor's lair.";
              if (orb in secret_chamber or secret_tunnel2 or sa_bobelisk) {
                  move st1_glow to self;
                  " A warm red glow is spilling down the tunnel from the southeast.";
              }
              remove st1_glow;
              new_line;
          ],
          se_to [;
              if (adar has general) {PAF(); MoveAdar(13);}
              return secret_tunnel2;
          ],
          w_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go west or southeast.",
          before [;
              Exit:
                  if (adar has general) {
                      print "As you exit the secret tunnel, ";
                      PAF(); MoveAdar(2);
                  }
                  PlayerTo(s_tunnel);
                  rtrue;
              Smell:
                  "The smell of the foul cavern drifts through this tunnel.";
          ];

! 05/03/06

  RoomObj -> st1_obj "tunnel"
    with  name 'wide' 'space' 'tunnel' 'room' 'alcove',
          description [;
              <<Look secret_tunnel1>>;
          ];

! 07/31/06

  Object  -> st1_door "stone door"
    with  name 'thick' 'stone' 'door',
          description
              "The thick stone door stands open to the junction, and the small idol that opened        it.",
          describe [;
              rtrue;
          ],
          before [;
              Enter:
                  <<Exit secret_tunnel1>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static;

! 07/31/06

  OutRch  -> st1_statue "idol"
    with  name 'statue' 'small' 'idol',
          description
              "It's hard to see the idol from here.";

! 07/31/06

  Object  -> st1_junction "junction"
    with  name 'junction',
          description
              "The junction stands on the other side of the door, brightly lit compared to this dark tunnel.",
          before [;
              Enter:
                  <<Exit secret_tunnel1>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 08/15/06

  Object  -> rune_ancient "ancient rune"
    with  name 'lizard' 'ancient' 'rune' '6230ph' 'picture' 'of',
          description [;
              print "The chisel marks have been softened by time, so the carving must be ancient. ";
              if (ancientrune == 1) "It obviously was executed by an expert hand, stylized in an image of a lizard.";
              print "It is quite a bit more detailed than the one in the ralckor's cavern, obviously
              executed by an expert hand. It is a stylized image of a ";
              switch (ancientrune) {
                  2: "man.";
                  3: "woman.";
                  4: "large worm.";
              }
          ],
          before [;
              Read:
                  "You can't read that. Why don't you try scanning it with you OmniTrans?";
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (ancientrune == 1 && self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a lizard represented the number five for the people that once
                      lived here. Depicted as 0101 using their favored binary number system, it meant
                      ~God against Light~ and is one of four holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  if (ancientrune == 2 && lc_mrune.haveread) {
                      POT();
                      style fixed;
                      print "The image of a man represented the number nine for the people that once
                      lived here. Depicted as 1001 using their favored binary number system, it meant
                      ~World God~ and is one of four holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  if (ancientrune == 3 && lc_wrune.haveread) {
                      POT();
                      style fixed;
                      print "The image of a woman represented the number ten for the people that once
                      lived here. Depicted as 1010 using their favored binary number system, it meant
                      ~World Nurturer~ and is one of four holy numbers they considered balanced.";
                      style roman;
                      "";
                  }
                  if (ancientrune == 4 && lc_lwrune.haveread) {
                      POT();
                      style fixed;
                      print "The image of a large worm represented the number six for the people that once
                      lived here. Depicted as 0110 using their favored binary number system, it meant
                      ~God of the World~ and is one of four holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  return PNE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          haveread false,
    has   scenery static;

! 08/15/06

  Object  -> st1_obelisk1
    with  name 'first' 'obelisk' 'pillar' 'column',
          short_name "first obelisk",
          article "the",
          description [;
              if (self.depressed) return POR();
              return ObeDesc();
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              PushDir, Push, UseItem:
                  if (self.depressed) return POA();
                  if (st1_obelisk2.depressed && st1_obelisk3.depressed && st1_obelisk4.depressed) return ResetObelisks();
                  st1_obelisk1.depressed = true;
                  st1_obelisk1.short_name = "first obelisk (depressed)";
                  PPO();
                  if (ObeliskTest()) return PLR();
                  rtrue;
              Take, Remove, Turn:
                  return PNH();
              Touch:
                  "The obsidian rock is cold to the touch.";
          ],
          depressed false,
    has   static;

! 08/15/06

  Object  -> st1_obelisk2
    with  name 'second' 'obelisk' 'pillar' 'column',
          short_name "second obelisk",
          article "the",
          description [;
              if (self.depressed) return POR();
              return ObeDesc();
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              PushDir, Push, UseItem:
                  if (self.depressed) return POA();
                  if (st1_obelisk1.depressed && st1_obelisk3.depressed && st1_obelisk4.depressed) return ResetObelisks();
                  st1_obelisk2.depressed = true;
                  st1_obelisk2.short_name = "second obelisk (depressed)";
                  PPO();
                  if (ObeliskTest()) return PLR();
                  rtrue;
              Take, Remove, Turn:
                  return PNH();
              Touch:
                  <<Touch st1_obelisk1>>;
          ],
          depressed false,
    has   static;

! 08/15/06

  Object  -> st1_obelisk3
    with  name 'third' 'obelisk' 'pillar' 'column',
          short_name "third obelisk",
          article "the",
          description [;
              if (self.depressed) return POR();
              return ObeDesc();
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              PushDir, Push, UseItem:
                  if (self.depressed) return POA();
                  if (st1_obelisk1.depressed && st1_obelisk2.depressed && st1_obelisk4.depressed) return ResetObelisks();
                  st1_obelisk3.depressed = true;
                  st1_obelisk3.short_name = "third obelisk (depressed)";
                  PPO();
                  if (ObeliskTest()) return PLR();
                  rtrue;
              Take, Remove, Turn:
                  return PNH();
              Touch:
                  <<Touch st1_obelisk1>>;
          ],
          depressed false,
    has   static;

! 08/15/06

  Object  -> st1_obelisk4
    with  name 'fourth' 'last' 'obelisk' 'pillar' 'column',
          short_name "fourth obelisk",
          article "the",
          description [;
              if (self.depressed) return POR();
              return ObeDesc();
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              PushDir, Push, UseItem:
                  if (self.depressed) return POA();
                  if (st1_obelisk1.depressed && st1_obelisk2.depressed && st1_obelisk3.depressed) return ResetObelisks();
                  st1_obelisk4.depressed = true;
                  st1_obelisk4.short_name = "fourth obelisk (depressed)";
                  PPO();
                  if (ObeliskTest()) return PLR();
                  rtrue;
              Take, Remove, Turn:
                  return PNH();
              Touch:
                  <<Touch st1_obelisk1>>;
            ],
            depressed false,
    has   static;

! 05/06/08

  STGlow  st1_glow "red glow"
    with  name 'warm' 'red' 'glow',
          before [;
              Examine, Search:
                  "The alcove towards the southeast is emanating a soft red glow.";
          ];

! ---------------------------------------------------------------------------- !
!       The SECRET TUNNEL (2). 07/31/06
!
  Room    secret_tunnel2 "Tunnel"
    with  description [ itest;
              print "The tunnel is especially cramped here, as it bends from the northwest and ends at an alcove to the south. ";
              itest = 0;
              if (orb in secret_chamber or sa_bobelisk) {
                  GlowRed();
                  print "A soft, red glow is coming from the alcove, giving you a warm, comfortable feeling.^";
              } else {
                  if (orb in self or player || (orb in milpack && milpack has open && (milpack in player or self or uniform))) {
                      itest = 1;
                      GlowRed();
                      print "Lit with the red glow from the orb, it gives the whole place a comfortable feeling.^";
                  } else {
                      if (torch in secret_chamber or sa_bobelisk && torch.onfire) {
                          GlowOrange();
                          print "There's a faint, orange light coming from the south alcove, giving the
                          place a creepy feeling.^";
                      } else {
                          if (torch in self or player && torch.onfire) {
                              itest = 1;
                              GlowOrange();
                              print "Lit with the orange light from the torch, it gives the whole place a creepy feeling.^";
                          } else {
                              if (datapad has light) {
                                  itest = 1;
                                  print "The data pad slightly glows, but fails to penetrate the gloom, making this place feel empty and hollow.^";
                              }
                              itest = 1;
                              print "Dark now, the place feels cold and gives you an eerie feeling.^";
                          }
                      }
                  }
              }
              if (itest == 0) move st2_glow to self;
              else remove st2_glow;
              if (ObeliskTest()) {
                  if (self hasnt general) {
                      give self general;
                      score = score + 5;
                  }
                  if (self.tripped) {
                      self.tripped = false;
                      "^The floor holds strong as you walk upon it.";
                  }
              } else {
                  print "^All of a sudden, the floor below you opens up, sucking you into the darkness below.";
                  if (adar has general) {
                      MoveAdar(14);
                      adar.adaroff = true;
                      print " Captain Adar is caught off guard and falls into the trap with you.";
                  }
                  print "^";
                  self.tripped = true;
                  deadp_obj.skip = true;
                  jagged_rock.skip = true;
                  deadly_pit.pitfall = true;
                  PlayerTo(deadly_pit);
                  rtrue;
              }
          ],
          s_to [;
              <<Enter st2_chamber>>;
          ],
          nw_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go northwest or south.",
          before [;
              Exit:
                  if (adar has general) {PAF(); MoveAdar(5);}
                  PlayerTo(secret_tunnel1);
                  rtrue;
              Smell:
                  "The smell of the foul cavern drifts through this tunnel.";
          ],
          tripped false;

! 07/31/06

  RoomObj -> st2_obj "tunnel"
    with  name 'cramped' 'space' 'tunnel' 'room',
          description [;
              <<Look secret_tunnel2>>;
          ];

! 07/31/06

  Object  -> st2_chamber "secret alcove"
    with  name 'secret' 'alcove',
          description [;
              if (orb in secret_chamber or sa_bobelisk) "The alcove towards the south is emanating a red glow that permeates the tunnel you're in.";
              if (torch in secret_chamber or sa_bobelisk && torch.onfire) "The alcove towards the south is emanating a faint orange light.";
              "The alcove towards the south is dark.";
          ],
          before [;
              Enter:
                  if (adar has general) {
                      print "As you enter the secret alcove, ";
                      PAF(); MoveAdar(6);
                  }
                  PlayerTo(secret_chamber);
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 05/06/08

  STGlow  st2_glow
    with  name 'warm' 'soft' 'red' 'glow',
          short_name "red glow",
          before [;
              Examine, Search:
                  if (orb in secret_chamber or sa_bobelisk) "The alcove towards the south is emanating a red glow that permeates the tunnel you're in.";
                  if (torch in secret_chamber or sa_bobelisk && torch.onfire) "The alcove towards the south is emanating an orange glow that permeates the tunnel you're in.";
                  "The soft white glow from the datapad is the only thing providing light";
          ];

! ---------------------------------------------------------------------------- !
!       The SECRET TUNNEL (3). 08/16/06
!
  Room    secret_tunnel3 "Tunnel"
    with  description [;
                print "The floor of this upward-sloping passage is covered with loose shale, no doubt deposited when
                the wall collapsed. The air in here is fresh, even though the corridor has not been used for ages. ";
                if (orb in tc_shrine) {
                    print "A blue cobalt covers the walls coming from the chamber above you to the southwest.";
                } else {
                  if (tc_shrine.fieldon) {
                      print "Sunlight floods through from a chamber above you to the southwest, mixed with a
                      different light in sparkling hues of blue and green. Dancing together upon the walls,
                      they make for a colorful show.";
                  } else {
                      print "Sunlight dances upon the walls coming from the chamber above you to the southwest.";
                  }
              }
                " You can also climb back out of the tunnel to the east.";
          ],
          u_to [;
              return EnterTran();
          ],
          d_to [;
              <<Exit self>>;
          ],
          e_to [;
              <<Exit self>>;
          ],
          sw_to [;
              return EnterTran();
          ],
          cant_go
              "You can only go east or southwest.",
          before [;
              Exit:
                  if (adar has general) {PAF(); MoveAdar(3);}
                  PlayerTo(w_tunnel);
                  rtrue;
              Smell:
                  "Fresh air seems to be coming down from above you, towards the southwest.";
            ];

! 08/16/06

  RoomObj -> st3_obj "tunnel"
    with  name 'downward' 'sloping' 'cavern' 'secret' 'tunnel' 'room',
          description [;
              <<Look secret_tunnel3>>;
          ];

! 08/16/06

  StaticShale -> st3_shale "shale"
    with  name 'loose' 'shale' 'rubble';

! 08/01/07

  Object  -> st3_sunlight "sunlight"
    with  name 'sun' 'light' 'sunlight' 'blue' 'green' 'cobalt',
          before [;
              Examine, Search:
                  if (orb in tc_shrine) "A blue cobalt covers the walls coming from the chamber above you to the southwest.";
                  if (tc_shrine.fieldon) "Sunlight dances upon the walls along with hues of blue and green, making for a colorful show, coming from the chamber above you to the southwest.";
                  "Sunlight dances upon the walls coming from the chamber above you to the southwest.";
          ],
    has   concealed static open container;
