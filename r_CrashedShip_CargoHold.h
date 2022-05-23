
! ---------------------------------------------------------------------------- !
!       The CARGO HOLD. 05/04/06
!
  Object  air_lock "Cargo Hold"
    with  description [;
              ALDes();
          ],
          n_to [;
              if (adar in self) {
                  PAF();
                  MoveAdar(9);
              }
              return crashed_ship;
          ],
          e_to [;
              if (al_door.albroken) {
                  "The hole is surrounded by jagged and twisted metal; you'd never get
                  through it without doing yourself an injury, or at least making a real
                  mess of your uniform.";
              }
              if (crashed_ship.airlockopen) {
                  ALExit();
                  return desert_crash;
              }
          ],
          u_to [;
              if ((orb in milpack && milpack has open && (milpack in player or air_lock or smallcrate or uniform)) || orb in player or air_lock or smallcrate || (datapad has light && datapad in milpack && milpack has open && (milpack in player or air_lock or smallcrate or uniform)) || (datapad has light && datapad in player or air_lock or smallcrate)) {
                  if (adar in self) {
                      print "As you carefully climb up on the large crate Captain Adar says, ~Be careful up there.~^";
                  } else {
                      print "Carefully you climb up on the large crate.^";
                  }
                  InventMSMAir();
                  PlayerTo(sm_airlock,1);
                  rtrue;
              }
          ],
          cant_go [;
              if (crashed_ship.airlockopen) {
                  "You can only go through the fore hatchway or the starboard cargo hatch.";
              } else {
                  "You can only go through the fore hatchway.";
              }
          ],
          before [;
              Exit:
                  if (crashed_ship.airlockopen) {
                      ALExit();
                      PlayerTo(desert_crash);
                      rtrue;
                  }
                  if (adar in self) {
                      PAF();
                      MoveAdar(9);
                  }
                  PlayerTo(crashed_ship);
                  rtrue;
              Listen:
                  if (crashed_ship.smoking) "The noisy engines struggle to run in bad conditions, as they surge to maintain intake pressure.";
                  if (crashed_ship.airlockopen || al_door.albroken) "You can only hear the soft sound of wind, whipping past your ears.";
                  if (datapad in player or milpack && datapad.dpstchon) "You can hear the soft hum of the data pad.";
                  "Dead silence.";
              Yes:
                  return ALeave();
          ];

! 05/04/06

  RoomObj -> airlock_obj "cargo hold"
    with  parse_name [ w1 w2;
              w1 = NextWord();
              if (w1 ~= 'area' or 'ship' or 'room' or 'cargo' or 'hold') return 0;
              w2 = NextWord();
              if (w1 == 'cargo' && w2 == 'hold') return 2;
              if (w1 == 'cargo') return 0;
              return 1;
          ],
          description [;
              <<Look air_lock>>;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Search:
                  return L__M(##Search, 4);
              Take, Remove, Turn, PushDir, Push, Pull:
                  "That's fixed in place.";
          ];

! 08/18/06

  Object  -> al_door "cargo hatch"
    with  name 'cargo' 'hatch' 'door' 'frame' '7319ph',
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  if (loxtank.pour) {
                      if (smallcrate has general) {
                      } else {
                          if (player in sm_airlock) "The cargo hatch door is just out of your reach, you should try pushing the large crate closer.";
                      }
                      if (self.albreak) {
                          ALAlt();
                          if (second ~= prybar) {
                              if (prybar in player || prybar in milpack && (milpack in player or air_lock or sm_scrate or smallcrate or uniform)) {
                                  if (prybar in milpack) give milpack open;
                                  print "(using the pry bar)^";
                              }
                          }
                          return PAL(1);
                      }
                  }
                  return PHS();
              Close:
                  if (self.albroken) "It seems to be electric and can't be closed manually.";
                  if (crashed_ship.airlockopen == false) "That's already closed.";
                  "It seems to be electric and can't be closed manually, try using the control panel.";
              Cut:
                  return PHS();
              Enter:
                  if (crashed_ship.airlockopen) {
                      print "You step out of the open airlock into a burning hot desert, which causes you to retreat to the cooler side of the ship. ";
                      if (adar in air_lock) {
                          PAF();
                          MoveAdar(8);
                      } else {
                          new_line;
                      }
                      u_obj.&name-->4 = 'sky';
                      PlayerTo(desert_crash);
                      rtrue;
                  }
                  if (self.albroken) "The gaping hole is dangerous, you'd cut yourself up on the door frame.";
                  "The cargo hatch is sealed shut.";
              Examine, Search:
                  return ALDoor();
              Fix:
                  if (self.albroken) "You could never repair all that broken metal.";
                  if (ochip in controlpanel) {
                      if (ochip.destroy) {
                          if (cwire in controlpanel) {
                          } else {
                              "It's the control panel that needs fixing, not the cargo hatch.";
                          }
                       }
                  } else {
                      if (cwire notin controlpanel) "It's the control panel that needs fixing, not the cargo hatch.";
                  }
                  if (autocoolant notin al_gen or sm_alelectric && self.deseng) "It's the auxiliary power unit that needs fixing, not the cargo hatch.";
              Kick:
                  if (loxtank.pour) {
                      if (smallcrate has general) {
                      } else {
                          if (player in sm_airlock) "The cargo hatch door is just out of your reach, you should try pushing the large crate closer.";
                      }
                      if (self.albreak) {
                          ALAlt();
                          return PAL(2);
                      }
                  }
                  return PHS();
              Lock:
                  "You should probably leave the hatch alone.";
              Open:
                  if (crashed_ship.airlockopen) "That's already open.";
                  "It seems to be electric and can't be opened manually, try using the control panel.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  "It's securely bolted to the ship.";
              Touch:
                  if (uniform in spacesuit) return PCF();
                  if (loxtank.pour) "Be careful, your hand could stick to the metal.";
                  "The cargo hatch is hot to the touch, from sitting underneath the sun.";
              Unlock:
                  "You need to open it, not unlock it.";
          ],
          deseng false,
          albreak true,
          smosuit false,
          firstate true,
          albroken false,
    has   static openable lockable locked;

