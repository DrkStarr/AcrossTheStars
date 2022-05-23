
! 04/23/06

  Object  uniform
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'your' or 'uniform' or 'clothes' or 'pocket' or 'clear-plastic' or 'clear' or 'plastic' or 'boots' or 'shirt') return 0;
              w2 = NextWord();
              if (w1 == 'your' && w2 == 'uniform' or 'clothes') {
                  self.pocket = false;
                  return 2;
              }
              if (w1 == 'your' or 'clear-plastic' or 'clear' or 'plastic' && w2 == 'pocket') {
                  self.pocket = true;
                  return 2;
              }
              if (w1 == 'uniform' or 'clothes') {
                  self.pocket = false;
                  return 1;
              }
              if (w1 == 'pocket') {
                  self.pocket = true;
                  return 1;
              }
              return 1;
          ],
          description [;
              if (spacesuit has worn) "You can't see your uniform with the space suit over it.";
              if (self has worn) {
                  if (self.pocket) {
                      if (p_badge in uniform) "Your personal ident badge is tucked tightly in the clear-plastic pocket of your uniform.";
                      "The pocket to your uniform is made of a clear plastic.";
                  }
                  print "It's a standard issue Xulthe'en crewman's uniform. Gray, plain, drab, but the civs still dig it!";
                  if (p_badge in uniform && omni_trans has worn) {
                      " Tucked away in a small clear-plastic pocket is your personal ident badge, while your OmniTrans hangs comfortably over your shoulder.";
                  } else {
                      if (p_badge in uniform) " Tucked away in the clear-plastic pocket is your personal ident badge.";
                      if (omni_trans has worn) " Your OmniTrans hangs comfortably over your shoulder.";
                  }
                  new_line;
                  rtrue;
              } else {
                  if (uniform in player) "It's a standard crewman's uniform.";
                  "A folded gray uniform lies on your bunk.";
              }
          ],
          describe [;
              "^You can see your uniform on the edge of the berth here.";
          ],
          article "a",
          short_name "your uniform",
          after [;
              Drop, PutOn:
                  move self to player;
                  "You really should put on your uniform. Can't go running around here in your skivvies.";
          ],
          before [;
              Attack:
                    return PDE();
              Disrobe:
                  if (self has worn) "That would be inappropriate, and would break codes of conduct.";
              Give:
                  "(first taking the uniform off)
                  ^Taking off your uniform breaks a lot of codes of conduct. I wouldn't try that.";
              LookUnder:
                  if (self in player) rfalse;
                  if (self.lunder) "You find your OmniTrans underneath the folded uniform.";
                  self.lunder = true;
                  move omni_trans to crew_quarters;
                  "You find your OmniTrans underneath the folded uniform.";
              PutOn:
                  if (second == player) {
                      if (self in player) <<Wear self>>;
                      PFT();
                      <<Wear self>>;
                  }
              Remove:
                  if (self has worn) "That would be inappropriate, and would break codes of conduct.";
                  <<Take self>>;
              Search:
                  if (self in player) {
                      if (self has worn) {
                          if (p_badge in uniform) "There's a personal ident badge tucked tightly in your pocket.";
                          "You don't find anything unusual.";
                      }
                      "You need to put on your uniform first.";
                  }
                  return PYC();
              Take:
                  if (self in player) "You already have that.";
                  if (self in spacesuit or mal_spacesuit) "You need to take the space suit off first.";
                  move self to player;
                  remove berth_uniform;
                  if (self.lunder && omni_trans.transtaken == false) "Taken.";
                  move omni_trans to crew_quarters;
                  if (self.lunder) print "As you take the uniform, you see your OmniTrans is still lying on the bunk.^^";
                  else print "Taking the uniform uncovers your OmniTrans.^^";
                  <<Wear self>>;
              Use, UseItem:
                  if (self in player) rfalse;
                  return PYC();
              Wear:
                  if (self has worn) "You're already wearing that!";
                  if (player in crew_quarters) {
                      if (self notin player) {
                          move self to player;
                          PFT();
                      }
                      give self worn;
                      give self ~proper;
                      self.short_name = "uniform";
                      remove skivvies;
                      remove berth_uniform;
                      move p_badge to uniform;
                      if (omni_trans in player) {
                      } else {
                          omni_trans.transtaken = false;
                          move omni_trans to player;
                      }
                      give omni_trans worn;
                      "Putting on your uniform, you make sure that everything is squared away.
                      As you tuck in your shirt and cross-lace your boots, you feel proud to
                      be in the service of the Empire. Also, the last time you weren't up to
                      par, the Captain chewed you out for an hour, landing you this week of extra duty.
                      ^^You sling the OmniTrans over your shoulder, and you're ready to go.";
                  }
                  "It's too cramped in here for that; you'll need to get out of your berth first.";
          ],
          lunder false,
          pocket false,
          booklookat false,
    has   proper clothing container open;
