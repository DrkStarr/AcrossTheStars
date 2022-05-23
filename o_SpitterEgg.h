
! 02/16/08

  Movable s_egg "egg"
    with  name 'spitter^s' 'egg',
          description [;
              print "The small egg moves and shifts ";
              if (self in player) print "as you hold it";
              if (self in milpack) print "inside the pack";
              ", the babies must be close to hatching.";
          ],
          after [;
              Insert:
                  if (second == sr_liquid) {
                      ResetEgg();
                      "Snatching up the egg before it falls into the acid, the spitter returns it to the nest.";
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(38);
          ],
          before [;
              Attack, Kick, Open:
                  print "As you crack open the egg,";
                  return PBDeth();
              Drop:
                  if (parent(player) == parent(sandworm)) {
                      ResetEgg();
                      print "Snatching up the egg before it hits the ground, the spitter ";
                      if (player in small_room) "returns it to the nest.";
                      "darts out of the room.";
                  }
              Give:
                  if (self in player) {
                      if (second == ralckor) return RalcDeth(1);
                      if (second == sandworm) {
                          ResetEgg();
                          print "Snatching up the egg very carefully in her mandibles, the spitter ";
                          if (player in small_room) "returns it to the nest.";
                          "darts out of the room.";
                      }
                  }
              Show:
                  if (second == ralckor) return RalcDeth(2);
                  if (second == sandworm)
                      "Mandibles move faster as the spitter utters a series of short clicks. Suddenly
                      she darts for the egg, as your reflexes kick in, burning the creature with the torch.
                      Recoiling with pain, the spitter looks for the next opening.";
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
                      if (second == ralckor) return RalcDeth(1);
                      if (second == sandworm) {
                          ResetEgg();
                          print "The spitter snatches the egg out of the air before it can even hit the ground, ";
                          if (player in small_room) "returning it to the nest.";
                          "darting out of the room.";
                      }
                  }
              Touch:
                  "You feel the egg move and shift as you touch it, the babies must be close to hatching.";
              Use:
                  if (self in player) {
                      if (second == ralckor) return RalcDeth(1);
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          eggscrd true;
