
! 01/31/07

  Movable datapad
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'data' or 'pad' or 'datapad' or 'switch') return 0;
              w2 = NextWord();
              if (w1 == 'switch') {
                  self.dpswitch = true;
                  return 1;
              }
              if (w1 == 'data' && w2 == 'switch') {
                  self.dpswitch = true;
                  return 2;
              }
              if (w1 == 'data' && w2 == 'pad') {
                  self.dpswitch = false;
                  return 2;
              }
              self.dpswitch = false;
              return 1;
          ],
          short_name "data pad",
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              if (self notin player) {
                  move self to player;
                  PFT();
              }
              if (self.dpswitch) {
                  if (self.dpstchon) {
                        PHt();
                      "he depressed switch now provides power to the data pad.";
                  }
                  "It's a standard push button switch.";
              }
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out a";
                  } else {
                      print "The";
                  }
              } else {
                  print "The";
              }
              if (self.dpstchon) {
                  print " beaten data pad, marred with deep scratches across its face, ";
                  if (e_beacon.eb_notseen) "that ";
                  "now glows, while a depressed switch can be seen on the left hand side of the unit providing power.";
              }
              print " beaten data pad, marred with deep scratches across the screen's face, ";
              if (e_beacon.eb_notseen) print "that ";
              print "gives you a horrid feeling";
              if (player in cavern) {
                  print " these skeletal remains suffered a brutal death. A";
              } else {
                  print ", while a";
              }
              print " push button switch can be seen on the left hand side of the pad";
              if (zipchip in self) ". Also, inserted into the data pad is a zipchip.";
              ".";
          ],
          invent [;
              if (self in player) {
                  print "a data pad";
                  if (zipchip in self) print "^    a zipchip";
                  rtrue;
              }
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(26);
          ],
          before [;
              Read:
                  if (self in tc_shrine && tc_shrine.fieldon) {
                      PFT();
                      return PBS();
                  }
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  if (self.dpstchon) {
                      print "The display's deep scratches make it too hard to read.";
                      if (omni_trans in player) " You might try inserting the zipchip into the OmniTrans to view the data.";
                      new_line;
                      rtrue;
                  }
                  "The unit is off, displaying no data at all.";
              Push:
                  if (self in tc_shrine) return PYC();
                  if (zipchip notin self) "The data pad won't work without a zipchip inserted.";
                  if (self.dpstchon) {
                      self.dpstchon = false;
                      "You press the switch turning off the data pad.";
                  }
                  self.dpstchon = true;
                  if (TestShrine() || TestAirLock()) "As you press the switch, you can hear the data pad come to life, but it doesn't penetrate this dark gloom.";
                  "As you press the switch, turning on the data pad, it comes alive with a soft glow.";
              Show:
                  if (second == adar) {
                      adar.grief = true;
                      print "~Dear God, that was Zy'gnan's data pad,~ ";
                      if (m_base.ch_maidens) {
                          print "cries Captain Adar, fighting back the tears. Suddenly she loses it, breaking down as she cries out";
                      } else {
                          print "says Captain Adar startled. Lowering his head, he says";
                      }
                      ", ~what have I done to us?~";
                  }
              FlipOff, SwitchOff:
                  if (self in tc_shrine) return PYC();
                  if (zipchip notin self) "That's already off.";
                  if (self.dpstchon) {
                      self.dpstchon = false;
                      "You press the switch turning off the data pad.";
                  }
                  "That's already off.";
              SwFlip, SwitchOn, UseItem:
                  if (self in tc_shrine) return PYC();
                  if (zipchip notin self) "The data pad won't work without a zipchip inserted.";
                  if (self.dpstchon == false) {
                      self.dpstchon = true;
                    if (TestShrine() || TestAirLock()) "As you press the switch, you can hear the data pad come to life, but it doesn't penetrate this dark gloom.";
                      "As you press the switch, turning on the data pad, it comes alive with a soft glow.";
                  }
                  "That's already on.";
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
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Use:
                  if (self in player) {
                      if (second == controlpanel or al_circuit) return PDP();
                      rfalse;
                  }
                  return PYC();
          ],
          dpstchon false,
          dpswitch false,
    has   container open;
