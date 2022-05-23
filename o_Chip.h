
! 07/18/07

  Movable ochip
    with  name 'operating' 'chip' '8729ph',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self.destroy) {
                  PHd();
                  "he operating chip is designed to start the hatch mechanism when the
                  button is pressed, but it looks like this one's operating days are over:
                  harsh burn marks scar the face of the blown chip. However, thanks to some
                  disreputable friends in your younger days, you still remember how to hotwire
                  these: you just have to bypass the chip with a little electrical wire and the
                  mechanism should be permanently activated.";
              }
              PHd();
              "his chip starts the hatch mechanism when the button is pressed. Thanks to some disreputable
              friends in your younger days, you still remember how to hotwire these: you just have to bypass
              the chip with a little electrical wire and the mechanism should be permanently activated.";
          ],
          short_name "operating chip",
          after [;
              Insert:
                  if (OCtoC()) rtrue;
              PutOn:
                  if (second == pedestal) return PedestalEnds(30);
          ],
          before [;
              Fix:
                  if (self.destroy) "It's beyond repair.";
              Insert:
                  if (second == omni_trans) "That's not designed to fit in there.";
              Search:
                  if (self.destroy) "The chip looks useless, burnt with blown circuitry.";
                  "The operating chip is in good condition.";
              ShortOut:
                  if (cwire in self) "The short has already been created.";
                  if (self in controlpanel || player in air_lock) {
                      if (cwire in player or milpack) {
                          if (cwire.cwscore) {
                              cwire.cwscore = false;
                              score = score + 5;
                          }
                          move cwire to controlpanel;
                          return PBC();
                      }
                      "You don't have anything suitable to create the short.";
                  }
                  if (player in sm_airlock) "You need to get off the crate to do that.";
                  "You need to short out the circuitry instead.";
              Remove:
                  <<Take self>>;
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
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (self in controlpanel) {
                      move self to player;
                      print "With a good strong tug, you pull the ";
                      if (self.destroy) print "blown ";
                      "operating chip out of the control panel.";
                  }
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (OCtoC()) rtrue;
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          destroy false;
