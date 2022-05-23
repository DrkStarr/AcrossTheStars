
! ---------------------------------------------------------------------------- !
!       The SECONDARY JUNCTION. 09/22/06
!
  RoomShp secondary_junction "Secondary Junction"
    with  description [;
              if (space_pirates in self or engine_room or main_airlock or armory or cargo_hold) return PirateDeath(0);
              "This is the lower level of the hub; from here you can go forward to the
              cargo hold, starboard to the main airlock, aft to the engine room and
              port to the armory. You can also see a ladder, leading up to the upper
              level of the hub.";
          ],
          n_to [;
              if (galley.gpboard == false) "The cargo hold is filled with small crates, making it impossible to enter the room.";
              return cargo_hold;
          ],
          s_to [;
              return engine_room;
          ],
          e_to [;
              return main_airlock;
          ],
          w_to [;
              return armory;
          ],
          u_to [;
              return MJunction();
          ],
          d_to "The ladder only goes up.",
          cant_go "You need to state which direction you want to go in.",
          before [;
              Climb:
                  return MJunction();
              Exit:
                  "You need to state which direction you want to go in.";
          ];

! 09/22/06

  RoomObj -> secjunctobj "secondary junction"
    with  name 'secondary' 'junction' 'ship' 'room',
          description [;
              <<Look secondary_junction>>;
          ];

! 09/22/06

  Object  -> sj_ladder "ladder"
    with  name 'ladder',
          description
              "The ladder leads up to the command section of the ship.",
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Climb, UseItem:
                  return MJunction();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static;

! 09/18/06

  Object  -> small_crates "small crates"
    with  name 'small' 'crate' 'crates' 'cargo',
          description
              "The small crates are stacked to the ceiling making it impossible to enter the cargo hold.",
          before [;
              Attack:
                  return PDE();
              LookBehind:
                  "The small crates are stacked to the ceiling and you're unable to see behind them.";
              Open:
                  "The crates are stacked one on top of another, and cannot be opened.";
              Take, Remove, Pull:
                  "Not only is it a hazard to move the cargo while you're in transit.
                  But as a punishment, the last guy that tried that found himself scrubbing
                  the exterior hull with a toothbrush, in a deep-space suit.";
              PushDir, Push, Turn:
                  "The cargo is packed tightly together, and refuses to move as you push on it.";
              Read:
                  "~Standard Rations~ is stamped across each crate.";
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the small crates.";
                  POT();
                  style fixed;
                  print "~Standard Rations~";
                  style roman;
                  "";
          ],
    has   static scenery pluralname;

