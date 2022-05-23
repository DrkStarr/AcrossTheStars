
! ---------------------------------------------------------------------------- !
!       The RALCKOR'S LAIR. 04/25/06
!
  Room    cavern "Ralckor's Lair"
   with   description [;
              if (sandworm in self)
                  "In the middle of the floor the vines of the ralckor whip about, as the widow-weave spitter
                  enrages, sensing the new enemy. Switching between you and the ralckor, the spitter's frustration
                  grows, the chattering now a buzz. Cornered, you keep the spitter at bay with the torch
                  as long vines lash out at you.";
              if (self.firstime) {
                  self.firstime = false;
                  detonator.adcavern = true;
                  if (knife in pantheon) move knife to self;
                  if (wrench in pantheon) move wrench to self;
                  if (prybar in pantheon) move prybar to self;
                  if (milpack in pantheon) move milpack to self;
                  if (playbeing in pantheon) move playbeing to self;
                  if (detonator in pantheon) move detonator to self;
                  if (coffee_cup in pantheon) move coffee_cup to self;
                  if (omni_trans in pantheon) move omni_trans to self;
                  if (og_datacard in pantheon) move og_datacard to self;
                  if (halfshelter in pantheon) move halfshelter to self;
                  if (milpack.detaken) {
                      milpack.detaken = false;
                      self.mpmove = true;
                      move milpack to cavern;
                  }
              }
              print "You're standing in a large, natural cave, with jagged walls and an earthen floor.
              In the middle of the floor, ";
              if (ralckor.dead) {
                  print "a half-eaten spitter twitches in the jaws of a dying ralckor, surrounded
                  by the scattered bones of its previous victims";
                  if (milpack in self && self.mpmove) {
                      print ". Also, a field pack lies next to the dead beast.";
                  } else {
                      print ".";
                  }
              } else {
                  print "bigger than a hovercar, you can see the mouth and sharp, pointed teeth of a ralckor.
                  Scattered bones surround it, all that remains of its previous victims";
                  if (milpack in self && self.mpmove) {
                      print ". Also, a field pack lies next to the beast.";
                  } else {
                      print ".";
                  }
              }
              print "^^Looking more closely, you can see that this must once have been a ceremonial chamber,
              for tribalistic runes line the walls. A tunnel has been hollowed out in the south wall,
              while a jagged hole in the eastern wall has destroyed some of the runes.";
              if (orb in tc_shrine)
                  "^^An eerie cobalt light streams in through a doorway in the western wall, and down from a
                  window -- too regular to simply be a hole -- in the roof.";
              print "^^Sunlight streams in through a doorway in the western wall, while a solitary beam falls
              down from a window -- too regular to simply be a hole -- in the roof to illuminate a ";
              if (trans_crystal.tcinbeam) "small dot on the floor.";
              "meter-wide patch of floor.";
          ],
          s_to [;
              if (sandworm in self) rfalse;
              if (adar has general) {PAF(); MoveAdar(2);}
              ClrBeam();
              return s_tunnel;
          ],
          e_to [;
              <<Exit self>>;
          ],
          w_to [;
              <<Enter lc_doorway>>;
          ],
          cant_go [;
              if (sandworm in self) "You can't, you're trapped between the spitter and ralckor.";
              "You can only go south, east, or west.";
          ],
          before [;
              Exit:
                  if (sandworm in self) "You can't, you're trapped between the spitter and ralckor.";
                  if (orb in tc_shrine) "The impenetrable force field sparks painfully as you try to step through the cobalt light.";
                  ClrBeam();
                  if (ralckor.dead) {
                      if (adar has general) {
                          MoveAdar(7);
                          if (chasm.blown) {
                              print "Stepping over a few rocks, Captain Adar follows.^";
                          } else {
                              PAF();
                          }
                      }
                      u_obj.&name-->4 = 'sky';
                      PlayerTo(chasm);
                      rtrue;
                  }
                  thinkpos = 18;
                  if (self.fnlext) "Remembering what happened last time you came within range of the ralckor, you think better of it.";
                  self.fnlext = true;
                  "As you approach the hole in the eastern wall, you have to pass within a
                  couple of meters of the ralckor. As soon as you do, a cluster of long,
                  flexible vines whips out, heading in your direction. You manage to jump
                  out of the way, but just barely. The ralckor makes a very effective sentry.";
              Listen:
                  if (sandworm in self) "The chattering from the spitter is a buzz in your ears.";
              Smell:
                  if (noun == ralckor)
                      "Foul, but what else do you expect of a creature that's little more than
                      a pot of stomach acid with teeth attached?";
                  "The cavern smells rancid as the foul beast pollutes the air.";
          ],
          fnlext false,
          mpmove false,
          firstime true,
          vfirstime true,
          beastmove true;

