
! ---------------------------------------------------------------------------- !
!       The HIDDEN COMPARTMENT. 04/20/06
!

  RoomShp hidden_compartment "Hidden Compartment"
    with  initial [;
              if (self.thinkset) {
                  self.thinkset = false;
                  thinkpos = 22;
              }
          ],
          description [;
              print "There's space in here for maybe half-a-dozen people, but it's not for
              the claustrophobic. It's designed as a last refuge in case of emergency, with
              a small EDS console built into the aft bulkhead.";
              if (ce_badge in h_s_eds) print " Inside the console is the Chief Engineer's ident badge.";
              print " There's also some basic communications equipment along with a few boxes
              of rations tucked in the back corner. Luckily, the console's still working,
              run off emergency power.^^";
              if (s_panel.sopen) "There's a panel here, open to the cargo hold.";
              else "There's a panel here, closed.";
          ],
          s_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go aft through the opening, or just type EXIT.",
          before [;
              HideRoom:
                  if (s_panel.sopen) {
                      s_panel.sopen = false;
                      "You close the panel, blocking you off from the rest of the ship.";
                  }
                  "You're already hiding.";
              Exit, SUp:
                  if (pland == (plimit+19)) {
                      thinkpos = 0;
                      pland++;
                  }
                  if (s_panel.sopen == false) {
                      s_panel.sopen = true;
                      print "(first opening the panel)^";
                  }
                  print "You crawl out of the hidden compartment.^";
                  PlayerTo(cargo_hold);
                  rtrue;
          ],
          thinkset true;

! 04/28/06

  RoomObj -> hiddenobj "hidden compartment"
    with  name 'hidden' 'small' 'compartment' 'ship' 'room',
          description [;
              <<Look hidden_compartment>>;
          ];

! 04/20/06

  Object  -> hs_panel "panel"
    with  name 'secret' 'panel',
          description [;
              if (s_panel.sopen) "The panel is moved aside, revealing an opening in the aft bulkhead.";
              "The panel is closed hiding you in this small compartment.";
          ],
          before [;
              Attack:
                    return PDE();
              Close, Pull:
                  if (s_panel.sopen) {
                      s_panel.sopen = false;
                      if (pland < (plimit+19)) "You close the panel, secure at last against the return of the pirates.";
                      "You close the panel, hiding behind it in this small compartment.";
                  }
                  "The panel is already closed.";
              Open, Take, Remove, Push, Pull:
                  if (s_panel.sopen) "The panel is already open.";
                  s_panel.sopen = true;
                  "You move the panel out of the way, revealing an opening in the aft bulkhead.";
          ],
    has   concealed static;

! 05/25/06

  Object  -> h_s_opening "opening"
    with  name 'small' 'opening',
          description [;
              if (s_panel.sopen) "It looks like there's a small opening in the aft bulkhead that goes to the cargo hold.";
              "It looks like the panel blocks the small opening in the aft bulkhead to the cargo hold.";
          ],
          before [;
              Enter:
                  <<Exit hidden_compartment>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 09/21/06

  Object  -> h_s_rations "rations"
    with  name 'ration' 'rations' 'meals' 'crate' 'crates' 'food' 'meal' 'mre' 'mres' 'box' 'boxes',
          description
              "The rations are standard military MREs. Meals, Ready-to-Eat, a low grade form
              of food that is mostly regarded as ~Meals Rejected by the Enemy~.",
          before [;
              Attack:
                  return PDE();
              Close:
                  "They're already closed.";
              Eat:
                  "You need to take one of the meals to do that.";
              Take, Remove, Open:
                  if (self.tknmre) "Your supplies should be sufficient.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  self.&name-->5 = '3132ph';
                  self.&name-->6 = '3133ph';
                  self.&name-->7 = '3134ph';
                  self.tknmre = true;
                  move hs_mre to player;
                  "You open the crate and take out one of the meals, reflecting on your training to always be prepared.";
              PushDir, Push, Pull:
                  "The rations are placed along the back bulkhead, and don't move around very easily.";
              Read:
                  "The lettering on the crates read: MREs, and your stomach convulses at the thought of what's inside.";
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the rations.";
                  POT();
                  style fixed;
                  print "MREs
                  ^Translation: Meal, Ready-to-Eat.";
                  style roman;
                  "";
          ],
          tknmre false,
    has   scenery static pluralname edible;

! 09/24/06

  Object  -> h_s_radio "basic communications equipment"
    with  name 'simple' 'radio' 'basic' 'communications' 'equipment',
          description
              "This is nothing more than a simple radio.",
          before [;
              Attack:
                  return PDE();
              FlipOff, SwitchOff:
                  "That's already off.";
              SwFlip, SwitchOn, Use, UseItem:
                  "There's no power going to the unit.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   scenery static;

! 02/07/08

  Object  -> h_s_eds "EDS console"
    with  name 'small' 'eds' 'console',
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (ce_badge in self)
                      "Shorted out in the destruction sequence, the EDS console no longer
                      works. Inserted into the console is the Chief Engineer's ident badge.";
                  "The EDS console is built into the aft bulkhead. Used to trigger the
                  equipment destruction sequence, which disables all ship systems, the console
                  takes a badge with Clearance Level: 3 or higher to operate.";
              FlipOff, SwitchOff:
                  return PSH();
              Read:
                  "The console has a short note: Insert badge, sequence will automatically activate.";
              SwFlip, SwitchOn, Use, UseItem:
                  if (ce_badge in player || (ce_badge in milpack && (milpack in player or hidden_compartment))) {
                      if (s_panel.sopen) {
                          s_panel.sopen = false;
                          print "(first closing the panel)^";
                      }
                      PirateLoot();
                      "Using the Chief Engineer's ident badge you start the equipment destruction
                      sequence. As the counter reaches zero and the panel shorts out, a shower of
                      sparks explodes, taking out the higher end electronics throughout the ship.
                      Darkness falls upon the room. A moment later you hear a small explosion;
                      it must be the Captain's ident badge as, shortly after, you hear the automatic
                      web netting snap back into place, securing the cargo into the corner of
                      the hold.
                      ^^Trapped in the darkness of this hidden room, you feel the ship enter gravity
                      again and land. It doesn't take long for the space pirates to open up the cargo
                      hatch and loot the ship. You hear them fan out, tearing out the engines, removing
                      navigation systems, and taking the main computer. There's a loud blast right before
                      they pull out the large crate, then silence. They must have finished their looting
                      and exited the plundered ship.
                      ^^After waiting a bit, you feel it's safe to leave the compartment.";
                  }
                  return PL2Auth();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static container open;
