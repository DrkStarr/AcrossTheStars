
! 09/23/06

  Movable knife "survival knife"
    with  name 'survival' 'knife' 'blade',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "he survival knife is 7 segments long, and is a standard military issue utility blade.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(23);
          ],
          before [;
              Attack:
                  if (self in tc_shrine) return PYC();
                  return PDE();
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Insert:
                  if (second == player && self in player) return PKY();
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
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                           move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) rfalse;
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ];
