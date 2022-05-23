
! 08/16/06

  Movable autocoolant "big bag of Zrok(TM) Autocoolant"
    with  name 'big' 'bag' 'zrok' 'zrok(tm)' 'auto' 'coolant' 'autocoolant' 'case' 'slogan',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              if (self in al_gen) "he Autocoolant is placed upon the auxiliary power unit.";
              if (self in adar) {
                  print "he Autocoolant is keeping Captain Adar's temperature down, as it's placed upon ";
                  if (m_base.ch_maidens) {
                      print "her";
                  } else {
                      print "his";
                  }
                  " head.";
              }
              if (self.onforehead) "he Autocoolant is helping keep your temperature down, placed upon your head.";
              "he modern equivalent of the ancient ice pack, this features an endothermic gel
              first used in engineering applications. It's massively overdimensioned for medical
              purposes, but it's also very cheap, so it's widely used.";
          ],
          after [;
              Insert:
                  if (second == medkit) {
                      move self to medkit;
                      "You put the autocoolant back into the med kit.";
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(19);
          ],
          before [;
              Push, PushDir, Pull, Transfer:
                  if (self in al_gen && al_gen.ps_turnedon) "The Autocoolant is the only thing preventing the auxiliary power unit from overheating; you dare not remove it now.";
              PutOn:
                  if (self in player) {
                      if (second == sm_alelectric) "You can't put the Zrok(TM) Autocoolant on the auxiliary power unit from up here.";
                      if (second == al_gen) {
                          if (self hasnt general) {
                              give self general;
                              score = score + 5;
                          }
                          give self ~worn;
                          self.onforehead = false;
                          move self to al_gen;
                          "You put the bag of Zrok(TM) Autocoolant on top of the auxiliary power unit's casing.";
                      }
                      if (second == player) return CoolPlayer();
                      if (second == adar) return CoolAdar();
                  }
              Remove:
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in al_gen && al_gen.ps_turnedon) "The Autocoolant is the only thing preventing the auxiliary power unit from overheating; you dare not remove it now.";
                  if (self in adar) {
                      give self ~worn;
                      self.onforehead = false;
                      move self to player;
                      print "Captain Adar gives a slight shrug as you take the coolant off ";
                      if (m_base.ch_maidens) {
                          print "her";
                      } else {
                          print "his";
                      }
                      " forehead.";
                  }
                  if (self has worn) {
                      give self ~worn;
                      self.onforehead = false;
                      "You take the auto coolant off your forehead.";
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
                  give self ~worn;
                  self.onforehead = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == player) return CoolPlayer();
                      if (second == adar) return CoolAdar();
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) "You need to use the Autocoolant on someone.";
                  return PYC();
              Wear:
                  if (self in tc_shrine) return PYC();
                  if (self.onforehead) "The Autocoolant is already on your forehead doing its job.";
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  return CoolPlayer();
          ],
          onforehead false;
