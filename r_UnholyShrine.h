
! ---------------------------------------------------------------------------- !
!       The UNHOLY SHRINE. 08/08/06
!
  Object  unholy_shrine "Unholy Shrine"
    with  description [;
              if (self has general) {
                  if (huge_boulder.boulderfalling) {
                      StartDaemon(self);
                      "This unholy shrine shakes with a fierce force, as the boulder from above
                      thunders its way towards you. An altar in the middle rattles with the force
                      from above. Around the altar, at each of the four main compass points, are
                      huge stone spikes, like the fangs of Cerberus. Impaled atop each is a skeleton
                      that shakes back and forth. There are openings to the north, east, south and
                      west, but they have all been blocked by the collapse of the staircase. The only
                      way out of here is back up the rope that hangs into the room.";
                  }
                  move us_rubble to unholy_shrine;
                  if (us_altar in self) remove us_altar;
                  if (us_rune in self) remove us_rune;
                  if (us_moss in self) remove us_moss;
                  return PUShrine(1);
              }
              if (self.unseen) {
                  self.unseen = false;
                  score = score + 5;
              }
              return PUShrine(2);
          ],
          u_to [;
              if (self has general && huge_boulder.boulderfalling) {
                  StopDaemon(self);
                  huge_boulder.boulderfalling = false;
                  print "Swarming up the rope faster than you'd ever thought you could, you
                  reach the top just as a boulder rolls out of the opening on the far side
                  of the pit and plummets into the darkness. A moment later, you hear an
                  almighty crash from below.^";
              } else {
                  print "You climb back up the rope.^";
              }
              return deadly_pit;
          ],
          cant_go
              "You can only go back up the rope.",
          before [;
              Exit:
                  if (self has general && huge_boulder.boulderfalling) {
                      StopDaemon(self);
                      huge_boulder.boulderfalling = false;
                      print "Swarming up the rope faster than you'd ever thought you could, you
                      reach the top just as a boulder rolls out of the opening on the far side
                      of the pit and plummets into the darkness. A moment later, you hear an
                      almighty crash from below.^";
                  } else {
                      print "You climb back up the rope.^";
                  }
                  PlayerTo(deadly_pit);
                  rtrue;
              Listen:
                  if ((torch in player or self or us_altar) && torch.onfire) "Only the soft burning of the torch can be heard.";
                  if (datapad in player or milpack && datapad.dpstchon) "You can hear the soft hum of the data pad.";
                  "Dead silence.";
              Smell:
                  if (((torch in player or us_altar) && torch.onfire) || datapad has light && datapad in milpack && milpack has open && (milpack in player or us_altar or self) || datapad has light && (datapad in player or us_altar or self) || orb in player or self or us_altar || (orb in milpack && milpack has open && (milpack in player or self or us_altar or uniform))) "The air down here is putrid as skeletal bodies slowly decompose underneath the rubble.";
                  "The air down here is putrid. Though you can't see the death, it fills you with its awful order, making your stomach churn.";
          ],
          daemon [;
                us_count++;
                if (us_count == 2) {
                    deadflag = 1;
                    return BoulderDeath();
                }
            ],
            unseen true;

! 08/08/06

  RoomObj -> us_obj "unholy shrine"
    with  name 'unholy' 'shrine' 'room',
          description [;
              <<Look unholy_shrine>>;
          ];

! 08/08/06

  Object  -> us_altar "stone altar"
    with  name 'stone' 'altar',
          description [;
              print "The stone altar is old and worn with time. Now covered in a dark green brown moss, it
              looks forgotten and in ruin.";
              if (statue in self) {
                  " Atop is placed a crude parody of a man, made of poorly-baked clay.";
              }
              new_line;
          ],
          describe [;
              rtrue;
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              Push:
                  "Pushing down on ", (the) self, " doesn't seem to do anything.";
              Take, Remove, Turn, PushDir, Pull:
                  "Firmly rooted into the ground, the stone altar will not move.";;
          ],
    has   supporter static;

! 08/08/06

  Object  -> us_skeleton "skeleton"
    with  name 'dozen' 'dozens' 'of' 'skeleton' 'skeletons',
          description [;
              "The skeletons that surround you are gruesome. Skulls smashed in from falling rubble,
              others run through, impaled upon spikes, all of their limbs broken and mangled. The
              sight begins to make your stomach convulse.";
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "It's better to leave dead alone, than to take the death with you.";
          ],
    has   scenery static;

! 08/08/06

  Object  -> us_spikes "huge spikes"
    with  name 'huge' 'spike' 'spikes' 'stone',
          description [;
              "Each of the spikes, placed at the four compass points of the room, are impaled with skeletons.";
          ],
          before [;
              Push:
                  "Pushing down on ", (the) self, " doesn't seem to do anything.";
              Take, Remove, Turn, PushDir, Pull:
                  return PNH();
          ],
    has   scenery static;

