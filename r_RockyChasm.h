
! ---------------------------------------------------------------------------- !
!       The ROCKY CHASM. 04/28/06
!
  Room    chasm "Rocky Chasm"
    with  description [;
              if (self.blown) {
                  adar.cblown = true;
                  print "The concussive explosion of the atomaton detonator has brought down the
                  unstable mountainside, filling in the chasm and creating a way across to the east.
                  The wind, frustrated by the rubble, catches you full in the face now. You can head
                  east across your newly-created path, or west through an opening in the base of the
                  mountain.^";
                  if (adar in self) {
                      if (self.adarspeaks) {
                          adar.grief = false;
                          adar.adaroff = true;
                          self.adarspeaks = false;
                          print "^~Grash, that was pretty neat Darington, guess I owe you one,~ Captain Adar
                          says, flashing a smile as you turn around, ~Who knows, at this rate, we might
                          even make it off this rock.~^";
                      }
                  }
              } else {
                  thinkpos = 8;
                  print "It looks like a meteor struck here long ago, leaving an impact crater and creating
                  a long, rocky gash in the desert floor. Just here, the chasm is about three meters wide
                  and ten meters deep, with glassy-smooth sides. As if that wasn't enough, you can feel the
                  wind whipping through here, channeled by the chasm. Twin moons hang on the horizon, barely
                  visible in the sunlight.
                  ^^Just here, the mountainside looks dangerously unstable, eroded to the point of collapse;
                  it looks like a loud sneeze would bring it down. The only exit appears to be an opening in
                  the western face of the mountain, leading back to the foul-smelling cavern.^";
                  if (adar in self) {
                      if (self.sadar) {
                          self.sadar = false;
                          adar.adaroff = true;
                          print "^Captain Adar looks up at you. ~We crashed the ship on the other side of this gorge,~ ";
                          PHeShe();
                          print " shouts over the wind. ~If you can get us across, maybe we can get her flying again.~^";
                      }
                  }
              }
              if (TorchOn()) {
                  TorchOut();
                  "^The torch blows out in the wind as you step out of the cavern.";
              }
          ],
          d_to [;
              <<Climb chasmobj>>;
          ],
          e_to [;
              if (self.blown) {
                  if (adar in self) {
                      print "Captain Adar follows as you carefully walk across the filled chasm.^";
                      MoveAdar(8);
                  }
                  CreateCompassObjects();
                  return desert_crash;
              }
          ],
          w_to [;
              <<Enter ch_mountainside>>;
          ],
          in_to [;
              <<Enter ch_mountainside>>;
          ],
          cant_go [;
              if (self.blown) "You can only go east or west.";
              "You can only go west back into the foul-smelling cavern.";
          ],
          before [;
              Jump:
                  if (self.blown) {
                      "You don't need to do that; the chasm is filled in.";
                  } else {
                      deadflag = 1;
                      "You try to jump across the rocky chasm, and only fall to your death below.";
                  }
              Smell:
                  "There's nothing but fresh air on the breeze.";
          ],
          sadar true,
          blown false,
          adarspeaks true;

! 04/30/06

  RoomObj -> chasmobj "chasm"
    with  name 'chasm' 'gorge' 'deep' 'rocky' 'cliff' 'valley',
          description [;
              <<Look chasm>>;
          ],
          before [;
              Climb:
                  if (chasm.blown) "You don't need to climb down into the gorge; the chasm is filled in creating a path towards the east.";
                  if (adar in chasm) {
                      print "As you try to climb down into the gorge, Captain Adar stops you. ~Are you insane?~ ";
                      PHeShe();
                      " says, shouting over the wind. ~This chasm is dangerous and my arm is already broken. We're going to have to find another way across.~";
                  }
                  "As you try to climb down into the gorge, you lose your footing. Desperately you reach out, barely saving yourself from a brutal death.";
              JumpOver:
                  <<Jump chasm>>;
            ];

! 05/29/07

  Object  -> ch_mountainside "mountainside"
    with  name 'unstable' 'mountain' 'side' 'mountainside' 'loose' 'rock' 'rocks' 'stone' 'stones' 'western' 'face',
          description [;
              if (chasm.blown) "Rocks no longer adorn the side of the mountain, since the detonator set them free.";
              "The mountainside looks like it's fallen down into the chasm before, with loose
              rocks covering the entire western face.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack, Kick:
                  if (chasm.blown) rfalse;
                  deadflag = 1;
                  "You give one of the rocks a good hit, and believe it or not this is enough to
                  bring the entire side of mountain down on top of you in a cascade of stone.";
              Climb:
                  if (chasm.blown) {
                      if (adar has general) "You better do as Captain Adar says.";
                      "You don't want to cause another avalanche, do you?";
                  }
                  deadflag = 1;
                  "The rocks look like they're scalable, and at first it seems they are. But as
                  you start to make your way up the mountainside, rocks start to shift under your
                  weight, cascading down tons of rock, burying you at the bottom of the chasm.";
              Enter:
                  if (adar has general) {PAF(); MoveAdar(1);}
                  u_obj.&name-->4 = '7840ph';
                  chasm.sadar = true;
                  PlayerTo(cavern);
                  rtrue;
              Search, Take, Remove, Turn, PushDir, Push, Pull:
                  if (chasm.blown) "The mountainside is immovable.";
                  "You don't want to move any of these stones; they could fall down on top of you.";
          ],
    has   static;

! 05/29/07

  Object  -> ch_opening "opening"
    with  name 'opening',
          before [;
              Attack, Kick, Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
              Enter:
                  <<Enter ch_mountainside>>;
              Examine, Search:
                  "The opening leads back into the foul-smelling cavern.";
              Open:
                  return PCB();
           ],
    has   static concealed;
