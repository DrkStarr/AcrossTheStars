
! 09/08/06

  Movable -> trans_crystal "clear-red crystal"
    with  name 'clear-red' 'clear' 'red' 'crystal' 'focal' 'point' 'magnifying' 'glass',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              "he crystal is about as big as your hand, and flawlessly clear. When you
              look through it, everything seems a bit bigger and rose colored: it acts
              like a crude magnifying glass.";
          ],
          after [;
              Insert:
                  if (second == deadp_obj) {
                      move self to unholy_shrine;
                      "You drop ", (the) self, " into the pit.";
                  }
                  if (second == cry_stand) {
                      move self to cry_stand;
                      "You place ", (the) self, " into ", (the) second, ".";
                  }
                  if (second == milpack) {
                      give milpack open;
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  move self to player;
                  if (second == lc_beamoflight or lc_space) {
                      if (torch.onfire) "The torch is already on fire.";
                      if (torch.tinbeam) {
                          TorBurn();
                          "You put the clear-red crystal into the beam of light and, as you'd
                          hoped, it has a focusing effect: the wide, bright circle on the floor
                          becomes a small dot. Carefully, you put the torch in the beam and move
                          the crystal until you see the torch start to smolder. A moment later,
                          the smoldering becomes a full-blown fire as the torch catches light.";
                      }
                      self.tcinbeam = true;
                      lc_space.&name-->2 = 'dot';
                      "You put the clear-red crystal into the beam of light and, as you'd
                      hoped, it has a focusing effect: the wide, bright circle on the floor
                      becomes a small dot.";
                  }
                  if (second == m_maidens or m_guards) "Now that's just perverted.";
                  if (second == controlpanel or al_circuit) "That's too big to fit in there.";
                  if (second == sm_controlpanel) return PCR();
                  if (second == st3_sunlight) "The light in this room is not direct and just reflects off the walls.";
                  if (second == tc_sunlight) {
                      "You put the clear-red crystal into the sunlight and, as you'd
                      hoped, it has a focusing effect: the wide, pattern on the floor
                      becomes a small dot.";
                  }
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          before [;
              Drop:
                  self.tcinbeam = false;
              PutOn:
                  if (self in player) {
                      if (second == pedestal) return PedestalEnds(4);
                  }
              Search:
                  if (self in player) "Even though the crystal itself is transparent, when you look through it everything is blurry and red.";
                  return PYC();
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
                  if (self in cry_stand) {
                      move self to player;
                      "As you take the crystal, you can't help but notice how much the three-pronged stand looks like a hook.
                      With a bit of rope, you probably could turn it into some sort of makeshift grappling hook.";
                  }
              Touch:
                  if (self in player) "The crystal feels cool in your hand.";
                  return PYC();
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == lc_beamoflight or lc_space) {
                          if (torch.tinbeam) {
                              if (torch.onfire) "The torch is already on fire.";
                              TorBurn();
                              "As you put the clear-red crystal into the beam of light, it focuses the beam, catching the torch on fire.";
                          }
                          self.tcinbeam = true;
                          lc_space.&name-->2 = 'dot';
                          "As you put the clear-red crystal into the beam of light, it focuses the light into a small dot on the floor.";
                      }
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          tcinbeam false,
          beamscore true;
