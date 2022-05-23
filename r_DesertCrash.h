
! ---------------------------------------------------------------------------- !
!       The DESERT CRASHED SHIP. 04/30/06
!
  Room    desert_crash "Desert"
    with  description [;
              if (crashed_ship.smoking) {
                  print "You stand on the edge of a scorching hot desert. Plumes of smoke pour
                  out of a crashed transport ship to the east, which are carried off by a strong
                  breeze. The engines throttle and grind, as desert winds kick sand into the
                  intakes. To the west, part of the mountain side has filled in the deep rocky
                  chasm, while all around you, the desert sun burns intensely underneath its fiery
                  glare.^";
                  if (crashed_ship.airlockopen == false && al_door.albroken == false) {
                      if (self.adarhint && adar in self) {
                          self.adarhint = false;
                          "^~You need to do something about that smoke,~ Captain Adar says, speaking up,
                          ~try opening up the cargo hatch, then the ship can vent itself.~";
                      }
                  }
                  rtrue;
              }
              if (thinkpos == 8) thinkpos = 7;
              "You're standing at the eastern edge of a long, rocky chasm running roughly
              north-south, on the other side of which stands a tall mountain with a jagged opening
              at its base. In every other direction there's nothing but scorching desert, stretching
              to the horizon, interrupted only by a crashed transport ship lying a short distance
              away to the east. Your recent explosive activities have filled the chasm with rubble
              here, creating a way across.";
          ],
          n_to [;
              if (noun == fore_obj) "You're not aboard ship now, matey.";
          ],
          s_to [;
              if (noun == aft_obj) "You're not aboard ship now, matey.";
          ],
          e_to [;
              if (noun == starboard_obj) "You're not aboard ship now, matey.";
              return PToCS();
          ],
          in_to [;
              return PToCS();
          ],
          w_to [;
              if (noun == port_obj) "You're not aboard ship now, matey.";
              if (adar in self) {
                  print "Captain Adar follows as you carefully walk across the filled in chasm.^";
                  MoveAdar(7);
              }
              DeleteCompassObjects();
              return chasm;
          ],
          cant_go [;
              if (noun == fore_obj || noun == aft_obj) {
                  return L__M(##Miscellany, 38);
              } else {
                  "You can only go east entering the ship or west towards the rocky chasm,
                  there's only burning sand in any other direction.";
              }
          ],
          before [;
              Listen:
                  if (crashed_ship.smoking) "The noisy engines struggle to run in bad conditions, as they surge to maintain intake pressure.";
                  if (spacesuit has worn && spacesuit.suitopen == false) "Dead silence.";
                  "You can only hear the soft sound of wind, whipping past your ears.";
              Smell:
                  if (crashed_ship.smoking) "Even though the smoke is blowing away from you, it can still be smelled upon the air.";
                  "There is nothing but fresh air on the breeze.";
          ],
          adarhint false;

! 07/29/07

  RoomObj -> desertobj "desert"
    with  parse_name [w1 w2;
              w1 = NextWord();
              w2 = NextWord();
              if (w1 == 'desert' && w2 == nothing) return 3;
              return 0;
          ],
          description [;
              <<Look desert_crash>>;
          ],
          before [;
              Search, Take, Remove, Turn, PushDir, Push, Pull:
                  "There's a lot of desert; that would take a long time.";
          ];

! 04/30/06

  Object  -> d_crashed_shipobj
    with  short_name "crashed ship",
          name 'crashed' 'ship' '7735ph' 'carbon' 'blasts' 'blast' 'transport' 'engine' 'engines' 'hull',
          describe [;
              rtrue;
          ],
          before [;
              Enter:
                  return PToCS();
              Examine, Search:
                  if (crashed_ship.smoking) "Heavy plumes of smoke pour out of the crashed ship, as the engines surge to maintain intake pressure, struggling with the sand.";
                  "The crashed ship doesn't look like she's taken much damage, with just a few carbon blasts across her hull.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
              Touch:
                  if (uniform in spacesuit) return PCF();
          ],
    has   static;

! 07/30/07

  OutRch  -> dcrsh_chasm "deep chasm"
    with  name 'deep' 'chasm' 'western' 'mountain' 'mountains',
          description
              "The western mountain has filled in the deep chasm allowing you to return to the large cavern.";
