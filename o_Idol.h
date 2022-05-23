
! 08/08/06

  Movable statue "hand-sized idol"
    with  name 'statue' 'idol' 'crude' 'parody' 'poorly-baked' 'poorly' 'baked' 'clay' 'man' 'figure' 'hand-sized',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "he idol is a crude parody of a man, about hand-sized, made of poorly-baked clay.";
          ],
          after [;
              Insert:
                  if (second == deadp_obj) {
                      remove self;
                      score = score - 5;
                      "As you drop ", (the) self, " into the pit you hear it shatter into a million pieces, as you realize you've just done something really stupid.";
                  }
          ],
          before [;
              Push, PushDir, Pull, Transfer:
                  if (sandworm in s_tunnel) return PSB();
                  if (self in pedestal) return DthIdol(1);
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          PushIdol();
                          rtrue;
                      } else {
                          move self to unholy_shrine;
                          "You push ", (the) self, " off the altar. Luckily it doesn't break.";
                      }
                  }
              PutOn, Use:
                  if (self in player) {
                      if (second == pedestal) {
                          if (sandworm in s_tunnel) return PSB();
                          move self to pedestal;
                          move stunnel_sdoor to s_tunnel;
                          "Carefully, you place the idol on the pedestal. As you let go of it,
                          you hear a deep rumbling. The noise gets louder and louder, and you
                          see stones start to fall away from the eastern wall, first small
                          pieces and then larger and larger rocks. Dust envelops you, and when
                          it eventually clears you see that a low passageway has opened up to
                          the east.";
                      }
                      if (second == us_altar) {
                          if (huge_boulder.boulderfalling) "You try to place the idol back on the altar, but it's too hard due to the rumbling and shaking.";
                      }
                  }
              Remove:
                  <<Take self>>;
              Take:
                  if (sandworm in s_tunnel) return PSB();
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (self in pedestal) return DthIdol(0);
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self.notaken) {
                      self.notaken = false;
                      score = score + 5;
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  adar.haveidol = true;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          remove self;
                          score = score - 5;
                          "As you throw ", (the) self, " into the pit you hear it shatter into a million pieces, as you realize you've just done something really stupid.";
                      }
                  }
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          notaken true;
