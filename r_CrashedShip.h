
! ---------------------------------------------------------------------------- !
!       The CRASHED SHIP. 04/30/06
!
  Room    crashed_ship "Crashed Ship"
    with  description [;
              print "Quite recently, she must have been something to behold: you're standing in the cockpit
              of a 393-Z6 light transport, the latest in the proud Z6 series from the Zrok Corporation.
              Sadly, however, she's since been given a pirate makeover and the damage is everywhere.
              Computer systems have been torn out, deckplating ripped up, wire harnesses cut. ";
              if (self.airlockopen || al_door.albroken) {
                  if (self.smoking) {
                      "Even the ventilation shaft is smoking, as it pours black fumes into the air that get
                      sucked out the aft cargo hatch. Also, the port hatchway exits back out to the desert.";
                  } else {
                      print "The port hatchway exits back out to the desert, while light ";
                      if (self.airlockopen) {
                          print "pours";
                      } else {
                          print "streams";
                      }
                      print " in from the aft hatchway due to the ";
                      if (self.airlockopen) {
                          print "open";
                      } else {
                          print "broken";
                      }
                      " cargo hatch.";
                  }
              } else {
                  if (self hasnt general) {
                      adar.foundship = true;
                      give self general;
                  }
                  omni_trans.ogz6 = true;
                  if (self.adardhint) desert_crash.adarhint = true;
                  print "This ship will never fly again. A hatchway to port leads back out into the desert,
                  while one to the aft leads into the cargo area.^";
                  if (self.adarfirstime && adar in self) {
                      thinkpos = 9;
                      adar.adaroff = true;
                      self.adarfirstime = false;
                      print "^~Greb,~ Captain Adar curses, ~this is the second ship I've lost, I don't know
                      what the frell I'm going to do. Assuming I even make it out of here.~ ";
                      if (m_base.ch_maidens) print "She";
                      else print "He";
                      print " pulls ";
                      if (m_base.ch_maidens) print "her";
                      else print "him";
                      "self together with a visible effort. ~Right. Our only chance is to turn on the ship's
                      emergency beacon. If we get lucky, a passing transport might be able to pick up the signal,
                      otherwise, we're dead. Problem is, the APU can't go five seconds without overheating and
                      without that we've got no power.~";
                  }
                  rtrue;
              }
          ],
          s_to [;
              <<Enter cs_hatch>>;
          ],
          w_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go through the aft or port hatchways.",
          before [;
              Exit:
                  TestSuit();
                  if (adar in self) {
                      PAF();
                      MoveAdar(8);
                  }
                  u_obj.&name-->4 = 'sky';
                  PlayerTo(desert_crash,2);
                  rtrue;
              Listen:
                  if (self.smoking) "The noisy engines struggle to run in bad conditions, as they surge to maintain intake pressure.";
                  if (spacesuit has worn && spacesuit.suitopen == false) "Dead silence.";
                  "You can only hear the soft sound of wind, whipping past your ears.";
              SitDown:
                  print "(on the pilot's seat)^";
                  <<Sit crshchair>>;
              Yes:
                  return ALeave();
          ],
          adarfirstime true,
          airlockopen false,
          adardhint false,
          smoking false;

