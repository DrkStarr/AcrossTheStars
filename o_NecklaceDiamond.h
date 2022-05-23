
! 09/25/06

  Movable diamond "diamond necklace"
    with  name 'diamond' 'necklace',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHi();
              "t's a pure diamond necklace, probably used for some ceremonial purpose.";
          ],
          describe [;
              if (self.ftseen) {
                  if (brntpage in secret_tunnel3) "^There's a burnt page on top of a diamond necklace here, lying amongst the rubble.";
                  "^There's a diamond necklace here amongst some rubble.";
              }
          ],
          after [;
              Insert:
                  if (second == milpack) {
                      give self ~worn;
                      give milpack open;
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  if (second == deadp_obj) {
                      give self ~worn;
                      move self to unholy_shrine;
                      "You drop ", (the) self, " into the pit.";
                  }
          ],
          before [;
              Push, PushDir, Pull, Transfer:
                  if (tc_shrine.fieldon == false) {
                      move self to tranquility_chamber;
                      tc_shrine.fieldon = true;
                      return PTP(noun);
                  }
                  if (self in tc_npedestal or tc_spedestal or tc_epedestal or tc_wpedestal) {
                      if (pedestalpos >= 1) {
                          move self to tranquility_chamber;
                          return PedPushNck(noun);
                      }
                  }
              PutOn, Use:
                  if (self in player) {
                      if (second == player) {
                          if (self has worn) "You're already wearing that!";
                          give self worn;
                          "You put ", (the) self, " on around your neck.";
                      }
                      if (second == pedestal) return PedestalEnds(15);
                      give self ~worn;
                      if (pedestalpos == 3) {
                          switch(diamondcount) {
                              1: if (second == tc_npedestal) {
                                     move self to tc_npedestal;
                                     tc_shrine.fieldon = false;
                                     return PPC();
                                 }
                              2: if (second == tc_spedestal) {
                                      move self to tc_spedestal;
                                     tc_shrine.fieldon = false;
                                     return PPC();
                                 }
                              3: if (second == tc_epedestal) {
                                     move self to tc_epedestal;
                                     tc_shrine.fieldon = false;
                                     return PPC();
                                 }
                              4: if (second == tc_wpedestal) {
                                     move self to tc_wpedestal;
                                     tc_shrine.fieldon = false;
                                     return PPC();
                                 }
                          }
                      }
                      if (second == tc_npedestal or tc_spedestal or tc_epedestal or tc_wpedestal) {
                          if (pedestalpos >= 1) {
                              move self to tranquility_chamber;
                              return PedPutNck(noun);
                          }
                          move self to second;
                          print "You put the diamond necklace on ", (the) second, ".^";
                          rtrue;
                      }
                      rfalse;
                  }
                  "You don't have that.";
              Show:
                  if (self in player) {
                      if (second == lc_vampires) return OrbDeath(3);
                      rfalse;
                  }
                  "You need to take ", (the) self, " before showing it to someone.";
              Remove:
                  <<Take self>>;
              Take:
                  if (self has worn) {
                      if (InventTotal() >= PMAX_WEIGHT + 1) {
                          if (milpack in player or uniform) {
                              InventMove(1);
                              give self ~worn;
                              "You take ", (the) self, " off from around your neck.";
                          } else {
                              return L__M(##Take, 12);
                          }
                      }
                      give self ~worn;
                      "You take ", (the) self, " off from around your neck.";
                  }
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
                  if (tc_shrine.fieldon == false) {
                      move self to player;
                      tc_shrine.fieldon = true;
                      return PTC(noun);
                  }
                  if (self in tc_npedestal or tc_spedestal or tc_epedestal or tc_wpedestal) {
                      if (pedestalpos >= 1) {
                          move self to player;
                          return PedTakNck(noun);
                      }
                  }
                  self.ftseen = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          give self ~worn;
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Touch:
                  return PST();
              UseItem:
                  if (self in player) return PYN();
                  "You don't have that.";
              Wear:
                  return WearNeck();
          ],
          ftseen true;