! 09/23/06

  Object  -> sj_sign
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'large' or 'sign' or 'cargo' or 'hold' or 'main' or 'airlock' or 'engine' or 'room' or 'armory') return 0;
              w2 = NextWord();
              if (w1 == 'large' && w2 == 'sign') {
                  self.short_name = "large sign";
                  self.sjsign = true;
                  self.sjchold = false;
                  self.sjmairlck = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 2;
              }
              if (w1 == 'cargo' && w2 == 'hold') {
                  self.short_name = "cargo hold";
                  self.sjchold = true;
                  self.sjsign = false;
                  self.sjmairlck = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 2;
              }
              if (w1 == 'main' && w2 == 'airlock') {
                  self.short_name = "main airlock";
                  self.sjmairlck = true;
                  self.sjsign = false;
                  self.sjchold = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 2;
              }
              if (w1 == 'engine' && w2 == 'room') {
                  self.short_name = "engine room";
                  self.sjeroom = true;
                  self.sjsign = false;
                  self.sjchold = false;
                  self.sjmairlck = false;
                  self.sjarmory = false;
                  return 2;
              }
              if (w1 == 'large' or 'sign') {
                  self.short_name = "large sign";
                  self.sjsign = true;
                  self.sjchold = false;
                  self.sjmairlck = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 1;
              }
              if (w1 == 'cargo' or 'hold') {
                  self.short_name = "cargo hold";
                  self.sjchold = true;
                  self.sjsign = false;
                  self.sjmairlck = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 1;
              }
              if (w1 == 'main' or 'airlock') {
                  self.short_name = "main airlock";
                  self.sjmairlck = true;
                  self.sjsign = false;
                  self.sjchold = false;
                  self.sjeroom = false;
                  self.sjarmory = false;
                  return 1;
              }
              if (w1 == 'engine' or 'room') {
                  self.short_name = "engine room";
                  self.sjeroom = true;
                  self.sjsign = false;
                  self.sjchold = false;
                  self.sjmairlck = false;
                  self.sjarmory = false;
                  return 1;
              }
              if (w1 == 'armory') {
                  self.short_name = "armory";
                  self.sjarmory = true;
                  self.sjsign = false;
                  self.sjchold = false;
                  self.sjmairlck = false;
                  self.sjeroom = false;
                  return 1;
              }
          ],
          description [;
              if (self.sjchold || self.sjmairlck || self.sjeroom || self.sjarmory) "You should try entering it.";
              return SSignRead();
          ],
          short_name "large sign",
          before [;
              Attack:
                  return PDE();
              Enter, Go:
                  if (self.sjchold) {
                      if (galley.gpboard == false) "The cargo hold is filled with smaller crates, making it impossible to enter the room.";
                      PlayerTo(cargo_hold);
                      rtrue;
                  }
                  if (self.sjmairlck) {
                      PlayerTo(main_airlock);
                      rtrue;
                  }
                  if (self.sjeroom) {
                      PlayerTo(engine_room);
                      rtrue;
                  }
                  if (self.sjarmory) {
                      PlayerTo(armory);
                      rtrue;
                  }
              Read:
                  if (self.sjchold || self.sjmairlck || self.sjeroom || self.sjarmory) rfalse;
                  return SSignRead();
              Scan:
                  if (self.sjchold || self.sjmairlck || self.sjeroom || self.sjarmory) rfalse;
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the sign.";
                  POT();
                  style fixed;
                  print "~Cargo Hold~, ~Main Airlock~, ~Engine Room~, ~Armory~,
                  ^~Bridge~, ~Data Mining Center~, ~Crew Quarters~, and ~Galley~.";
                  style roman;
                  "";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (self.sjchold || self.sjmairlck || self.sjeroom || self.sjarmory) rfalse;
                  return PAG();
          ],
          sjsign false,
          sjchold false,
          sjeroom false,
          sjarmory false,
          sjmairlck false,
    has   static scenery;

! 09/23/06

  Object  -> sj_hatches "hatchway"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'aft' or 'port' or 'starboard' or 'fore' or 'forward' or 'door' or 'doors') return 0;
              if (w1 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhsj = false;
                  self.ahsj = false;
                  self.phsj = false;
                  self.sbhsj = false;
                  return 3;
              }
              w2 = NextWord();
              if (w1 == 'fore' or 'forward' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhsj = true;
                  self.ahsj = false;
                  self.phsj = false;
                  self.sbhsj = false;
                  return 3;
              }
              if (w1 == 'aft' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhsj = false;
                  self.ahsj = true;
                  self.phsj = false;
                  self.sbhsj = false;
                  return 3;
              }
              if (w1 == 'port' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhsj = false;
                  self.ahsj = false;
                  self.phsj = true;
                  self.sbhsj = false;
                  return 3;
              }
              if (w1 == 'starboard' && w2 == 'hatchway' or 'hatchways' or 'hatchway^s' or 'hatch' or 'door' or 'doors') {
                  self.fhsj = false;
                  self.ahsj = false;
                  self.phsj = false;
                  self.sbhsj = true;
                  return 3;
              }
              return 0;
          ],
          description [;
              if (self.fhsj) "The forward hatchway leads to the cargo hold.";
              if (self.ahsj) "The aft hatchway leads to the engine room.";
              if (self.phsj) "The port hatchway leads to the armory.";
              if (self.sbhsj) "The starboard hatchway leads to the main airlock.";
              "The hatchways here lie fore, aft, port and starboard.";
          ],
          before [;
              Attack:
                  return PDE();
              Close:
                  "In case of fire, this hatchway should be left open.";
              Enter, Exit:
                  "Please use normal navigation directions. FORWARD, AFT, PORT, and STARBOARD.";
              Open:
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          fhsj false,
          ahsj false,
          phsj false,
          sbhsj false,
    has   concealed static enterable;
