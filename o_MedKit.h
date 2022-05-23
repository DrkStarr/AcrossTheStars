
! 08/16/06

  Movable medkit "emergency med kit"
    with  name 'emergency' 'med' 'medicine' 'kit' 'medkit',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHi();
              "t's a standard issue kit, certified by the Imperial Safety Commission.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(17);
          ],
          before [;
              Open, Close:
                  if (self in tc_shrine) return PYC();
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
              Use, UseItem:
                  if (self in player) rfalse;
                  return PYC();
          ],
    has   container openable;
