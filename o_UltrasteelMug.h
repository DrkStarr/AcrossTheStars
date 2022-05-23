
! 04/13/06

  Movable coffee_cup "large ultrasteel mug"
    with  name 'stained' 'large' 'cup' 'mug' '0100ph' 'ultrasteel',
          invent [;
              if (self has general) {
                  print "a large ultrasteel mug (filled with ";
                  switch (icupdis) {
                      1: print "coffee";
                      2: print "tea";
                      3: print "water";
                  }
                  print ")";
                  rtrue;
              }
          ],
          after [;
              Drop:
                  if (second == radar) {
                      if (radar.coffeesplit == false) {
                          if (self has general) return PourCup();
                      }
                  }
                  if (player in radar_room) {
                      if (second == nothing || second == proxtar) {
                          move self to location;
                          if (proxtar.power) {
                              ProxOff();
                              if (self has general) {
                                  print "As the large mug falls out of your hand, it hits the power
                                  switch to the prox-tar as ";
                                  switch (icupdis) {
                                        1: print "coffee";
                                        2: print "tea";
                                        3: print "water";
                                  }
                                  iproxdis = icupdis;
                                  " spills all over the place. Someone from maintenance is going to have
                                  to clean this up. At last silence descends.";
                              } else {
                                  "As the large mug falls out of your hand, it hits the power
                                  switch to the prox-tar on the way down. At last silence
                                  descends.";
                              }
                          }
                      }
                  }
                  if (self has general) {
                      give self ~general;
                      self.&name-->4 = '0100ph';
                      print "You spill the ";
                      switch (icupdis) {
                          1: print "coffee";
                          2: print "tea";
                          3: print "water";
                      }
                      print " as you drop the mug.^";
                      if (player in galley && robowash.working) "^~Like I don't have enough work to do,~ scoffs the robo-wash.";
                      rtrue;
                  } else {
                      print "Dropped.^";
                      if (player in galley && robowash.working) "^~Like I don't have enough work to do,~ scoffs the robo-wash.";
                      rtrue;
                  }
          ],
          before [;
              Attack:
                  if (self in tc_shrine) return PYC();
                  return PDE();
              Drink:
                  if (self in tc_shrine) return PYC();
                  if (self notin player) {
                      PFT();
                      move self to player;
                  }
                  return CCupDrink();
              Drop:
                  if (player in outside_airlock or ontopofship) return PLD();
              Examine, Search:
                  if (self in tc_shrine && tc_shrine.fieldon) return PSL();
                  PHi();
                  if (self has general) {
                      print "t's stained and slightly scuffed, but at least it's full of ";
                      switch (icupdis) {
                          1: print "coffee";
                          2: print "tea";
                          3: print "water";
                      }
                      ".";
                  }
                  "t's stained, slightly scuffed and (sadly) empty.";
              Fill:
                  if (self in tc_shrine) return PYC();
                  if (second == mb_lake) "You can't reach that from here.";
                  if (second ~= drinkrep or nothing) "You can't fill the large mug with that.";
                  if (coffee_cup in player or drinkrep) {
                      if (player in galley && drinkrep in galley_counter) {
                          if (self has general) {
                              print "The large mug is already full.^";
                              if (robowash.working) Robotalk();
                              rtrue;
                          } else {
                              if (drinkrep.mdtea) {
                                  self.&name-->4 = 'tea';
                                  icupdis = 2;
                                  give self general;
                                  print "You press the ~Tea~ button and, after a bit of gurgling, a liquid the
                                  color of used dishwater starts dribbling into the mug.^";
                                  if (robowash.working) Robotalk();
                                  rtrue;
                              }
                              if (drinkrep.mdwater) {
                                  self.&name-->4 = 'water';
                                  icupdis = 3;
                                  give self general;
                                  print "You press the ~Water~ button, and a slightly cloudy liquid starts
                                  splashing into the mug.^";
                                  if (robowash.working) Robotalk();
                                  rtrue;
                              }
                              self.&name-->4 = 'coffee';
                              icupdis = 1;
                              give self general;
                              print "You press the ~Coffee~ button and, after a bit of gurgling, the dark
                               liquid that passes for coffee around here gloops slowly into the mug.^";
                              if (robowash.working) Robotalk();
                              rtrue;
                          }
                      }
                  } else {
                      print "You haven't got that.^";
                      if (player in galley) {
                          if (robowash.working) Robotalk();
                      }
                      rtrue;
                  }
              Give:
                  if (self in player) {
                      if (second == adar) {
                          if (self has general) "Adar smiles and says, ~I'm not dehydrated enough to drink that quite yet.~";
                      }
                  }
              Insert:
                  if (self in player) {
                      if (second == robowash) "The robo-wash is a rather temperamental robot, you might not want to give your mug to him, he's been known to keep thing just out of spite.";
                      if (second == drinkrep) {
                          move self to drinkrep;
                         "You jiggle the large mug into the jaws of the cup-holder.";
                      }
                  }
              PUnder:
                  if (self in player) {
                      if (second == drinkrep) {
                          move self to drinkrep;
                         "You jiggle the large mug into the jaws of the cup-holder.";
                      }
                  }
              Pour:
                  if (self has general) {
                      if (second == proxtar or radar && radar.coffeesplit == false) return PourCup();
                      if (second == robowash && robowash.working) {
                          give self ~general;
                          self.&name-->4 = '0100ph';
                          "~Hey, what are you doing,~ squawks the robo-wash, getting out of the way
                          as he runs across the room.";
                      }
                      rfalse;
                  }
                  "The large mug is empty.";
              PutOn:
                  if (self in player) {
                      if (player in outside_airlock or ontopofship) return PLD();
                      if (self has general) {
                          if (second == proxtar or radar && radar.coffeesplit == false) return PourCup();
                      }
                      if (second == pedestal) return PedestalEnds(1);
                    }
              Remove:
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
              ThrowAt:
                  if (self in player) {
                      if (second == proxtar) {
                          if (proxtar.power) {
                              ProxOff();
                              move self to location;
                              print "You hurl the mug at the prox-tar with a little topspin and a lot
                              of venom. With a loud, ringing ~clang~";
                              if (self has general) {
                                  print " and a fountain of ";
                                  switch (icupdis) {
                                      1: print "coffee";
                                      2: print "tea";
                                      3: print "water";
                                  }
                              }
                              " it bounces off and lands on the floor, silencing the prox-tar at last.
                              Someone from maintenance isn't going to be very pleased with you.";
                          }
                          "That would only turn it back on, and you've had quite enough of its bleeping for today.";
                      }
                      if (second == radar) {
                          if (self has general) {
                              deadflag = 1;
                              "With a full mug of coffee, you let the thing fly across the
                              room. Much to your amazement, the entire radar station electronically
                              shorts out and catches on fire. The room is almost at once engulfed
                              in flames, and the rest of the ship shortly follows afterwards.";
                          }
                      }
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                      if (location == main_junction) {
                          move self to secondary_junction;
                      } else {
                          move self to location;
                      }
                      if (self has general) {
                          print "As the large mug bounces off ", (the) second, ", ";
                          switch (icupdis) {
                              1: print "coffee";
                              2: print "tea";
                              3: print "water";
                          }
                          " goes flying everywhere.";
                      }
                      print "The large mug bounces off ", (the) second, " landing on the ";
                      if (player in desert or self.pcdunes) "ground.";
                      if (player in main_junction) "deck below.";
                      "deck.";
                  }
              Use:
                  if (self in player) {
                      if (second == drinkrep) <<Fill self>>;
                      rfalse;
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          pcdunes false;