! 05/06/06

  Object  -> al_gen "auxiliary power unit"
    with  name 'auxiliary' 'power' 'unit' 'motor' 'turbine' 'apu' 'casing',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  return ALGen();
              SwitchOn, UseItem:
                  if (self.ps_turnedon) "The auxiliary power unit is already on if you didn't already notice the smoke.";
                  self.ps_beenon = true;
                  if (autocoolant in self) {
                      if (controlpanel has open) {
                          give controlpanel ~open;
                          give al_circuit ~open;
                          give sm_controlpanel ~open;
                          print "(first closing the control panel with the universal tool)^";
                      }
                      if (crashed_ship.airlockopen || al_door.albroken) {
                          print "As before, the auxiliary power unit kicks into life, and immediately you can feel that the
                          heat isn't so bad this time. You hear a painful grinding noise and smoke starts pouring
                          out of the ventilation shaft. You can still hear the auxiliary power unit valiantly running, under
                          the hum of the secondary ventilation shaft, as the smoke goes out the open airlock.^";
                          return StartSmoke();
                      } else {
                          if (cwire in controlpanel) {
                              if (crashed_ship.airlockopen) "The cargo hatch is already open.";
                              if (loxtank.pour) {
                                  if (al_door.albroken) "The hydraulic piston whines as it tries to open the broken cargo hatch, but only succeeds in tearing off a few more pieces of twisted metal.";
                                  CPOn();
                                  ALAlt();
                                  if (adar has general) {
                                      if (player in sm_airlock) {
                                          move adar to sm_airlock;
                                      } else {
                                          move adar to air_lock;
                                      }
                                  }
                                  print "With the control panel shorted out, the door shatters into a million pieces
                                  of jagged metal as the hydraulic piston kicks in. This creates a gaping hole in the
                                  middle of the door, which sucks out all the smoke in the room.^";
                                  if (adar has general) "^Captain Adar returns once the air is breathable again.";
                                  rtrue;
                              }
                              if (al_arm.fixed) {
                                  if (controlpanel.cp_scored) {
                                      controlpanel.cp_scored = false;
                                      score = score + 5;
                                  }
                                  CPOn();
                                  if (self.gentried) {
                                      print "As before, t";
                                  } else {
                                      print "T";
                                  }
                                  self.gentried = true;
                                  StSmVarSet();
                                  print "he auxiliary power unit reluctantly kicks into life. Just as your optimism
                                  is rising, you hear a painful grinding noise and smoke starts pouring out. Amazingly,
                                  though, you can still hear the auxiliary power unit valiantly running, under the hum
                                  of the secondary ventilation shaft.
                                  ^^You hear a low rumbling sound as the piston slowly starts to open the cargo
                                  hatch. As it does so, you feel your back start to get a little warm, but it's nothing
                                  to worry about. The hatch continues to open, and the smoke starts flowing through it
                                  and safely out into the desert.^";
                                  if (adar has general) {
                                      if (adar in air_lock or sm_airlock) {
                                          print "^Captain Adar turns to you, smiling, ";
                                      } else {
                                      if (player in sm_airlock) {
                                          move adar to sm_airlock;
                                      } else {
                                          move adar to air_lock;
                                      }
                                          print "^Captain Adar returns once the air is breathable again. ";
                                      }
                                      "~Wow, I never thought you'd get that door to work. I knew it was broken when
                                      I bought this ship, but the Altairian Dollar doesn't go as far as it used to
                                      and beggars can't be choosers.~";
                                  }
                                  rtrue;
                              }
                              if (bolt in al_arm) {
                                  if (self.gentried) {
                                      print "As before, t";
                                  } else {
                                      print "T";
                                  }
                                  print "he auxiliary power unit kicks into life, ";
                                  if (self.gentried) {
                                      print "but again you hear the";
                                  } else {
                                      print "and you hear a";
                                  }
                                  print " grinding noise, followed by billowing black smoke.";
                                  if (spacesuit.suitopen || adar in air_lock) {} else {
                                      print " At least";
                                      if (self.gentried) print ", this time,";
                                      self.gentried = true;
                                      print " the deep-space suit protects you.";
                                  }
                                  self.forcedout = false;
                                  move bolt to air_lock;
                                  smallcrate.boltloose = true;
                                  print "^";
                                  StartSmoke();
                                  if (self.forcedout) {
                                      self.forcedout = false;
                                      rtrue;
                                  }
                                  print "^";
                                  "You hear a low rumbling sound as the piston activates, followed by a sharp snap! as a
                                  flying bolt just misses you. The rumbling sound is replaced by the high-pitched whirring
                                  of a motor spinning freely.";
                              }
                              print "As before, the auxiliary power unit kicks into life, but with the
                              hydraulic piston missing a bolt, all you hear from it is the high-pitched
                              whirring of the motor, spinning freely.^";
                              return StartSmoke();
                          }
                          if (self.gentried) {
                              print "As before, t";
                          } else {
                              print "T";
                          }
                          self.gentried = true;
                          print "he auxiliary power unit kicks into life, and immediately you can feel that the heat isn't
                          so bad this time. Just as your optimism is rising, you hear a painful grinding noise
                          and smoke starts pouring out. You can still hear the auxiliary power unit valiantly running,
                          under the hum of the secondary ventilation shaft, but the room's slowly filling with
                          toxic fumes.^";
                          return StartSmoke();
                      }
                  } else {
                      self.gentried = true;
                      al_door.deseng = true;
                      "As you press the switch, you can hear the auxiliary power unit trying to kick over.
                      For a moment, it looks like there might be a little life left in the old girl after
                      all, but then you start to feel waves of heat coming off it, accompanied by a plume
                      of black smoke. The overheating gets worse until, within moments, the thermal shutoff
                      engages and shuts it down again.";
                  }
              FlipOff, SwitchOff:
                  if (e_beacon.eb_notseen) print "Feeling around in all this smoke, you finally find the power switch shutting it off. ";
                  if (self.ps_turnedon) {
                      self.ps_turnedon = false;
                      StopDaemon(self);
                      ialsmoke = 0;
                      remove smokeobj;
                      remove intsmokeobj1;
                      remove intsmokeobj2;
                      give controlpanel ~general;
                      e_beacon.eb_notseen = false;
                      crashed_ship.smoking = false;
                      d_crashed_shipobj.short_name = "crashed ship";
                      d_crashed_shipobj.&name-->2 = '7735ph';
                      print "You turn the auxiliary power unit off. As it winds down, the smoke stops pouring out.^";
                      if (adar notin air_lock && adar has general) {
                          MoveAdar(9);
                          "^Captain Adar returns once the air is breathable again.";
                      }
                      rtrue;
                  }
                  "The auxiliary power unit is already off.";
              SwFlip, Push:
                  if (self.ps_turnedon) <<SwitchOff self>>;
                  <<SwitchOn self>>;
              Take, Remove, Turn, PushDir, Pull:
                  "The auxiliary power unit is securely fastened to the engine.";
              Touch:
                  if (uniform in spacesuit) return PCF();
                  print "The casing ";
                  if (self.ps_turnedon) "is hot, burning you as you touch it.";
                  if (self.ps_beenon) "feels warm, as it dissipates the heat.";
                  "has buckled, feeling uneven and wrinkled.";
          ],
          daemon [;
              ialsmoke++;
              if (ialsmoke >= 2) {
                  if (crashed_ship.airlockopen == false && al_door.albroken == false) {
                      StopDaemon(self);
                      ialsmoke = 0;
                      remove smokeobj;
                      remove intsmokeobj1;
                      remove intsmokeobj2;
                      give controlpanel ~general;
                      self.ps_turnedon = false;
                      e_beacon.eb_notseen = false;
                      crashed_ship.smoking = false;
                      d_crashed_shipobj.short_name = "crashed ship";
                      d_crashed_shipobj.&name-->2 = '7735ph';
                      print "^The environmental regulator must have kicked in, because you hear
                      the auxiliary power unit wind down and stop.";
                      if (self.gendmnfrst) {
                          self.gendmnfrst = false;
                          print " Maybe if you'd vented the ship a bit more, the air wouldn't have
                          become toxic enough to trip the regulator.";
                      }
                      if (player in crashed_ship or air_lock) " The black smoke starts to die down.";
                      new_line;
                      rtrue;
                  }
              }
              if (player in crashed_ship) {
                  if (CHDoorOpen()) "^Smoke is pouring out of the cargo hold.";
              }
              if (player in desert_crash) "^Thick black smoke pours out of the crashed ship.";
          ],
          gentried false,
          ps_scored true,
          forcedout false,
          gendmnfrst true,
          ps_beenon false,
          ps_turnedon false,
     has  static scenery supporter;

