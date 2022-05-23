
! 09/18/07

  Movable bolt "bolt"
    with  name 'main' 'bolt' 'bolts',
          description [;
              if (al_arm.fixed) "The main bolt is screwed back into the hydraulic piston.";
              if (self in al_arm or sm_arm) "The main bolt looks a little loose, but it's nothing that your trusty universal tool couldn't fix.";
              "One of the main bolts from the hydraulic piston.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(33);
          ],
          before [;
              Fix, Turn:
                  if (player in sm_airlock) {
                      if (smallcrate has general) {
                          if (al_arm.fixed) "The hydraulic piston has already been fixed.";
                          if (wrench in player or milpack) return FixBolt();
                          "You need to tighten the bolt with something.";
                      }
                      "You can't fix the hydraulic piston from here, try pushing the crate underneath it.";
                  }
                  if (player in air_lock) "You can't fix the hydraulic piston from here.";
              Insert:
                  if (second == sm_arm) {
                      if (smallcrate has general) {
                          if (wrench in player or milpack) return FixBolt();
                          move self to sm_arm;
                          "You put the bolt back into the hydraulic piston, but without your universal tool you can't tighten it.";
                      }
                      "You can't fix the hydraulic piston from here, try pushing the crate underneath it.";
                  }
              Remove:
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in al_arm) "You can't reach that from here.";
                  if (al_arm.fixed) "You've just fixed it; why undo your good work now?";
                  if (self in player) "You already have that.";
                  if (self in sm_arm && player in sm_airlock) {
                      if (smallcrate has general) {
                      } else {
                          "You can't reach the bolt from here, try pushing the crate underneath hydraulic piston.";
                      }
                  }
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (self in sm_arm && player in sm_airlock) {
                      move self to player;
                      "Taken.";
                  }
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == sm_arm) {
                          if (smallcrate has general) {
                              if (al_arm.fixed) "The hydraulic piston has already been fixed.";
                              if (wrench in player or milpack) return FixBolt();
                              "You need to tighten the bolt with something.";
                          }
                          "You can't fix the hydraulic piston from here, try pushing the crate underneath it.";
                      }
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ];
