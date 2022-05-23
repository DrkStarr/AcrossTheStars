
! 04/28/06

   Movable detonator "atomaton detonator"
     with  name 'atomaton' 'detonator' 'warning' 'label' 'small' 'timed' 'bomb' '0273ph' '0272ph',
           article "an",
           before [;
               Attack:
                   if (self in tc_shrine) return PYC();
                   return PDE();
               Drop:
                   if (player in outside_airlock or ontopofship) return PLD();
               PutOn:
                   if (player in outside_airlock or ontopofship) return PLD();
                   if (self in player) {
                       if (second == pedestal) return PedestalEnds(8);
                   }
               Examine, Search, Read:
                   if (self in tc_shrine && tc_shrine.fieldon) return PSL();
                   AtomatonLabel();
                   "^Underneath, some wag has scrawled, ~If you lose your legs, don't come running to us!~.";
               Insert:
                   if (self in player) {
                       if (second == chasmobj) {
                           if (atomdet > 0) move self to chasmobj;
                           else remove self;
                           "You drop ", (the) self, " into the chasm, lost forever.";
                       }
                   }
                   if (second == chasmobj) "You need to be holding ", (the) self, " before you can put it into something else.";
               Scan:
                   if (omni_trans notin player) "You need to use an OmniTrans to scan the detonator.";
                   POT();
                   return AtomatonLabel();
               SwFlip, SwitchOn, Push, UseItem, Set:
                   if (self in tc_shrine) return PYC();
                   if (atomdet > 0) "The atomaton detonator is already activated.";
                   if (atomdet == 0 && player in chasm) {
                       self.&name-->7 = 'red';
                       self.&name-->8 = 'light';
                       StartDaemon(self);
                       if (self in player) return PAD();
                       move self to player;
                       PFT();
                       return PAD();
                   }
                   if (player in desert or dunes or m_base)
                       "The sand may be annoying, but blowing it into even smaller bits is not
                       the answer.";
                   if (self.adcavern)
                       "You don't really want to bring thousands of tons of rock down on your
                       head, do you? Even if you could get outside before the explosion, you'd
                       still be blasted with rocks and dust.";
                   print "The label does say that it shouldn't be detonated in a confined space, and this ";
                   if (player in pantheon) {
                       print "room";
                   } else {
                       print "ship";
                   }
                   " certainly qualifies. Even if you got away before it exploded, the blast wave
                   would still kill you.";
               FlipOff, SwitchOff:
                   if (atomdet > 0) {
                       atomdet = 0;
                       StopDaemon(self);
                       self.&name-->7 = '0273ph';
                       self.&name-->8 = '0272ph';
                       "You quickly shut off the atomaton detonator before it can explode.";
                   }
                   "The atomaton detonator is already deactivated.";
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
               ThrowAt:
                   if (self in player) {
                       if (second == deadp_obj) {
                           move self to unholy_shrine;
                           "You throw ", (the) self, " into the pit.";
                       }
                       if (second == chasmobj) {
                           if (atomdet > 0) move self to chasmobj;
                           else remove self;
                           "You throw ", (the) self, " into the chasm, lost forever.";
                       }
                       if (second == ralckor) "You should probably turn it on first.";
                   }
               Use:
                   if (self in tc_shrine) return PYC();
                   "Just try USE DETONATOR.";
           ],
           daemon [;
               atomdet++;
               switch (atomdet) {
                   3: StopDaemon(self);
                      if (parent(self) == player || parent(self) == parent(player) || parent(parent(self)) == player || parent(parent(self)) == parent(player) || (parent(self) == milpack && (parent(milpack) == player || parent(parent(milpack)) == player))) {
                          deadflag = 1;
                          "^The timer on the atomaton detonator reaches zero. For an unreal instant
                          everything is still, then the booming explosion. You're briefly aware of a
                          searing fireball, of your limbs being torn from your body before, mercifully,
                          you cease to be aware of anything at all.";
                      } else {
                          ! Tells the player how they hear the blast

                          print "^You feel the mountainside collapse as the atomaton detonator explodes.";
                          if (player in cavern) {
                              print " A cloud of dust and small pieces of rock puffs through the opening in the eastern wall, but not enough to do you any harm (though your tailor might disagree).^";
                          } else {
                              new_line;
                          }

                          ! Removes tangible objects that might be in room
                          RemoveTObj();

                          ! Removes room objects
                          if (parent(self) == chasm || parent(parent(self)) == chasm) {
                              score = score + 5;
                              chasm.blown = true;
                          }

                          ! Removes self
                          adar.bgnoff = true;
                          if (parent(self) == milpack) {
                              remove self;
                              remove milpack;
                              rtrue;
                          } else {
                              remove self;
                              rtrue;
                          }
                      }
               }
           ],
           adcavern false;
