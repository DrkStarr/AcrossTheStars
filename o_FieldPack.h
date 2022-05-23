
! 09/22/06

  Movable milpack "field pack"
    with  name 'field' 'backpack' 'pack',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out a field pack that";
                  } else {
                      print "The field pack";
                  }
              } else {
                  print "The field pack";
              }
              " is used in off-world exploration, allowing teams to carry back
              any number of samples for research scientists to examine.";
          ],
          describe [;
              if (cavern.mpmove) rtrue;
          ],
          after [;
              Insert:
                  if (second == uniform or player) {
                      give self worn;
                      move self to uniform;
                      "You put the field pack on.";
                  }
                  if (second == galley_closet) {
                      move self to galley_closet;
                      "You put ", (the) self, " into the Captain's locker.";
                  }
                  if (second == deadp_obj) {
                      move self to unholy_shrine;
                      "You drop ", (the) self, " into the pit.";
                  }
                  move self to player;
                  if (second == milpack) "You can't put the field pack into itself.";
                  if (second == m_maidens or m_guards) "Now that's just perverted.";
                  if (second == controlpanel or al_circuit) "That's too big to fit in there.";
                  if (second == sm_controlpanel) return PCR();
                  L__M(##Insert, 2, noun);
                  rtrue;
              PutOn:
                  if (second == uniform or player) {
                      give self worn;
                      move self to uniform;
                      "You put the field pack on.";
                  }
                  if (second == pedestal) return PedestalEnds(22);
                  give self ~worn;
          ],
          before [;
              Attack:
                  if (self in tc_shrine) return PYC();
                  return PDE();
              Disrobe:
                  if (self in uniform) {
                      give self ~worn;
                      move self to player;
                      "You take off the field pack.";
                  }
              Drop:
                  if (player in outside_airlock or ontopofship) return PLD();
                  if (self in uniform) {
                      give self ~worn;
                      move self to location;
                      "(first taking off the field pack)
                      ^Dropped.";
                  }
              PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Remove:
                  if (self in uniform) {
                      give self ~worn;
                      move self to player;
                      "You take off the field pack.";
                  }
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) return L__M(##Take, 12);
                  TPackScore();
                  give self ~worn;
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (cavern.mpmove) {
                      cavern.mpmove = false;
                      move self to player;
                      "You dare to get close to the ralckor, as vines whip about, grabbing the field pack.";
                  }
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (second == uniform or player) {
                      if (self notin player) PFT();
                      give self worn;
                      move self to uniform;
                      "You put the field pack on.";
                  }
                  rfalse;
              Wear:
                  if (self in tc_shrine) return PYC();
                  if (self has worn) "You're already wearing that!";
                  if (self notin player) PFT();
                  TPackScore();
                  if (uniform in spacesuit || uniform in mal_spacesuit) "You can't put that on over the deep-space suit.";
                  give self worn;
                  move self to uniform;
                  "You put the field pack on.";
          ],
          detaken true,
          scrtaken false,
    has   container openable;
