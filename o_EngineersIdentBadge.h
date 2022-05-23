
! 09/18/06

  Movable ce_badge "Chief Engineer's ident badge"
    with  name 'chief' 'chief^s' 'chiefs' 'engineer^s' 'engineers' 'engineer' 'ident' 'badge',
          article "the",
          description
              "This is the Chief Engineer's ident badge. It looks much like yours, apart from the
              rank insignia. Unlike yours, this badge will authorize certain functions on the ship.",
          after [;
              Insert:
                  if (second == milpack) {
                      give milpack open;
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  move self to player;
                  if (second == main_computer) {
                      if (ident_badge in main_computer) "The Captain's ident badge is already here.";
                      "This badge isn't designed to be inserted into the computer.";
                  }
                  if (second == web_netting or ch_chipreader) return PL1Auth();
                  if (second == uniform) "The Chief Engineer's insignia would look out of place on a crewman's uniform.";
                  if (second == omni_trans) "The Chief Engineer's ident badge won't authorize any function within your OmniTrans.";
                  if (second == h_s_eds) <<SwitchOn h_s_eds>>;
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Insert:
                  if (self in player) {
                      if (second == flow_regulator) return PUB();
                      if (second == galley_closet) {
                          if (galley_closet has locked) {
                              second = noun;
                              <<Open galley_closet second>>;
                          }
                      }
                  }
              Read:
                  "It's a standard Xulthe'en Military I.D., with the Chief's name, rank and service number embossed on the back.
                  ^^Name: Wallace Grimes
                  ^Rank: Senior Chief
                  ^Service Number: 17530713-9280C";
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the badge.";
                  POT();
                  style fixed;
                  print "   ~Xulthe'en Military I.D.~
                  ^        Chief Engineer
                  ^^Name: Wallace Grimes
                  ^Rank: Senior Chief
                  ^Service Number: 17530713-9280C";
                  style roman;
                  "";
              Remove:
                  <<Take self>>;
              Take:
                  if (self in player) "You already have that.";
                  if (self in h_s_eds) "The electrical damage that shorted the console out has fused the badge, making it impossible to pull out.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in flow_regulator) {
                      move self to player;
                      "Even though it seems to be stuck, with a little force, you manage to pull it out.";
                  }
              Open:
                  if (self in h_s_eds) "It's no use, the badge is fused in there pretty good.";
                  if (self in flow_regulator) <<Take self>>;
              Use:
                  if (self in player) {
                      if (second == flow_regulator) return PUB();
                      if (second == web_netting or ch_chipreader) return PL1Auth();
                      if (second == h_s_eds) <<SwitchOn h_s_eds>>;
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ];
