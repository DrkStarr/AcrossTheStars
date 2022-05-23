
! 05/04/06

  Movable spacesuit "deep-space suit"
    with  name 'deep' 'deep-space' 'deepspace' 'space' 'suit' 'suits' 'spacesuit' 'spacesuits' 'helm' 'helmet' 'hood',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out a deep-space suit that";
                  } else {
                      print "Made from the latest alloys and plastics, the deep-space suit";
                  }
              } else {
                  print "Made from the latest alloys and plastics, the deep-space suit";
              }
              print " will keep you alive in the harshest of environments for up to 36 hours. It's a
              one-piece affair, designed to stretch or shrink to fit the wearer. The only rigid component
              is the helm. Right now the helm is ";
              if (self.suitopen) "open.";
              "closed.";
          ],
          describe [;
              if (self.dshidden) rtrue;
          ],
          after [;
              Disrobe:
                  if (e_beacon.eb_notseen && (player in crashed_ship or air_lock or sm_airlock)) {
                      give self worn;
                      "You can't take off the deep-space suit in all this smoke, how could you breath?";
                  }
                  adar.asksuit = false;
                  move uniform to player;
              Insert:
                  if (second == deadp_obj) {
                      move self to unholy_shrine;
                      "You drop ", (the) self, " into the pit.";
                  }
                  move self to player;
                  if (second == milpack) "The space suit is too bulky to fit into that.";
                  if (second == controlpanel or al_circuit) "That's too big to fit in there.";
                  if (second == sm_controlpanel) return PCR();
                  L__M(##Insert, 2, noun);
                  rtrue;
          ],
          before [;
              Close:
                  if (self in player && self has worn) {
                      if (self.suitopen) {
                          self.suitopen = false;
                          print "With the helm closed, the suit switches over to the internal air scrubbers. You're now enclosed in a totally self-contained environment.^";
                          if (adar in parent(player)) {
                              adar.asksuit = true;
                              "^Once shut, Captain Adar asks, ~Are you going to do something hazardous?~";
                          }
                          rtrue;
                      }
                      "The helm to the deep-space suit is already closed.";
                  }
                  "You need to put the deep-space suit on.";
              Drop:
                  adar.asksuit = false;
                  give self ~container;
              Open:
                  if (self in player && self has worn) {
                      if (e_beacon.eb_notseen && (player in crashed_ship or air_lock or sm_airlock)) "You can't open the helm to the deep-space suit in all this smoke, how could you breath?";
                      if (self.suitopen) "The helm to the deep-space suit is already open.";
                      self.suitopen = true;
                      adar.asksuit = false;
                      "Opening the helm, you expose yourself to the harsh desert air.";
                  }
                  "You need to put the deep-space suit on.";
              PutOn:
                  if (self in player) {
                      if (second == pedestal) return PedestalEnds(11);
                  }
                  give self ~container;
              Remove:
                  if (self has worn) {
                      if (e_beacon.eb_notseen && (player in crashed_ship or air_lock or sm_airlock)) {
                          give self worn;
                          "You can't take off the deep-space suit in all this smoke, how could you breath?";
                      }
                      give self ~worn;
                      adar.asksuit = false;
                      move uniform to player;
                      "You take off the deep-space suit.";
                  }
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
                  self.dshidden = false;
                  give self ~container;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use, UseItem:
                  if (self in player) rfalse;
                  return PYC();
              Wear:
                  if (self in tc_shrine) return PYC();
                  if (self has worn) "You're already wearing that!";
                  if (self in sm_airlock) return PCR();
                  if (self notin player) {
                      self.dshidden = false;
                      move self to player;
                      PFT();
                  }
                  TPackSuit();
                  give self worn;
                  give self container;
                  move uniform to self;
                  return PYM();
          ],
          dshidden true,
          suitopen true,
    has   clothing open;