! 05/06/06

  Object  -> controlpanel
    with  short_name "control panel",
          name 'control' 'panel' 'console',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Close:
                  if (self has open) {
                      if (wrench in player || wrench in milpack && (milpack in player or uniform or air_lock)) {
                          if (second ~= wrench) print "(using the universal tool)^";
                          give self ~open;
                          give al_circuit ~open;
                          give sm_controlpanel ~open;
                          "You close the control panel.";
                      }
                      if (second == nothing) "You need to close the control panel with some sort of tool.";
                      "You can't close the control panel with that. You need some sort of tool.";
                  }
                  "That's already closed.";
              Examine:
                  return PCPanel();
              Fix:
                  "You're going to have to tell me how.";
              Lock:
                  <<Lock al_door>>;
              SwFlip, Push, Turn, UseItem:
                  if (self has on) <<SwitchOff self>>;
                  <<SwitchOn self>>;
              Read:
                  if (self has general) {
                      if (crashed_ship.airlockopen) "The display reads: OPEN";
                      "The display reads: CLOSED";
                  }
                  "There's no readout on the display.";
              Open:
                  if (self has open) "That's already open.";
                  if (self has general) "Instead of electrocuting yourself to death, why don't you shut the power off first.";
                  if (wrench in player || wrench in milpack && (milpack in player or uniform or air_lock)) {
                      if (second ~= wrench) print "(using the universal tool)^";
                      give self open;
                      give al_circuit open;
                      give sm_controlpanel open;
                      print "You unscrew the control panel using the universal tool and open it up. Inside is a mass of circuitry";
                      if (ochip in self && cwire in self) {
                          print ", with a";
                          if (ochip.destroy) {
                              print " blackened";
                          } else {
                              print "n";
                          }
                          " operating chip sitting in the middle of it all bypassed with some copper wire.";
                      }
                      if (ochip in self) {
                          print ", with a";
                          if (ochip.destroy) {
                              print " blackened";
                          } else {
                              print "n";
                          }
                          " operating chip sitting in the middle of it all.";
                      } else {
                          if (cwire in self) ", with copper wire shorting it out.";
                          ".";
                      }
                  }
                  if (second == nothing) "You need to open the control panel with some sort of tool.";
                  "You can't open the control panel with that. You need some sort of tool.";
              Search:
                  if (self has open) {
                      if (cwire in self && ochip in self) {
                          print "Inside the control panel, copper wire bypasses the ";
                          if (ochip.destroy) print "blown ";
                          "operating chip.";
                      }
                      if (ochip in self) {
                          if (ochip.destroy) "Inside the control panel is a blown operating chip.";
                          "Inside the control panel is an operating chip.";
                      }
                      if (cwire in self) "Inside the control panel is some copper wire.";
                      "There's a receptacle for an operating chip, which you might be able to bypass.";
                  }
                  "You'll have to open it up to find out what's in there.";
              ShortOut:
                  if (self has open) {
                      if (cwire in self) "The short has already been created.";
                      if (second == zipchip or og_datacard or datapad) return PDP();
                      if (cwire in player or milpack) {
                          if (cwire.cwscore) {
                              cwire.cwscore = false;
                              score = score + 5;
                          }
                          move cwire to controlpanel;
                          return PBC();
                      }
                      "You don't have anything suitable to create the short.";
                  }
                  "You need to open the panel before you can do that.";
              SwitchOn:
                  if (self has general) {
                      if (cwire in self) "The control panel has been bypassed.";
                      if (ochip in self) {
                          if (ochip.destroy) "With the control panel's circuitry blown, the hatch fails to operate.";
                          self.oburnt = true;
                          ochip.destroy = true;
                          ochip.&name-->2 = 'blown';
                          ochip.short_name = "blown operating chip";
                          if (spacesuit has worn) print "Fumbling with gloved fingers, you manage to press the red button. ";
                          "Briefly, it lights up but then you hear the fzzzt! of something shorting out
                          inside and the light dies.";
                      }
                      if (cwire in self) "The control panel has been bypassed.";
                      "You need to short circuit the control panel to get it operating.";
                  }
                  "You press the button, but nothing happens; all the ship's systems are currently useless.";
              FlipOff, SwitchOff:
                  if (self has general) {
                      if (cwire in self) "The control panel has been bypassed.";
                      if (ochip.destroy) "With the control panel's circuitry blown, the hatch fails to operate.";
                      "The control panel is already off.";
                  }
                  "You press the button, but nothing happens; all the ship's systems are currently useless.";
              Take, Remove, PushDir, Pull:
                  "The control panel is securely bolted to the bulkhead.";
              Touch:
                  if (uniform in spacesuit) return PCF();
                  if (self has general) "With power going to the panel, it is slightly warm to the touch.";
                  "The panel is cold to the touch.";
          ],
          oburnt false,
          poweron false,
          cp_scored true,
          driveshaft false,
    has   static ~on ~open container scenery;

