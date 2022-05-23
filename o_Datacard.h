
! 04/12/06

  Movable datacard "datacard" proxtar
    with  name 'datacard' 'data' 'card',
          description [;
              PHi();
              if (self in proxtar) {
                  if (self.engoff) print "t's a standard datacard, and should have plenty of information about the pirate ship";
                  else print "t's a standard datacard, and should tell the Captain all he needs to know about the mysterious mass";
                  ". Your OmniTrans can read it, but first you'll have to get it out of the prox-tar.";
              }
              print "t's a standard datacard, compatible with all standard card readers (such as the one in your OmniTrans)";
              if (proxtar.shutdown) ". You just hope your novel prox-tar shutdown procedure hasn't scrambled the data.";
              ".";
          ],
          after [;
              Attack:
                  if (self in tc_shrine) return PYC();
                  return PDE();
              Insert:
                  if (OmniTest() && second == omni_trans) {
                      move self to player;
                      "Both slots are already filled.";
                  }
                  if (ident_badge in omni_trans && second == omni_trans) {
                      move self to player;
                      return PDatacard();
                  }
                  if (second == omni_trans) {
                      move self to player;
                      "The card slides snugly into the slot, but all that comes up on the screen is a simple message: ~Captain's Eyes Only. Authorized ident required.~";
                  }
                  if (second == videogame) {
                      move self to player;
                      "Only cubits will fit inside.";
                  }
          ],
          before [;
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Pull:
                  if (self in player) rfalse;
                  <<Take self>>;
              Read:
                  "You need to put it in the OmniTrans to do that.";
              Remove:
                  <<Take self>>;
              Scan:
                  if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) {
                       PFT();
                       return PBS();
                  }
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the datacard.";
                  if (self in proxtar) "You need to take the datacard out of the prox-tar to be able to scan it.";
                  if (self in player) {
                      if (og_datacard in omni_trans && ident_badge in omni_trans) "Both slots are already filled.";
                      if (ident_badge in omni_trans) return PDatacard();
                      "The card slides snugly into the slot, but all that comes up on the screen is a simple message: ~Captain's Eyes Only. Authorized ident required.~";
                  }
                  "You need to insert the datacard into the OmniTrans to do that.";
              Take:
                  if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (proxtar.power) "You can't take the datacard while the prox-tar is powered up; with the state it's in right now, you'd scramble the information beyond repair.";
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (self.dcfrstkn) {
                      self.dcfrstkn = false;
                      move datacard to player;
                      radar_room.note_taken = false;
                      give proxtar ~open;
                      give proxtar ~container;
                      "Taken.";
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
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          daemon [;
              piratecount = piratecount - 25;
              if (piratecount == 0) {
                  pattack = 2;
                  StopDaemon(self);
                  StartDaemon(pirates_board);
              }
          ],
          read false,
          engoff false,
          dcfrstkn true;