! 08/09/06

  Object  -> us_wall "wall"
    with  name 'wall' 'walls' 'crack' 'cracked' 'cracks' 'dense' 'stone',
          description
              "The walls are made of a dense stone to have last all these years. Now cracked with age,
              vines have made their way into the shrine forming a bizarre pattern of thick bramble.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 08/09/06

  Object  -> us_vine "vine"
    with  name 'sharp' 'vine' 'vines' 'bramble' 'bizarre' 'pattern' 'briar',
          description
              "Sharp vines cling to the walls, driving deeper into the earth, through large cracks that
              have formed in the dense stone.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "Now how are you going to do that? You could cut your hands to shreds on that briar.";
          ],
    has   concealed static;

! 08/09/06

  Object  -> us_moss "moss"
    with  name 'dark' 'green' 'brown' 'moss',
          description [;
              if (statue in us_altar)
                  "The moss has heavily grown over the altar, making it hard to see any of the runes engraved
                  upon it. Strangely enough, it does not cover over the crude parody of the man.";
              "The moss has heavily grown over the altar, making it hard to see any of the runes engraved upon it.";
          ],
          before [;
              Attack, Kick:
                  remove self;
                  us_rune.mossgone = true;
                  us_rune.&name-->2 = 'broken';
                  us_rune.&name-->3 = 'circle';
                  "You break away the moss revealing two runes. The first has been chiseled off, with the second
                  being carved on top of it, a broken circle.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  remove self;
                  us_rune.mossgone = true;
                  us_rune.&name-->2 = 'broken';
                  us_rune.&name-->3 = 'circle';
                  "You push away the moss revealing two runes. The first has been chiseled off, with the second
                  being carved on top of it, a broken circle.";
          ],
    has   concealed static;

! 08/09/06

  Object  -> us_rune "runes"
    with  name 'rune' 'runes' '4821ph' '4822ph',
          description [;
              if (self.mossgone) "On top of a chiseled off rune, lies a broken circle, similar to the one in the foul-smelling cavern.";
              "You can't make out any of the runes due to the moss having grown over so thickly.";
          ],
          before [;
              Push:
                  "Pushing down on ", (the) self, " doesn't seem to do anything.";
              Read:
                  if (self.mossgone) {
                      print "On top of a chiseled off rune, lies a broken circle.";
                      if (omni_trans in player or milpack) " Perhaps your OmniTrans can translate it.";
                  }
                  "You can't make out any of the runes due to the moss having grown over so thickly.";
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.mossgone == false) rfalse;
                  if (lc_brcrune.haveread) {
                      POT();
                      style fixed;
                      print "The image of a broken circle represented the number fifteen for the people that
                      once lived here. Depicted as 1111 using their favored binary number system, it meant
                      ~Children of Children~ and embodies division and discord throughout life.";
                      style roman;
                      "";
                  }
                  return PNE();
              Take, Remove, Turn, PushDir, Pull:
                  if (self.mossgone) return PNH();
                  remove us_moss;
                  self.mossgone = true;
                  self.&name-->2 = 'broken';
                  self.&name-->3 = 'circle';
                  "You push away the moss revealing two runes. The first has been chiseled off, with the second
                  being carved on top of it, a broken circle.";
          ],
          mossgone false,
    has   concealed static pluralname;

! 09/27/06

  Object  -> us_rope "rope, hanging down from above"
    with  name 'rope',
          description
              "The rope hangs down from above.",
          before [;
              Climb:
                  if (unholy_shrine has general && huge_boulder.boulderfalling) {
                      StopDaemon(unholy_shrine);
                      huge_boulder.boulderfalling = false;
                      print "Swarming up the rope faster than you'd ever thought you could, you
                      reach the top just as a boulder rolls out of the opening on the far side
                      of the pit and plummets into the darkness. A moment later, you hear an
                      almighty crash from below.^";
                  } else {
                      print "You climb back up the rope.^";
                  }
                  PlayerTo(deadly_pit);
                  rtrue;
              Take, Remove:
                  "You can't. It seems to be secured on the other side.";
              Pull:
                  "You give it a good tug, and the anchor seems to hold.";
              PushDir, Push:
                  "It only seems to swing back and forth as you play with it.";
          ],
    has   static scenery;

! 10/12/06

  Object  -> us_staircase "staircase"
    with  name 'staircase' 'stairway' 'large' 'broken' 'stone' 'stones' 'stairs' 'collapsed' 'circular',
          description
              "Large pieces of broken stone now make up what once was a large circular staircase
              that descended into the room. Crushed skeletons now lay under these large stones that
              block the openings that lie to the north, east, south, and west.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The stones are firmly in place, and don't seem to move.";
          ],
    has   concealed static;

! 10/12/06

  Object  -> us_opening "opening"
    with  name 'opening' 'openings',
          description
              "You can only see darkness as you try to peer through one of the cracks, looking into
              the opening.",
          before [;
              Enter:
                  "Large broken stones block the way.";
              PushDir, Push, Pull:
                  "You can't get to the opening since your way is blocked.";
          ],
    has   concealed static;