! 05/06/06

  ORchSe  -> al_arm "hydraulic piston"
    with  name 'large' 'hydraulic' 'piston',
          describe [;
             rtrue;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  return ALRam();
              Fix, Turn:
                  "You can't reach it from here.";
              Take, Remove, Touch, Turn, Push, PushDir, Pull:
                  "You can't reach the hydraulic piston from down here.";
          ],
          fixed false,
     has  container transparent;

! 07/27/07

  Object  -> al_button "large red button"
    with  name 'large' 'red' 'button',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  PHl();
                  "he large red button is used to operate the cargo hatch.";
              SwFlip, SwitchOn, Push, Touch, Turn, UseItem:
                  <<SwitchOn controlpanel>>;
              FlipOff, SwitchOff:
                  <<SwitchOff controlpanel>>;
              Take, Remove, PushDir, Pull:
                  "The large red button is part of the control panel.";
            ],
    has   concealed static;

! 07/29/07

  Object  -> al_circuit "circuitry"
    with  name 'circuitry' 'circuit',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  if (controlpanel has open) <<Search controlpanel>>;
                  "You need to open the control panel to do that.";
              SwFlip, Push, Turn, UseItem:
                  if (controlpanel has on) <<SwitchOff controlpanel>>;
                  <<SwitchOn controlpanel>>;
              ShortOut:
                  <<ShortOut controlpanel>>;
              SwitchOn:
                  <<SwitchOn controlpanel>>;
              FlipOff, SwitchOff:
                  <<SwitchOff controlpanel>>;
              Take, Remove, PushDir, Pull:
                  <<Take controlpanel>>;
              Touch:
                   if (controlpanel has open && uniform in spacesuit) return PCF();
                   if (controlpanel has open) "You don't want to get your fingers stuck inside.";
                   "You need to open the control panel to do that.";
          ],
    has   concealed static;

