
! ---------------------------------------------------------------------------- !
!       ON TOP OF SHIP. 02/19/07
!
  Room    ontopofship "On Top of Ship"
    with  description [;
              if (radar_room.enterbridge == false) {
                  StopDaemon(datacard);
                  StopDaemon(radar_room);
                  StopDaemon(pirates_board);
                  pattack = 10;
                  piraterange = 0;
                  bridge.dstop = false;
                  radar_room.enterbridge = true;
                  radar_room.captainknow = false;
                  print "As you make your way to the top of the ship, you see what was causing the prox-tar
                  to freak out. Headed straight for you is a large black ship, with no markings, and that
                  could mean only one thing. Space Pirates!^^[Hit any key]^";
                  PageBreak();
                  print "^Before you have time to think the ship collides with yours. You lose your grip
                  on the hand railing, and desperately reach out managing to grab hold of an aerial antenna.
                  Carefully working your way back to the ship.^";
                  return PirateAttack();
              }
              "From atop the ship you have a great view of a large black corsair towing you through space.
              Dread sinks in, as you realize that you're a prisoner of these pirates, and that you're going
              to have to face them or burn up out here on reentry. A rail system criss-crosses the hull around
              you, designed to aid routine maintenance.";
          ],
          d_to [;
              <<Exit self>>;
          ],
          cant_go
              "As you grab the rail, your footing slips and you're barely able to stop yourself drifting
              away into space. It may look easy when the experts do it, but you're not trained for this.",
          before [;
                Listen:
                    "Only dead silence in the cold of space.";
                Exit:
                    if (bu_planet in self) move bu_planet to outside_airlock;
                    print "Carefully you grab the rail, making your way down.^";
                    PlayerTo(outside_airlock);
                    rtrue;
          ];

! 02/20/07

  RoomObj -> otos_obj "ship"
    with  name 'on' 'top' 'of' 'ship' 'room',
          description [;
              <<Look ontopofship>>;
          ];

! 02/20/07

  Object  -> otos_antenna "aerial antenna"
    with  name 'aerial' 'antenna',
          description
              "Handling all the communications for the ship, about a half dozen of these have been erected out here.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static scenery;

! 02/20/07

  OutRch  -> otos_ship "large black ship"
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'pirate' or 'pirates' or 'large' or 'black' or 'ship' or 'corsair') return 0;
              w2 = NextWord();
              if (w1 == 'pirate' or 'pirates' or 'large' or 'black' && w2 == 'ship' or 'corsair') return 2;
              w3 = NextWord();
              if (w1 == 'large' && w2 == 'pirate' or 'pirates' or 'black' && w3 == 'ship' or 'corsair') return 3;
              return 1;
          ],
          description
              "The large black ship is attached to yours on the port side, pulling you through space.";