! 05/03/06

  RoomObj -> crashedshipobj "crashed ship"
    with  name 'crashed' 'ship' 'room' 'cockpit' 'structure' 'airframe',
          description [;
              <<Look crashed_ship>>;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Search:
                  return L__M(##Search, 4);
              Take, Remove, Turn, PushDir, Push, Pull:
                  "That's fixed in place.";
            ];

! 05/06/06

  Object  -> e_beacon "emergency beacon"
    with  name 'emergency' 'beacon' 'clear' 'hinged' 'cover' 'large' 'red' 'button' 'housing' 'case',
          description [;
              print "A standard feature on all ships, the emergency beacon can broadcast a mayday
              message to all vessels in the vicinity. Fortunately, it looks undamaged.
              ^^The interface consists of a large red button, ";
              if (self.eb_open) "now accessible with it's cover open.";
              "housed under a clear hinged cover to prevent accidental activation.";
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Close:
                  if (self.eb_open) {
                      self.eb_open = false;
                      "You close the cover of the emergency beacon.";
                  }
                  "The cover is already closed.";
              Open:
                  if (self.eb_open) "The cover is already open.";
                  self.eb_open = true;
                  "You flip open the cover of the emergency beacon.";
              SwFlip, SwitchOn, Push, Touch, Turn, UseItem:
                  if (self.eb_open == false) {
                      self.eb_open = true;
                      print "(first opening the clear hinged cover)^";
                  }
                  if (al_gen.ps_turnedon) {
                      if (crashed_ship.airlockopen || al_door.albroken) return GameEnd(0);
                      print "You press the button, and it starts blinking reassuringly, telling you
                      that the mayday message is on its way to the fleet -- for a few seconds,
                      anyway. Just as you're starting to relax, the smoke trips the
                      environmental regulator, shutting down the auxiliary power unit and the beacon with
                      it. Needless to say, the odds of anyone having received your signal are
                      slim at best.";
                      if (al_gen.gendmnfrst) {
                          al_gen.gendmnfrst = false;
                          " Maybe if you'd vented the ship a bit more, the air wouldn't have become toxic
                          enough to trip the regulator.";
                      }
                      new_line;
                      rtrue;
                  }
                  "You press the button, but nothing happens; all the ship's systems are currently useless.";
              FlipOff, SwitchOff:
                  "The beacon is already off.";
              Take, Remove:
                  "You'd have to work harder to bring home the beacon.";
          ],
          eb_open false,
          eb_endscr false,
          eb_notseen false,
    has   static ~on;

! 07/26/07

  Object  -> cs_floorboards "deckplating"
    with  name 'deckplating' 'deck' 'plating' 'floor' 'flooring',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  if (self.loxtaken) "The deckplating has been pushed aside leaving the structure exposed.";
                  if (self.loxfound) "The deckplating has been pushed aside revealing a liquid-oxygen tank underneath the flooring.";
                  self.loxfound = true;
                  move loxtank to crashed_ship;
                  "The deckplating have been pushed aside revealing a liquid-oxygen tank underneath the flooring.";
              Push, PushDir, Pull:
                  "The deckplating have already been pushed out of the way.";
              Take, Remove, Turn:
                  "The plating looks big and heavy, better just leave it in place.";
          ],
          loxfound false,
          loxtaken false,
    has   static;

! 07/26/07

  Object  -> cs_wire "wire harnesses"
    with  parse_name [ w1 w2;
              w1 = NextWord();
              if (w1 ~= 'cut' or 'wire' or 'wires' or 'wiring' or 'harness' or 'harnesses' or 'assembly') return 0;
              w2 = NextWord();
              if (w1 == 'wire' && w2 == 'harness' or 'harnesses' or 'assembly') return 2;
              if (w1 == 'cut' && w2 == 'wire' or 'wires') return 2;
              if (w1 == 'harness' or 'harnesses' or 'wires' or 'wiring' or 'assembly') return 1;
              return 0;
          ],
          before [;
              Attack, Kick:
                  return PHS();
              Cut:
                  "You don't need to add to the damage.";
              Examine, Search:
                  "The pirates disabled the ship by cutting into the wire harnesses,
                  leaving strands of broken wire everywhere.";
              Fix:
                  return PWB();
              Push, PushDir, Pull, Turn:
                  "Secured to the bulkhead of the cockpit, the wire harnesses can't be moved.";
              Take, Remove:
                  "The wire harnesses go deep into the ship, and can't be pull out.";
          ],
    has   scenery pluralname static;

! 07/26/07

  Object  -> cs_compsys "computer systems"
    with  name 'computer' 'system' 'systems' 'scorched' 'blast' 'marks' 'computers',
          before [;
              Examine, Search:
                  "Looking around, you see nothing but empty spaces and dangling wires
                  where the ship's key systems should have been. Even the little that
                  remains has been scorched by blaster fire.";
              Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, GetOff, Grapple, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip, FlipOff:
                  "The computer systems have been torn out.";
              Push, PushDir, Pull, Read, Remove, Rub, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "The computer systems have been torn out.";
          ],
    has   scenery pluralname static;

