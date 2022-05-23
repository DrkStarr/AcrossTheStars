
! ---------------------------------------------------------------------------- !
!       The MAIN AIRLOCK. 09/22/06
!
  RoomShp main_airlock "Main Airlock"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              print "The main airlock is empty, but for once this is to be expected.
              Only used to dock with ships or space stations, ";
              if (pland < (plimit+15)) {
                  print "the door is usually kept tightly closed, ";
                  if (ma_airlock has open) print "though, it's currently open";
                  else print "protecting you from the vacuum of space";
              } else {
                  print "the door is tightly closed";
              }
              print ". There's a control panel to operate the airlock on the aft bulkhead, while rows of
              empty space suits line the walls of this deserted room. ";
              if (blastdoor in self) print "The blast door blocks the port hatchway";
              else print "An open hatchway lies to port";
              print ", while the engineering access cover is ";
              if (ma_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          e_to [;
              if (ma_airlock has open) return MAirEnter();
          ],
          w_to [;
              if (blastdoor in self) "The blast door blocks your attempt.";
              TestMSuit();
              return secondary_junction;
          ],
          in_to [;
              <<Enter ma_eacover>>;
          ],
          cant_go
              "You can go through the port hatchway or the e-tube.",
          before [;
              Exit:
                  if (ma_airlock has open) return MAirEnter();
                  if (blastdoor in self) "The blast door blocks your attempt.";
                  TestMSuit();
                  PlayerTo(secondary_junction);
                  rtrue;
          ];

! 09/23/06

  RoomObj -> mairlockobj "main airlock"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'main' or 'ship' or 'room') return 0;
              w2 = NextWord();
              if (w2 == nothing) return 3;
              if (w1 == 'main' && w2 == 'airlock' or 'air') return 3;
              return 0;
          ],
          description [;
              <<Look main_airlock>>;
          ];

