
! 04/16/06

  Object  wrench "universal tool"
    with  name 'wrench' 'universal' 'tool' 'spanner',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out the universal tool. W";
                  } else {
                      print "W";
                  }
              } else {
                  print "W";
              }
              "here in ancient times technicians needed a box full of spanners, wrenches and the like, now all these functions have been built into this one tool.";
          ],
          article "a",
          after [;
              Attack:
                  return PDE();
              Drop:
                  move self to player;
                  "No good crewman would ever leave their universal tool behind.";
              Insert:
                  if (second == milpack) {
                      give milpack open;
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  move self to player;
                  "No good crewman would ever leave their universal tool behind.";
              PutOn:
                  move self to player;
                  "No good crewman would ever leave their universal tool behind.";
          ],
          before [;
              Drop:
                  if (player in outside_airlock or ontopofship) return PLD();
              Give:
                  if (self in player) "No good crewman would ever give away their universal tool.";
              Insert:
                  if (second == smallcrate or sm_scrate) "No good crewman would ever leave their universal tool behind.";
              PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Remove:
                  <<Take self>>;
              Take:
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
              ThrowAt:
                  if (self in player) return PFD();
              Use:
                  if (self in player) {
                      if (second == armory_gate) "The security gate is already open.";
                      if (second == al_arm) "You can't fix the hydraulic piston from here.";
                      if (second == sm_arm) {
                          if (smallcrate has general) {
                              if (al_arm.fixed) "The hydraulic piston has already been fixed.";
                              if (bolt in player or milpack or sm_arm) return FixBolt();
                              "You need the bolt to fix the hydraulic piston.";
                          }
                          "You can't fix the hydraulic piston from here, try pushing the crate underneath it.";
                      }
                      if (second == bolt) {
                          if (player in sm_airlock) {
                              if (smallcrate has general) {
                                  if (al_arm.fixed) "The hydraulic piston has already been fixed.";
                                  if (bolt in player or milpack or sm_arm) return FixBolt();
                                  "You need to need the bolt to fix the hydraulic piston.";
                              }
                              "You can't fix the hydraulic piston from here, try pushing the crate underneath it.";
                          }
                          "You can't fix the hydraulic piston from here.";
                      }
                      if (second == web_netting) {
                          second = self;
                          <<Open web_netting (second)>>;
                      }
                      if (second == proxtar) {
                          if (proxtar.power) "As you try to turn off the unit, a powerful electrical shock hits you, knocking you back. Clearly, the problem is worse than usual this morning.";
                      }
                      if (second == circuit_breaker) {
                          if (circuit_breaker has open) "The panel already has been opened.";
                          "You might be able to pry open the panel, but not with the universal tool. It's too small to get any leverage.";
                      }
                      if (second == engine) "They're not broken.";
                      if (second == galley_closet) {
                          if (galley_closet has open) "That's already open.";
                          "You can't open the locker with the universal tool, only the Captain's ident badge can do that.";
                      }
                      if (second == plaque) "Securely fastened to the bulkhead, it would take a lot more than a universal tool to get the ship's plaque off.";
                      if (second == tiedown_claps) {
                          if (web_netting.nettingon == false) <<Open web_netting>>;
                          return PNetFOpen();
                      }
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ];
