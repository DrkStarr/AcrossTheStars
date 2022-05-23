
! ---------------------------------------------------------------------------- !
!       The PANTHEON. 04/24/06
!
  Room    pantheon
   with   description [;
              if (m_base.oldman) {
                  print "A small area has been carved out of the corner of the hangar, somewhere
                  for visitors to wait while the guards make sure it's safe to let them
                  in. It features standard military-issue decor, obviously designed by
                  someone too junior to get out of it. There are a few sad-looking posters
                  on the walls, a wilting ficus plant in the corner, and a couple of
                  uncomfortable-looking couches with a glass-topped table in-between. To
                  the east, double sliding doors lead in to the hangar proper, while a
                  narrow corridor leads off to the north.^";
                  if (self.omanfst) {
                      self.omanfst = false;
                      "^~I just have to go and check on a few things, make sure nothing blows up
                      without me,~ the old man says, with a wheezy chuckle. ~In the meantime,
                      why don't you get along to the commissary? Just tell them that Arnold
                      sent you. I'll be along shortly.~ After pointing you toward the northern
                      corridor, he sets off at a brisk shuffle through the double doors.";
                  }
                  rtrue;
              }
              print "Inside, the temple is blessedly cool and quiet. It's also almost completely empty,
              though you do see doors on all sides that must lead to the living areas. Occasional shafts
              of sunlight from the high windows complement the light from the door, illuminating bare
              walls and a flagstone floor. Up on a raised dais in the center of the floor you can see
              the only furniture, a large gold throne and a long dining table.^";
              if (self.firstime) rtrue;
              self.firstime = true;
              print "^~I know it's a little odd, but why don't you take a seat while I go and prepare
              something to eat,~ ";
              if (m_base.ch_maidens) {
                  print "Ral";
              } else {
                  print "Kor";
              }
              print " says, hurrying through a door to the north.^^A little odd? The ";
              if (m_base.ch_maidens) {
                  print "woman";
              } else {
                  print "man";
              }
              print "'s asking you to sit in the throne they probably reserve for the high priest and ";
              if (m_base.ch_maidens) {
                  print "she";
              } else {
                  print "he";
              }
              " calls it ~a little odd~? You start to notice a pleasant, fuzzy feeling at the back of your
              mind; you shouldn't worry, everything will be all right, won't it? Dreamily, you shake your head.";
          ],
          short_name "Temple",
          n_to [;
              if (m_base.oldman) return CorDeath();
          ],
          w_to [;
              <<Exit self>>;
          ],
          cant_go [;
              if (m_base.oldman)
                  "The doors don't open, but you'd have been surprised if they had, what
                  with you being a stranger in a secret facility and all.";
              if (self.cntg) {
                  print "Why would you want to do that? There's a comfortable throne waiting for you, and ";
                  if (m_base.ch_maidens) {
                      print "Ral";
                  } else {
                      print "Kor";
                  }
                  " will be back any minute with dinner.";
              }
              self.cntg = true;
              "You don't dare go deeper into the temple without permission; you don't know their ways.";
          ],
          before [;
              Exit:
                  thinkpos = 0;
                  score = score + 5;
                  if (m_base.oldman) {
                      print "A bit fed up now, you turn to stride out of the fake military base and
                      out into the desert. As you go, you feel as if a great weight has been
                      lifted; perhaps, this time, you'll wake up for real. ";
                      PAU();
                  } else {
                      print "With a terrific effort, you force yourself to ignore the urge to sit on the throne
                      and start walking back out of the temple. With each step, it feels like you're wading
                      deeper and deeper into treacle, but you keep going. Eventually, just as you're about to
                      cross the threshold, it's as if reality just snaps, like a piece of elastic. Dazed, you
                      turn around to see the temple literally dissolving around you, as if someone has poured
                      paint-stripper all over it, revealing jagged cave walls. Most of the floor is hard-packed
                      earth, but where the dais used to be you see only the gaping maw of a ralckor!^";
                  }
                  PlayerTo(cavern,2);
                  rtrue;
              Listen:
                  "Dead silence.";
              SitDown:
                  if (m_base.oldman) <<Sit p_couch>>;
                  <<Sit p_throne>>;
              Smell:
                  thinkpos = 0;
                  score = score + 5;
                  print "The odor in here is appalling, and it wakes you out of the trance that you're under.
                  As you struggle, the room literally dissolves around you, as if someone has poured paint-stripper
                  all over it, revealing jagged cave walls. Most of the floor is hard-packed earth, but where the
                  dais used to be you see only the gaping maw of a ralckor!^";
                  PlayerTo(cavern);
                  rtrue;
              Sleep:
                  "How can you go any further than you are?";
              Wake:
                  return CavWake();
          ],
          cntg false,
          omanfst true,
          rchange false,
          firstime false;

