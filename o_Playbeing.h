
! 04/28/06

  Movable playbeing "Playbeing magazine"
    with  name 'playbeing' 'trashy' 'porn' 'magazine' 'article' 'articles',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "his is the latest issue of Playbeing magazine, a trashy porn rag that's sparsely laced
              with a few decent articles.";
          ],
          before [;
              Drop:
                  if (player in outside_airlock or ontopofship) return PLD();
              PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
                  if (self in player) {
                      if (second == radar) {
                          move self to player;
                          "You wouldn't want to block the view of the radar, now would you?";
                      }
                      if (second == pedestal) return PedestalEnds(5);
                  }
              Read, UseItem:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (playbeing in player) {
                      pblook++;
                      switch (pblook) {
                          1: "The magazine has an article that briefly covers the issue of inter-dimensional travel through wormholes, but fails to mention that such things are unstable.";
                          2: "This issue has a nice layout of a hot Flebeon brunette, with three breasts, that goes on to say that she would like to see the ~untouched~ given a place of their own to live.";
                          3: "The article here goes into the issue of offsetting an over weighted shipment with helium balloons.";
                          4: pblook = 0;
                             "There's a spread in here of a well-hung Xulthe'en male that feels the Empire should quit wasting its credits on space exploration. In his own words, ~Don't we have enough?~";
                      }
                  } else {
                      return PYC();
                  }
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
          ];
