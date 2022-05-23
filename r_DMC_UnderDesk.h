
! ---------------------------------------------------------------------------- !
!       The DATA MINING CENTER (UNDER DESK). 04/14/06
!
  RoomShp under_desk
    with  short_name [;
              print "Data Mining Center ";
              style roman;
              print "(under desk)";
              rtrue;
          ],
          description [;
              print "It's a little cramped, but somehow you've managed to squeeze your way in. ";
              if (self.patk) {
                  "You're briefly relieved that the maintenance staff keeps everything clean and
                  dust-free; you wouldn't want to sneeze now!";
              }
              "Down here it looks like the maintenance staff keeps everything clean and dust-free.";
          ],
          w_to [;
              print "You crawl out from underneath the desk.^";
              return radar_room;
          ],
          cant_go [;
              "You need to crawl out from underneath the desk, or just type EXIT.";
          ],
          before [;
              Exit, SUp:
                  print "You crawl out from underneath the desk.^";
                  PlayerTo(radar_room,2);
                  rtrue;
              HideRoom:
                  "You're already hiding.";
          ],
          patk false;

! 04/15/06

  RoomObj -> underobj "desk"
    with  name 'desk' 'table' 'bureau' 'circular' 'large',
          description
              "The large circular desk covers you completely.",
          before [;
              Exit:
                  <<Exit under_desk>>;
              Hide:
                  "You're already hiding.";
              LookUnder:
                  "You're here.";
          ];
