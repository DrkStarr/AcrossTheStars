
! 02/01/07

  Movable zipchip "zipchip"
    with  name 'zip' 'zipchip',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self notin player && self notin datapad && self notin omni_trans) {
                  move self to player;
                  PFT();
              }
              if (self in datapad) {
                  PHt();
                  "he zipchip is inserted into the data pad.";
              }
              if (self in omni_trans) {
                  PHt();
                  "he zipchip is inserted into the OmniTrans.";
              }
              PHi();
              "t's a small memory stick for portable devices. The five-zero imprinted at the bottom stands for fifty zettabytes.";
          ],
          after [;
              Insert:
                  if (second == datapad) {
                      move self to datapad;
                      "You insert ", (the) self, " into the data pad.";
                  }
                  if (second == omni_trans) {
                      move self to omni_trans;
                      print "As you insert ", (the) self, " into the OmniTrans it automatically translates the data.^^";
                      return PReadout();
                  }
                  if (second == controlpanel or al_circuit) {
                      move self to player;
                      return PDP();
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(27);
          ],
          before [;
              Read:
                  if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self in omni_trans) {
                      return PReadout();
                  }
                  "A small five-zero is imprinted on the bottom of the chip.";
              Scan:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (omni_trans notin player) return PNO();
                  if (self notin omni_trans) {
                      move self to omni_trans;
                      print "(first inserting the zipchip into the OmniTrans)^";
                  }
                  return PReadout();
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
                  if (self in datapad && datapad.dpstchon) {
                      datapad.dpstchon = false;
                      give datapad ~light;
                      print "(first shutting off the data pad)^";
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
                      if (second == controlpanel or al_circuit) return PDP();
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) rfalse;
                  return PYC();
          ];
