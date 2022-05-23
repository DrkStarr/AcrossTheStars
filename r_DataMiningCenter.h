
! ---------------------------------------------------------------------------- !
!       The DATA MINING CENTER. 04/12/06
!
  RoomShp radar_room "Data Mining Center"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              if (self.rrdaemonstart) {
                  self.rrdaemonstart = false;
                  cq_head.hreport = true;
                  StartDaemon(self);
                  score = score + 5;
                  thinkpos = 2;
              }
              if (cargo_hatch.hatchopen) {
                  desk.desdhide = true;
                  print "The room is barren: computer banks torn out of their sockets. Only the large
                  circular desk is left in the middle of the room";
                  PDskChld();
                  print "An open hatchway lies to port, while the engineering access cover is ";
                  if (rr_eacover.panopn) "opened, giving you access to the e-tubes.";
                  "closed.";
              }
              if (self.flowoff) {
                  print "The equipment is still here, but none of it's working since you shut off the
                  flow regulator. An open hatchway lies to port, while the engineering access cover is ";
                  if (rr_eacover.panopn) "opened, giving you access to the e-tubes.";
                  "closed.";
              }
              if (self.piratesgone) {
                  print "The equipment is still here, ";
                  if (radar.power) print "and it's still working. That can only mean that the pirates haven't";
                  else print "but deactivated; the pirates mustn't have";
                  print " finished their looting yet. An open hatchway lies to port,
                  while the engineering access cover is ";
                  if (rr_eacover.panopn) "opened, giving you access to the e-tubes.";
                  "closed.";
              }
              if (self.rrfrstme) {
                  self.rrfrstme = false;
                  print "Normally, there's a team of three working here, sorting through the
                  Sat-Net's cross-traffic concerning this quadrant. Today, however, the place
                  is deserted; something must be badly wrong. The equipment is still working,
                  though, and a local readout from a mining satellite looks like something is
                  off the port bow, and it's huge. This far out, that can only mean a comet or
                  a pirate ship. Either way, it's a problem, one the Captain should know about
                  immediately.
                  ^^Since no one is here, it looks like that duty falls upon you. In the middle of
                  the computer banks lining the starboard bulkhead sits the prox-tar, with a datacard that
                  should have all the information you need, but it's been acting up lately.
                  Engineering hasn't been able to fix it yet -- they've already got too much to
                  do just keeping this bucket of bolts in the sky -- but they told you that if you
                  switch it off before you take the card out, all should be well.";
              } else {
                  if (radar.power) {
                      print "Rows of computer banks encircle the room, relaying the information
                      broadcast across the Sat-Net. All the posts are unmanned, and the local
                      readout from the mining satellite doesn't look good. Something is off
                      the port bow, and it's huge.";
                  } else {
                      print "Rows of computer banks encircle the room, while posts go unmanned,
                      equipment broken and shorted out.";
                  }
              }
              print " An open hatchway lies to port, while the engineering access cover is ";
              if (rr_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          w_to [;
              return main_junction;
          ],
          in_to [;
              <<Enter rr_eacover>>;
          ],
          cant_go
              "You can go through the port hatchway or into the e-tube.",
          before [;
              Exit:
                  PlayerTo(main_junction);
                  rtrue;
              HideRoom:
                  switch (pattack) {
                      8: print "You crawl under the desk, just in the nick of time.^";
                      default: print "You crawl under the desk.^";
                  }
                  PlayerTo(under_desk);
                  rtrue;
              Listen:
                  if (proxtar.power) {
                      print "Mixed in with the low murmur of the engines, you can hear a quiet
                      humming noise coming from the prox-tar";
                      if (proxtar.proxhit == false) {
                          proxtar.proxhit = true;
                          ". Reaching out gingerly, you give it the lightest of touches and receive
                          a powerful electric shock for your pains. Clearly, the problem is worse
                          than usual this morning.";
                      }
                      ".";
                  }
          ],
          daemon [;
              piraterange = piraterange - 25;
              piratetheta = piratetheta - 2;
              piratephi = piratephi + 1;
              if (piraterange == 0) {
                    pattack = 2;
                    StopDaemon(self);
                    StartDaemon(pirates_board);
              }
          ],
          flowoff false,
          rrfrstme true,
          note_taken true,
          captainknow true,
          enterbridge false,
          piratesgone false,
          rrdaemonstart true;

! 04/28/06

  RoomObj -> radarobj "data mining center"
    with  name 'ship' 'center' 'room',
              description [;
              <<Look radar_room>>;
          ];

! 04/18/06

  Object  -> radar "computer banks"
    with  name 'computer' 'computers' 'of' 'bank' 'banks',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (self.power) "The computer banks encircle the room, relaying the Sat-Net's broadcast, screens filled with information.";
                  "The computer banks encircle the room, but have been disabled with no power going to them.";
              Read:
                  "Try reading the screens.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, UseItem:
                  "There's no power switch for the computer banks; they're hard-wired straight into the ship's electrical system.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
              Unplug:
                  "There's nothing to unplug; the computer banks are hard-wired into the ship's electrical system.";
          ],
          power true,
          coffeesplit false,
    has   scenery static pluralname;

