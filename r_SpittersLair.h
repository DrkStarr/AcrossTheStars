
! ---------------------------------------------------------------------------- !
!       The SPITTER'S LAIR. 04/26/06
!

  Room    small_room "Spitter's Lair"
    with  description [;
              if (sandworm in self) {
                  if (itakegg == 3) {
                      print "The eye-watering mixture is nothing compared to the furious chattering of
                      the large widow-weave spitter. Sensing the egg, she's frustrated, only wanting to
                      return it to the nest.";
                  } else {
                      print "The first thing that hits you is the smell: an eye-watering mix of acid and rotten eggs,
                      coming from a heap of half-digested mush lying in a pool of acid in the center of the floor,
                      presided over by a large widow-weave spitter.";
                  }
                  if (TorchOn()) {
                      PSMItm();
                      print "^^By the leaping torchlight, you see that the ralckor is not the spitter's only victim:
                      at the far back of the chamber, in the middle of a large web covered with smaller eggs, you can
                      see a roughly humanoid shape, coated in some sticky beige substance. ";
                      if (self.smfirefst) {
                          self.smfirefst = false;
                          print "You assume this will be the spitter's next meal, once it has polished off the ralckor.
                          ^^With a sick sensation in the pit of your stomach, you see the shape move slightly and make a
                          moaning sound; whatever it is, it's not quite dead yet. What a truly awful way to die.";
                      } else {
                          print "A few of the eggs are even out of the range of the spitter.";
                      }
                      "^^The spitter is keeping its distance from you, wary of the torch's flame. Two tunnels lead out of here: a fairly wide tunnel to the north and a rather smaller one to the southeast.";
                  }
                  thinkpos = 15;
                  if (self.smdaemonstart) {
                      self.smdaemonstart = false;
                      StartDaemon(self);
                  }
                  RSMItm();
                  if (self.smdisfst)
                      print " When you can bring yourself to look more closely, you see the unmistakable teeth
                      of a ralckor in the mix, though even they're succumbing to the acid. In a day or so there
                      will literally be nothing left of the ralckor that must once have lived here.";
                  print "^^The chamber is large, but it's hard to make out much else in the dim light that spills
                  in through the entrance tunnel. You can, however, make out the muffled sound of another creature,
                  somewhere in the darkness. The only way out you can see is the way you came in, back to the north.^";
                  if (self.smdisfst) {
                      self.smdisfst = false;
                      "^Spitter's are known for their voracious appetites, and there's not much left of the ralckor; hang around too long and you'll be next.";
                  }
                  rtrue;
              }
              print "Even though the spitter's gone the pungent aroma of rotten eggs still
              permeates the room, coming from a heap of half-digested mush lying in a pool of
              acid in the center of the floor.";
              if (TorchOn()) {
                  PSMItm();
                  print "^^At the back of the chamber, you can ";
                  if (adar has general) print "still see the remains of Adar's prison, glistening in the torchlight";
                  else print "see a roughly humanoid shape, coated in some sticky beige substance";
                  ". As well as the passage to the north, you can now see that there is also a small
                  passageway in the southeast corner, leading off into the darkness.";
              } else {
                  RSMItm();
                  print "^^The chamber is large, but it's hard to make out much else in the dim light that spills
                  in through the entrance tunnel. ";
                  if (adar has general) "The only way out you can see is the way you came in, back to the north.";
                  "You can, however, make out the muffled sound of another creature, somewhere in the darkness.
                  The only way out you can see is the way you came in, back to the north.";
              }
          ],
          n_to [;
              <<Exit self>>;
          ],
          se_to [;
              if (sandworm in self) {
                  if (itakegg == 3) "As you turn towards the tunnel, the spitter cuts you off, blocking it, before you can head southeast.";
                  if (sandworm.threatened) {
                      sandworm.threatened = false;
                      StopDaemon(sm_eggs);
                      sattack=0;
                      print "When you look away from the egg the spitter strikes, only to miss as you exit the room.^";
                      return deadly_pit;
                  }
                  if (TorchOn()) {
                      print "You sidle slowly past the spitter, keeping it at bay with the torch,
                      until you finally reach the safety of the passage.^";
                      return deadly_pit;
                  }
                  rfalse;
              }
              if (adar has general) {PAF(); MoveAdar(14);}
              return deadly_pit;
          ],
          cant_go [;
              if (sandworm in self) {
                  if (TorchOn()) "You can only go north or southeast.";
                  "You can only go north.";
              }
              "You can only go north or southeast.";
          ],
          before [;
              Exit:
                  StopDaemon(self);
                  sandworm_attack = 0;
                  self.smdaemonstart = true;
                  if (sandworm in self) {
                      if (itakegg == 3) {
                          move sandworm to w_tunnel;
                          print "Wanting to get the egg back, the spitter follows you into the tunnel.^";
                      } else {
                          if (sandworm.threatened) {
                              sandworm.threatened = false;
                              StopDaemon(sm_eggs);
                              sattack=0;
                              print "When you look away from the egg the spitter strikes, only to miss as you exit the room.^";
                          } else {
                              if (TorchOn()) {
                                  print "Carefully, waving the torch in front of you to keep the spitter at bay,
                                  you back out of the chamber and back up the passage.^";
                              } else {
                                  print "Narrowly avoiding the spitter's strike, you make it out of the room.^";
                              }
                          }
                      }
                  }
                  if (adar has general) {PAF(); MoveAdar(3);}
                  PlayerTo(w_tunnel);
                  rtrue;
              Listen:
                  if (adar has general) "Dead silence.";
                  if (self.spitmad) "The spitter chatters nervously.";
                  print "You can hear a low moaning sound coming from the ";
                  if (TorchOn()) "humanoid shape in the corner of the room.";
                  "darkness.";
              Smell:
                  "As you inhale, the stench of rotten eggs penetrates you.";
          ],
          daemon [;
              sandworm_attack++;
              if (sandworm_attack >= 2) {
                  print "^Suddenly,";
                  return PSKill();
              }
          ],
          spitmad false,
          smdisfst true,
          smfirefst true,
          finalqstn false,
          adarquestion false,
          smdaemonstart true;

