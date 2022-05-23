
! ---------------------------------------------------------------------------- !
!       The BRIDGE. 04/12/06
!
  RoomShp bridge "Bridge"
    with  initial [;
              if (self.dstop) {
                  thinkpos = 0;
                  self.dstop = false;
                  StopDaemon(datacard);
                  StartDaemon(pirates_board);
                  radar_room.enterbridge = true;
                  "The bridge is deserted, just like in your dream. There should be crewmen and
                  cadets rushing to follow the orders of the officers, but instead there's only
                  silence. The bridge should never be left unmanned; even the rawest recruit
                  knows that.";
              }
          ],
          description [;
              if (space_pirates in self) return PirateDeath(0);
              if (cargo_hatch.hatchopen) {
                  print "You stand alone on the bridge, pirates having abandoned her on this desert planet.
                  They stripped off everything of value; the main computer, navigation systems, even the
                  ship's plaque. In this condition, she'll never fly again.";
              } else {
                        if (self.boarded) {
                            print "You stand alone on the bridge. Though there's no course laid in, you can see
                            through the viewport that the ship is moving slowly; the pirates are towing you
                            through deep space using a tractor beam. With nobody else here, the space is
                            empty and hollow.";
                        } else {
                            if (self.bridgealarm) {
                                print "You stand alone on the bridge. The emergency alert system announces the
                                damage taken to the port side of the ship.";
                            } else {
                                print "You stand alone on the bridge. In happier circumstances, you'd take gleeful
                                advantage of your chance to sample the Captain's chair, but that hardly
                                seems appropriate now. The few times you've been up here, you've
                                always been too busy to take it all in; now, you're too anxious.";
                            }
                  }
              }
              if (mb_hatchway has open) print " An open";
              else print " A closed";
              print " hatchway lies aft, while the engineering access cover is ";
              if (br_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          s_to [;
              if (mb_hatchway has open) return main_junction;
              give mb_hatchway open;
              print "(first opening the hatchway)^";
              return main_junction;
          ],
          in_to [;
              <<Enter br_eacover>>;
          ],
          before [;
              Exit:
                  if (mb_hatchway has open) {
                      PlayerTo(main_junction);
                      rtrue;
                  }
                  give mb_hatchway open;
                  print "(first opening the hatchway)^";
                  PlayerTo(main_junction);
                  rtrue;
              HideRoom:
                  if (pattack > 2 && pattack < 10) "Hiding on the bridge is a bad, bad idea.";
              SitDown:
                  print "(on the captain's chair)^";
                  return CaptainChair();
          ],
          cant_go
              "You can go through the aft hatchway or into the e-tube.",
          dstop true,
          boarded false,
          bridgealarm false;


! 04/28/06

  RoomObj -> bridgeobj "bridge"
    with  name 'command' 'bridge' 'room',
          description [;
              <<Look bridge>>;
          ],
          before [;
              Hide:
                  if (pattack > 2 && pattack < 10) "Hiding on the bridge is a bad, bad idea.";
          ];

! 04/12/06

  Object  -> mb_ship "trans-stellar transport"
    with  name 'trans' 'stellar' 'transport' 'ship' 'trans-stellar' 'transstellar',
          description [;
              print "It's like any other trans-stellar transport you've ever seen, big, ugly, cold, and gray.";
              if (main_computer.poweron) " But up here it does seem to sparkle a little more, with lights blinking away on the consoles while monitors display status information.";
              new_line;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed;

! 04/15/06

  Object  -> viewport "main viewport"
    with  name 'main' 'view' 'port' 'viewport',
              article "the",
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (pland >= (plimit+15)) {
                      "As you look out the viewport, you see a harsh, burnt, red, desert with a hot sun that
                      beats down on a dead planet. It looks like little, if anything, is alive out there.";
                  } else {
                      if (pland >= (plimit+1)) {
                          if (r_planet notin bridge) move r_planet to bridge;
                          print "As you look out the viewport, you can see ";
                          if (self.planetseen) {
                              print "the";
                          } else {
                              self.planetseen = true;
                              print "a";
                          }
                          " red planet getting closer as the large black towing you with a tractor beam lands the vessels.";
                      } else {
                          if (pland == plimit) {
                              self.planetseen = true;
                              if (r_planet notin bridge) move r_planet to bridge;
                              "As you look out the viewport, you see a red planet come into view
                              as the large black ship towing you with a tractor beam lands the vessels.";
                          } else {
                              if (self.boarded) {
                                  if (ship notin bridge) {
                                      move ship to bridge;
                                      move tbeam to bridge;
                                  }
                                  "As you look out the viewport, you see the large black ship towing you out into deep space with a tractor beam.";
                              } else {
                                  if (ship notin bridge) move ship to bridge;
                                  if (crew_asteroid notin bridge) move crew_asteroid to bridge;
                                  if (pattack < 3) {
                                      print "Coming at";
                                  } else {
                                      print "Hanging in space before";
                                  }
                                  print " you is a large black ship that must be the source of all your problems.
                                  There's no registration insignia, but it's a pirate ship, as surely as if they'd
                                  painted a skull-and-crossbones on the side.";
                                  if (self.vseen) {
                                      self.vseen = false;
                                      "^^A cloud of what, at first, you take to be small asteroids surrounds the
                                      ship. On closer inspection, however, you learn the appalling truth: the
                                      'asteroids' are the bodies of your crewmates, bloated by the vacuum of space
                                      and spinning slowly.
                                      ^^Thinking about it further, you realize that it must be the strange metal
                                      alloy of your bunk that saved you from their fate.";
                                  } else {
                                      "^^The disgusting site of a cloud of bodies surrounds the ship, crewmates slowly
                                      spinning, bloated by the vacuum of space.";
                                  }
                              }
                          }
                      }
                  }
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          vseen true,
          boarded false,
          planetseen false,
    has   static;

! 04/15/06

  Object  -> bridge_alarm "emergency alert alarm system"
    with  name 'emergency' 'alert' 'alarm' 'system',
          daemon [;
              if (player in bridge)
                  "^The screech from the emergency alert alarm system is nearly deafening, as it
                  reports the damage taken to the port side of the ship.";
          ],
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (self.alarmon) "The emergency alert alarm system is currently switched on.";
                  "The emergency alert alarm system is currently switched off.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, Use, UseItem:
                  return PSH();
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
              Unplug:
                  print (The) self, " isn't plugged into anything, it's hard-wired into the ship's electrical system.^";
                  rtrue;
          ],
          alarmon false,
    has   concealed static;

! 04/18/06

  Object  -> main_computer "main computer"
    with  name 'main' 'computer' 'scanner',
          invent [;
              if (ident_badge in self) print "the main computer (in which is the Captain's ident badge)";
              else print "the main computer";
              rtrue;
          ],
          description [;
                  if (self.poweron) {
                      print "The main computer is set into the starboard bulkhead. An array of screens
                      and keypads allows the bridge officers to control all the ship's functions. Of course,
                      all of this is beyond you. There's also an ident-badge scanner, at eye level";
                      if (ident_badge in self) {
                          print ", in which is the Captain's badge. The Captain's badge will authorize
                          pretty much anything, and he would normally never let it out of his sight";
                          if (self.mcseen) {
                              self.mcseen = false;
                              ". It's yet another indicator of how bad the situation is.";
                          }
                          ".";
                      }
                      ".";
                  }
                  "The main computer is set into the starboard bulkhead. The array of screens
                  and keypads are dead, showing no activity, since there's no power going to this unit.";
              ],
          before [;
              AskChar, TellTo:
                  "Some computers in the armada use voice activation, but this ship is beyond dated.";
              Attack:
                  return PDE();
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push:
                  "The main computer has no power switch; it's hard-wired into the ship's electrical system.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
              Unplug:
                  print (The) self, " isn't plugged into anything, it's hard-wired into the ship's electrical system.^";
                  rtrue;
              UseItem:
                  if (self.poweron) "Besides calculating Burin curves for planetary orbit, there's not much that you can do with it.";
                  "There's no power going to the computer.";
          ],
          life [;
              Answer, AnswerDir, Ask, Tell:
                  "Some computers in the armada use voice activation, but this ship is beyond dated.";
          ],
          orders [;
              Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, Follow, GetOff, Give, Grapple, Hello, Help, Hide, JumpOver, Kick, Listen, LookUnder, No, Open, Plug, PlugItem, SwFlip, Push:
                  "Some computers in the armada use voice activation, but this ship is beyond dated.";
              PushDir, Pull, Read, Remove, Rub, Search, Set, SetTo, ShortOut, Sit, Smash, Smell, Sorry, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave, Yes:
                  "Some computers in the armada use voice activation, but this ship is beyond dated.";
          ],
          mcseen true,
          poweron true,
          systemunplugged false,
    has   animate static container open;

! 07/28/07

  Object  -> cscreens "screens"
    with  name 'screens' 'screen',
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Examine, Read, Search:
                  if (main_computer.poweron) {
                      if (galley.gpboard) {
                          print "The screens display:^^";
                          style fixed;
                          print "** Warning **
                          ^^Unexpected Stellar Location
                          ^^Attempting to recalibrate...
                          ^^Attempting to connect to Corps Transponder...";
                          style roman;
                          "";
                      }
                      print "The screens display:^^";
                      style fixed;
                      print "Planetary Readout: Enrys: IV
                      ^Rotation: 2.4532 x B.P.
                      ^Orbital Speed: 164,267 mm/h
                      ^Gravity: 0.825
                      ^Gravitational Pull: 0.792 mm/s";
                      style roman;
                      "";
                  }
                  "Since the computer isn't working, there's no information on the screens to read.";
              FlipOff, SwFlip, SwitchOn, SwitchOff:
                  <<SwitchOn main_computer>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static pluralname;

! 04/23/07

  Object  -> console "monitors"
    with  name 'console' 'consoles' 'monitor' 'monitors',
          before [;
              Attack:
                  return PDE();
              Examine, Read, Search:
                  if (main_computer.poweron) {
                      if (galley.gpboard) {
                          print "The monitor displays:^^";
                          style fixed;
                          print "** Warning **
                          ^^Unexpected Stellar Location
                          ^^Attempting to recalibrate...
                          ^^Attempting to connect to Corps Transponder...";
                          style roman;
                          "";
                      }
                      print "The monitor displays:^^";
                      style fixed;
                      print "Planetary Readout: Enrys: IV
                      ^Circumference: 2.18 x 10 @@94 4 P.U.
                      ^Density: 1.1
                      ^Gravity: 0.825
                      ^Satellites: 0
                      ^^Atmosphere: Oxygen/Nitrogen
                      ^Hydrosphere: Balanced
                      ^Biosphere: Sentient beings present
                      ^Climate: Temperate mix
                      ^Radiation: 2%
                      ^^Note:
                      ^Re-supply coordinates:
                      ^Latitude: 85.29
                      ^Longitude: -105.93";
                      style roman;
                      "";
                  }
                  "Since the console isn't working there's no information on the monitors to read.";
               PushDir, Push:
                   return PSH();
              Take, Remove, Turn, Pull:
                  return PAG();
          ],
    has   scenery static pluralname;

! 05/10/06

  Object  -> plaque "ship's plaque"
    with  name 'ships' 'ship^s' 'plaque',
          description [;
              return PSP(0);
          ],
          article "the",
          before [;
              Attack:
                    return PDE();
              LookUnder, Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Read:
                    return PSP(0);
          ],
    has   static;

! 09/22/06

  Object  -> mb_hatchway "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'hatch' 'door' 'doors',
          description [;
              if (mb_hatchway has open) "The aft hatchway leads to the main junction.";
              "The hatchway that leads to the aft of the ship is closed.";
          ],
          before [;
              Attack:
                  return PDE();
              Enter:
                  if (self has open) {
                      PlayerTo(main_junction);
                      rtrue;
                  }
                  give self open;
                  print "(first opening the hatchway)^";
                  PlayerTo(main_junction);
                  rtrue;
              Open:
                  if (self has open) "That's already open.";
                  give self open;
                  "The bolts of the hatchway draw back with a reassuring ~thunk~.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static enterable openable;

! 11/07/06

  Object  -> capt_chair
    with  parse_name [w1 w2;
              w1 = NextWord();
              w2 = NextWord();
              if (w1 ~= 'captains' or 'captain^s' or 'captain' or 'pilot' or 'pilots' or 'pilot^s' or 'chair' or 'seat' or 'small' or 'control' or 'panel' or 'light' or 'lights' or 'button' or 'buttons') return 0;
              if (w1 == 'captains' or 'captain^s' or 'captain' or 'pilot' or 'pilots' or 'pilot^s' && w2 == 'chair' or 'seat') {
                  self.short_name = "captain's chair";
                  self.captainschair = true;
                  return 3;
              }
              if (w1 == 'small' or 'control' or 'panel' or 'lights' or 'light' or 'button' or 'buttons') {
                  self.short_name = "small control panel";
                  self.captainschair = false;
                  return 3;
              }
              if (w1 == 'chair' or 'seat') {
                  self.short_name = "captain's chair";
                  self.captainschair = true;
                  return 1;
              }
                  return 0;
          ],
          short_name "captain's chair",
          description [;
              if (self.captainschair) {
                  print "The captain's chair sits in the middle of the bridge looking out towards the viewport.";
                  if (main_computer.poweron) " Lights blink along a small control panel built into the chair's arm.";
                  "";
              }
              if (main_computer.poweron) "The small control panel blinks with activity.";
              "The small control panel is dead, along with every other computer in here.";
          ],
          before [;
              Attack:
                  return PDE();
              Enter, Sit:
                  if (self.captainschair) {
                      return CaptainChair();
                  }
                  rfalse;
              SwFlip, SwitchOn, UseItem:
                  if (self.captainschair) rfalse;
                  if (main_computer.poweron) "Buttons aren't toys.";
                  "No power is going to the panel.";
              FlipOff, SwitchOff:
                  if (self.captainschair) rfalse;
                  if (main_computer.poweron) "Buttons aren't toys.";
                  "That is already off.";
              Push, Turn:
                  if (self.captainschair) return PAG();
                  if (main_computer.poweron) "Buttons aren't toys.";
                  "No power is going to the panel.";
              Take, Remove, PushDir, Pull:
                  return PAG();
          ],
          captainschair false,
    has   static scenery;

! 09/22/06

  Object  -> mb_keypad "keypad"
    with  name 'keypad' 'keypads' 'keyboard' 'keyboards' 'keys' 'key' 'pad',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  print "All the ship's functions can be controlled from here, down to the duty
                  cycle of the robo-wash. With power comes complexity, though, and you have no
                  idea which button does what.";
                  if (main_computer.poweron) {
                      new_line;
                      rtrue;
                  }
                  " Also, without power they're all completely useless anyway.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
              Push, Touch, UseItem:
                  print "Fingers poised in imitation of the keypad virtuosos who usually man
                  these stations, it strikes you that randomly pressing buttons wouldn't be a smart move. ";
                  if (main_computer.poweron) "You might disengage life support or, worse, you might put the Captain's music collection on shuffle.";
                  "Then it strikes you that the power's off, so why not? For a few joyous
                  moments, you do your imitation of a concert pianokeyboard player in full
                  flow until, in the middle of a particularly energetic glissando, reality
                  sinks in again and you, sheepishly, stop.";
          ],
    has   static scenery;

! 05/13/08

  EACovr  -> br_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph' 'safety' 'latch' 'panel',
          before [ itest;
              Enter:
                  itest = 0;
                  if (self.cvrlck) {
                      itest = 1;
                      self.cvrlck = false;
                      print "(first unlocking the safety latch)^";
                  }
                  if (self.panopn == false) {
                      self.panopn = true;
                      if (itest == 1) print "(next opening the engineering access cover)^";
                      else print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(br_etube);
                  rtrue;
              Examine, Search:
                  print "The engineering access cover is ";
                  if (self.panopn) "open, giving you access to the e-tubes.";
                  if (self.cvrlck) "closed, and locked with a safety latch.";
                  "closed.";
              Lock:
                  if (self.cvrlck) "That's already locked.";
                  "There's no need.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (self.panopn) "That's already open.";
                  if (self.cvrlck) {
                      self.cvrlck = false;
                      print "(first unlocking the safety latch)^";
                  }
                  self.panopn = true;
                  self.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the e-tubes.";
              Unlock:
                  if (self.cvrlck) {
                      self.cvrlck = false;
                      "You unlock the safety latch.";
                  }
                  "That's already unlocked.";
          ],
          cvrlck true,
          panopn false;