! 05/24/06

  RoomObj -> pantheonobj "pantheon"
    with  name 'pantheon' 'room' 'hall',
              description [;
              <<Look pantheon>>;
          ],
          before [;
              Take, Remove, Touch, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ];

! 04/24/06

  Object  -> p_light "sunlight"
    with  name 'sun' 'sunlight' 'light',
          description
              "The golden light blinds you, making it impossible to see any of the details within the room.",
          before [;
              Take, Remove, Touch, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  concealed static;

! 04/24/06

  Object  -> p_throne "large gold throne"
    with  name 'big' 'large' 'gold' 'heavy-looking' 'throne' 'thick' 'red' 'cushion' 'seat',
          description [;
              print "Big and heavy-looking, the throne glistens in a shaft of sunlight. You're looking
              appreciatively at the thick, red cushion on the seat when you notice your reflection in
              the high back. ";
              PSY();
              "^This is real, though, isn't it? The fuzz in your head gets worse, but you don't feel inclined to
              worry about it. You'll just go and sit on the throne and everything will be fine.";
          ],
          before [;
              Enter, Sit:
                  return ThrnDth(1);
              Search:
                  return ThrnDth(2);
              Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return ThrnDth(3);
          ],
     has  static scenery;

! 09/10/07

  Object  -> p_dais "dais"
    with  name 'raised' 'dais' 'long' 'rectangular' 'of' 'stairs',
          description
              "Long and rectangular, the dais is made of the same, neatly dressed stone
              as the rest of the temple. It is stepped on all four sides, rising about
              half a meter from the floor. Standing on it, you can see a large wooden
              table and a golden throne.",
          before [;
              Enter, Sit:
                 return ThrnDth(1);
              Search:
                 return ThrnDth(4);
              Take, Touch, Remove, Turn, PushDir, Push, Pull:
                 return ThrnDth(5);
          ],
     has  static scenery;

! 09/10/07

  Object  -> p_table "long dining table"
    with  name 'long' 'dining' 'table' 'square' 'slablike' 'thick' 'rectangular' 'chunky' 'legs',
          description
              "The person who made this table was probably more used to working with
              stone, because everything about it is square and slablike, from the
              thick rectangular top to the chunky square legs. It would probably seat
              about thirty people, though at present there are no chairs other than
              the throne.",
          before [;
              Sit:
                  return ThrnDth(1);
              Search:
                  return ThrnDth(6);
              Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return ThrnDth(7);
          ],
     has  static scenery;

! 09/10/07

  Object  -> p_doors "immense stone doors"
    with  name 'immense' 'stone' 'doors',
          description
              "Each door is fashioned from an immense slab of stone, about five meters
              high and two meters wide. On this side, they're completely plain.",
          before [;
              Enter:
                  <<Exit pantheon>>;
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull, Open, Close:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery pluralname;

! 09/10/07

  ORchSe  -> p_windows "high windows"
    with  name 'high' 'window' 'windows' 'openings' 'opening' 'slit' 'slits',
          description
              "Up near the ceiling, you can see a few small openings, more like slits
              than anything else. They seem to be positioned to cast light on the dais
              in the center of the room.",
     has  scenery pluralname;

! 09/10/07

  OutRch  -> p_reflect "reflection"
    with  name 'reflection',
          description [;
              print "Your reflection is hard to make out. ";
              return PSY();
          ];