! 04/29/06

  RoomObj -> sr_obj "lair"
    with  name 'lair' 'room',
          description [;
              <<Look small_room>>;
          ],
          before [;
              Search:
                  if (Spitter()) "You can't get past the spitter in order to search the room.";
          ];

! 02/13/08

  Object  -> sm_cobweb "tangled cobwebs"
    with  name 'tangled' 'cobweb' 'cobwebs' 'web' 'webs' 'netting' 'nest' 'wiry' 'strand' 'strands',
          describe [;
              if (small_pearl in small_room && small_pearl.pnhidden) {
                  print "^On the floor";
                  if (sandworm in small_room) print ", out of the range of the spitter";
                  ", lies a pearl necklace.";
              }
              rtrue;
          ],
          before [;
              Attack:
                  <<Attack sr_substance>>;
              Burn:
                  <<Burn sr_substance>>;
              Cut:
                  <<Cut sr_substance second>>;
              Eat, Taste:
                  if (Spitter()) return PBA();
                  "Chewy, but the meal synthesizer's produced worst.";
              Examine:
                  print "A mess of wiry strands ";
                  if (adar has general) print "make";
                  else print "secure a humanoid shape in the back, making";
                  print " up a tangled cobweb ";
                  if (adar has general) print "in the back";
                  else print "that covers the sticky beige substance, which shudders and groans";
                  print ". Woven ";
                  if (adar has general) print "into this netting";
                  else print "around the shape";
                  ", many small eggs move and shift as they grow and mature in the nest.";
              Open:
                  if (adar has general) "You've already freed Adar.";
                  if (Spitter()) return PBA();
                  "You're going to have to cut them with something in order to do that.";
              Search:
                  if (Spitter()) return PBA();
                  <<Examine self>>;
              Take, Remove, PushDir, Push, Pull:
                  if (Spitter()) return PBA();
                  "The spitter's web would surely tie up your hands, making it impossible to handle anything else.";
          ],
    has   static edible pluralname;

! 04/26/06

  Object  -> sm_dralc "half-digested mush"
    with  name 'old' 'dead' 'ralckor' 'mush' 'heap' 'half-digested' 'half' 'digested',
           before [;
              Examine, Search:
                  "It looks like this use to be a ralckor, the only way you can tell is by the teeth; everything
                  else has been turned into an icky brown sludge. Even the teeth are well on their way.";
               Taste, Take, Remove, PushDir, Push, Pull:
                     "Now that's just nasty.";
            ],
    has   static scenery;

