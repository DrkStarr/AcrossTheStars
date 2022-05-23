
! ---------------------------------------------------------------------------- !
!       The DEADLY PIT. 08/08/06
!
  Room    deadly_pit "Deadly Pit"
    with  description [;
              if (self.pitfall) {
                  self.pitfall = false;
                  print "Rolling onto the ground from the hidden door above, you narrowly miss falling into the pit";
              } else {
                  print "The tunnel comes to an abrupt end here, at the edge of a pit";
              }
              print" that drops away into the darkness below. The air here is stagnant and putrid, and
              a feeling of death pervades everything. The opening is perhaps forty feet in diameter, with
              what was once a wide staircase spiraling down, hugging the perimeter. Time and tremors have
              brought it down, however, and only the top few steps remain intact. A jagged outcrop of
              rock juts out over the abyss.^";
              if (adar in self) {
                  if (statue in pedestal) {
                  } else {
                      if (self.saidonce) {
                          adar.adaroff = true;
                          self.saidonce = false;
                          print "^~I have a bad feeling about this,~ Captain Adar says under ";
                          if (m_base.ch_maidens) {
                              print "her";
                          } else {
                              print "his";
                          }
                          " breath.";
                      }
                  }
                  if (self.dpfirstime) {
                      self.dpfirstime = false;
                      adar.adaroff = true;
                      "^~Thank goodness you made it!~ says Captain Adar, obviously relieved.";
                  }
              }
          ],
          nw_to [;
              if (adar has general) {PAF(); MoveAdar(4);}
              return small_room;
          ],
          d_to [;
              if (grappling_hook.attached && (grappling_hook in deadp_obj or jagged_rock)) {
                  if (unholy_shrine has general) {
                      if (adar has general) print "~I'm not going down there now,~ says Captain Adar as you start to work your way down the rope.^";
                  } else {
                      if (adar has general) {
                          print "~I think I'll stay here,~ says Captain Adar as y";
                      } else {
                          print "Y";
                      }
                      print "ou nervously start to work your way down the rope. As you descend, the smell gets worse,
                      much worse. This is a place where only evil could thrive. Eventually, you reach the bottom";
                      if (((torch in player or us_altar) && torch.onfire) || datapad has light && datapad in milpack && milpack has open && (milpack in player or us_altar or unholy_shrine) || datapad has light && (datapad in player or us_altar or unholy_shrine) || orb in player or us_altar or unholy_shrine || (orb in milpack && milpack has open && (milpack in player or unholy_shrine or us_altar or uniform)) || datapad has light) {
                          print ", and hardly dare to turn around.^";
                      } else {
                          print ".^";
                      }
                 }
                 return unholy_shrine;
              }
              "The staircase is broken and can't be used to enter the pit.";
          ],
          cant_go
              "You can only go back up the tunnel towards the northwest.",
          before [;
              Exit:
                  if (adar has general) {PAF(); MoveAdar(4);}
                  PlayerTo(small_room);
                  rtrue;
              Smell:
                  "The air is grotesque, with a foul stench of rotting death that must occupy the pit below.";
          ],
          pitfall false,
          saidonce true,
          dpfirstime false;

! 08/08/06

  Object  -> deadp_obj "deadly pit"
    with  name 'deadly' 'deep' 'pit' 'abyss' 'chasm',
          describe [;
              if (self.skip) {
                  self.skip = false;
                  rtrue;
              }
              if (grappling_hook in self) "^Attached to ", (the) self, ", the makeshift grappling hook hangs down into it.";
              rtrue;
          ],
          before [;
              Enter:
                  deadflag = 1;
                  return DPEntr(1);
              Examine, Search:
                  if (self.lookat) {
                      score = score + 5;
                      self.lookat = false;
                      "As you stare into the darkness, you hear a faint chanting. Low voices praying
                      to an unholy god. Light starts to flicker in the pit as worshipers collect around
                      a shrine, prostrating before a crude idol that rests atop it.
                      ^^The leader steps forward, pushing cult members aside as his guards muscle
                      their way next to him. Suddenly, he shouts at the top of his lungs as the guards grab
                      one of the cult members. The member tries to break free; but overpowered by the guards,
                      they impale his body upon a large spike as a hideous scream echoes throughout the pit.
                      ^^As the echo continues down the cavern, the vision slowly fades to black.";
                  }
                  if (grappling_hook in self) {
                      print "Attached to the side of the pit, the makeshift grappling hook hangs down into ";
                      if ((torch in us_altar && torch.onfire) || orb in unholy_shrine or us_altar) "the faint light below.";
                      "the darkness below.";
                  }
                  if ((torch in us_altar && torch.onfire) || orb in unholy_shrine or us_altar) "You see a faint red glow at the bottom of the pit, but it's too hard to make anything out.";
                  "It's too dark to see anything at the bottom of the pit.";
              Grapple:
                  if (grappling_hook in player || (grappling_hook in milpack && ((milpack in player or uniform) || (parent(milpack) == parent(player))))) return PGrpPit();
              JumpOver:
                  deadflag = 1;
                  return DPEntr(2);
              Sit:
                  "You can't sit on the pit.";
              Take, Remove, Turn, PushDir, Push, Pull:
                 "That's fixed in place.";
          ],
          skip false,
          lookat true,
    has   container open static;

! 08/08/06

  ORchSe  -> jagged_rock "jagged rock"
    with  name 'jagged' 'rock' 'rocks' 'outcrop' 'of',
          description [;
              print "The jagged outcrop of rock juts out over the abyss";
              if (grappling_hook in self) " with the makeshift grappling hook attached to it, hanging down into the pit.";
              ".";
          ],
          describe [;
              if (self.skip) {
                  self.skip = false;
                  rtrue;
              }
              if (grappling_hook in self) "^Attached to ", (the) self, ", the makeshift grappling hook hangs down into the pit.";
              rtrue;
          ],
          before [;
              Grapple:
                  if (grappling_hook in player || (grappling_hook in milpack && ((milpack in player or uniform) || (parent(milpack) == parent(player))))) return PGrpHk(1);
          ],
          skip false,
    has   supporter;

! 10/12/06

  Object  -> dp_staircase "staircase"
    with  name 'wide' 'staircase' 'stairway' 'step' 'steps' 'stair' 'stairs',
          description
              "The wide staircase that descends into the pit is nothing more than a few steps that drop
              away into the darkness below.",
          describe [;
              rtrue;
          ],
          before [;
              Climb:
                  "The staircase is broken and can't be used to enter the pit.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static;

! 10/12/06

  OutRch  -> dp_opening "opening"
    with  name 'circular' 'opening',
          description
              "The circular opening about five feet wide, and it's very hard to see into.";

! 10/12/06

  Object  -> dp_darkness "darkness"
    with  name 'darkness',
          article "the",
          description
              "The pit is deep and wide, and only full of death.",
          before [;
              Enter:
                  <<Enter deadp_obj>>;
              Sit:
                  <<Sit deadp_obj>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static pluralname;
