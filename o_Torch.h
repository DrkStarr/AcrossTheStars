
! 08/13/06

  Movable torch "torch"
    with  name 'torch' 'cold' 'dead' 'old',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (w_tunnel.hastorch) "It's a cold, dead, torch, gone out in this passage long ago.";
              if (self.onfire) {
                  if (player in secret_tunnel3) "The torch fights against a breeze that's coming from the southwest.";
                  if (player in tranquility_chamber) "The torch struggles to survive against the breeze that is in this room.";
                  "The torch blazes with newfound life.";
              }
              PHi();
              if (self.burned) "t's cold and dead, once again.";
              "t's a cold, dead, torch.";
          ],
          describe [;
              if (self in w_tunnel) rtrue;
          ],
          invent [;
              if (self.onfire) {
                  print "a torch (burning)";
                  rtrue;
              }
          ],
          after [;
              Insert:
                  if (second == milpack) {
                      if (self.onfire && ralckor.dead == false) {
                          move self to player;
                          "You might still need this important tool.";
                      }
                      give milpack open;
                      move self to milpack;
                      if (self.onfire) {
                          self.onfire = false;
                          give self ~light;
                          self.&name-->1 = 'cold';
                          self.&name-->2 = 'dead';
                          "You put the torch out before putting it into the field pack.";
                      }
                      "You put ", (the) self, " into the field pack.";
                  }
                  if (second == deadp_obj) {
                      if (ralckor.dead == false) {
                          move self to player;
                          "You might not want to lose such an important tool.";
                      }
                      move self to unholy_shrine;
                      if (self.onfire) {
                          self.onfire = false;
                          give self ~light;
                          self.&name-->1 = 'cold';
                          self.&name-->2 = 'dead';
                         "As you drop ", (the) self, " into the pit it goes out.";
                      }
                      "You drop ", (the) self, " into the pit.";
                  }
                  if (second == sr_liquid) {
                      remove self;
                      print "You drop ", (the) self, " into the acid, watching it dissolve into nothing, lost forever.^";
                      if (sandworm in small_room) {
                                print "^Suddenly";
                                return PSKill();
                      }
                      rtrue;
                  }
                  move self to player;
                  if (second == lc_beamoflight or lc_space) {
                      if (self.onfire) "The torch is already on fire.";
                      if (trans_crystal.tcinbeam) {
                          TorBurn();
                          "Carefully, you put the torch in the beam and move the crystal until you see
                          the torch start to smolder. A moment later, the smoldering becomes a full-blown
                          fire as the torch catches light.";
                      }
                      return PTI();
                  }
                  if (second == controlpanel or al_circuit) "That's too big to fit in there.";
                  if (second == sm_controlpanel) return PCR();
                  if (second == st3_sunlight) "The light in this room is not direct and just reflects off the walls.";
                  if (second == tc_sunlight) "The breeze makes it too hard to start a fire here.";
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          before [;
              Burn:
                  if (self in player) {
                      if (self.onfire) "The torch is already on fire.";
                      if (second == trans_crystal) {
                          if (player in cavern) {
                              TorBurn();
                              "You put the clear-red crystal into the beam of light and, as you'd
                              hoped, it has a focusing effect: the wide, bright circle on the floor
                              becomes a small dot. Carefully, you put the torch in the beam and move
                              the crystal until you see the torch start to smolder. A moment later,
                              the smoldering becomes a full-blown fire as the torch catches light.";
                          }
                          if (player in chasm or desert_crash) "The wind is blowing too strong to start a fire here.";
                          if (player in tranquility_chamber) "The breeze makes it too hard to start a fire here.";
                          "Not here, there's no direct light.";
                      }
                      if (second == nothing) "You need to light the torch with something.";
                      if (second == lc_beamoflight) return PTI();
                      print (The) second, " doesn't seem to do the job.^";
                      rtrue;
                  }
                  return PYC();
              Drop:
                  if (self notin player) "The torch is already here.";
                  self.tinbeam = false;
                  if (self.onfire && player in small_room && sandworm in small_room) return RemoveWorm(1);
                  if (self.onfire && (parent(player) == parent(sandworm))) return RemoveWorm(2);
                  if (player in w_tunnel) {
                      move self to w_tunnel;
                      "You put the torch back in its holder.";
                  }
                  if (player in unholy_shrine or deadly_pit && ralckor.dead == false) "You might not want to lose such an important tool.";
                  move self to location;
                  "Dropped.";
              Insert:
                  if (second == wt_holder) {
                      move self to w_tunnel;
                      "You put the torch back in the holder.";
                  }
              PutOn:
                  if (self in player) {
                      if (second == pedestal) return PedestalEnds(9);
                      if (second == us_altar && ralckor.dead == false) "You shouldn't leave that behind.";
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
                  w_tunnel.hastorch = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          if (ralckor.dead == false) "You might not want to lose such an important tool.";
                          move self to unholy_shrine;
                          if (self.onfire) {
                              self.onfire = false;
                              give self ~light;
                              self.&name-->1 = 'cold';
                              self.&name-->2 = 'dead';
                              "As you throw ", (the) self, " into the pit it goes out.";
                          }
                          "You throw ", (the) self, " into the pit.";
                      }
                      if (second == sandworm) {
                          print "The torch bounces off the spitter, inflicting no damage.^^Suddenly,";
                          return PSKill();
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == lc_beamoflight or lc_space) {
                          if (trans_crystal.tcinbeam) {
                              if (self.onfire) "The torch is already on fire.";
                              TorBurn();
                              "As you put the torch into the focused beam of light, it catches on fire.";
                          }
                          return PTI();
                      }
                      if (second == sandworm) {
                          if (self.onfire) {
                              "The spitter feels the approach of the flame and backs away. It can move pretty quickly
                              when it has to, and the two of you wind up chasing each other round the pool of acid.
                              Not wanting to stumble into it, you give up the chase.";
                          }
                      }
                      if (second == wt_holder) {
                          move self to w_tunnel;
                          "You put the torch back in the holder.";
                      }
                      rfalse;
                  }
                  "You don't have that.";
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
              Wave:
                  if ((parent(player) == parent(sandworm)) && self.onfire) {
                      if (sandworm.threatened) return BrnSpit();
                      "You wave the torch in front of the spitter, keeping the creature at bay.";
                  }
          ],
          burned false,
          onfire false,
          tinbeam false;