! 08/06/07

  Object  -> sr_liquid "acidic liquid"
    with  name 'pungent' 'acid' 'acidic' 'liquid' 'liquids' 'pool' 'of' 'mixture' 'mix' 'eye-watering',
          before [;
              Burn:
                  if (TorchOn() && sandworm in small_room) return RemoveWorm(0);
                  if (TorchOn()) {
                      TorchOut();
                      move torch to small_room;
                      "As you put the torch into the pool of acid, the liquid smothers the fire out.";
                  }
                  "You have nothing to burn the liquid with.";
              Examine:
                  if (Spitter()) "A pool of pungent acid is currently turning the once-proud ralckor into the spitter's dinner.";
                  "A pool of pungent acid is consuming the once-proud ralckor.";
              Search, Touch:
                  "As you touch the acidic liquid it burns you, burrowing into your flesh.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static concealed container open;

! 05/03/06

  Object  -> sr_substance "substance"
    with  name 'sticky' 'beige' 'substance' 'excretion' 'goo' 'cocoon' 'brown' 'prison' 'remains',
          before [;
              Attack:
                  if (adar has general) "You beat on the remaining goo for a while, working off your aggression.";
                  if (Spitter()) return PBA();
                  "You try to tear open the figure's sticky coating, but all you succeed in
                  doing is to stretch it slightly. You begin to see why its occupant is
                  having such a hard time getting out.";
              Burn:
                  if (adar has general && TorchOn()) "You try to light the sticky goo, but it doesn't seem to catch fire.";
                  if (Spitter()) return PBA();
                  if (TorchOn())
                      "You approach the spitter's last victim, meaning to put it out of its
                      misery, but you can't quite bring yourself to torch the unfortunate
                      creature. Apart from anything else, this is the first real humanoid
                      you've seen since you got here.";
                  "You have nothing to burn it with.";
              Close:
                  if (adar has general) "Once open, it can't be closed.";
                  if (Spitter()) return PBA();
                  "That's already closed.";
              Cut:
                  if (adar has general) "You slash at the remaining goo for a while, working off your aggression.";
                  if (Spitter()) return PBA();
                  if (second == nothing) "You're going to need something sharper than your hands to cut the sticky substance.";
                  if (second == knife) return PFAdar();
                  "That's not sharp enough to do the job.";
              Examine, Search:
                  if (adar has general)
                      "The remains of Adar's prison are still stuck to the wall, glistening in the torchlight.
                      ^^Adar catches you looking at it and shudders.";
                  if (Spitter()) "You can't get past the spitter in order to get a closer look.";
                  "Cautiously, you approach and take a closer look. It looks to be highly compressed sand,
                  mixed with a mucous goo and you shudder to think what else. The end result is both sticky
                  and highly elastic.";
              Kick:
                  if (adar has general) "You kick at the remaining goo for a while, working off your aggression.";
                  if (Spitter()) return PBA();
                  "That won't help; do you really want to give the spitter's victim more pain?";
              Open:
                  if (adar has general) "You've already freed Adar.";
                  if (Spitter()) return PBA();
                  "You're going to have to cut it with something in order to do that.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (Spitter()) return PBA();
                  return PNH();
              Touch:
                  if (Spitter()) return PBA();
                  print "Gingerly, you reach out a hand to the gooey mass. There's a wet, slimy layer on the
                  outside -- some of which is now on your fingers -- and a firmer, elastic layer underneath. ";
                  if (adar has general) "Grossed out, you wipe your hand off on your uniform.";
                  "It feels warm to the touch. Grossed out, you wipe your hand off on your uniform.";

          ],
     has  static scenery;

! 08/14/06

  Object  -> sandworm "widow-weave spitter"
    with  name 'large' 'widow' 'weave' 'widow-weave' 'spitter' 'long' 'spade-like' 'legs' 'centipede' 'mandibles' 'spider' 'creature',
          description [;
              if (self in cavern)
                  "The spitter's anger boils over as a constant buzz rings out, mandibles looking to
                  destroy the threat around her. Darting between you and the Ralckor, she doesn't seem
                  to know what to do.";
              if (itakegg == 3)
                  "The furious spitter chatters, legs twitching, as she tries to sense an opening.
                  Frustrated, she can only bob and shift, attention fixed on the egg.";
              print "A multitude of long spade-like legs line the one meter round body, reminiscent
              of a centipede, while the vicious mandibles of a spider look to feed upon your flesh";
              if (self.desfirst) {
                  self.desfirst = false;
                  print ". Spitter's lack any sense of sight, hearing or smell but make up for it by being
                  highly sensitive to touch. For example, they can detect the slightest movement in
                  the air around them -- such as you've just stirred up by walking into the cavern,
                  for example -- and use it to hone in on their prey";
              }
              ".";
          ],
          before [;
              Attack:
                  if (self.threatened) return BrnSpit();
                  if (TorchOn()) return PSA();
                  if (second ~= knife && knife in player) print "(with survival knife)^";
                  print "The spitter feels the rush of air as you approach and backs away. With surprising speed,";
                  return PSKill();
              Burn:
                  if (self.threatened) return BrnSpit();
                  if (TorchOn()) return PSA();
                  "You have nothing to burn the spitter with.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (TorchOn())
                      "The vicious mandibles open, ready to strike. Upon further thought you wave the torch,
                      keeping the creature at bay.";
                  "The vicious mandibles open, ready to strike. Upon further thought you keep your distance.";
            ],
            desfirst true,
            threatened false,
    has   animate static scenery;

! 04/26/06

  Object  -> sm_hshape "humanoid shape"
    with  name 'humanoid' 'shape' 'human',
          description [;
              "At the back of the cavern, a humanoid shape has been covered in a sticky beige substance then
              woven into a tangled cobweb along with a bunch of smaller eggs. It's emitting a low moaning noise,
              and occasionally musters a slight wriggling motion, so it's evidently still alive.";
          ],
          before [;
              Attack:
                  <<Attack sr_substance>>;
              Kick:
                  <<Kick sr_substance>>;
              Cut:
                  <<Cut sr_substance second>>;
              Burn:
                  <<Burn sr_substance>>;
              Open:
                  <<Open sr_substance>>;
              Search:
                  <<Search sr_substance>>;
              Take, Remove, PushDir, Push, Pull:
                  <<Take sr_substance>>;
              Touch:
                  <<Touch sr_substance>>;
            ],
    has   static scenery;

! 08/14/06

  StaticShale -> sr_shale "shale"
    with  name 'loose' 'shale' 'rubble';

! 02/15/08

  Object  -> sm_eggs "small eggs"
    with  name 'egg' 'eggs' 'small' 'one',
          before [;
              Attack, Kick:
                  print "As you break open one of the eggs,";
                  return PBDeth();
              Burn:
                  if (sandworm in small_room) {
                      print "As you put the burning torch to the base of the eggs,";
                      return PSKill();
                  }
                  if (TorchOn()) {
                      deadflag = 1;
                      "As you put the burning torch to the base of the eggs it starts a fire, slowly burning
                      the organic material. It doesn't take long for the babies to become agitated, as they
                      burst forth hatching early. Looking for fresh food to feed on, they tear your limbs apart
                      chewing through your torso, as they devour your intestines fighting over what's left of
                      your entrails.";
                  }
                  "You have nothing to burn the eggs with.";
              Cut, Open, Remove, Take:
                  if (sandworm.threatened) return PSDeth(0);
                  if (itakegg >= 3) "You already took one.";
                  if (knife in player || (knife in milpack && (milpack in player or uniform))) {
                      if (knife notin player) {
                          if (knife in milpack && (milpack in player or uniform)) {
                              print "(first taking the survival knife)^";
                              if (InventTotal() >= PMAX_WEIGHT + 1) InventMove(1);
                              move knife to player;
                              give milpack open;
                          }
                      }
                      switch (itakegg) {
                          0: InSpit();
                             "Using the sharp edge of the blade, you manage to cut part of the web freeing the egg a little. Mandibles start to chatter as the spitter comes in closer, protecting her young.";
                          1: InSpit();
                             "Using the sharp edge of the blade, you cut again, freeing the egg a little more. Mandibles start to chatter as the spitter comes in closer, protecting her young.";
                           2: return TEgg();
                      }
                  }
                  "Trying to take the egg without something to cut it free is practically impossible.";
              Eat, Taste:
                  return PDL();
              Examine, Search:
                  print "A bunch of small eggs are woven into a tangled mess of cobwebs, while they surround ";
                  if (adar has general) print "an open cocoon";
                  else print "a humanoid shape that's been covered in a sticky beige substance";
                  print ". The eggs overflow right to the edge of the nest";
                  if (itakegg >= 3) ".";
                  " and are out of the protective range of the spitter.";
              PushDir, Push, Pull:
                  "The eggs are solidly in place.";
              Touch:
                  "The eggs feel warm to the touch.";
          ],
          daemon [;
              sattack++;
              if (sattack == 2) return PSDeth(1);
          ],
    has   static concealed edible pluralname;
