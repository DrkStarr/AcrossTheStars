
! 08/16/06

  Movable firstaidwraps "first-aid wraps"
    with  name 'first' 'aid' 'first-aid' 'firstaid' 'wrap' 'wraps' 'bandage' 'bandages',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "he first-aid wraps are like any you've ever seen; just wrap them around a patient to help heal wounds.";
          ],
          article "some",
          after [;
              Insert:
                  if (second == medkit) {
                      move self to medkit;
                      "You put the first-aid wraps back into the med kit.";
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(18);
          ],
          before [;
              PutOn:
                  if (self in player) {
                      if (second == al_arm or sm_arm) {
                          if (player in sm_airlock) return PWM();
                          "You can't reach the hydraulic piston from down here.";
                      }
                      if (second == controlpanel or sm_controlpanel) {
                          if (player in sm_airlock) "You can't reach the control panel from up here.";
                          return PWM();
                      }
                      if (second == al_arm or sm_arm) return PWM();
                      if (second == cs_vent) {
                          if (player in sm_airlock) return PWM();
                          "You can't reach the ventilation shaft from down here.";
                      }
                      if (second == al_gen or sm_alelectric) {
                          if (player in sm_airlock) "You can't reach the auxiliary power unit from up here.";
                          return PWM();
                      }
                      if (second == player) {
                          move self to player;
                          "You don't want to waste these; you're not injured at the present moment.";
                      }
                      if (second == adar) return BandAdar();
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
                  if (self in player) {
                      if (second == player) "You don't want to waste these; you're not injured at the present moment.";
                      if (second == adar) return BandAdar();
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) "You need to use the first-aid wraps on someone.";
                  return PYC();
              Wear:
                  if (self in tc_shrine) return PYC();
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  "You don't want to waste these; you're not injured at the present moment.";
              Wrap:
                  if (second == adar) return BandAdar();
                  if (second == player) "You don't want to waste these; you're not injured at the present moment.";
                  "You need to wrap those around someone.";
              Tie:
                  if (second == adar) return BandAdar();
                  if (second == player) "You don't want to waste these; you're not injured at the present moment.";
                  "You need to tie those around someone.";
            ],
    has   pluralname;