! 08/26/07

  Object  -> al_hatch "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s',
          before [;
              Close:
                  "In case of fire, this hatchway should be left open.";
              Enter:
                  if (adar in air_lock) {
                      PAF();
                      MoveAdar(9);
                  }
                  PlayerTo(crashed_ship);
                  rtrue;
              Examine, Search:
                  PHl();
                  "he hatchway leads to the fore of the ship.";
              Open:
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Touch:
                  if (uniform in spacesuit) return PCF();
                  "The hatchway is smooth to the touch.";
          ],
    has   concealed static enterable openable;

! 09/16/07

  Object  -> al_engine "engine"
    with  name 'engine' 'engines' 'shiny' 'new',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  return ALEngine();
              Take, Remove, Turn, Push, PushDir, Pull:
                  return PNH();
              Touch:
                  if (uniform in spacesuit) return PCF();
                  print "The metal ";
                  if (al_gen.ps_turnedon) "is hot, burning you as you touch it.";
                  if (al_gen.ps_beenon) "feels warm, as it dissipates the heat.";
                  "feels cold to the touch.";
          ],
    has   static scenery;

! 09/16/07

  Object  -> al_maindrive "main drive"
    with  name 'main' 'drive',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  return ALMDrive();
              SwFlip, Push, SwitchOn, UseItem:
                  "You don't know how, and it's probably missing too many parts to be of much use in any case.";
              Take, Remove, Turn, PushDir, Pull:
                  return PNH();
              Touch:
                  <<Touch al_engine>>;
          ],
    has   static scenery;

