
! 07/21/07

  Movable blchpage "bleached page"
    with  name 'bleached' 'page' 'pages',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out t";
                  } else {
                      print "Bleached from being in the sun all these years, t";
                  }
              } else {
                  print "Bleached from being in the sun all these years, t";
              }
              "he script-based handwriting is still visible on a page brittle with time.";
          ],
          after [;
              Insert:
                  if (second == journal) {
                      move self to journal;
                      "Carefully you place ", (the) self, " back into the journal, closing the book, securing it in place.";
                  }
                  if (second == omni_trans) {
                      move self to player;
                      <<Scan self>>;
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(32);
          ],
          before [;
              Consult, Read:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  print "This form of script is unfamiliar to you.";
                  if (omni_trans in player or milpack) " Perhaps your OmniTrans can translate it.";
                  new_line;
                  rtrue;
              Scan:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNP();
                  if (second == nothing or omni_trans) {
                      POT();
                      return JournalC2();
                  }
                  return PNP();
              ScanC1:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNP();
                  POT();
                  return JournalC2();
              ScanC2, ScanC3, ScanC4, ScanC5, ScanC6, ScanC7, ScanC8, ScanC9, ScanC10, ScanC11, ScanC12, ScanC13, ScanC14, ScanC15, ScanC16:
                  "There is only one chapter in ", (the) self, ".";
              Show:
                  if (self in player) {
                      if (second == adar) return PShowJournal();
                      if (second == lc_vampires) return OrbDeath(2);
                      rfalse;
                  }
                  "You need to take ", (the) self, " before showing it to someone.";
              Remove:
                  <<Take self>>;
              Take:
                  if (self in journal) "You should leave ", (the) self, " safe and secure within the journal.";
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
              ThrowAt:
                  if (self in journal) "You should leave ", (the) self, " safe and secure within the journal.";
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