! 04/14/06

  Object  -> desk "desk"
    with  name 'desk' 'table' 'bureau' 'large' 'circular',
          description [;
              print "The large circular desk sits in the middle of this room";
              if (radar.power) print ", mostly covered by embedded digital charts that display this quadrant";
              PDskChld();
              "The space underneath is bigger than your bunk; on bad days, you've been sorely
              tempted to take refuge there, hidden from the world.";
          ],
          describe [;
              if (self.desdhide) {
                  self.desdhide = false;
                  rtrue;
              }
              print "^In the middle of the room sits a large circular desk";
              if (radar.power) print ", with its digital charts turned on";
              PDskChld();
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Close, Open:
                  "It's not that type of desk.";
              Enter, Hide:
                  switch (pattack) {
                      8: print "You crawl under the desk, just in the nick of time.^";
                      default: print "You crawl under the desk.^";
                  }
                  PlayerTo(under_desk);
                  rtrue;
              LookUnder:
                  "It looks like there's enough room for you to hide under the desk.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          twobj false,
          desdhide false,
    has   supporter enterable static;

! 04/12/06

 Object  -> proxtar "prox-tar"
   with  name 'prox-tar' 'proxtar' 'prox-tars' 'proxtars' 'prox-tar^s' 'proxtar^s' 'case' 'teletype' 'machine' 'prox' 'tar' 'unit' 'proximity' 'detector',
         description [;
             if (radar.coffeesplit) {
                 print "The prox-tar has been disabled due to some moron who spilled ";
                 switch (iproxdis) {
                     1: print "coffee";
                     2: print "tea";
                     3: print "water";
                 }
                 " all over the place.";
             }
             if (self.power) {
                 if (self.desfrst) {
                     self.desfrst = false;
                     print "The prox-tar (proximity detector) -- an out-of-date device, which the
                     military still relies on -- is a simple computer used to report the location
                     of hazardous objects, asteroids, comets, or space-junk, downloading the
                     information onto datacards. The unit does have a datalink to Command, but on
                     a ship this old it was broken long before you were recruited. Now the datacards
                     have to be couriered up there by low-level crewmen (like you).^^";
                 }
                 print "An anonymous-looking box about twenty centimeters square and ten centimeters
                 tall, the prox-tar has become the bane of your life. Its only notable features
                 are a slot on the front for a datacard (currently ";
                 if (datacard in self) {
                     print "occupied";
                 } else {
                     print "empty";
                 }
                 ") and a cantankerous power switch round the back.
                 Getting the thing switched on or off was a real pain until you discovered, to
                 your great satisfaction, that a good hard thump anywhere on the case did the
                 job every time. (Fortunately, the Captain hasn't noticed the dents yet.)";
             }
             print "Thanks to your concussive maintenance, the prox-tar is currently switched off. ";
             if (datacard in self) "There's a datacard in the slot.";
             "The datacard slot is empty.";
         ],
         describe [;
             if (self.deshide) {
                 self.deshide = false;
                 new_line;
                 rtrue;
             }
             print "Encircling ";
             if (DeskTest() == 0) {
                 print "it";
             } else {
                 print "the desk";
             }
             print " are banks of computers with ", (the) self, " in the middle of them, along the starboard bulkhead";
             if (datacard in self) ". Inside ", (the) self, " sits a datacard.";
             ".";
         ],
         before [;
             Attack:
                 if (second == coffee_cup or wrench) {
                     if (second in player) <<ThrowAt second noun>>;
                     "You're not holding ", (the) second, ".";
                 }
                 if (self.power) {
                     if (self.proxhit) return PSk();
                     self.proxhit = true;
                     "As you're winding up to give the prox-tar a blow it will never forget,
                     something feels wrong. After a moment, you realize what it is: the
                     device is humming quietly. Reaching out gingerly, you give it the
                     lightest of touches and receive a powerful electric shock for your
                     pains. Clearly, it's going to fight back this morning.";
                 }
                 return PDE();
             Fix:
                 "Too bad your ~A~ School training barely covered how to use the unit, let alone how to repair it.";
             Plug, Unplug:
                 "Hard-wired into the radar system, the prox-tar lacks a plug.";
             SwFlip, SwitchOn, UseItem:
                 if (self.power) "That's already on.";
                 "The prox-tar doesn't seem to respond.";
             FlipOff, SwitchOff:
                 if (self.power) {
                     if (self.proxhit) return PSk();
                     self.proxhit = true;
                     if (second ~= nothing) {
                         if (second == coffee_cup or wrench)
                             "The moment ", (the) second, " touches the prox-tar, a powerful
                             electrical shock hits you, knocking you back. Clearly, the problem
                             is worse than usual this morning.";
                         "The switch is too small to operate with anything other than your bare
                         hands (and even then it only works about one time in three).";
                     }
                     "As you reach round to turn off the unit, a powerful electrical shock
                     hits you, knocking you back. Clearly, the problem is worse than usual
                     this morning.";
                 }
                 "That's already off.";
             Take, Remove, Turn, PushDir, Push, Pull:
                 return PAG();
             Touch, Search:
                 if (self.power) {
                     if (second ~= nothing) {
                         if (second == coffee_cup or wrench) {
                             if (self.proxhit) return PSk();
                             self.proxhit = true;
                             "The moment ", (the) second, " touches the prox-tar, a powerful
                             electrical shock hits you, knocking you back. Clearly, the problem
                             is worse than usual this morning.";
                         }
                         "Nothing happens.";
                     }
                     "Hot from operation, the prox-tar burns you as you touch it.";
                 }
                 "Even though the prox-tar's not operating, the machine is still warm.";
         ],
         power true,
         daemon [;
             if (player in radar_room) "^The prox-tar is bleeping, annoyingly.";
         ],
         desfrst true,
         deshide true,
         proxhit false,
         shutdown false,
   has   static container open;

! 08/05/07

  Object  -> rr_pswitch "power switch"
    with  name 'power' 'switch',
          before [;
              Attack:
                  <<Attack proxtar>>;
              Examine:
                  "The prox-tar's power switch must have been designed by a sadist: it's
                  small, fiddly and only works about one time in three. Fortunately, a
                  good hard thump anywhere on the prox-tar's case seems to work just as
                  well (and is a lot more satisfying).";
              Fix:
                  <<Fix proxtar>>;
              Plug, Unplug:
                  <<Plug proxtar>>;
              Search, Touch:
                  <<Touch proxtar>>;
              SwFlip, SwitchOn, UseItem:
                  <<SwitchOn proxtar>>;
              FlipOff, SwitchOff:
                  <<SwitchOff proxtar>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static concealed;

! 01/20/08

  Object  -> rr_ch_ss "digital charts"
    with  parse_name [w1 w2;
              w1=NextWord();
              if (w1 ~= 'speed' or 'course' or 'chart' or 'charts' or 'chart^s' or 'ship' or 'ships' or 'ship^s') return 0;
              w2=NextWord();
              if (w1 == 'chart' or 'charts' or 'chart^s' or 'ship' or 'ships' or 'ship^s' && w2 == 'speed') {
                  self.cspeed = true;
                  return 2;
              }
              if (w1 == 'chart' or 'charts' or 'chart^s' or 'ship' or 'ships' or 'ship^s' && w2 == 'course') {
                  self.cspeed = false;
                  return 2;
              }
              if (w1 == 'speed') {
                  self.cspeed = true;
                  return 1;
              }
              if (w1 == 'course') {
                  self.cspeed = false;
                  return 1;
              }
              return 0;
          ],
          before [;
              Attack:
                  return PDE();
              Examine, Search, Read:
                  if (radar.power) {
                      if (self.cspeed) {
                          if (galley.gpboard) "The ship's speed reads: 0.015 Sub Light";
                          "The ship's speed reads: 0 Sub Light";
                      }
                      "The ship's heading reads: 118.26*";
                  }
                  return PCO();
              SwitchOn, SwFlip, UseItem:
                  "That's already on.";
              FlipOff, SwitchOff:
                  return PLN();
              Take, Remove, Turn, PushDir, Push, Pull:
                  <<Take rr_charts>>;
          ],
          cspeed false,
    has   static concealed;

! 01/20/08

  Object  -> rr_charts "digital charts"
    with  name 'embedded' 'digital' 'star' 'chart' 'charts' 'scattered' 'red' 'dots' 'sat-net' 'satnet' 'net' 'transponder' 'transponders' 'planet' 'planets' 'quadrant' 'blue' 'octagon' 'enrys' 'system',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (radar.power) "The digital star charts blink with life, as scattered red dots
                  display all Sat-Net transponders. Few planets can be seen in this quadrant,
                  while the blue octagon of your ship display's course and speed.";
                  return PCO();
              Read, UseItem:
                  if (radar.power) "It looks like the ship is near the Enrys System.";
                  return PCO();
              SwitchOn, SwFlip:
                  "That's already on.";
              FlipOff, SwitchOff:
                  return PLN();
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The digital charts are embedded within the desk.";
          ],
    has   static concealed pluralname;

! 01/20/08

  Object  -> rr_screen "screens"
    with  name 'screen' 'screens' 'monitor' 'monitors',
          before [;
              Attack:
                  return PDE();
              Examine, Search:
                  if (radar.power) "The screens are filled with all sorts of information, changing as the updates come in from the Sat-Net.";
                  "The screens are blank, cold, and dead.";
              Read:
                  if (radar.power) {
                      if (galley.gpboard) "A deep-space monitoring station shows the transport ship being towed by a black corsair. Hopefully the station's crew aren't asleep at their posts.";
                      if (self.scrset) {
                          self.scrset = false;
                          PArrayScr();
                      }
                      if (iscreen == 4) iscreen = -1;
                      iscreen++;
                      switch (scrn_reply-->iscreen) {
                          1: if (under_desk.patk) "Enrys IV's Tel-Com satellite displays what looks like two asteroids colliding.";
                             "Enrys IV's Tel-Com satellite displays what looks like two asteroids on a collision course.";
                          2: "Half of the Solar-Sync satellite is covered by an obscure black shape.";
                          3: "Gamma-Recorder node 15738-H shows the transport ship hovering over Enrys IV.";
                          4: if (under_desk.patk) "The infrared display on S-Collector 738-0A shows two bright objects colliding.";
                             "The infrared display on S-Collector 738-0A shows two bright objects ready to collide.";
                          5: "The weather satellite for Enrys IV shows the transport ship against a black background,
                             lacking the planet it should be monitoring.";
                      }
                  }
                  "The screens are blank, cold, and dead.";
              SwitchOn, SwFlip, Push, UseItem:
                  if (radar.power) "They're already on.";
                  "They're hard-wired right into the computer banks.";
              FlipOff, SwitchOff:
                  if (radar.power) "They're hard-wired right into the computer banks.";
                  "They're already off.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
          ],
          scrset true,
    has   static concealed pluralname;

! 01/20/08

  Object  -> rr_msat "mining satellite"
    with  parse_name [w1 w2;
              w1=NextWord();
              if (w1 ~= 'mining' or 'satellite' or 'local' or 'readout') return 0;
              w2=NextWord();
              if (w1 == 'mining' or 'local' or 'satellite' && w2 == 'satellite' or 'local') {
                  self.lrout = false;
                  return 2;
              }
              if (w1 == 'mining' or 'local' && w2 == 'readout') {
                  self.lrout = true;
                  return 2;
              }
              if (w1 == 'mining' or 'satellite') {
                  self.lrout = false;
                  return 1;
              }
              if (w1 == 'local' or 'readout') {
                  self.lrout = true;
                  return 1;
              }
              return 0;
          ],
          before [;
              Attack:
                  if (self.lrout) return PDE();
                  "This is a Transport Ship, not a Battle Cruiser.";
              Examine, Search, Read:
                  "In the top corner of the mining satellite's survey camera, a dark object drifts toward the transport ship.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (self.lrout) return PAG();
                  "You can't affect things on the screen.";
          ],
          lrout false,
    has   static concealed;

! 05/13/08

  EACovr  -> rr_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph' 'panel',
          before [;
              Enter:
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(rr_etube);
                  rtrue;
          ],
          panopn false;