! 09/16/07

  Object  -> al_plaque "plaque"
    with  name 'maker' 'makers' 'maker^s' 'plaque',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search, Read:
                  return ALPlaque();
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The plaque is securely fastened to the engine.";
              Touch:
                  if (uniform in spacesuit) return PCF();
                  "The plaque feels warm to the touch, as heat radiates through the hull.";
          ],
    has   static scenery;

! 09/18/07

  Object  -> al_switch "switch"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 == 'switch') return 3;
              return 0;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  if (e_beacon.eb_notseen) {
                      print "Through the swirling black smoke, you can just make out that t";
                  } else {
                      print "T";
                  }
                  "his switch is used to operate the auxiliary power unit.";
              SwFlip, Push, Touch, Turn, UseItem:
                  if (al_gen.ps_turnedon) <<SwitchOff al_gen>>;
                  <<SwitchOn al_gen>>;
              SwitchOn:
                  <<SwitchOn al_gen>>;
              FlipOff, SwitchOff:
                  <<SwitchOff al_gen>>;
              Take, Remove, PushDir, Pull:
                  "The switch is part of the auxiliary power unit.";
            ],
    has   concealed static;

! 09/19/07

  Object  -> al_cable "cable"
    with  name 'cable' 'cables' 'wire' 'wires' 'wiring',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Climb:
                  "This isn't a gymnasium.";
              Eat, Taste:
                  return PDL();
              Examine, Search, Read:
                  return ALCable();
              Fix:
                  "They seem intact.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The cables are all securely fastened down. The pirates didn't want them, so why do you?";
              Unplug:
                  "The cables run through the ship, and just can't be simply unplugged.";
          ],
    has   static scenery pluralname;

! 09/19/07

  Object  -> al_plate "metal plate"
    with  name 'metal' 'plate' 'backplate' 'scoring' 'small' 'screw' 'screws',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  return ALMPlate();
              Open:
                  "The plate is flush against the bulkhead and is only supporting the panel.";
              Remove:
                  "You can't remove the plate, it's flush against the bulkhead and is only supporting the panel.";
              Take, Turn, Push, PushDir, Pull:
                  "The metal plate is securely fastened to the bulkhead and is only supporting the panel.";
          ],
    has   static scenery;

! 05/04/06

  Object  smallcrate "large crate"
    with  name 'large' 'crate',
          description [;
              if (e_beacon.eb_notseen) {
                  print "Through the swirling black smoke, t";
              } else {
                  print "T";
              }
              print "he large crate looks like some sort of durainium-plastic composite,
              which is strong and sturdy yet light and moveable. Currently it's ";
              if (self has general) "pushed against the cargo hatch sitting underneath the hydraulic piston.";
              "against the bulkhead.";

          ],
          before [;
              Climb, Enter, Stand:
                  if (adar in air_lock) {
                      print "As you carefully climb up on the large crate Captain Adar says, ~Be careful up there.~^";
                  } else {
                      print "Carefully you climb up on the large crate.^";
                  }
                  InventMSMAir();
                  PlayerTo(sm_airlock,1);
                  rtrue;
              Close:
                  "That's already closed.";
              Lock:
                  if (adar in air_lock) "Captain Adar stops you, ~Have you no respect, that's my cargo and you should not be handling it.~";
                  if (adar has general) "You should respect Captain Adar's cargo.";
                  "The crate is already locked.";
              Push, PushDir, Pull, Transfer:
                  if (second == al_arm && self has general) "The large crate is already underneath the hydraulic piston.";
                  if (self.boltloose) {
                      if (e_beacon.eb_notseen) {
                          if (self has general) {
                              give self ~general;
                              "Somehow you manage to push the large crate back in all this smoke.";
                          }
                          give self general;
                          "Somehow you manage to push the large crate under the hydraulic piston in all this smoke.";
                      }
                      if (self has general) {
                          give self ~general;
                          if (adar in air_lock) "Pushing the large crate back in place Captain Adar says, ~Be careful, would you.~";
                          "You push the large crate back across the cargo hold.";
                      }
                      give self general;
                      if (adar in air_lock) "As you push the large crate under the hydraulic piston, Captain Adar says, ~Please respect my cargo.~";
                      "You push the large crate under the hydraulic piston.";
                  }
                  if (second == al_arm) {
                      give self general;
                      if (e_beacon.eb_notseen) "Somehow you manage to push the large crate under the hydraulic piston in all this smoke.";
                      if (adar in air_lock) "As you push the large crate under the hydraulic piston, Captain Adar says, ~Please respect my cargo.~";
                      "You push the large crate under the hydraulic piston.";
                  }
                  if (self.pcrate) {
                      self.pcrate = false;
                      if (adar in air_lock) "Pushing the large crate back in place Captain Adar says, ~Be careful, would you.~";
                      "You push the large crate back across the cargo hold.";
                  }
                  self.pcrate = true;
                  if (adar in air_lock) "As you push the large crate deeper into the cargo hold, Captain Adar asks, ~Do you even know what you're doing?~";
                  "You push the large crate deeper into the cargo hold.";
              Read:
                  "The crate has no lettering on it at all, giving you no clue as to what is inside.";
              Take, Remove:
                  if (adar in air_lock) "Captain Adar stops you, ~Have you no respect, that's my cargo and you should not be handling it.~";
                  if (adar has general) "You should respect Captain Adar's cargo.";
                  "The crate is too big, you'd never be able to pull it through the hatch.";
              Open, Unlock:
                  if (adar in air_lock) "Captain Adar stops you, ~Have you no respect, that's my cargo and you should not be handling it.~";
                  "The large crate is locked with a 256 bit, changing, numeric sequence.
                  Without the corresponding key fod, you'll never be able to open the lock.";
              Touch:
                  if (uniform in spacesuit) return PCF();
                  "The plastic feels smooth to the touch.";
              UseItem:
                  return PYC();
          ],
          pcrate false,
          boltloose false,
    has   supporter scenery;

