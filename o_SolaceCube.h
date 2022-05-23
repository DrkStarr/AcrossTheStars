
! 08/16/06

  Movable solace_cube
    with  name 'small' 'black' 'cube' '4287ph',
          short_name "small black cube",
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self.shimmering) {
                  PHt();
                  "he cube seems to shimmer now, showing faint signs of life every now and then.";
              }
              PHi();
              if (player in m_base or chasm or desert_crash or crashed_ship or air_lock or sm_airlock) "t's small, about one inch across, and impossibly black: it seems to suck in light.";
              "t's small, about one inch across, and impossibly black: it seems to suck in light. It must have been very important to the cult that once lived here.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(20);
          ],
          before [;
              Eat:
                  "Small as it is, it could get stuck in your throat. Better hold on to it.";
              Give:
                  if (second == lc_vampires) return SpiritDeath();
              Remove:
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
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
                  if (self hasnt general) {
                      give self general;
                      score = score + 5;
                      move self to player;
                      "As you pick up the small black cube, a feeling of peace washes over your body.";
                  }
              Show, Use:
                  if (self in player) {
                      if (second == lc_vampires) return SpiritDeath();
                      rfalse;
                  }
                  "You don't have that.";
              ThrowAt:
                  if (self in player) {
                      if (second == lc_vampires) return SpiritDeath();
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                      rfalse;
                  }
                  "You don't have that.";
              UseItem:
                  if (self in player) return PYN();
                  "You don't have that.";
          ],
          shimmering false;
