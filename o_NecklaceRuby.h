
! 08/16/06

  Movable ruby "ruby necklace"
    with  name 'red' 'ruby' 'necklace',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHi();
              "t's a blood red ruby necklace, probably used for some ceremonial purpose.";
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
                      if (second == pedestal) return PedestalEnds(10);
                      give self ~worn;
                      if (pedestalpos == 2) {
                          switch(rubycount) {
                              1: if (second == tc_npedestal) {
                                     pedestalpos = 3;
                                     move self to tc_npedestal;
                                     print "As you put the ruby necklace on ", (the) second,
                                     ", each pedestal in the chamber sinks down a few inches.^";
                                     rtrue;
                                 }
                              2: if (second == tc_spedestal) {
                                     pedestalpos = 3;
                                     move self to tc_spedestal;
                                     print "As you put the ruby necklace on ", (the) second,
                                     ", each pedestal in the chamber sinks down a few inches.^";
                                     rtrue;
                                 }
                              3: if (second == tc_epedestal) {
                                     pedestalpos = 3;
                                     move self to tc_epedestal;
                                     print "As you put the ruby necklace on ", (the) second,
                                     ", each pedestal in the chamber sinks down a few inches.^";
                                     rtrue;
                                 }
                              4: if (second == tc_wpedestal) {
                                     pedestalpos = 3;
                                     move self to tc_wpedestal;
                                     print "As you put the ruby necklace on ", (the) second,
                                     ", each pedestal in the chamber sinks down a few inches.^";
                                     rtrue;
                                 }
                          }
                      }
                      if (second == tc_npedestal or tc_spedestal or tc_epedestal or tc_wpedestal) {
                          if (pedestalpos >= 1) {
                              move self to tranquility_chamber;
                              return PedPutNck(noun);
                          }
                          move self to second;
                          print "You put the ruby necklace on ", (the) second, ".^";
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
          ];
