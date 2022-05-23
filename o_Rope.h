
! 03/22/08

  Movable rope "frayed rope"
    with  name 'frayed' 'rope',
          description
              "With a good snap from the length of rope, it seems to retain most of its strength, frayed as it is.",
          before [;
              Climb:
                  "But it's not attached to anything.";
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
              Tie, Use:
                  if (second == cry_stand) return MkGrp();
                  if (second == deadp_obj or jagged_rock or dp_staircase)
                      "The rope won't hold on to anything by itself, you'll probably need some sort of hook tied to it to help you out.";
              Touch:
                  "As ruff to the touch the frayed rope is, it seems to have been made with great care, still retaining most of its strength.";
              UseItem:
                    if (self in player) return PYN();
                    return PYC();
          ];
