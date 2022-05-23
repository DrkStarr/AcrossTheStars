
! 02/27/09

  Movable torntome "torn tome"
    with  name 'leather' 'book' 'of' 'lydin' 'bible' 'heavy' 'torn' 'tome',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self notin player) {
                  move self to player;
                  PFT();
              }
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out that a";
                  } else {
                      print "A";
                  }
              } else {
                  print "A";
              }
              " torn tome still bound together, brittle with time, is written in some sort of code
              using ones and zeros, probably binary, filling four chapters here.";
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(28);
          ],
          before [;
              Close:
                  "The tome is burnt and can't be closed.";
              Consult, Read, Open:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  print "As you browse through its pages, it looks like this book is written
                  in some sort of code using ones and zeros, probably binary. Each chapter starts
                  off with a symbol, but the code is indecipherable.";
                  if (omni_trans in player or milpack) " Perhaps your OmniTrans can translate it.";
                  new_line;
                  rtrue;
              Insert:
                  if (second == omni_trans) {
                      move self to player;
                      <<Scan self>>;
                  }
              Scan:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  if (second == nothing or omni_trans) {
                      print "You can SCAN CHAPTER X, or continue reading the entire book. Press Q to quit at anytime.^^";
                      BookLC5();
                      if (PageBreak()) jump end;
                      print "^";
                      BookLC6();
                      if (PageBreak()) jump end;
                      print "^";
                      BookLC7();
                      if (PageBreak()) jump end;
                      print "^";
                      BookLC8();
                      if (PageBreak()) jump end;
                      .end;
                      rtrue;
                  }
                  return PNO();
              ScanC5:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  return BookLC5();
              ScanC6:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  return BookLC6();
              ScanC7:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  return BookLC7();
              ScanC8:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  return BookLC8();
              Show:
                  if (self in player) {
                      if (second == adar) return PShowTome();
                       if (second == lc_vampires) return OrbDeath(1);
                      rfalse;
                  }
                  "You need to take ", (the) self, " before showing it to someone.";
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
                  adar.foundtome = true;
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
          ];
