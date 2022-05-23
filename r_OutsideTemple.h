
! ---------------------------------------------------------------------------- !
!       The OUTSIDE THE TEMPLE. 04/24/06
!
  Room    m_base
   with   description [;
              if (self.exitcav) {
                  "You're standing at the entrance to a large cave, set in the base of a
                  barren, rocky mountain. The rockface is almost vertical, and the
                  incessant sandstorms have ground the surface to a glassy smoothness. All
                  around, you can see nothing but sand.
                  ^^The cave, looking dark and deliciously cool, is to the east, and you
                  recall that your ship lies far to the west.";
              }
              if (self.firstime) {
                  self.firstime = false;
                  StartDaemon(self);
                  thinkpos = 19;
                  "Up close, you can see that the building is clearly ceremonial. It's large, and made
                  from neatly dressed stone covered in detailed carvings. They show humanoid creatures
                  dressed in simple cloaks, probably engaged in some sort of ritual. Images of the sun
                  crop up a lot, too, so you decide it's probably a temple.
                  ^^To the north you can see either a small lake or a large pond -- you're not sure
                  which -- surrounded by shady palm trees.
                  ^^Suddenly, immense stone doors start to swing open in the front of the temple and a
                  gust of cool air hits you. Just as you're luxuriating in how good it feels, a man and
                  a woman come striding out, dressed in fire-red cloaks. Calling them ~a man~ and ~a woman~
                  doesn't really do them justice, though: each is a perfect physical specimen, tall, slender
                  and flawlessly beautiful. If this is what the natives look like, you could get to like it here.
                  ^^~Welcome, stranger! I am Ral,~ the woman says, bowing gently.
                  ^^~... and I am Kor,~ finishes the man, bowing in his turn.
                  ^^~You look like you have traveled far,~ Ral says.
                  ^^~... and must be in need of nourishment. Please, accept this ...~
                  ^^~... apple ...~ Ral says, holding out a juicy red apple.
                  ^^~... pear ...~ Kor says, holding out an equally juicy red pear.
                  ^^~... as a token of our friendship.~ they finish, together.
                  ^^At that, they look at each other, confused and a little embarrassed. You get the strangest
                  feeling that they're competing for you, somehow. Now that you look for it, both of them have
                  looks in their eyes that you'd never have expected from priests. They can't get many visitors
                  out here, you think, though it has to be said that you're not a bad physical specimen yourself.";
              }
              if (self.oldman) {
                  StopDaemon(self);
                  print "Where the temple used to be, you now see a barren, rocky mountain,
                  blasted to a glassy smoothness by the incessant sandstorms. Set in the
                  base of the mountain is a large metal hangar door, about ten meters tall
                  and fifteen meters wide, like the entrance to a military facility.^";
                  if (self.oldfst) {
                      self.oldfst = false;
                      "^After a moment or two, a smaller, human-sized door opens in the bottom
                      of the larger one, and out steps the incongruous figure of a wizened old
                      man. A grandfatherly figure with a shock of white hair and a limp, he's
                      dressed in a three-piece suit that's seen better days. His voice, when
                      he speaks, is surprisingly rich and warm.
                      ^^~Congratulations! Not many who pass this way have the will to resist our
                      little test. Our work is very delicate, you know. Oh yes, very delicate.
                      It really wouldn't do if it were to fall into the wrong hands.
                      ^^~But, dear me, I'm forgetting my manners. You must be parched; I think
                      we can give you a little food and drink without compromising security!~
                      ^^With that, he turns and makes his way slowly back through the door,
                      beckoning you to follow.";
                  }
                  rtrue;
              }
              print "Up close, you can see that the building is clearly ceremonial, probably
              a temple. It's large, and made from neatly dressed stone covered in detailed
              carvings, showing images of the sun and of humanoid creatures dressed in simple
              cloaks engaged in some sort of ritual. To the north you can see either a small lake
              or a large pond -- you're not sure which -- surrounded by shady palm trees.^";
              if (self.fruiteaten) rtrue;
              print "^Ral and Kor are standing before you, offering fruit that would quench
              the thirst in the back of your throat. ";
              if (self.mbrocker) {
                  self.mbrocker = false;
                  "As the wind surges around the building, Ral says with a smile,
                  ~Do you desire my offer, the apple is only one of the many things we may come to share.~";
              } else {
                  self.mbrocker = true;
                  "As the wind surges around the building, Kor says with a wry smile,
                  ~I'll show you your heart's desire, if you take of my pear.~";
              }
          ],
          short_name "Outside the Temple",
          n_to [;
              if (self.fruiteaten) rfalse;
              "You desperately want to satisfy your thirst, but there's
              something hypnotic about Ral and Kor, rooting you to the spot.";
          ],
          e_to [;
              return PToPan();
          ],
          w_to [;
              self.triedwest = true;
              "Without adequate supplies, you'd never make it back to your ship.";
          ],
          in_to [;
              return PToPan();
          ],
          cant_go [;
              if (self.exitcav)
                  "You could go that way, but it's a landscape only a sandophile could love, and you're
                  dehydrating rapidly. Have you considered returning to the cave?";
              if (self.fruiteaten) {
                  if (self.oldman) {
                      "You should do as the old man says, and follow him into the mountain.";
                  } else {
                      if (self.ch_maidens) {
                          "Come now, the nice lady's given you an apple, the least you can do is follow her.";
                      } else {
                          "Come now, the nice gentleman has given you a pear, the least you can do is follow him.";
                      }
                  }
              }
              print "You could go that way, but it's a landscape only a sandophile could love, and you're
              dehydrating rapidly. Have you considered all that these priests have to offer";
              if (self.triedwest) {
                  "?";
              } else {
                  ", or possibly returning west to the remains of your ship?";
              }
          ],
          before [;
              Smell:
                  if (self.ch_maidens) return PMS();
                  if (self.fruiteaten) "The air is harsh and nasty as the sand digs it's way into your nostrils.";
                  return PMS();
              Listen:
                  "There's nothing but the rush of the harsh wind past your ears.";
              Wake:
                  if (self.exitcav) rfalse;
                  if (self.oldman) {
                      if (self.pcwake) {
                          print "Really, this is too much. Again, y";
                      } else {
                          print "Y";
                      }
                      MBCavEnt();
                      print "ou summon up all the willpower you can muster and tell the hangar that
                      it doesn't exist. This time, it feels different, as if a great weight has been
                      lifted; this time, maybe you'll wake up for real. The change is more subtle
                      than before: the mountain is still there, but the hangar door has melted,
                      revealing the entrance to a foul-smelling cave.^";
                      <<Look self>>;
                  }
                  OldManOut();
                  self.pcwake = true;
                  print "It takes all the willpower and self-control that you have, but you force
                  yourself to see beyond the illusion that surrounds you, to believe your
                  eyes and not your mind. For a moment, you feel like you're in two places
                  at once, but then Ral, Kor, the temple and the oasis all snap out of
                  existence and you find yourself somewhere else.^";
                  <<Look self>>;
          ],
          daemon [;
              ifruit++;
              if (ifruit == 10) {
                  OldManOut();
                  print "^All of a sudden, you feel like you're in two places at once, but then ";
                  if (self.fruiteaten == false) {
                      self.fruiteaten = true;
                      print "Ral, Kor, ";
                  }
                  print "the temple and the oasis all snap out of existence and you find yourself somewhere else.^";
                  <<Look self>>;
              }
          ],
          oldfst true,
          oldman false,
          pcwake false,
          exitcav false,
          firstime true,
          mbrocker true,
          triedwest false,
          dreamawake true,
          ch_maidens false,
          fruiteaten false;

