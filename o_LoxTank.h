
! 07/26/07

  Movable loxtank
    with  name 'liquid' 'oxygen' 'liquid-oxygen' 'lox' 'tank' 'tanks' 'tank^s' 'valve',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out that i";
                  } else {
                      print "I";
                  }
              } else {
                  print "I";
              }
              print "t's a large";
              if (self.pour) {
                  print ", empty, tank";
              } else {
                  print " tank of liquid oxygen";
              }
              print ", used during space flight";
              if (self.connected) ", connected to the internal lines of the ship.";
              ".";
          ],
          short_name "liquid-oxygen tank",
          after [;
              Insert:
                  if (second == milpack) {
                      move self to player;
                      print (The) self, " is too big to fit into that.^";
                      rtrue;
                  }
              PutOn:
                  if (second == pedestal) return PedestalEnds(34);
          ],
          before [;
              Close, SwitchOff:
                  if (self.tankopen) {
                      self.tankopen = false;
                      "Carefully you close the tank's valve.";
                  }
                  "The tank's valve is already closed.";
              Drink:
                  return PLO();
              Pour:
                  if (loxtank.pour) "The tank is empty, with nothing coming out.";
                  return PPrLx();
              Open, SwitchOn:
                  if (self.connected) {
                      self.connected = false;
                      print "(first removing the internal lines)^";
                  }
                  if (self.tankopen) "The tank's valve is already open.";
                  self.tankopen = true;
                  "Cautiously you open the tank's valve.";
              Remove:
                  <<Take self>>;
              Take:
                  if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT) {
                      if (milpack in player or uniform) {
                          print "(first moving ";
                          FirstPrint();
                          AndPrint();
                          print " to the field pack)^";
                          self.loxnext = true;
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (self.connected) {
                      self.connected = false;
                      if (self.loxnext) {
                          print "(next removing the internal lines)^";
                      } else {
                          print "(first removing the internal lines)^";
                      }
                  }
                  cs_floorboards.loxtaken = true;
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (second == cs_lines) {
                      if (self.connected) "The internal lines are already connected to the liquid-oxygen tank.";
                      "Why bother, this ship will never fly again.";
                  }
                  if (second == spacesuit)
                      "The tank is designed to work with the internal lines of a space ship, not a deep-space suit.
                      Besides, the space suit has scrubbers to clean the air anyways.";
                  if (self in player) {
                      if (loxtank.pour) "The tank is empty, and has already been used.";
                      return PPrLx();
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          pour false,
          nseen true,
          loxnext false,
          tankopen false,
          connected true;
