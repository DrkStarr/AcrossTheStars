
! 09/23/06

  Movable halfshelter "half shelter"
    with  name 'half' 'shelter' 'tent',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "his is a simple chameleon tent designed to provide temporary shelter or concealment.
              When combined with another half-shelter, it makes for a small ~pup tent~.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(24);
          ],
          before [;
              Attack:
                    if (self in tc_shrine) return PYC();
                    return PDE();
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Open, Set, Use, UseItem:
                  if (self in player) "You can't do that, it takes two half shelters in order to create a tent.";
                  return PYC();
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
          ];
