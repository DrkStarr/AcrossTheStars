
! 04/15/07

  Object  robowash "robo-wash"
    with  name 'robo-wash' 'robowash' 'robo' 'wash' 'robot' 'bot' '9989ph' '9999ph' 'washer',
          invent [;
              print "a robo-wash";
              rtrue;
          ],
          before [;
              Attack:
                  PDE();
                  if (self.working) Robotalk();
                  rtrue;
              Close:
                  if (self has open) {
                      give self ~open;
                      give self ~container;
                      self.&name-->6 = '9989ph';
                      self.&name-->7 = '9999ph';
                      "You close the storage container to the robo-wash.";
                  }
                  print "The storage container to the robo-wash is already closed.^";
                  if (self.working) Robotalk();
                  rtrue;
              Examine:
                  if (self.working) "The robo-wash trots around the room, picking up the plates, internally storing them.";
                  if (galley.cleanon) "The robo-wash is a two-foot tall robot that sits on top of the counter in the corner of the room, softly purring to itself as it cleans the dishes.";
                  if (self.latrobo) "The robo-wash is a two-foot-tall robot, currently sitting on top of the counter in the corner of the room, deactivated.";
                  self.latrobo = true;
                  "You smile, remembering the drunken night when the Chief Engineer first decided to give the robo-wash some ~personality~. Since then, it's been adopted as a sort of ship's pet; even the Captain's grown quite attached to ~him~.";
              FlipOff:
                  if (self.working) "~Hmm,~ scoffs the robo-wash, ~and I bet you think you're officer material.~";
              Follow:
                  if (self.working) {
                      print "But he's not trying to lead you anywhere.^";
                      return Robotalk();
                  }
                  "You can only do that to something animate.";
              Help:
                  if (self.working) "~If you want to help me,~ snaps the robo-wash, ~leave me to my work.~";
                  "You can only do that to something animate.";
              Hug:
                  if (self.working) "~You don't really care,~ says the robo-wash.";
                  "You can only do that to something animate.";
              Open:
                  if (self.working || galley.cleanon) {
                      print "You can't do that while the robo-wash is in operation.^";
                      return Robotalk();
                  }
                  if (self has open) "The storage container to the robo-wash is already open.";
                  give self open;
                  give self container;
                  self.&name-->6 = 'storage';
                  self.&name-->7 = 'container';
                  "You open the storage container revealing some cleaned plates.";
              Search:
                  if (self has open) "There are some clean plates inside.";
                  <<Examine self>>;
              SwFlip, SwitchOn, UseItem:
                  if (pattack > 2) "There's nothing for the robo-wash to clean up.";
                  if (galley.cleanon) "The robo-wash is in his cleaning cycle and won't clean up the rest of the room right now.";
                  if (self.working) {
                      print "The robo-wash is already doing his best to clean up the room.^";
                      return Robotalk();
                  }
                  return OnRobot(1);
              SwitchOff:
                  if (ma_airlock.alflowoff || self.working == false) "That's already off.";
                  give self ~scenery;
                  give self ~animate;
                  self.working = false;
                  galley.workon = false;
                  galley.cleanon = true;
                  move self to galley_counter;
                  "~Thank God,~ says the robo-wash as he quits picking up the dishes and hops back to his spot on
                  top of the counter. Closing his eyes, you can still hear the soft internal purr of the cleaning cycle.";
              Take, Remove, Turn, PushDir, Push, Pull, LookUnder:
                  if (self.working) "~Keep your hands to yourself buddy,~ squawks the robo-wash.";
                  "The robo-wash is too heavy to move.";
          ],
          life [;
              Answer:
                  return RobotAnswer(noun);
              AnswerDir:
                  return RobotAnswer(second);
              Ask:
                  if (self.trnon == false) return OnRobot(2);
                  switch(second) {
                      t_bridge: "~Oh, that's where all the great computers work,~ smiles the robo-wash, ~blinking away, talking back and forth to the crew. Respected, oh how I wish.~";
                      t_crew: "~They're useless,~ snaps the robo-wash, ~always ordering me around, like they have better things to do.~";
                      t_cup:
                          if (self.descup) {
                              self.descup = false;
                              "~Fill the mug why don't you,~ whines the robo-wash, ~the drink dispenser is right there.~";
                          }
                          self.descup = true;
                          "~Have some coffee,~ says the robo-wash, ~see if I care.~";
                      t_help: "~If you want to help me,~ snaps the robo-wash, ~leave me to my work.~";
                      t_meal: "~If you want something to eat,~ says the robo-wash cheerfully, ~turn on the meal synthesizer.~";
                      t_money: "~What, do I look like a bank,~ cries the robo-wash, ~and they have me doing their dishes too, amazing!~";
                      t_pirates: "~Pirates,~ cries the robo-wash, ~don't tell me you caused a bunch of trouble attracting them. That would be hell for both of us.~";
                      t_plates: "~Why don't you try cleaning up a few,~ snaps the robo-wash.";
                      t_player: "~Well, you may be new around here,~ says the robo-wash, ~but I'm sure you'll turn out like all the rest.~";
                      t_work: "~You try spending your entire life washing dishes and see how happy you'd be about it,~ squawks the robo-wash.";
                      t_zship, t_tship: "~You got to be kidding me,~ whines the robo-wash, ~this is the worst duty I've ever had.~";
                  }
                  "The robo-wash pays you no mind as he continues to clean off the tables.";
              AskChar, TellTo:
                  if (self.trnon == false) return OnRobot(2);
                  "The robo-wash pays you no mind as he continues to clean off the tables.";
              Kiss:
                  if (self.trnon == false) return OnRobot(3);
                  "~Whoopee!!!~ cries out the robo-wash, ~at least someone loves me.~";
              Tell:
                  if (self.trnon == false) return OnRobot(2);
                  "~What do you know about it,~ squawks the robo-wash as he continues to clean off the tables.";
          ],
          orders [;
              Rub:
                  if (self.trnon == false) return OnRobot(2);
                  if (noun == galley_seats or galley_tables or galley_food or galley_plate) "~What,~ cries the robo-wash, ~I'm not working hard enough.~";
                  "~That's your area buddy, not mine,~ the robo-wash says with a wink.";
              Help:
                  if (self.trnon == false) return OnRobot(2);
                  "~If you want to help me,~ snaps the robo-wash, ~leave me to my work.~";
              Hello:
                  if (self.trnon == false) return OnRobot(2);
                  "~Hello yourself,~ snaps the robo-wash, ~I'm over here slaving away...~";
              Yes, No, Sorry:
                  if (self.trnon == false) return OnRobot(2);
                  "~Liar,~ says the robo-wash, blinking his wide eyes. A moment later he turns back to cleaning off the tables.";
          ],
          trnon false,
          descup false,
          latrobo false,
          working false,
    has   static male animate;
