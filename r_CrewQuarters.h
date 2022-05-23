
! ---------------------------------------------------------------------------- !
!       The CREW QUARTERS. 09/18/06
!
  RoomShp crew_quarters "Crew Quarters"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              print "On all sides, berths like your own are stacked one on top of another.
              Each berth is compact but functional, the system a model of space-saving efficiency. ";
              if (rack.curtain_open) {
                  print "The curtains to all berths but your own are closed";
              } else {
                  print "The curtains to all berths are closed";
              }
              if (self.rseen) {
                  self.rseen = false;
                  print ", which is strange: at the start of each duty shift, half of the crew should, like you,
                  be preparing to start work. Remembering your recent dream, you shiver slightly.
                  ^^Looking up at the clock, you see you've taken longer to wake up than usual; everyone else
                  must already be in the galley. The realization comes as a relief, until you remember what the
                  Captain'll do to you when he finds out: you'll be pulling extra duty for another week. Great,
                  this is the last thing that you need. Maybe if you get to your duty station in the DMC ASAP,
                  nobody will notice. ";
              } else {
                  if (pland > (plimit+14)) {
                      print " and the room is silent. ";
                  } else {
                      print ", and you can hear the low murmur of the engines from below. ";
                  }
              }
              if (b_hatchway has open) {
                  print "An open";
              } else {
                  print "A closed";
              }
              print " hatchway leads to the fore of the ship, while the head lies towards the aft.
              Also, the engineering access cover is ";
              if (cq_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          n_to [;
              <<Exit self>>;
          ],
          s_to [;
              <<Enter cq_head>>;
          ],
          u_to [;
              return EnterBerth();
          ],
          in_to [;
              <<Enter cq_eacover>>;
          ],
          cant_go
              "You can go through the fore hatchway or into the e-tube.",
          before [;
              Exit:
                  if (noun == b_hatchway) "Please use normal navigation directions. FORWARD, AFT, PORT, and STARBOARD.";
                  if (uniform has worn) {
                      if (b_hatchway has open) {
                          PlayerTo(main_junction);
                          rtrue;
                      }
                      give b_hatchway open;
                      print "(first opening the hatchway)
                      ^The bolts of the hatchway draw back with a reassuring ~thunk~.^";
                      PlayerTo(main_junction);
                      rtrue;
                  }
                  return PDV();
              HideRoom:
                  self.cqhide = true;
                  return EnterBerth();
              Smell:
                  "Unwashed socks, overused underwear, and stale cologne linger strongly in
                  the air. I guess these guys need to bathe a little more often.";
          ],
          fore false,
          rseen true,
          cqhide false,
          firsttime true,
          crewquarters false;

! 04/28/06

  RoomObj -> cq_obj "crew quarters"
    with  name 'crew' 'quarters' 'ship' 'room',
          description [;
              <<Look berth>>;
          ],
          before [;
              Hide:
                  <<HideRoom crew_quarters>>;
              Search:
                  "You might find something your really not looking for. It's better you
                  leave well enough alone in here.";
          ];

! 04/11/06

  Object  -> cq_rack "your berth"
    with  name 'berth' 'bunk' 'rack' 'bed' 'mat' 'your',
          description [;
              if (rack.curtain_open == false) "You can't see into your berth since the curtains are closed.";
              if (rack.lighton) {
                  print "Your berth's bathed in a warm reading light, illuminating a ";
                  if (self.made) {
                      print "rack that's properly squared away to military specifications";
                  } else {
                      print "blanket and pillow";
                  }
              } else {
                  print "Your berth's made of some unpronounceable alloy, ";
                  if (self.made) {
                      print "properly squared away to military specifications";
                  } else {
                      print "equipped with a blanket and pillow";
                  }
              }
              "; and even though it's not the most comfortable bunk in the 'verse, it is large enough to call home.";
          ],
          describe [;
              if (uniform notin player) rtrue;
              if (omni_trans.transtaken) rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              Close, Open:
                  "It's not that type of berth.";
              Enter, Sit, Climb:
                  return EnterBerth();
              Hide:
                  <<HideRoom crew_quarters>>;
              Make:
                  if (BerthTest()>0 || omni_trans.transtaken) {
                      if (berth_uniform in berth) "Your uniform would only get in the way if you tried to square up this rack.";
                      if (omni_trans.transtaken) print "Your OmniTrans";
                      else if (detonator in self) print "The detonator";
                      else if (playbeing in self) print "The Playbeing";
                      else if (coffee_cup in self) print "The large mug";
                      else if (ident_badge in self) print "The Captain's ident badge";
                      else if (ce_badge in self) print "The Chief Engineer's ident badge";
                      else if (og_datacard in self) print "The Omnibus Galacticus datacard";
                      else if (prybar in self) print "The pry bar";
                      else if (milpack in self) print "The field pack";
                      else if (knife in self) print "The knife";
                      else if (halfshelter in self) print "The half shelter";
                      " would only get in the way if you tried to square up this rack.";
                  }
                  if (self.made) "Your berth is already squared away, tight enough to bounce a cubit off it.";
                  self.made = true;
                  "You square away your berth, making very neat hospital corners at both ends. When you finish,
                  the rack is tight enough to bounce a cubit off it.";
              Search:
                  "You can't search your berth from down here.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          made false,
          lighton false,
          curtain_open false,
    has   supporter proper static scenery;

! 04/13/06

  Object  -> cq_rack_light "wall-mounted light"
    with  name 'wall-mounted' 'wall' 'mounted' 'light' 'lights' 'warm' 'reading' 'securely' 'encased' 'shock' 'proof',
          description
              "It's a standard government-issue, securely encased, shock proof light.",
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                  return PDE();
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, UseItem:
                  "You have to be in your berth to operate that light.";
              Take, Remove, Turn, PushDir, Pull:
                  return PAG();
          ],
    has   static;

! 09/02/06

  Object  -> cq_otherack "other berths"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'other' or 'berths' or 'racks') return 0;
              w2 = NextWord();
              if (w1 == 'other' && w2 == 'berths' or 'racks') return 2;
              if (w1 == 'other') return 0;
              return 1;
          ],
          article "the",
          description
              "All the curtains to the other berths are closed.",
          before [;
              Attack:
                  return PDE();
              Enter, Sit, Climb, Close, Open, Search:
                  "In accordance with NASLemInst 11101.M and Xulthe'en Navel Reg 1173, tampering
                  with personal equipment aboard a deep space transport is punishable by death.
                  This ensures trust amongst crew members.";
              Hide:
                  <<HideRoom crew_quarters>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          orcurtains false,
    has   scenery static pluralname;

! 09/02/06

  Object  -> cq_ocurtain "other curtains"
    with  name 'other' 'others' 'curtains' 'black' 'polymer' 'stain-proof' 'stain' 'proof',
          article "the",
          description
              "The matching black polymer stain-proof curtains are closed, preventing you from seeing what is in the other racks.",
          before [;
              Attack:
                  return PDE();
              Enter, Close, Open, Search, Take, Remove, Turn, PushDir, Push, Pull:
                  "In accordance with NASLemInst 11101.M and Xulthe'en Navel Reg 1173, tampering
                  with personal equipment aboard a deep space transport is punishable by death.
                  This ensures trust amongst crew members.";
              Hide:
                  <<HideRoom crew_quarters>>;
              Rip, Tear:
                  return PDE();
          ],
          orcurtains false,
    has   scenery static pluralname;

! 04/13/06

  Object  -> cq_rack_curtain "your curtains"
    with  name 'your' 'yours' 'mine' 'my' 'curtain' 'curtains' 'black' 'polymer' 'stain-proof' 'stain' 'proof',
          description [;
              print "The black polymer stain-proof curtains ";
              if (rack.curtain_open) {
                  print "are open";
              } else {
                  print "are closed";
              }
              " and shimmer in the light.";
          ],
          before [;
              Attack, Tear, Rip:
                    return PDE();
              Close:
                  if (rack.curtain_open) {
                      remove cq_rack_light;
                      rack.curtain_open = false;
                      if (pillow in cq_rack) {
                          remove pillow;
                          remove blanket;
                      }
                      "You close the curtains to your berth.";
                  }
                  "The curtains to your berth are already closed.";
              Open:
                  if (rack.curtain_open) "The curtains to your berth are already open.";
                  move pillow to cq_rack;
                  move blanket to cq_rack;
                  move cq_rack_light to crew_quarters;
                  rack.curtain_open = true;
                  "You open the curtains to your berth.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          firsttime true,
    has   scenery proper pluralname static;

! 09/18/06

  OutRch  -> cq_overhead "overhead light"
    with  name 'overhead' 'light' 'lights' 'blinding' 'neon',
          description [;
              if (rack_light.poweroff) "The overhead light is off since the power was disabled. The light reflecting in here is from the gaping hole in the galley.";
              if (rack_light.flowregoff) "The overhead light fails to work due to the flow regulator cutting the power off. The only light in here comes from emergency lighting.";
              "The overhead light glares down at you from above.";
          ];

! 09/18/06

  Object  -> cq_hatchway "hatchway"
    with  name 'forward' 'fore' 'hatchway' 'hatchways' 'hatchway^s' 'hatch' 'door' 'doors',
          description [;
              if (b_hatchway has open) "The forward hatchway leads to the main junction.";
              "The hatchway that leads to the fore of the ship is closed.";
          ],
          before [;
              Attack:
                  return PDE();
              Close:
                  if (self has open) give b_hatchway ~open;
              Enter:
                  <<Exit crew_quarters>>;
              Open:
                  if (uniform hasnt worn) return PDV();
                  if (self has open) "That's already open.";
                  give b_hatchway open;
                  give self open;
                  "The bolts of the hatchway draw back with a reassuring ~thunk~.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static enterable openable;

! 10/20/06

  Object  -> cq_head "head"
    with  name 'head' 'bathroom' 'lavatory',
          description
              "The head is a common area where all crew members can clean up and use the lavatory.",
          before [;
              Attack:
                  return PDE();
              Enter, UseItem:
                  if (self.hreport) "You don't need to use the head right now.";
                  "You'd better report to your duty station. It looks like you're already late,
                  and if the Captain finds out he'll have you pulling extra duty for another week.
                  He's already on the warpath thanks to you and your uniform not being squared away,
                  so he'll be even less amused than usual -- a sight no-one should ever have to see.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          hreport false,
    has   concealed static;

! 09/01/07

  Object  -> cq_clock "clock"
    with  name 'clock' 'time' 'minute',
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Examine, Read, Search:
                  if (ma_airlock.alflowoff) "With no power going to the clock, the display fails to function.";
                  "The digital display reads: ", iclk1, iclk2, ":", iclk3, iclk4, "";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   static scenery;

! 05/13/08

  EACovr  -> cq_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph' 'panel',
          before [;
              Enter:
                  if (uniform has worn) {
                      if (cq_head.hreport == false) <<Enter cq_head>>;
                      if (self.panopn == false) {
                          self.panopn = true;
                          print "(first opening the engineering access cover)^";
                      }
                      print "You enter the e-tube.^";
                      PlayerTo(cq_etube);
                      rtrue;
                  }
                  return PDV();
          ],
          panopn false;
