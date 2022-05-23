
! ---------------------------------------------------------------------------- !
!       The MAIN JUNCTION. 09/22/06
!
  RoomShp main_junction "Main Junction"
    with  description [;
              if (space_pirates in self or crew_quarters or radar_room or galley) return PirateDeath(0);
              print "Like most small Xulthe'en ships, the XSS Supalace has a radial design, with
              all functions branching off a column of junctions";
              if (self.mjfrstm) {
                  self.mjfrstm = false;
                  ", affectionately known as the hub. You have to go through it to get from anywhere to
                  anywhere else, so it's usually buzzing with activity, but right now it's eerily empty.
                  Every step you take rings hollowly.
                  ^^Corridors lead forward to the bridge, starboard to the DMC, aft to the crew quarters,
                  and port to the galley. You can also see a ladder, leading down to the lower level of
                  the hub.";
              }
              ". From here you can go forward to the bridge, starboard to the DMC, aft to the crew
              quarters, and port to the galley. You can also see a ladder, leading down to the
              lower level of the hub.";
          ],
          n_to [;
              return EBText();
          ],
          s_to [;
              if (b_hatchway has open) return crew_quarters;
              give b_hatchway open;
              print "(first opening the hatchway)^";
              return crew_quarters;
          ],
          e_to [;
              return radar_room;
          ],
          w_to [;
              if (pattack > 2 && pattack < 10) {
                  deadflag = 1;
                  "You walk in on a bunch of space pirates as they're boarding the ship. ~Aye,~ one of
                  them says, ~looks like we got us a live one here.~ A roar of laughter breaks out as
                  the pirates grab hold of you, throwing you out their airlock.";
              }
              return galley;
          ],
          u_to "The ladder only goes down.",
          d_to [;
              return SJunction();
          ],
          cant_go "You need to state which direction you want to go in.",
          before [;
              ClimbDown:
                  return SJunction();
              Exit:
                  "You need to state which direction you want to go in.";
          ],
          mjfrstm true;

! 09/22/06

  RoomObj -> mainjunctobj "main junction"
    with  name 'main' 'junction' 'ship' 'room',
          description [;
              <<Look main_junction>>;
          ];

! 09/22/06

  Object  -> mj_ladder "ladder"
    with  name 'ladder',
          description
              "The ladder leads down to the bowels of the ship.",
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Climb, UseItem:
                  return SJunction();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static;

! 09/23/06

  Object  -> mj_sign
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'large' or 'sign' or 'data' or 'mining' or 'center' or 'dmc' or 'crew' or 'quarters' or 'bridge' or 'galley') return 0;
              w2 = NextWord();
              w3 = NextWord();
              if (w1 == 'data' && w2 == 'mining' && w3 == 'center') {
                  self.short_name = "data mining center";
                  self.mjradar = true;
                  self.mjsign = false;
                  self.mjcrew = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 3;
              }
              if (w1 == 'large' && w2 == 'sign') {
                  self.short_name = "large sign";
                  self.mjsign = true;
                  self.mjradar = false;
                  self.mjcrew = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 2;
              }
              if (w1 == 'data' or 'mining' && w2 == 'center') {
                  self.short_name = "data mining center";
                  self.mjradar = true;
                  self.mjsign = false;
                  self.mjcrew = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 2;
              }
              if (w1 == 'crew' && w2 == 'quarters') {
                  self.short_name = "crew quarters";
                  self.mjcrew = true;
                  self.mjradar = false;
                  self.mjsign = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 2;
              }
              if (w1 == 'large' or 'sign') {
                  self.short_name = "large sign";
                  self.mjsign = true;
                  self.mjradar = false;
                  self.mjcrew = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 1;
              }
              if (w1 == 'data' or 'mining' or 'center' or 'dmc') {
                  self.short_name = "data mining center";
                  self.mjradar = true;
                  self.mjsign = false;
                  self.mjcrew = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 1;
              }
              if (w1 == 'crew' or 'quarters') {
                  self.short_name = "crew quarters";
                  self.mjcrew = true;
                  self.mjradar = false;
                  self.mjsign = false;
                  self.mjbridge = false;
                  self.mjgalley = false;
                  return 1;
              }
              if (w1 == 'bridge') {
                  self.short_name = "bridge";
                  self.mjbridge = true;
                  self.mjcrew = false;
                  self.mjradar = false;
                  self.mjsign = false;
                  self.mjgalley = false;
                  return 1;
              }
              if (w1 == 'galley') {
                  self.short_name = "galley";
                  self.mjgalley = true;
                  self.mjbridge = false;
                  self.mjcrew = false;
                  self.mjradar = false;
                  self.mjsign = false;
                  return 1;
              }
          ],
          description [;
              if (self.mjradar || self.mjcrew || self.mjgalley || self.mjbridge) "You should try entering it.";
              return MSignRead();
          ],
          short_name "large sign",
          before [;
              Attack:
                  return PDE();
              Enter, Go:
                  if (self.mjradar) {
                      PlayerTo(radar_room);
                      rtrue;
                  }
                  if (self.mjcrew) {
                      PlayerTo(crew_quarters);
                      rtrue;
                  }
                  if (self.mjgalley) {
                      PlayerTo(galley);
                      rtrue;
                  }
                  if (self.mjbridge) return EBText();
              Read:
                  if (self.mjradar || self.mjcrew || self.mjgalley || self.mjbridge) rfalse;
                  return MSignRead();
              Scan:
                  if (self.mjradar || self.mjcrew || self.mjgalley || self.mjbridge) rfalse;
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the sign.";
                  POT();
                  style fixed;
                  print "~Bridge~, ~Data Mining Center~, ~Crew Quarters~, ~Galley~,
                  ^~Cargo Hold~, ~Main Airlock~, ~Engine Room~, and ~Armory~.";
                  style roman;
                  "";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (self.mjradar || self.mjcrew || self.mjgalley || self.mjbridge) rfalse;
                  return PAG();
          ],
          mjcrew false,
          mjsign false,
          mjradar false,
          mjbridge false,
          mjgalley false,
    has   static scenery;