! 05/03/06

  RoomObj -> cavernobj "large cavern"
    with  name 'large' 'cavern' 'room',
          description [;
              <<Look cavern>>;
          ];

! 04/25/06

  Object  -> ralckor "ralckor"
    with  name 'ralckor' 'monster' 'teeth' 'sharp' 'mouth' 'pointed' 'beasty' 'creature' '8874ph' '8875ph' 'beast' 'vine' 'vines' 'plant' 'jaw' 'jaws' 'long' 'flexible',
          description [;
              if (self.dead)
                  "Little is left of this once ferocious beast, the spitter having cut off
                  most of the long flexible vines. Now she's stuck in the large jaws of
                  the ralckor, dying herself.";
              if (sandworm in cavern)
                  "The spitter's presence has enrage the ralckor, as long flexible vines whip about.";
              "You could be forgiven for thinking that the ralckor was just a hole in the ground,
              with teeth attached. Big, sharp teeth, designed to devour anything and everything
              that comes its way. Looking more closely, you can see that it has burrowed down into
              the earthen floor, protecting its small body underneath its enormous mouth.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  if (self.dead) "Just leave the creature in peace.";
                  return PCV();
              Burn:
                  if (self.dead) rfalse;
                  return PCV();
              Dig:
                  if (self.dead) "Just leave the creature in peace.";
                  thinkpos = 18;
                  "You don't dare get that close.";
              Enter:
                  if (self.dead) "But the spitter's blocking the way.";
                  deadflag = 1;
                  "The ralckor gladly welcomes you with long-reaching vines that quickly pull you into
                  razor-sharp teeth that tear through your flesh. Digging into your organs, teeth find
                  bone, only to grind it into a calcium paste, leaving none of what you were to waste.";
              JumpOver, Push, PushDir, Pull, Search, Touch, Take, Remove, Turn:
                  if (self.dead) "After everything you've been through to escape its clutches, you plan to keep a safe distance from now on.";
                  return PCV();
              Taste:
                  "Eewww. Ralckor tartare probably tastes like chicken anyway.";
          ],
          dead false,
    has   animate container open static;

! 08/14/06

  Object  -> lc_bones "bones"
    with  name 'bone' 'bones' 'of' 'the' 'dead' 'pile',
          description [;
              if (self.bonedpfnd) {
                  self.bonedpfnd = false;
                  move datapad to cavern;
                  "As you look through some of the bones, you find a data pad amongst the carnage.";
              }
              "The bones lie around the room, dispersed and restless.";
          ],
          article "some",
          before [;
              Search:
                  if ((self.bonedpfnd) || (datapad in cavern)) {
                      self.bonedpfnd = false;
                      move datapad to cavern;
                      "As you search through some of the bones you find a data pad amongst the carnage.";
                  }
                  "As you search through the bones again, you find nothing of interest.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "It's better to leave dead alone, than to take the death with you.";
          ],
          bonedpfnd true,
    has   scenery static;

