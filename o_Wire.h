
! 07/18/07

  Movable cwire
    with  name 'broken' 'copper' 'wire' 'strand' 'strands',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self.cwrntkn) "This piece of copper wire must have fallen out when the pirates cut into the harnesses.";
              PHi();
              "t's a small piece of copper wire.";
          ],
          short_name "piece of copper wire",
          after [;
              Insert:
                  if (CtoC()) rtrue;
              PutOn:
                  if (second == pedestal) return PedestalEnds(35);
          ],
          before [;
              Insert:
                  if (second == cs_wire) return PWB();
              Search:
                  "There's not much to look at.";
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
                      "Grabbing onto the copper wire, you pull it out of the control panel.";
                  }
                  self.cwrntkn = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Tie:
                  if (second == cs_wire) return PWB();
              Use:
                  if (self in player) {
                      if (second == cs_wire) return PWB();
                      if (CtoC()) rtrue;
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          cwrntkn true,
          cwscore true;