! ---------------------------------------------------------------------------- !
!       The CARGO HOLD (on large crate). 02/11/07
!
  Object  sm_airlock
    with  short_name [;
              print "Cargo Hold ";
              style roman;
              print "(on large crate)";
              rtrue;
          ],
          description [;
              return ALDes();
          ],
          d_to [;
              print "You get off the large crate.^";
              InventMSCrate();
              PlayerTo(air_lock,1);
              rtrue;
          ],
          cant_go
              "You can only climb down off the crate.",
          before [;
              ClimbDown, Exit, GetDown, GetOff:
                  print "You get off the large crate.^";
                  InventMSCrate();
                  PlayerTo(air_lock,1);
                  rtrue;
              Jump:
                  if (adar in self) "~That is what you call respect?~ scoffs Captain Adar with disgust, as you jump up and down on the crate.";
              Listen:
                  if (crashed_ship.smoking) "The noisy engines struggle to run in bad conditions, as they surge to maintain intake pressure.";
                  if (crashed_ship.airlockopen || al_door.albroken) "You can only hear the soft sound of wind, whipping past your ears.";
                  "Dead silence.";
              Yes:
                  return ALeave();
          ];

! 02/11/07

  RoomObj -> smairlock_obj "cargo hold"
    with  parse_name [ w1 w2;
              w1 = NextWord();
              if (w1 ~= 'area' or 'ship' or 'room' or 'cargo' or 'hold') return 0;
              w2 = NextWord();
              if (w1 == 'cargo' && w2 == 'hold') return 2;
              if (w1 == 'cargo') return 0;
              return 1;
          ],
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine:
                  <<Look sm_airlock>>;
              Search:
                  return L__M(##Search, 4);
              Take, Remove, Turn, PushDir, Push, Pull:
                  "That's fixed in place.";
          ];

! 02/11/07

  AirObj  -> sm_aldoor "cargo hatch"
    with  name 'cargo' 'hatch' 'door' 'frame',
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  <<Attack al_door>>;
              Close:
                  <<Close al_door>>;
              Cut:
                  return PHS();
              Enter:
                  <<Enter al_door>>;
              Examine, Search:
                  return ALDoor();
              Fix:
                  <<Fix al_door>>;
              Kick:
                  <<Kick al_door>>;
              Lock:
                  <<Lock al_door>>;
              Open:
                  <<Open al_door>>;
              Take, Remove, Turn, Push, PushDir, Pull:
                  <<Take al_door>>;
              Touch:
                  <<Touch al_door>>;
              Unlock:
                  "You need to get down to reach the control panel.";
          ];

! 02/11/07

  AirObj  -> sm_controlpanel
          with  name 'control' 'panel' 'console',
          short_name "control panel",
          before [;
              Examine, Search:
                  "From up here, the control panel is hard to get a good look at.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, Turn, Touch, UseItem:
                  return PCR();
          ],
    has   scenery container;

