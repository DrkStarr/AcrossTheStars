
! 09/23/06

  Movable journal "journal"
    with  name 'high' 'priests' 'priest^s' 'priest' 'journal' 'protective' 'leather',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out a";
                  } else {
                      print "A";
                  }
              } else {
                  print "A";
              }
              print " small journal, bound in protective leather, ";
              if (e_beacon.eb_notseen) print "that ";
              print "is ";
              if (JrnlTest()) "about half way filled with a script-based handwriting on pages brittle with time.";
              "partially filled with a script-based handwriting, missing a few chapters.";
          ],
          invent [;
              print "a journal";
              rtrue;
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(25);
          ],
          before [;
              Close:
                  if (self.jrnopn) {
                      self.jrnopn = false;
                      "Carefully you close ", (the) self, ", making sure none of the pages fall out.";
                  }
                  "That's already closed.";
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
              Insert:
                  if (second == milpack) {
                      if (self.jrnopn) {
                          self.jrnopn = false;
                          print "(first closing the journal)^";
                      }
                  }
                  if (second == omni_trans) {
                      move self to player;
                      <<Scan self>>;
                  }
              Open:
                  if (self.jrnopn) {
                      print "As you look through";
                  } else {
                      self.jrnopn = true;
                      print "As you open";
                  }
                  print " the journal, you notice that it's filled with a script that's unfamiliar to you.";
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
                  if (omni_trans notin player) return PNO();
                  if (second == nothing or omni_trans) {
                      print "You can SCAN CHAPTER 1 - 5 IN JOURNAL or continue reading the entire journal. Press Q to quit at anytime.^^";
                      POT();
                      if (oldpage in self) {
                          JournalC1();
                          if (PageBreak()) jump end;
                          print "^";
                      }
                      if (blchpage in self) {
                          JournalC2();
                          if (PageBreak()) jump end;
                          print "^";
                      }
                      if (brntpage in self) {
                          JournalC3();
                          if (PageBreak()) jump end;
                          print "^";
                      }
                      JournalC4();
                      if (PageBreak()) jump end;
                      print "^";
                      JournalC5();
                      .end;
                      rtrue;
                  }
                  return PNO();
              ScanC1:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (oldpage in self) {
                      if (self notin player) {
                          move self to player;
                          PFT();
                      }
                      if (omni_trans notin player) return PNO();
                      POT();
                      return JournalC1();
                  }
                  "It looks like the first chapter is missing from the journal.";
              ScanC2:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (blchpage in self) {
                      if (self notin player) {
                          move self to player;
                          PFT();
                      }
                      if (omni_trans notin player) return PNO();
                      POT();
                      return JournalC2();
                  }
                  "It looks like the second chapter is missing from the journal.";
              ScanC3:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (brntpage in self) {
                      if (self notin player) {
                          move self to player;
                          PFT();
                      }
                      if (omni_trans notin player) return PNO();
                      POT();
                      return JournalC3();
                  }
                  "It looks like the third chapter is missing from the journal.";
              ScanC4:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (omni_trans notin player) return PNO();
                  POT();
                  return JournalC4();
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
                  POT();
                  return JournalC5();
              ScanC6, ScanC7, ScanC8, ScanC9, ScanC10, ScanC11, ScanC12, ScanC13, ScanC14, ScanC15, ScanC16:
                  "There are only five chapters in ", (the) self, ".";
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
                  adar.foundjournal = true;
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
          jrnopn false,
          ch1read false,
          ch2read false,
          ch3read false,
          ch4read false,
          ch5read false,
    has   container open;
