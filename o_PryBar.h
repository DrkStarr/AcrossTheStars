
! 09/19/06

  Movable prybar "pry bar"
    with  name 'pry' 'bar' 'prybar',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHi();
              "t's a solid stainless steel bar about two feet long. Bent round to a wide point, creating a lever at one end.";
          ],
          describe [;
              if (self.pbartaken) rtrue;
          ],
          after [;
              Insert:
                  if (second == circuit_breaker) {
                      move self to player;
                      if (circuit_breaker has open) "The panel has already been opened.";
                      give circuit_breaker open;
                      "With a good pull on the pry bar you manage to open the circuit breaker panel revealing the Chief Engineer's ident badge.";
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(21);
          ],
          before [;
              Drop, PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
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
                  self.pbartaken = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == armory_gate) "The security gate is already open.";
                      if (second == circuit_breaker) {
                          if (circuit_breaker has open) "The panel has already been opened.";
                          <<Open circuit_breaker self>>;
                      }
                      if (second == large_crate) {
                          if (web_netting.nettingon) "You can't access the crate since it's secured within the net.";
                          "No matter how hard you try, you can't open the crate with the pry bar.";
                      }
                      if (second == galley_closet) {
                          if (galley_closet has open) "That's already open.";
                          "As you try to pry open the locker, the pry bar slips away, scratching the steel.";
                      }
                      if (second == web_netting or tiedown_claps && web_netting.nettingopen == false) {
                          "The pry bar is useless against ", (the) second, "; the pirates would have the
                          cargo by now if this were not true.";
                      }
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          pbartaken true;
