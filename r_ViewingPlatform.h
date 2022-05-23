
! ---------------------------------------------------------------------------- !
!       The VIEWING PLATFORM. 02/22/07
!
  Room    view_plat "Viewing Platform"
    with  description [;
              self.seenplat = true;
              "The platform faces north, towards the gleaming spires of an advanced city lying on the far horizon.
              In between, a huge impact crater has devastated the area, ruining the civilization that once lived
              here and allowing a vast desert to claim the landscape. On the other three sides, the mountain
              continues its climb towards the sun.
              ^^A row of stone seats has been carved into the northern edge of the platform, perched precipitously
              on the edge of the cliff, while the makeshift grappling hook is attached to a broken stone railing
              leading back down into the chamber below.";
          ],
          d_to [;
              <<Exit self>>;
          ],
          cant_go
                "You can only go down into the tranquility chamber.",
          before [;
              ClimbDown, Exit, GetOff, GetDown:
                  print "Carefully you climb down the makeshift grappling hook.^";
                  PlayerTo(tranquility_chamber);
                  rtrue;
              SitDown:
                  print "(on the carved stone seats)^";
                  <<Enter vp_seat>>;
              Smell:
                  "Fresh air fills your lungs.";
          ],
          seenplat false;

! 02/23/07

  RoomObj -> vp_obj "viewing platform"
    with  name 'viewing' 'platform' 'room',
          description [;
              <<Look view_plat>>;
          ];

! 02/23/07

  Object  -> vp_seat "seats"
    with  name 'four' 'stone' 'carved' 'seat' 'seats',
          description
              "Four seats have been carved at the room's edge, and look out towards the gleaming spires.",
          describe [;
              rtrue;
          ],
          before [;
              Enter, Sit:
                  print "You climb down into one of the carved stone seats.^";
                  PlayerTo(vplat_seats,1);
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static pluralname;

! 02/27/07

  OutRch  -> vp_city "advanced city"
    with  name 'abandoned' 'advanced' 'city' 'gleaming' 'spires' 'of' 'an',
          description
              "The gleaming spires of an advanced city lie on the far horizon across the desert.
              Except for a sparkle of light every now and then, the city looks long forgotten and
              abandoned in this wasteland.",
          article "an";

! 03/03/07

  Object  -> vp_hook "makeshift grappling hook"
    with  name 'makeshift' 'grappling' 'hook' 'rope',
          description
              "The makeshift grappling hook is attached to the broken stone railing, hanging down into the chamber below.",
          before [;
              Take, Remove, Tie, PushDir, Push, Pull:
                  "You better leave it hanging down into the chamber; it's the only safe way back down.";
          ],
    has   static scenery;

! 03/03/07

  Object  -> vp_bsrail "broken stone railing"
    with  name 'broken' 'stone' 'rail' 'railing',
          description
              "The stone railing is broken and worn down over time. Little of it stands, only an outcropping,
              which the makeshift grappling hook has attached itself to.",
          before [;
              Fix:
                  "Nothing short of magic could do that.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static scenery;

! ---------------------------------------------------------------------------- !
!       The VIEWING PLATFORM SITTING. 02/23/07
!
  Room    vplat_seats
    with  short_name [;
              print "Viewing Platform ";
              style roman;
              print "(in the seats)";
              rtrue;
          ],
          description
              "Sitting at the cliff's edge, with nothing before you but air, causes your stomach to knot.
              To quell your nerves, you focus on the gleaming spires of the advanced city sitting on the
              horizon. You can't help but wonder if they even knew of the noble civilization that perished
              here.
              ^^The platform lies above and behind you, reassuringly safe.",
          u_to [;
              <<Exit self>>;
          ],
          d_to
             "Are you suicidal? The fall would surely kill you.",
          cant_go
              "You can only climb up out of the seats.",
          before [;
              Exit, GetOff:
                  print "You get out of the seat, climbing back up to the platform.^";
                  PlayerTo(view_plat,1);
                  rtrue;
              SitDown:
                  "You're already sitting down.";
              Smell:
                  "Fresh air fills your lungs.";
          ];

! 02/23/07

  RoomObj -> vplats_obj "viewing platform"
    with  name 'viewing' 'platform' 'room',
          description [;
              <<Look view_plat>>;
          ];

! 02/23/07

  Object  -> vplats_seat "seats"
    with  name 'four' 'stone' 'carved' 'seat' 'seats',
          description
              "Four seats are placed at the cliffs edge, and look out towards the gleaming spires of an advanced city.",
          describe [;
              rtrue;
          ],
          before [;
              Enter, Sit:
                  "You're already sitting down.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static pluralname;

! 03/02/07

  OutRch  -> vplats_city "advanced city"
    with  name 'abandoned' 'advanced' 'city' 'gleaming' 'spires' 'of' 'an',
          description [;
              if (self.acscore) {
                  self.acscore = false;
                  score = score + 5;
                  "As you stare across at the gleaming spires, a flash of light catches your eye.
                  All of a sudden, thousands of people come flooding out of the advanced city,
                  and you look up to see a meteor plummeting towards you. Screaming, the citizens
                  run out into the wilderness, only to fall prey to large lizards only too ready
                  to feast on the scared humans. Terrified, buffeted by the emotion from the people
                  below, you stare up at the meteor helplessly.
                  ^^As quickly as it came, the vision fades, leaving you awash with fear and sadness.";
              }
              "The gleaming spires of an advanced city lie on the far horizon across the desert.
              Except for a sparkle of light every now and then, the city looks long forgotten and
              abandoned in this wasteland.";
          ],
          article "an",
          acscore true;