! 08/14/06

  Object  -> lc_hole "jagged hole"
    with  name 'jagged' 'hole',
          description [;
              "Through the hole, you can see a deep chasm in the desert. An ancient
              meteor impact must have weakened the already-eroded cave wall enough
              that it gave way.";
          ],
          before [;
              Enter:
                  <<Exit cavern>>;
              Open:
                  if (ralckor.dead) return PCB();
                  return PCV();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static scenery;

! 09/27/07

  Object  -> lc_doorway "doorway"
    with  name 'door' 'doorway',
          description [;
              "The doorway leads back out to the hot-burning desert.";
          ],
          before [;
              Enter:
                  if (sandworm in cavern) "You can't, you're trapped between the spitter and ralckor.";
                  if (orb in tc_shrine) "The impenetrable force field sparks painfully as you try to step through the cobalt light.";
                  if (m_base.exitcav == false) MBCavEnt();
                  if (adar has general) {PAF(); move adar to m_base; }
                  ClrBeam();
                  PlayerTo(m_base);
                  rtrue;
              Open:
                  return PCB();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static scenery;

! 08/14/06

  Object  -> lc_beamoflight "beam of light"
    with  name 'beam' 'of' 'light' 'ray' 'sunlight',
          description [;
              print "A hole high up in the roof of the cave allows a solitary beam of
              sunlight through, illuminating dust motes dancing their Brownian dance
              before falling onto a ";
              if (trans_crystal.tcinbeam) "small dot on the floor.";
              "meter-wide patch of the floor.";
          ],
          before [;
              Close:
                  "It's coming from a hole, high up in the roof, and there's no way to block it.";
              Enter, Stand:
                  "There's no reason to block the light.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed container static open;

! 08/12/07

  Object  -> lc_space "small space"
    with  name 'small' 'space' '0909ph' 'meter-wide' 'meter' 'wide' 'patch',
          before [;
              Enter, Stand:
                  if (self.standing) {
                      print "You are already standing on the ";
                  } else {
                      self.standing = true;
                      print "You stand on the ";
                  }
                  if (trans_crystal.tcinbeam) print "small dot";
                  else print "patch";
                  " of light.";
              Examine, Search:
                  if (trans_crystal.tcinbeam) "A small dot of light can be seen on the floor.";
                  "A meter-wide patch of light can be seen on the floor.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          standing false,
    has   concealed container static open;

! 09/11/07

  ORchSe  -> lc_window "window"
    with  name 'window' 'hole' 'pinhole',
          description
              "Situated high up in the roof, it looks like no more than a pinhole from
              here, but it's probably just about wide enough to fall through, should
              anybody be foolish enough to climb up there.",
    has   scenery;

! 08/14/06

  OutRch  -> lc_tribalistic "tribalistic runes"
    with  name 'sixteen' 'tribalistic' 'tribal' 'runes',
    with  parse_name [ w1 w2;
              w1 = NextWord();
              if (w1 ~= 'runes' or 'tribalistic' or 'tribal') return 0;
              w2 = NextWord();
              if (w1 == 'tribal' or 'tribalistic' && w2 == 'rune' or 'runes') return 2;
              if (w1 == 'runes') return 3;
              return 1;
          ],
          description
              "From first to last, starting with the northernmost rune, you see a hollow circle,
              a star, a filled in circle, two moons, a few destroyed runes, a large worm, half a
              circle (pointing down), a square, a man, a woman, a child, a rat, a triangle
              (pointing down), half a circle (pointing up), and a broken circle.",
          article "some",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  "Try scanning each individual rune.";
          ],
    has   pluralname;

! 02/14/07

  OutRch  -> lc_hcrune "hollow circle"
    with  name 'hollow' 'circle' 'rune',
          description
              "It's a rune of a hollow circle positioned on the northern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of the hollow circle represented the number zero for the people that once
                      lived here. Depicted as 0000 using their favored binary number system, it meant
                      ~Universal Void~ and embodies the concept of emptiness and the negative along with
                      fullness and the positive.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_srune "star"
    with  name 'star' 'rune',
          description
              "It's a rune of a star positioned on the northeastern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of the star represented the number one for the people that once
                      lived here. Depicted as 0001 using their favored binary number system, it meant
                      ~Universal God~ and embodies the concept of energy and light.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_fcrune "filled in circle"
    with  name 'filled' 'in' 'circle' 'rune',
          description
              "It's a rune of a filled in circle positioned on the northeastern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of the filled in circle represented the number two for the people that once
                      lived here. Depicted as 0010 using their favored binary number system, it meant
                      ~Universal World and embodies the concept of life, nurturing, giving, or mother.";
                      style roman;
                      "";
                  }
                  return PNE();
        ],
        haveread false;

! 02/14/07

  OutRch  -> lc_tmrune "two moons"
    with  name 'two' 'moon' 'moons' 'moon^s' 'rune',
          description
              "It's a rune of two moons positioned on the northeastern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of the two moons represented the number three for the people that once
                      lived here. Depicted as 0011 using their favored binary number system, it meant
                      ~Universal Half~ and embodies the concept of part, lesser, or pain.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 08/14/06

  OutRch  -> lc_drune "destroyed runes"
    with  name 'destroyed' 'rune' 'runes',
          article "a",
          description
              "You can't see the damaged runes; they're destroyed.";

! 02/14/07

  OutRch  -> lc_lwrune "large worm"
    with  name 'large' 'worm' 'rune',
          description
              "It's a rune of a large worm positioned on the southeastern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a large worm represented the number six for the people that once
                      lived here. Depicted as 0110 using their favored binary number system, it meant
                      ~God of the World~ and is one of four holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false,
    has   pluralname;

! 02/14/07

  OutRch  -> lc_hlfcrune "half circle (pointing down)"
    with  name 'half' 'circle' 'rune' 'pointing' 'down',
          description
              "It's a rune of a half circle (pointing down) positioned on the southeastern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a half circle (pointing down) represented the number of seven for the
                      people that once lived here. Depicted as 0111 using their favored binary number system,
                      it meant ~Part of God~ and embodies their concept of the shard.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_sqrune "square"
    with  name 'square' 'rune',
          description
              "It's a rune of a square positioned on the southern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a square represented the number eight for the people that once
                      lived here. Depicted as 1000 using their favored binary number system, it meant
                      ~World Universe~ and embodies their concept of an established kingdom.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_mrune "man"
    with  name 'man' 'rune',
          description
              "It's a rune of a man positioned on the southwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a man represented the number nine for the people that once
                      lived here. Depicted as 1001 using their favored binary number system, it meant
                      ~World God~ and is one of four holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_wrune "woman"
    with  name 'woman' 'rune',
          description
              "It's a rune of a woman positioned on the southwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a woman represented the number ten for the people that once
                      lived here. Depicted as 1010 using their favored binary number system, it meant
                      ~World Nurturer~ and is one of four holy numbers they considered balanced.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_crune "child"
    with  name 'child' 'rune',
          description
              "It's a rune of a child positioned on the southwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a child represented the number eleven for the people that once
                      lived here. Depicted as 1011 using their favored binary number system, it meant
                      ~Part of the World~ and embodies their concept of the child.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_rrune "rat"
    with  name 'rat' 'rune',
          description
              "It's a rune of a rat positioned on the western face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a rat represented the number twelve for the people that once
                      lived here. Depicted as 1100 using their favored binary number system, it meant
                      ~Children of Emptiness~ and embodies their concept of want.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_trirune "triangle (pointing down)"
    with  name 'triangle' 'pointing' 'down' 'rune',
          description
              "It's a rune of a triangle (pointing down) positioned on the northwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a triangle (pointing down) represented the number thirteen for the
                      people that once lived here. Depicted as 1101 using their favored binary number system,
                      it meant ~Children of God~ and embodies their concept of death.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_hcrsurune "half circle (pointing up)"
    with  name 'half' 'circle' 'pointing' 'up' 'rune',
          description
              "It's a rune of a half circle (pointing up) positioned on the northwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a half circle (pointing up) represented the number fourteen for the
                      people that once lived here. Depicted as 1110 using their favored binary number system,
                      it meant ~Children of the World~ and embodies their concept of fear.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;

! 02/14/07

  OutRch  -> lc_brcrune "broken circle"
    with  name 'broken' 'circle' 'rune',
          description
              "It's a rune of a broken circle positioned on the northwestern face of the cavern.",
          before [;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (self.haveread) {
                      POT();
                      style fixed;
                      print "The image of a broken circle represented the number fifteen for the people that
                      once lived here. Depicted as 1111 using their favored binary number system, it meant
                      ~Children of Children~ and embodies division and discord throughout life.";
                      style roman;
                      "";
                  }
                  return PNE();
          ],
          haveread false;
