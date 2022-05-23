
! 05/11/06

  Movable p_badge "personal ident badge"
    with  name 'personal' 'ident' 'badge',
          description [;
              PBadgeLook();
          ],
          after [;
              Insert:
                  if (second == uniform) {
                      move self to uniform;
                      "It's a tight fit, but you manage to tuck your personal ident badge back into the pocket of your uniform.";
                  }
                  move self to player;
                  if (second == milpack) {
                      "You might lose it by putting it into the field pack. If you couldn't identify
                      yourself at a spaceport or something, they'd lock you in the brig, and maybe,
                      maybe do a retina neural activation scan.";
                  }
                  if (second == web_netting or ch_chipreader) return PL1Auth();
                  if (second == main_computer) {
                      if (ident_badge in main_computer) "The Captain's ident badge is occupying the scanner.";
                      "Your badge isn't designed to be inserted into the computer.";
                  }
                  if (second == omni_trans) "Your badge won't authorize any function within your OmniTrans.";
                  if (second == m_maidens or m_guards) "Now that's just perverted.";
                  if (second == sm_controlpanel) return PCR();
                  "You don't want to lose your ident badge. If you couldn't identify yourself
                  at a spaceport or something, they'd lock you in the brig, and maybe, maybe
                  do a retina neural activation scan.";
          ],
          before [;
              Attack:
                  return PDE();
              Drop, PutOn, Give, ThrowAt:
                  if (second == uniform) {
                      if (self in uniform) "Your personal ident badge is already in the pocket of your uniform.";
                      move self to uniform;
                      "It's a tight fit, but you manage to tuck your personal ident badge back into the pocket of your uniform.";
                  }
                  move self to player;
                  if (player in outside_airlock or ontopofship) return PLD();
                  "You don't want to lose your ident badge. If you couldn't identify yourself
                  at a spaceport or something, they'd lock you in the brig, and maybe, maybe
                  do a retina neural activation scan.";
              Insert:
                  if (self in player) {
                      if (second == flow_regulator or h_s_eds) return PL2Auth();
                      if (second == galley_closet) {
                          if (galley_closet has locked) {
                              second = noun;
                              <<Open galley_closet second>>;
                          }
                      }
                  }
              Read:
                  PBadgeLook();
                  rtrue;
              Remove:
                  <<Take self>>;
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the badge.";
                  POT();
                  style fixed;
                  print "   ~Xulthe'en Military I.D.~
                  ^Radar Communications Specialist
                  ^
                  ^Name: An Darington
                  ^Rank: Crewman Third Class
                  ^Service Number: 47531022-9280F";
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
              Use:
                  if (self in player) {
                      if (second == web_netting or ch_chipreader) return PL1Auth();
                      if (second == flow_regulator) return PL2Auth();
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
              Wear:
                  if (self in uniform) "Your personal ident badge is already in the pocket of your uniform.";
                  move self to uniform;
                  "It's a tight fit, but you manage to tuck your personal ident badge back into the pocket of your uniform.";
          ];