! 04/24/06

  Object  -> mb_shade "shade"
    with  name 'shade',
          description
              "A little shade is cast here, as the sun shines down from high above.",
          before [;
              Enter, Sit:
                  "You can't escape the heat of the desert.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
     has  concealed static;

! 04/24/06

  Object  -> m_door
    with  name 'immense' 'stone' '1776ph' 'carved' '1777ph' 'door' 'doors' 'entrance',
          description [;
              if (m_base.exitcav)
                  "It's too dim to see clearly, but you remember that it's large and serves
                  as the ralckor's lair.";
              if (m_base.oldman)
                  "It looks like it's designed to swing up, allowing some piece of
                  newly-designed military hardware to roll out and unleash death upon all
                  who would stand in its way. You have no doubt that it's made of the
                  latest, strongest alloys and is well-nigh blast proof. If it wasn't for
                  the open door set into the bottom, you wouldn't have a hope of getting in.";
              "Each door is fashioned from an immense slab of stone, about five meters
              high and two meters wide. Like the rest of the temple, they're ornately
              carved, each featuring an image of the sun and a single supplicant,
              kneeling with their arms raised in prayer.";
          ],
          short_name "immense stone doors",
          before [;
              Close:
                  "Nothing happens.";
              Enter:
                  return PToPan();
              Open:
                  "It's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
     has  static scenery pluralname;

! 09/10/07

  Object  -> mb_building
    with  name 'building' 'temple' 'tall' 'stepped' 'pyramid' 'four' 'stories' 'triangular' 'large',
          description [;
              if (m_base.exitcav)
                  "Tall and barren, the rocky mountain is part of a range that stretches to the
                  northern and southern horizons. The mountain's surface is almost shiny, where
                  it isn't covered by a thin coating of sand. Just in front of you is the entrance
                  to a large cave.";
              if (m_base.oldman)
                  "Tall and barren, the mountain's surface is almost shiny, where it isn't
                  covered by a thin coating of sand. Just in front of you, set into the
                  base of the mountain, is a hangar door with a smaller door set into it.";
              "About four stories tall and shaped like a stepped pyramid, it's
              certainly impressive. Every available surface is covered with intricate
              carvings: images of the sun and fire crop up a lot, as do prostrate
              worshippers, probably praying for their crops not to be destroyed. There
              are only a few small openings, up near the top, and in front you can see
              two massive stone doors, swung wide open.";
          ],
          short_name "building",
          before [;
              Enter:
                  return PToPan();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
     has  static scenery;

! 09/10/07

  ORchSe  -> mb_trees "palm trees"
    with  name 'tall' 'leafy' 'palm' 'tree' 'trees' 'green',
          description
              "The temple and the lake are surrounded by tall, leafy palm trees, the
              first splash of green you've seen since arriving on this barren planet.
              Strangely, despite the wind, they're nearly motionless.",
     has  scenery pluralname;

! 09/10/07

  ORchSe  -> mb_lake "lake"
    with  name 'oasis' 'pool' 'of' 'clear' 'blue' 'lake' 'water',
          description
              "Clear blue and shining in the sunlight, the lake nestles invitingly amid
              a stand of palm trees. Just seeing it makes you want to dive in and wash
              off this accursed sand.",
          before [;
              Enter:
                  "That's too far away.";
          ],
     has  scenery;

! 09/11/07

  ORchSe  -> mb_carvings "carvings"
    with  name 'detailed' 'carving' 'carvings' 'cover' 'covering' 'covered' 'human' 'humanoid' 'creature' 'creatures' 'simple' 'cloak' 'cloaks' 'ritual' 'intricate' 'fire' 'worshipper' 'worshippers' 'prostrate',
          description
              "Detailed and executed with a good artistic eye, they appear to tell the
              story of these people and their relationship with the sun. You can't see
              it all from here, but it's evident that theirs is a harsh and unmerciful god.",
     has  scenery;
