
! 09/20/07

  Movable hs_mre "Meal, Ready-to-Eat"
    with  name 'ready-to-eat' 'food' 'meal' 'brown' 'package' 'mre',
          description
              "The brown package is your standard military MRE. Meals, Ready-to-Eat, a low grade form
              of food that is mostly regarded as ~Meals Rejected by the Enemy~.",
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(37);
          ],
          before [;
              Eat, Open, UseItem:
                  if (self.pchungry) {
                      remove self;
                      "In ordinary circumstances, you'd never touch this stuff. However, these are far
                      from being normal circumstances, and you gobble the rations down as if they were
                      gourmet treats. Afterwards, you feel a little queasy, but also a bit less hungry.";
                  }
                  "You're not hungry enough yet.";
              Give:
                  if (self in player) {
                      if (second == adar) "Adar smiles and says, ~Thanks, but I'll manage. My stomach has been through enough today.~";
                  }
              Read:
                  "The lettering on the package reads: MRE.";
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the package.";
                  POT();
                  style fixed;
                  print "MRE
                  ^Translation: Meal, Ready-to-Eat.";
                  style roman;
                  "";
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
          ],
          pchungry false,
    has   edible;
