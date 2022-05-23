
! 08/08/06

  Movable grappling_hook "makeshift grappling hook"
    with  name 'makeshift' 'grappling' 'hook' 'rope' 'stand',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self in jagged_rock) "Currently the makeshift grappling hook is attached to the outcropping of rock, with the length of rope hanging into the pit.";
              if (self in deadp_obj) {
                  print "Currently the makeshift grappling hook has been placed at the edge of the pit, hanging down into the ";
                  if ((torch in us_altar && torch.onfire) || orb in unholy_shrine or us_altar) "faint light below.";
                  "darkness below.";
              }
              if (self in tc_bsrail) "Currently the makeshift grappling hook is attached to the broken stone rail, with the length of rope hanging in this chamber.";
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out a";
                  } else {
                      print "It's a";
                  }
              } else {
                  print "It's a";
              }
              " makeshift three-pronged grappling hook, with a length of rope attached. Created from the patina-covered stand and some rope from a belt, it's a useful tool that might help get you off this planet.";
          ],
          after [;
              Insert:
                  if (second == deadp_obj) {
                      move self to player;
                      "If you did that, how could you get down there?";
                  }
          ],
          before [;
              Climb:
                  if (self.attached == false) "You need to attach the hook to something before you can climb the rope.";
                  if (player in deadly_pit) {
                      if (adar has general) {
                          print "~I think I'll stay here,~ says Captain Adar as y";
                      } else {
                          print "Y";
                      }
                      print "ou nervously start to work your way down the rope. As you descend, the smell gets worse,
                      much worse. This is a place where only evil could thrive. Eventually, you reach the bottom";
                      if (((torch in player or self or us_altar) && torch.onfire) || orb in player or self or us_altar || (orb in milpack && milpack has open && (milpack in player or unholy_shrine or us_altar or uniform))) {
                          print ", and hardly dare to turn around.^";
                      } else {
                          print ".^";
                      }
                      PlayerTo(unholy_shrine);
                      rtrue;
                  }
                  if (player in unholy_shrine) {
                      if (unholy_shrine has general) {
                          StopDaemon(unholy_shrine);
                          huge_boulder.boulderfalling = false;
                          print "Swarming up the rope faster than you'd ever thought you could, you
                          reach the top just as a boulder rolls out of the opening on the far side
                          of the pit and plummets into the darkness. A moment later, you hear an
                          almighty crash from below.^";
                      }
                      PlayerTo(deadly_pit);
                      rtrue;
                  }
                  if (player in tranquility_chamber) {
                      if (adar has general) print "~Have fun up there,~ says Captain Adar as you climb up the rope.^";
                      PlayerTo(view_plat);
                      rtrue;
                  }
              Grapple:
                  if (self.attached) "That's already attached to something.";
                  if (self in player) {
                      if (player in deadly_pit) return PGrpHk(1);
                      if (player in tranquility_chamber) return PGrpHk(2);
                      rfalse;
                  }
                  "You don't have that.";
              PutOn:
                  if (self in player) {
                      if (second == jagged_rock) return PGrpHk(1);
                      if (second == tc_bsrail) return PGrpHk(2);
                      if (second == pedestal) return PedestalEnds(7);
                      if (second == deadp_obj or dp_staircase) return PGrpPit();
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
                  self.attached = false;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) "If you did that, how could you get down there?";
                      if (second == jagged_rock) return PGrpHk(1);
                      if (second == tc_bsrail) return PGrpHk(2);
                  }
              Tie:
                  if (self in tc_shrine) return PYC();
                  "The makeshift grappling hook is designed to grapple with things, not to be tied off to them.";
              Use:
                  if (self in player) {
                      if (second == jagged_rock) return PGrpHk(1);
                      if (second == deadp_obj or dp_staircase) return PGrpPit();
                      if (second == tc_bsrail) return PGrpHk(2);
                      rfalse;
                  }
                  "You don't have that.";
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          attached false;
