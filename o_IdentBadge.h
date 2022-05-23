
! 04/18/06

  Movable ident_badge "Captain's ident badge"
    with  name 'captain' 'captains' 'captain^s' 'ident' 'identity' 'badge',
          article "the",
          description
              "This is the Captain's ident badge. It looks much like yours, apart from the
              rank insignia. Unlike yours, this badge will authorize any function on the ship.",
          after [;
              Insert:
                  if (second == main_computer) {
                      move self to player;
                      "The computer is useless since the ship is running off emergency power.";
                  }
                  if (second == omni_trans) {
                      move self to omni_trans;
                      "It's a snug fit, but you manage to insert the Captain's ident badge into the OmniTrans.";
                  }
                  if ((second == web_netting or ch_chipreader) && web_netting has on) {
                      give web_netting ~on;
                      web_netting.nettingon = false;
                      move ident_badge to web_netting;
                      "As you slide the Captain's ident badge into the reader, the display
                      changes to read, ~Manual override engaged.~";
                  }
                  if (second == milpack) {
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  if (second == galley_closet) {
                     move self to galley_closet;
                     "You put ", (the) self, " into the Captain's locker.";
                  }
                  move self to player;
                  if (second == uniform) "The Captain's insignia would look out of place on a crewman's uniform.";
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Insert:
                  if (second == galley_closet) {
                      if (galley_closet has locked) {
                          second = noun;
                          <<Open galley_closet second>>;
                      }
                  }
              Open:
                  return BadgePull(1);
              Pull:
                  return BadgePull(2);
              Read:
                  "It's a standard Xulthe'en Military I.D., with the Captain's name, rank and service number embossed on the back.
                  ^^Name: Leazar Ebe Yon
                  ^Rank: Captain
                  ^Service Number: 11530525-9280B";
              Remove:
                  <<Take self>>;
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the badge.";
                  POT();
                  style fixed;
                  print "   ~Xulthe'en Military I.D.~
                  ^      Transport Commander
                  ^^Name: Leazar Ebe Yon
                  ^Rank: Captain
                  ^Service Number: 11530525-9280B";
                  style roman;
                  "";
              Take:
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (main_computer.poweron) {
                      if (second == prybar) return BadgePull(2);
                      "As you try to pull the ident badge out of the main computer you receive a strong electrical
                      shock. A DNA scanner in the badge reader must have spotted that you're not the Captain.";
                  }
                  if (self in web_netting) {
                      give web_netting on;
                      move ident_badge to player;
                      web_netting.nettingon = true;
                      if (s_panel in cargo_hold) remove s_panel;
                      if (space_lock in cargo_hold) remove space_lock;
                      if (web_netting.nettingopen) {
                          large_crate.movedaft = false;
                          web_netting.nettingopen = false;
                          "As you pull the Captain's ident badge out of the chip reader the automatic
                          web netting kicks in, wrapping itself around the crate once again, securing
                          the cargo back in place.";
                      }
                      "Taken.";
                  }
                  if (self hasnt general) {
                      give self general;
                      score = score + 5;
                      StartDaemon(pirates_land);
                      move ident_badge to player;
                      "Taken.";
                  }
              Touch:
                  if (main_computer.poweron) {
                      "As you touch the ident badge you receive a strong electrical shock. A DNA scanner in the
                      badge reader must have spotted that you're not the Captain.";
                  }
              Use:
                  if (self in player) {
                      if (second == galley_closet && galley_closet has locked) {
                          give galley_closet ~locked;
                          "You unlock the Captain's locker.";
                      }
                      if (second == web_netting or ch_chipreader && web_netting has on) {
                          give web_netting ~on;
                          web_netting.nettingon = false;
                          move ident_badge to web_netting;
                          "As you slide the Captain's ident badge into the reader, the display
                          changes to read, ~Manual override engaged.~";
                      }
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ];