! 07/26/07

  Object  -> cs_lines "internal lines"
    with  name 'internal' 'lines',
          before [;
              Attack, Kick:
                  return PHS();
              Cut:
                  if (loxtank.connected) "That could be extremely dangerous, liquid oxygen could go everywhere.";
                  "You don't need to add to the damage.";
              Examine, Search:
                  if (loxtank.connected) "The internal lines run liquid oxygen throughout the ship.";
                  "The internal lines dangle, useless, waiting to be connected.";
              Plug:
                  if (loxtank.connected) "The internal lines are already connected to the liquid-oxygen tank.";
                  if (second == loxtank) "Why bother, this ship will never fly again.";
                  "What are you going to plug them into?";
              Push, PushDir, Pull:
                  if (loxtank.connected) "You can't, they're connected to the liquid-oxygen tank.";
                  "The internal lines go deep into the ship, and can't be pull out.";
              Take, Remove:
                  if (loxtank.connected) {
                      loxtank.connected = false;
                      "You remove the internal lines from the liquid-oxygen tank, now giving you better access.";
                  }
                  "The internal lines go deep into the ship, and can't be pull out.";
              Turn:
                  if (loxtank.connected) "The internal lines are attached to the liquid-oxygen tank and can't be moved.";
                  "The internal lines are attached to the bulkhead and can't be moved.";
              Unplug:
                  if (loxtank.connected) {
                      loxtank.connected = false;
                      "You remove the internal lines from the liquid-oxygen tank, now giving you better access.";
                  }
                  "The internal lines are hooked up to nothing.";
          ],
    has   concealed pluralname static;

! 07/27/07

  Object  -> crshchair "pilot's seat"
    with  name 'captain' 'captains' 'captain^s' 'pilot' 'pilots' 'pilot^s' 'chair' 'seat',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  "The pilot's seat has been torn into by the pirates, like everything else on this ship.";
              Sit:
                  "The seat is extremely uncomfortable to sit in; with it torn up the way it is, you don't stay for long.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The pilot's seat is securely bolted to the ship.";
          ],
    has   scenery static;

! 07/29/07

  Object  -> cs_switch "switches"
    with  name 'broken' 'switches',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  "Switches line the console of the ship, but they've all been broken, blasted or smashed by the pirates.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, Turn:
                  "Buttons aren't toys.";
              Take, Remove, PushDir, Pull:
                  "The switches are built into the console.";
          ],
    has   concealed static pluralname;

! 07/29/07

  Object  -> cs_console "console"
    with  name 'ship^s' 'ships' 'console' 'controls',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  "The pirates have done a thorough job of disabling the ship's controls,
                  taking the valuable parts and destroying the rest. The only one that
                  might still work is the emergency beacon.";
              Take, Remove, PushDir, Pull:
                  "The console is built into the airframe of the ship.";
          ],
    has   concealed static pluralname;

! 09/23/06

  Object  -> cs_hatch "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'hatch',
          description
              "The hatchway leads aft, further into the ship.",
          before [;
              Close:
                  "In case of fire, this hatchway should be left open.";
              Enter:
                  if (crashed_ship.smoking && CHDoorOpen()) {
                      if (spacesuit has worn) {
                        if (spacesuit.suitopen) {
                            spacesuit.suitopen = false;
                            print "(first closing the helm to the deep-space suit)^";
                        }
                        print "You enter the smoking cargo hold.^";
                        PlayerTo(air_lock);
                        rtrue;
                      } else {
                          "You can't enter the cargo hold with it smoking like that.";
                      }
                  }
                  if (adar in crashed_ship) {
                      PAF();
                      MoveAdar(10);
                  }
                  PlayerTo(air_lock);
                  rtrue;
              Open:
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Touch:
                  <<Touch al_hatch>>;
          ],
    has   concealed static enterable openable;