! 02/11/07

  AirObj  -> sm_arm "hydraulic piston"
    with  name 'large' 'hydraulic' 'piston',
          describe [;
              rtrue;
          ],
          before [;
              Examine, Search:
                  return ALRam();
              Fix, Turn:
                  if (smallcrate has general) {
                      if (al_arm.fixed) "The hydraulic piston has already been fixed.";
                      if (wrench in player or milpack && bolt in player or milpack or self) return FixBolt();
                      if (bolt in player or milpack or self) "You need to tighten the bolt with something.";
                      "You need the bolt to fix the hydraulic piston.";
                  }
                  return PRP();
              Open:
                  if (smallcrate has general) {
                      if (al_arm.fixed) "You've just fixed it; why undo your good work now?";
                      "The piston is already broken, you're going to need the bolt to fix it.";
                  }
                  return PRP();
              Take, Remove, Push, PushDir, Pull:
                  if (smallcrate has general) {
                      if (al_arm.fixed) "The hydraulic piston is securely bolted to the bulkhead.";
                      "The hydraulic piston swings back and forth, its base securely bolted to the bulkhead.";
                  }
                  return PRP();
              Touch:
                  if (smallcrate has general) {
                      if (uniform in spacesuit) return PCF();
                      "The metal feels smooth to the touch.";
                  }
                  return PRP();
          ],
    has   container transparent;

! 02/11/07

  AirObj  -> sm_alelectric "auxiliary power unit"
    with  name 'auxiliary' 'power' 'unit' 'motor' 'turbine' 'apu',
          before [;
              Examine, Search:
                  "From up here, the auxiliary power unit is hard to get a good look at.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, Turn, UseItem, Touch:
                  return PCR();
           ],
    has   static supporter scenery;

! 02/11/07

  AirObj  -> sm_scrate "large crate"
    with  name 'small' 'crate',
          before [;
              Examine, Search:
                  <<Examine smallcrate>>;
              Climb, Enter, Stand:
                  "You're already on that.";
              Push, PushDir, Pull, Take, Remove, Turn, Transfer, Open, Close, UseItem:
                  "You'll have to get off the large crate first.";
              Touch:
                  <<Touch smallcrate>>;
          ],
    has   supporter scenery;

! 07/27/07

  AirObj  -> sm_button "large red button"
    with  name 'large' 'red' 'button',
          before [;
              Examine, Search:
                  <<Examine al_button>>;
          ],
    has   concealed;

! 09/19/07

  AirObj  -> sm_circuit "circuitry"
    with  name 'circuitry' 'circuit',
          before [;
              Examine, Search:
                  "From up here, the circuitry is hard to get a good look at.";
          ],
    has   concealed;

! 08/26/07

  AirObj  -> sm_hatch "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'hatch',
          before [;
              Examine:
                  <<Examine al_hatch>>;
          ],
    has   scenery;

! 09/19/07

  AirObj  -> sm_engine "engine"
    with  name 'engine' 'engines' 'shiny' 'new',
          before [;
              Examine, Search:
                  return ALEngine();
          ],
    has   scenery;

! 09/19/07

  AirObj  -> sm_maindrive "main drive"
    with  name 'main' 'drive',
          before [;
              Examine, Search:
                  return ALMDrive();
          ],
    has   scenery;

! 09/19/07

  AirObj  -> sm_plaque "plaque"
    with  name 'maker' 'makers' 'maker^s' 'plaque',
          before [;
              Examine, Search, Read:
                  "From up here, the plaque is hard to get a good look at.";
          ],
    has   scenery;

! 09/19/07

  AirObj  -> sm_switch "switch"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 == 'switch') return 3;
              return 0;
          ],
          before [;
              Examine, Search:
                  "From up here, the switch is hard to get a good look at.";
          ],
    has   concealed;

! 09/19/07

  AirObj  -> sm_cable "cable"
    with  name 'cable' 'cables',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Climb:
                  <<Climb al_cable>>;
              Examine, Search, Read:
                  return ALCable();
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The cables are all securely fastened down. The pirates didn't want them, so why do you?";
              Unplug:
                  <<Unplug al_cable>>;
          ],
    has   scenery pluralname;

! 09/19/07

  AirObj  -> sm_plate "metal plate"
    with  name 'metal' 'plate' 'backplate' 'scoring' 'small' 'screw' 'screws',
          before [;
              Examine, Search:
                  "From up here, the metal plate is hard to get a good look at.";
          ],
    has   scenery;