! 09/23/06

  Object  -> ma_airlock "airlock door"
    with  name 'airlock' 'air' 'lock' 'door',
          description [;
              print "The airlock is tightly sealed";
              if (pland < plimit) ", and is the only thing between you and the vacuum of space.";
              " shut.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Close:
                  if (self has open) {
                      give self ~open;
                      "You feel a little easier as the airlock comes down, closing off the gaping hole into deep space.";
                  }
                  "That's already closed.";
              Enter:
                  if (self has open) return MAirEnter();
                  "You need to open the airlock first.";
              Open:
                  if (self has open) "That's already open.";
                  if (pland >= (plimit+15)) {
                      if (second == prybar) "Even though you apply a little leverage, the door seems jammed and won't open.";
                      "The airlock door seems jammed for some reason and won't open.";
                  }
                  if (pland >= (plimit+10)) "You would have to be insane to try to open the airlock during reentry.";
                  if (self.alflowoff) "There's no power going to the control panel.";
                  if (mal_spacesuit in player && mal_spacesuit has worn) {
                      if (mal_spacesuit.malopn) {
                          mal_spacesuit.malopn = false;
                          print "(first closing the helm to the deep-space suit)^";
                      }
                      if (ma_panel.pressure) {
                          print "First you hear the ~thunk~ of the inner door sealing itself, then the hiss of the
                          airlock depressurizing. You start to imagine all the oxygen molecules flooding through
                          the vents, and check the seals on your suit nervously.
                          ^^Just as you manage to convince yourself that the suit is sound, the hiss dies away and
                          the outer door slides silently open, revealing the black emptiness of space. You clump
                          ungracefully across the floor, stumbling as you reach the hatch and go beyond the reach
                          of the ship's artificial gravity.^";
                          outside_airlock.oairdis = true;
                          d_obj.&name-->5 = '0101ph';
                          PlayerTo(outside_airlock);
                          rtrue;
                      } else {
                          give self open;
                          "The outer door slides silently open, revealing the black emptiness of space.";
                      }
                  }
                  "You would have to be insane to try to open the airlock in deep space.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          alflowoff false,
    has   static;

! 09/23/06

  Object  -> ma_panel
    with  parse_name [ w1 w2;
              w1 = NextWord();
              if (w1 ~= 'control' or 'panel' or 'red' or 'blue' or 'button' or 'buttons') return 0;
              w2 = NextWord();
              if (w1 == 'red' && w2 == 'button') {
                  self.red = true;
                  self.blue = false;
                  self.panel = false;
                  self.short_name = "red button";
                  return 2;
              }
              if (w1 == 'blue' && w2 == 'button') {
                  self.red = false;
                  self.blue = true;
                  self.panel = false;
                  self.short_name = "blue button";
                  return 2;
              }
              if (w1 == 'control' && w2 == 'panel') {
                  self.red = false;
                  self.blue = false;
                  self.panel = true;
                  self.short_name = "control panel";
                  return 2;
              }
              if (w1 == 'red') {
                  self.red = true;
                  self.blue = false;
                  self.panel = false;
                  self.short_name = "red button";
                  return 1;
              }
              if (w1 == 'blue') {
                  self.red = false;
                  self.blue = true;
                  self.panel = false;
                  self.short_name = "blue button";
                  return 1;
              }
              if (w1 == 'button' or 'buttons') {
                  self.red = false;
                  self.blue = false;
                  self.panel = false;
                  self.short_name = "button";
                  return 1;
              }
              if (w1 == 'control' or 'panel') {
                  self.red = false;
                  self.blue = false;
                  self.panel = true;
                  self.short_name = "control panel";
                  return 1;
              }
          ],
          short_name "control panel",
          description [;
              if (self.red) "The red button is labeled ~Open~.";
              if (self.blue && self.pressure) "The blue button is labeled ~Depressurize~.";
              if (self.blue && self.pressure == false) "The blue button is labeled ~Pressurize~.";
              if (self.panel) "The control panel has two buttons, one red and one blue, used to operate the airlock.";
              "Try looking at each individual button.";
          ],
          before [;
              Attack:
                  return PDE();
              FlipOff, SwitchOff:
                  if (self.panel || self.red || self.blue) "The panel doesn't work like that, try turning one on.";
                  "Try choosing an individual button.";
              SwFlip, SwitchOn, Touch, Push, UseItem:
                  if (self.red) {
                      if (ma_airlock.alflowoff) "There's no power going to the control panel.";
                      <<Open ma_airlock>>;
                  }
                  if (self.panel) "The panel doesn't work like that; try an individual button.";
                  if (self.blue) {
                      if (ma_airlock.alflowoff) "There's no power going to the control panel.";
                      if (self.pressure) {
                          if (mal_spacesuit in player && mal_spacesuit has worn) {
                              self.pressure = false;
                              move blastdoor to main_airlock;
                              if (mal_spacesuit.malopn) {
                                  mal_spacesuit.malopn = false;
                                  print "(first closing the helm to the deep-space suit)^";
                              }
                              "First you hear the ~thunk~ of the inner door sealing itself, then the hiss of the
                              airlock depressurizing. You start to imagine all the oxygen molecules flooding
                              through the vents, and check the seals on your suit nervously.
                              ^^Just as you manage to convince yourself that the suit is sound, the hiss dies away.";
                          }
                          "You'd have to be crazy to depressurize the airlock. How are you going to breath?";
                      } else {
                          self.pressure = true;
                          if (blastdoor in main_airlock) remove blastdoor;
                          "You feel the room equalize as pressure is once again exerted on your body, finally allowing
                          the blast door to open.";
                      }
                  }
                  "You need to choose an individual button to push.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
          ],
          red false,
          blue false,
          panel true,
          pressure true,
    has   static scenery;

! 10/25/06

  Object  -> ma_spacesuit "deep-space suit"
    with  parse_name [ w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'deep' or 'deep-space' or 'deepspace' or 'space' or 'suit' or 'suits' or 'spacesuit' or 'spacesuits') return 0;
              w2 = NextWord();
              if (w1 == 'deep' or 'deep-space' or 'deepspace' or 'space' && w2 == 'suits' or 'spacesuits') return 3;
              if (mal_spacesuit notin main_airlock or player or milpack && (w1 == 'deep' or 'deep-space' or 'deepspace' or 'space' && w2 == 'suit' or 'spacesuit')) return 3;
              w3 = NextWord();
              if (w1 == 'deep' && w2 == 'space' && w3 == 'suits') return 3;
              if (mal_spacesuit notin main_airlock or player or milpack && (w1 == 'deep' && w2 == 'space' && w3 == 'suit')) return 3;
              if (w1 == 'suits' or 'spacesuits') return 3;
              if (mal_spacesuit notin main_airlock or player or milpack && (w1 == 'suit' or 'spacesuit')) return 3;
              return 0;
          ],
          description [;
              print "The space suits that line the walls are used by certified crew members for deep-space EVAs.";
              if (self.noteva) " As you look at the plastic and metal, you wonder if you'll ever use your zero gravity training.";
              new_line;
              rtrue;
          ],
          article "the",
          before [;
              Attack:
                  return PDE();
              Enter, PutOn, UseItem, Wear:
                  if (mal_spacesuit in player && mal_spacesuit has worn) "You're already wearing that!";
                  if (mal_spacesuit in main_airlock || parent(mal_spacesuit) == nothing) PFT();
                  move mal_spacesuit to player;
                  give mal_spacesuit worn;
                  move uniform to mal_spacesuit;
                  return PYM();
              Take, Remove:
                  <<Take mal_spacesuit>>;
              PushDir, Push, Pull:
                  return PAG();
          ],
          noteva true,
    has   static concealed;

! 05/13/08

  EACovr  -> ma_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph',
          before [;
              Enter:
                  if (spmove == 16) return PPD(0);
                  if (ma_panel.pressure == false) "That could depressurize the ship.";
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  TestMSuit();
                  print "You enter the e-tube.^";
                  PlayerTo(ma_etube);
                  rtrue;
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (spmove == 16) return PPD(1);
                  if (ma_panel.pressure == false) "That could depressurize the ship.";
          ],
          panopn false;
