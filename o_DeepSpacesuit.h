
! 02/18/07

  Object  mal_spacesuit "deep-space suit"
    with  name 'deep' 'deep-space' 'deepspace' 'space' 'suit' 'spacesuit' 'helm' 'helmet' 'hood',
              description [;
              PSD();
              if (self.malopn) "open.";
              "closed.";
          ],
          after [;
              Disrobe:
                  move uniform to player;
              Insert:
                  move self to player;
                  if (second == milpack) "The space suit is too bulky to fit into that.";
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          describe [;
              if (self in main_airlock) rtrue;
          ],
          before [;
              Close:
                  if (self in player && self has worn) {
                      if (self.malopn) {
                          self.malopn = false;
                          "With the helm closed, the suit switches over to the internal air scrubbers.
                          You're now enclosed in a totally self-contained environment.";
                      }
                      "The helm to the deep-space suit is already closed.";
                  }
                  "You need to put the deep-space suit on.";
              Disrobe:
                  if (player in outside_airlock or ontopofship) "You are insane. You'd explode if you took off your space suit now.";
                  if (player in main_airlock && ma_panel.pressure == false) "You are insane. You'd suffocate if you took off your space suit now.";
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Open:
                  if (self in player && self has worn) {
                      if (player in outside_airlock or ontopofship) "You don't want to do that, you'd expose yourself to the vacuum of space.";
                      if (self.malopn) "The helm to the deep-space suit is already open.";
                      self.malopn = true;
                      "You open the helm to the deep-space suit.";
                  }
                  "You need to put the deep-space suit on.";
              Remove:
                  if (self has worn) {
                      if (player in outside_airlock or ontopofship) "You are insane. You'd explode if you took off your space suit now.";
                      if (player in main_airlock && ma_panel.pressure == false) "You are insane. You'd suffocate if you took off your space suit now.";
                      give self ~worn;
                      move uniform to player;
                      "You take off the deep-space suit.";
                  }
                  <<Take self>>;
              Take:
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
              Use, UseItem:
                  if (self in player) rfalse;
                  return PYC();
              Wear:
                  if (self has worn) "You're already wearing that!";
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  TPackSuit();
                  give self worn;
                  move uniform to self;
                  return PYM();
          ],
          malopn true,
    has   clothing container open;
