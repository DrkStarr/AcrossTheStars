
! ---------------------------------------------------------------------------- !
!       The ENGINE ROOM. 04/16/06
!
  RoomShp engine_room "Engine Room"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              if (cargo_hatch.hatchopen) {
                  print "The engine room is empty and deserted since the pirates looted the ship.
                  The two twin acardiolytic engines that powered her have both been removed, while
                  an open hatchway lies forward.";
              } else {
                  print "Like the rest of the ship, the room is deserted";
                  if (engine.eoff) print " and comes ";
                  else print ", but it's far from quiet. The ship is ";
                  print "equipped with twin acardiolytic engines, powerful enough to take her from star to star in a matter of hours";
                  if (ce_badge in flow_regulator) print ". ";
                  else print ", while the flow regulator coils itself around them. ";
                  if (engine.eoff) print "The engines are mounted on the aft bulkhead and take";
                  else print "Even though they're barely idling right now, they still make the bulkheads rattle, taking";
                  print " up most of the room, while an open hatchway lies forward.";
              }
              print " Also, the engineering access cover is ";
              if (er_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          n_to [;
              return secondary_junction;
          ],
          in_to [;
              <<Enter er_eacover>>;
          ],
          cant_go
              "You can go through the fore hatchway or into the e-tube.",
          before [;
              Exit:
                  PlayerTo(secondary_junction);
                  rtrue;
              HideRoom:
                  "There's nowhere for you to hide in here.";
          ],
          pdownsafe true;

! 04/28/06

  RoomObj -> engineobj "engine room"
    with  name 'ship' 'room',
          description [;
              <<Look engine_room>>;
          ],
          before [;
              Search:
                  if (self has general) {
                      return L__M(##Search, 4);
                  } else {
                      give self general;
                      move playbeing to workbench;
                      "As you search around the room, you find the latest issue of Playbeing.
                      I guess the Chief was a dirty old man to boot.";
                  }
          ];

! 09/18/06

  Object  -> flow_regulator "flow regulator"
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'flow' or 'regulator' or 'power' or 'conduit' or 'manual' or 'shutdown' or 'slot' or 'ident' or 'badge') return 0;
              w2 = NextWord();
              w3 = NextWord();
              if (w1 == 'manual' or 'flow' or 'ident' && w2 == 'shutdown' or 'regulator' or 'badge' && w3 == 'slot') return 3;
              if (w1 == 'flow' or 'regulator' or 'power' or 'manual' or 'shutdown' or 'badge' or 'ident' && w2 == 'regulator' or 'conduit' or 'shutdown' or 'slot') return 2;
              if (w1 == 'flow' or 'regulator' or 'power' or 'conduit' or 'manual' or 'shutdown') return 1;
              if (w1 == 'slot') return 3;
              return 0;
          ],
          describe [;
              if (ce_badge in self) "^In the flow regulator is the Chief Engineer's ident badge.";
              rtrue;
          ],
          description [;
              print "The flow regulator is a power conduit, leading to the main circuit breaker and
              then on to the rest of the ship's systems. ";
              if (radar_room.flowoff) {
                  print "Presently ";
                  if (ce_badge in self) print "the Chief Engineer's ident badge is inserted into the ~Manual Shutdown~ slot";
                  else print "it's off";
                  ". Without power from the engines, the ship has shifted to the backup batteries,
                  which are only capable of maintaining the most basic level of life support.";
              }
              "It's an extremely advanced piece of technology, but for once the interface is comprehensible:
              it consists of an ident badge slot with the words ~Manual Shutdown~ above it.
              ^^It's only usually shut down when the ship is in space-dock for maintenance:
              without power from the engines, the ship shifts to the backup batteries, which
              are only capable of maintaining the most basic level of life support.";
          ],
          before [;
              Attack:
                  return PDE();
              SwFlip, SwitchOn, UseItem:
                  if (self has on) "Power is already flowing through the conduit.";
                  "You don't want to alert the pirates to your presence again.";
              FlipOff, SwitchOff, Unplug:
                  if (self has on) {
                      if (ce_badge in player) return PUB();
                      "You need the Chief Engineer's ident badge to break the connection in ", (the) self, ".";
                  }
                  return PCA();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static container open on;

! 09/18/06

  Object  -> circuit_breaker "circuit breaker panel"
    with  name 'main' 'circuit' 'breaker' 'panel' 'breakers',
          description
              "This controls access to the ship's main circuit breaker; all the power that the flow regulator
              draws from the engines is routed through here.",
          describe [;
              if (child(workbench) == nothing) {
                  print "^The workbench has been picked clean";
              } else {
                  print "^On the workbench";
                  WriteListFrom(child(workbench), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
              }
              print", while ";
              if (self has open) print "an open";
              else print "a";
              print " circuit breaker panel is embedded into the bulkhead above it";
              if (self has open && ce_badge in self) print " containing the Chief Engineer's ident badge";
              ".";
          ],
          before [;
              Attack, Cut:
                  return PDE();
              Close:
                  if (self has open) {
                      give self ~open;
                      "You close the circuit breaker panel.";
                  }
                  "That's already closed.";
              Open:
                  if (self has open) "That's already open.";
                  if (self.cbalop) {
                      give self open;
                      print "You open the circuit breaker panel";
                      if (ce_badge in self) print ", revealing the Chief Engineer's ident badge";
                      ".";
                  }
                  if (prybar in player) {
                      give self open;
                      self.cbalop = true;
                      move ce_badge to self;
                      move cp_wires to self;
                      move cp_breaker to self;
                      outside_airlock.popen = true;
                      self.&name-->4 = 'ph3289';
                      if (second == prybar) return PTB();
                      print "(using the pry bar)^";
                      return PTB();
                  }
                  if (second == wrench) "You might be able to pry open the panel, but not with the universal tool. It's too small to get any leverage.";
                  "The panel would normally be sealed tightly shut, and require the Chief Engineer's
                  ident badge to open. Today, though, it looks like it's actually a little loose.
                  With a lever and a bit of brute force, it might yield.";
              Search:
                  if (self has open) {
                      if (ce_badge in self) rfalse;
                      "Large breakers and thousands of wires connect all the circuitry together.";
                  }
                  "You can't do that with the panel closed.";
              FlipOff, SwFlip, SwitchOn, SwitchOff:
                  if (self has open) "The circuit breakers themselves are electronically controlled through the flow regulator.";
                  "The circuit breaker panel is closed.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          cbalop false,
    has   static container;

! 04/16/06

  Object  -> workbench "workbench"
    with  name 'workbench' 'work' 'bench',
          description [;
              if (spareparts in self) "There's just enough space for the cluttered workbench, pushed up against the port bulkhead,         while it's piled high with what you hope are spare parts.";
              "Pushed up against the port bulkhead, the workbench stands alone in this empty room.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Enter, Hide:
                  "It's too small for you to crawl underneath there.";
              LookUnder:
                  "The space underneath is pretty small, unlike the desk in the DMC.";
              Search:
                  if (self.wrenchfound) {
                      self.wrenchfound = false;
                      move wrench to workbench;
                      "As you search the workbench, you find a universal tool amongst the spare parts.";
                  }
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          wrenchfound true,
    has   supporter static;

! 04/16/06

  Object  -> -> spareparts "untidy heap of spare parts"
    with  name 'untidy' 'heap' 'of' 'spare' 'part' 'parts' 'bits',
          description [;
              print "As you look over the spare parts, you don't see much that you recognize;
              engineering was never one of your strong suits. These could be engine parts
              or bits of the Captain's robot dog for all you know.";
              if (workbench.wrenchfound || wrench in workbench) {
                  workbench.wrenchfound = false;
                  move wrench to workbench;
                  " In amongst all the junk, though, you do find a universal tool.";
              }
              new_line;
              rtrue;
          ],
          article "an",
          before [;
              Attack:
                  return PDE();
              Search, Turn:
                  if (workbench.wrenchfound) {
                      workbench.wrenchfound = false;
                      move wrench to workbench;
                      "As you turn over a few spare parts, you find a universal tool amongst some of them.";
                  }
              Take, Remove, PushDir, Push, Pull:
                  return PSH();
          ],
    has   static;

! 04/16/06

  Object  -> engine "acardiolytic engine"
    with  name 'acardiolytic' 'engines' 'engine',
          description
              "These engines are brand new and the top of the line in Xulthe'en technology.
              Since the ship's refit she's faster and lighter, with engines made out of advanced
              composites. Operating on principles that only a handful of the Empire's brightest
              scientists and engineers understand, they're the product of decades of research.
              ^^The vast majority of the engine's output is used for propulsion, but a small amount
              is siphoned off by a flow regulator to power the ship's other systems.",
          article "a",
          before [;
              Attack:
                  return PDE();
              FlipOff, SwitchOff, Unplug:
                  if (galley.gpboard) {
                      deadflag = 1;
                      "As you throw the emergency shutdown switch, they engines start to sputter then
                      stop completely. The pirates that were towing the ship come back to investigate, and find
                      you aboard.^^~Aye,~ says one of the pirates, ~I knew we still had a little
                      wretch'n onboard. Let's go feed this one to lil' Timmy.~ At that, all the
                      pirates break out into a full roar.";
                  }
                  self.eoff = true;
                  if (pattack < 2) {
                      pattack = 2;
                      thinkpos = 0;
                      piraterange = 0;
                      StopDaemon(datacard);
                      StopDaemon(radar_room);
                      StartDaemon(pirates_board);
                      bridge.dstop = false;
                      datacard.engoff = true;
                      radar_room.enterbridge = true;
                      radar_room.captainknow = false;
                  }
                  "Walking to the front of the engines, you shut off them down using the emergency
                  shut switch.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Touch:
                  if (self.eoff) "All is quite, since the engines have been shut off.";
                  "You feel strong vibrations coming off the engines, rattling the entire ship.";
          ],
          eoff false,
    has   scenery static;

! 04/16/06

  Object  -> er_eswitch "emergency shutdown switch"
    with  name 'emergency' 'shutdown' 'switch',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  "The emergency shutdown switch will cut the power to and from the engines immediately, once it's pushed.";
              SwFlip, SwitchOn, Turn, UseItem:
                  <<SwitchOff engine>>;
              FlipOff, SwitchOff:
                  return PSH();
              Take, Remove, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static;

! 05/13/08

  EACovr  -> er_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph',
          before [;
              Enter:
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(er_etube);
                  rtrue;
          ],
          panopn false;