! 09/23/06

  Object  -> mj_hatches "hatchway"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'aft' or 'port' or 'starboard' or 'fore' or 'forward' or 'door' or 'doors') return 0;
              if (w1 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhmj = false;
                  self.ahmj = false;
                  self.phmj = false;
                  self.sbhmj = false;
                  return 3;
              }
              w2 = NextWord();
              if (w1 == 'fore' or 'forward' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhmj = true;
                  self.ahmj = false;
                  self.phmj = false;
                  self.sbhmj = false;
                  return 3;
              }
              if (w1 == 'aft' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhmj = false;
                  self.ahmj = true;
                  self.phmj = false;
                  self.sbhmj = false;
                  return 3;
              }
              if (w1 == 'port' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhmj = false;
                  self.ahmj = false;
                  self.phmj = true;
                  self.sbhmj = false;
                  return 3;
              }
              if (w1 == 'starboard' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhmj = false;
                  self.ahmj = false;
                  self.phmj = false;
                  self.sbhmj = true;
                  return 3;
              }
              return 0;
          ],
          description [;
              if (self.fhmj) {
                  if (mb_hatchway has open) "The forward hatchway to the bridge is open.";
                  "The forward hatchway to the bridge is closed.";
              }
              if (self.ahmj) {
                  if (b_hatchway has open) "The aft hatchway to the crew quarters is open.";
                  "The aft hatchway to the crew quarters is closed.";
              }
              if (self.phmj) "The port hatchway leads to the galley.";
              if (self.sbhmj) "The starboard hatchway leads to the DMC.";
              "The hatchways here lie fore, aft, port and starboard.";
          ],
          before [;
              Attack:
                  return PDE();
              Close:
                  if (self.fhmj) {
                      if (mb_hatchway has open) {
                          give mb_hatchway ~open;
                          "You close the forward hatchway to the bridge.";
                      }
                      "The forward hatchway to the bridge is already closed.";
                  }
                  if (self.ahmj) {
                      if (b_hatchway has open) {
                          give b_hatchway ~open;
                          "You close the aft hatchway to the crew quarters.";
                      }
                      "The aft hatchway to the crew quarters is already closed.";
                  }
                  "In case of fire, this hatchway should be left open.";
              Enter, Exit:
                  "Please use normal navigation directions. FORWARD, AFT, PORT, and STARBOARD.";
              Open:
                  if (self.fhmj) {
                      if (radar_room.note_taken && radar_room.captainknow) {
                          if (radar_room.rrdaemonstart && galley.entergalley) "You have no reason to bother Command.^^The only places you really want to go right now are the galley and your duty station in the DMC.";
                          if (radar_room.rrdaemonstart) "You have no reason to bother Command.^^The only place you really want to go right now is to your duty station in the DMC.";
                          "You need to take the datacard before you can go and see the Captain.";
                      }
                      if (mb_hatchway has open) "That's already open.";
                      give mb_hatchway open;
                      "The bolts of the hatchway draw back with a reassuring ~thunk~.";
                  }
                  if (self.ahmj) {
                      if (b_hatchway has open) "That's already open.";
                      give b_hatchway open;
                      "The bolts of the hatchway draw back with a reassuring ~thunk~.";
                  }
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          fhmj false,
          ahmj false,
          phmj false,
          sbhmj false,
    has   concealed static enterable;
