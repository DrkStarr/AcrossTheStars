
! ---------------------------------------------------------------------------- !
!       These objects are moved into place as the game proceeds.
!

! 04/15/06

  Object  ship "large black ship"
    with  name 'pirate' 'large' 'black' 'ship' 'corsair' 'old' 'jolly' 'roger',
          before [;
              Attack:
                  "This is a Transport Ship, not a Battle Cruiser.";
              Kick:
                  "You can't kick the main viewport; it would mess up that spit shine polish.";
              Examine, Search:
                  print "As you look out the viewport, you see a large black ship ";
                  if (self.lookatflag) {
                      print "with";
                  } else {
                      self.lookatflag = true;
                      print "and realize it has";
                  }
                  " an old Jolly Roger painted on the side.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't affect things through the viewport.";
          ],
          lookatflag false,
    has   concealed static;

! 04/23/06

  Object  r_planet "planet"
    with  name 'harsh' 'burnt-red' 'burnt' 'red' 'planet',
          before [;
              Attack:
                  "This is a Transport Ship, not a Battle Cruiser.";
              Kick:
                  "You can't kick the main viewport; it would mess up that spit shine polish.";
              Examine, Search:
                  "It's hard to see past the large black ship blocking your view, but as you
                  look out the viewport you can make out a harsh burnt-red planet that looks
                  like its atmosphere has been scorched off.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't affect things through the viewport.";
          ],
    has   concealed static;

! 05/24/06

  Object  desertscene "desert"
    with  name 'dead' 'planet' 'harsh' 'burnt' 'burnt-red' 'burning' 'hot' 'red' 'unbearable' 'desert' 'sun',
          before [;
              Attack:
                  "This is a Transport Ship, not a Battle Cruiser.";
              Kick:
                  "You can't kick the main viewport; it would mess up that spit shine polish.";
              Examine, Search:
                  "As you look out the viewport, you see a harsh burnt-red desert with a hot sun that
                  beats down on a dead planet. It looks like little, if anything, is alive out there.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't affect things through the viewport.";
          ],
    has   concealed static;

! 11/08/06

  Object  crew_asteroid "asteroid"
    with  name 'small' 'asteroid' 'asteroids' 'asteroid^s' 'crew' 'mate' 'mates' 'crewmates' 'cloud' 'clouds' 'bloated' 'bodies' 'body' 'slowly' 'spinning',
          before [;
              Attack:
                  "This is a Transport Ship, not a Battle Cruiser.";
              Kick:
                  "You can't kick the main viewport; it would mess up that spit shine polish.";
              Examine, Search:
                  "As you look out the viewport, the disgusting site of bloated bodies slowly spining in vacuum of space makes you sick.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't affect things through the viewport.";
          ],
    has   concealed static;

! 08/13/07

  Object  tbeam "tractor beam"
    with  name 'tractor' 'beam' 'tractorbeam',
          before [;
              Attack:
                  "This is a Transport Ship, not a Battle Cruiser.";
              Kick:
                  "You can't kick the main viewport; it would mess up that spit shine polish.";
              Examine, Search:
                  "As you look out the viewport, you can see the tractor beam coming out of the pirate ship, wrapping around yours.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't affect things through the viewport.";
          ],
    has   concealed static;

! 04/17/06

  OutRch  overhead_light "overhead light"
    with  name 'overhead' 'light' 'lights' 'blinding' 'neon',
          description [;
              if (rack_light.poweroff) "The overhead light is off since the power was disabled. The light reflecting in here is from the gaping hole in the galley.";
              if (rack_light.flowregoff) "The overhead light fails to work due to the flow regulator cutting the power off. The only light in here comes from emergency lighting.";
              "The overhead light glares down at you from above.";
          ];

! 04/19/06

  Object  space_lock "quantum entanglement lock"
    with  name 'big' 'quantum' 'entanglement' 'lock',
          description
              "To unlock it, you need a 1024-bit code, which isn't determined until someone observes the key.
              Without the key, you're stuck.",
          before [;
              Attack:
                  "Nothing you can do, short of blowing up the ship, will open the quantum entanglement lock.";
              Open, Unlock:
                  "Come on now, you think you can open a quantum entanglement lock with what you have in your
                  inventory?";
              SwFlip, SwitchOn:
                  "That's already activated.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              UseItem:
                  return PSH();
          ],
    has   concealed lockable locked static;

! 04/20/06

  Object  s_panel "secret panel"
    with  name 'secret' 'panel',
          description [;
              if (self.sopen) {
                  "The secret panel is moved aside, revealing an opening in the fore bulkhead.";
              } else {
                  "This panel is studded in two rivet intervals instead of one, like all of the others,
                  and is the only indication that there's an opening behind it in the fore bulkhead.";
              }
          ],
          before [;
              Close, Pull:
                  if (self.sopen) {
                      self.sopen = false;
                      remove c_s_opening;
                      "You close the secret panel, hiding the opening in the fore bulkhead.";
                  } else {
                      "The secret panel is already closed.";
                  }
              Enter:
                  if (self.sopen == false) {
                      self.sopen = true;
                      print "(first opening the secret panel)^";
                  }
                  <<Enter c_s_opening>>;
              Open, Take, Remove, PushDir, Push:
                  if (self.sopen) {
                      "The secret panel is already open.";
                  } else {
                      self.sopen = true;
                      move c_s_opening to cargo_hold;
                      "You move the panel out of the way, revealing a opening in the fore bulkhead
                      just large enough for you to squeeze through.";
                  }
          ],
          sopen false,
    has   concealed static;

! 05/25/06

  Object  c_s_opening "opening"
    with  name 'small' 'opening' 'hidden' 'compartment' 'secret',
          description
              "It looks like there's a small opening in the fore bulkhead that goes to a hidden compartment.",
          before [;
              Enter:
                  print "You crawl into the hidden compartment.^";
                  PlayerTo(hidden_compartment);
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static;

! 04/20/06

  Object  h_large_crate "large crate"
    with  name 'large' 'crate' 'cargo',
          before [;
              Examine, Search, Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't see the large crate; it's just blocking you in.";
          ],
    has   concealed static;

! 05/25/06

  Object  ts_bulkhead "bulkhead"
    with  name 'bulkhead' 'bulkheads' 'wall' 'walls',
          description
              "The bulkheads are big, ugly, and painted with a dull color of gray.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          found_in berth radar_room bridge galley engine_room cargo_hold hidden_compartment armory main_airlock main_junction secondary_junction
    has   concealed static;

! 05/25/06

  OutRch  b_hatchway "hatchway"
    with  name 'forward' 'fore' 'hatchway' 'hatchways' 'hatch' 'door' 'doors',
          description [;
              if (self has open) "The forward hatchway leads to the main junction.";
              "The hatchway that leads to the fore of the ship is closed.";
          ],
          before [;
              Close, Enter, Open, Take, Remove, Turn, PushDir, Push, Pull:
                  "You need to get out of the rack first.";
          ],
    has   enterable openable;

! 05/25/06

  Object  skivvies "your skivvies"
    with  name 'your' 'skivvies',
          description
                  "They're the only thing you're wearing.",
          before [;
              Disrobe, Drop, Remove:
                  "Let's not be rude.";
              PutOn:
                  if (second == player) "You're already wearing them!";
              Take:
                  "You already have them.";
              Turn:
                  "You'd have to take them off first.";
              Wear:
                  "You're already wearing them!";
          ],
    has   static proper concealed worn pluralname;

! 04/23/06

  Object  pillow "pillow"
    with  name 'standard' 'government' 'issue' 'government-issue' 'pillow' 'stuffing',
          before [;
              Examine, Search:
                  "It's a standard government-issue pillow, overused, with little stuffing left.";
              Push, PushDir, Pull:
                  "You push the pillow to the other side of the rack.";
              Take, Remove:
                  "The pillow should probably stay in the rack; you might look a little strange
                  walking around the ship with that thing.";
              Turn:
                  "You turn the pillow over in your rack.";
          ],
    has   concealed static;

! 04/24/06

  OutRch  desert_sun "sun"
    with  name 'blinding' 'blazing' 'sun' 'sunlight',
          description [;
              if (player in vplat_seats) "It's blinding to look at and burns your flesh, as you sit underneath it.";
              "It's blinding to look at and burns your flesh, as you stand underneath it.";
          ],
          found_in desert dunes m_base chasm desert_crash view_plat vplat_seats;

! 04/25/06

  Object  desert_desert "burnt red desert"
    with  name 'burnt' 'burning' 'red' 'scorching' 'harsh' 'barren' 'hot' 'desert' 'deserted' 'planet' 'sand' 'sands' 'dune' 'dunes' 'place',
          description
              "The burnt red desert is harsh and barren, and you notice that nothing lives in this deserted place.",
          before [;
              Search, Take, Remove, Turn, PushDir, Push, Pull:
                  "There's a lot of desert; that would take a long time.";
          ],
          found_in desert dunes m_base chasm desert_crash
    has   concealed static;

! 05/25/06

  Object  cargo_desert "burnt red desert"
    with  name 'burnt' 'burning' 'red' 'scorching' 'harsh' 'barren' 'hot' 'desert' 'deserted' 'planet' 'sand' 'sands' 'dune' 'dunes' 'place' 'outside',
          description
              "The burnt red desert is harsh and barren, and it looks like little, if anything, lives out there.",
          before [;
              Enter:
                  PlayerTo(desert,2);
                  rtrue;
              Search:
                  "You need to go outside to do that.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You need to go outside to do that.";
          ],
    has   concealed static;

! 05/02/06

  Object  access_panel "self-sealing metal plate"
    with  name 'self' 'seal' 'sealing' 'self-sealing' 'metal' 'plate' 'improvised' 'suction',
          description
              "The self-sealing metal plate is used to repair hull breaches, but you've never heard of pirates using it to seal access points.",
          before [;
              Close:
                  "That's already closed.";
              Open:
                  if (prybar in player) {
                      if (second == prybar) "You don't want to expose yourself to the vacuum of space.";
                      "(using the pry bar)
                      ^You don't want to expose yourself to the vacuum of space.";
                  }
                  if (second ~= nothing) {
                      print (The) second, " doesn't seem to do the job.^";
                      rtrue;
                  }
                  return PNH();
              Remove:
                  if (second ~= nothing) {
                      print (The) second, " doesn't seem to do the job.^";
                      rtrue;
                  }
                  return PNH();
              Take, Turn, PushDir, Push, Pull:
                  return PNH();
             ],
    has   concealed static;

! 05/03/06

  Object  stunnel_sdoor "secret door"
    with  name 'secret' 'door' 'passageway',
          description
              "The opening in the eastern wall reveals a secret passageway.",
          before [;
              Close:
                  "Nothing happens.";
              Enter:
                  if (adar has general) {
                      print "Captain Adar follows as you walk through the door cautiously.^";
                      MoveAdar(5);
                  } else {
                      print "You walk through the door cautiously.^";
                  }
                  PlayerTo(secret_tunnel1,2);
                  rtrue;
              Open:
                  "It's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 05/05/06

  OutRch  smokeobj "smoke"
    with  name 'thick' 'black' 'smoke' 'heavy' 'plumes' 'of' 'large',
            description
                "The smoke pours out of the ship in large black plumes, blowing away on the breeze.";

! 05/07/06

  Object  intsmokeobj1 "smoke"
    with  name 'thick' 'black' 'smoke',
          description
              "The smoke pours out of the ventilation shaft, as the backwash fails to vent it into
              the atmosphere.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 05/07/06

  Object  intsmokeobj2 "smoke"
    with  name 'thick' 'black' 'smoke',
          description
              "The smoke pours out of the ventilation shaft, as the backwash fails to vent it into
              the atmosphere.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   concealed static;

! 05/24/06

  Object  largehole "large blast-hole"
    with  name 'large' 'blast-hole' 'blast' 'hole' 'opening' 'hull' 'breach' 'breaches' 'access' 'point' 'points',
          description
              "The space pirates have created a large blast-hole in the port bulkhead,
              closed to the vacuum of space with a self-sealing metal plate.",
          before [;
              Enter, Exit:
                  "A sealed access hatch blocks the hole.";
              Open:
                  return PCB();
              Search:
                  "The sealed access hatch blocks the opening.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  return PNH();
          ],
    has   concealed static;

! 05/24/06

  Object  largeholedesert "large hole"
    with  name 'large' 'blast' 'hole' 'blast-hole' 'gaping' 'jagged' 'metal' 'open' 'opening',
          description
              "The large hole in the port bulkhead is open to a hot, arid desert.",
          before [;
              Enter, Exit:
                  "You don't want to do that. You could damage your uniform on all that jagged metal.";
              Open:
                  return PCB();
              Search:
                  "As you look through the hole, the desert is burnt, harsh, and lifeless.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  return PNH();
          ],
    has   concealed static;

! 08/08/06

  Object  huge_boulder "huge boulder"
    with  name 'large' 'huge' 'enormus' 'boulder',
          description [;
              if (self.boulderfalling) "The huge boulder is falling straight for you...";
              "The huge boulder has crushed the altar into millions of pieces of rubble that are scattered around the room.";
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          boulderfalling false,
    has   concealed static;

! 08/15/06

  Object  dead_spitter "spitter"
    with  name 'large' 'widow' 'weave' 'widow-weave' 'spitter' 'long' 'spade-like' 'legs' 'centipede' 'mandibles' 'spider' 'creature' 'dying',
          before [;
              Examine, Search:
                  "The spitter now lies in the jaws of the dying ralckor, her heroic efforts painfully claming her life.";
              Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, GetOff, Grapple, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip, FlipOff:
                  "Just leave the creature in peace.";
              Push, PushDir, Pull, Read, Remove, Rub, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "Just leave the creature in peace.";
          ],
    has   static scenery;

! 08/15/06

  Object  wt_secretdoor "secret door"
    with  name 'secret' 'door' 'passage',
          description
              "The secret door leads into an even darker passage to the west.",
          before [;
              Enter:
                  if (adar has general) {PAF(); MoveAdar(15);}
                  PlayerTo(secret_tunnel3);
                  rtrue;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          foundsecret false,
    has   concealed static;

! 09/18/06

  Object  berth_uniform "your uniform"
    with  name 'your' 'uniform' 'clothes' 'pocket',
          description
              "It's a little hard to see while you're lying down.",
          describe [;
              "^You can see your uniform on the edge of the berth here.";
          ],
          before [;
              Search, Touch, UseItem:
                   return PYC();
              Wear, Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, Follow, GetOff, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip:
                  "It's too cramped in here for that; you'll need to get out of your berth first.";
              Push, PushDir, Pull, Read, Remove, Rub, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "It's too cramped in here for that; you'll need to get out of your berth first.";
          ],
          unimoved true,
          booklookat false,
    has   proper clothing;

! 09/23/06

  Object  upper_hatchways "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'hatch' 'door' 'doors',
          description
              "The hatchway leads to the main junction.",
          before [;
              Close:
                  "In case of fire, this hatchway should be left open.";
              Enter:
                  PlayerTo(main_junction);
                  rtrue;
              Open:
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          found_in radar_room galley
    has   concealed static enterable openable;

! 09/23/06

  Object  secondary_hatchways "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'hatch' 'door' 'doors',
          description
              "The hatchway leads to the secondary junction.",
          before [;
              Close:
                  "In case of fire, this hatchway should be left open.";
              Enter:
                  PlayerTo(secondary_junction);
                  rtrue;
              Open:
                  "That's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          found_in main_airlock engine_room armory
    has   concealed static enterable openable;

! 09/27/06

  Object  us_rubble "rubble"
    with  name 'rubble',
          description
              "The rubble is scattered all around the room, since the boulder crushed the altar to pieces.",
          before [;
              Turn, PushDir, Push, Pull:
                  "You do little but scatter the rubble.";
              Take, Remove:
                  "It's no use. There's no way you'll be able to clear the rubble one piece at a time.";
          ],
    has   concealed static;

! 02/05/07

  Dust    wt_dust "dust"
    with  description
              "The dust comes from the mortar that once held the wall.";

! 02/14/07

  Object  twin_moons "twin moons"
    with  name 'twin' 'moons' 'moon^s' 'moon',
          description [;
              if (player in chasm) "The twin moons hang peacefully above the eastern horizon.";
              "The twin moons hang peacefully above the mountain range.";
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          found_in desert dunes chasm
    has   concealed pluralname static;

! 02/17/07

  Object  lc_ffield "cobalt-blue force field"
    with  name 'cobalt' 'blue' 'cobalt-blue' 'force' 'field' 'energy' 'stream',
          description
              "A cobalt-blue force field blocks the way out of the cavern. These ancient people must
              have understood a technology that is long forgotten.",
          before [;
              Attack, Kick, Take, Remove, Touch, Transfer, Turn, PushDir, Push, Pull:
                  "The force field sparks as you try to touch it, stinging you with a sharp pain.";
          ],
    has   concealed static;

! 02/17/07

  OutRch  tc_ffield "cobalt-blue force field"
    with  name 'cobalt' 'blue' 'cobalt-blue' 'force' 'field' 'energy' 'stream',
          description
              "The cobalt-blue force field covers the ceiling in a spectacular display of power.
              These ancient people must have understood a technology that is long forgotten.";

! 02/20/07

  Object  rail_system "rail system"
    with  name 'hand' 'rail' 'rails' 'handrail' 'handrails' 'system',
          description
              "A system of handrails has been installed so routine maintenance can be performed more easily.",
          before [;
              Climb, UseItem:
                  if (player in ontopofship) {
                      print "Carefully you grab the rail, making your way down the ship.^";
                      if (bu_planet in ontopofship) move bu_planet to outside_airlock;
                      PlayerTo(outside_airlock);
                  } else {
                      print "Carefully you grab the rail, making your way up the ship.^";
                      if (bu_planet in outside_airlock) move bu_planet to ontopofship;
                      PlayerTo(ontopofship);
                  }
                  rtrue;
              Search:
                  return L__M(##Search, 4);
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          found_in outside_airlock ontopofship
    has   static concealed;

! 02/20/07

  OutRch  outside_stars "star"
    with  name 'million' 'millions' 'of' 'star' 'stars',
          description
              "Millions of stars can be seen from out here, the view is quite amazing.",
          found_in outside_airlock ontopofship;

! 02/20/07

  OutRch  bu_planet "planet"
    with  name 'small' 'harsh' 'burnt' 'red' 'planet',
          description [;
              if (pland >= (plimit+5)) "The burnt, harsh, red planet glows in the sky as the pirates prepare to land.";
              "In the distance a small red planet comes closer as the pirates maneuver in for a landing.";
          ];

! 02/20/07

  Object  blastdoor "blast door"
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'blast' or 'blastdoor' or 'environmental' or 'seal') return 0;
              w2 = NextWord();
              if (w1 == 'blast' or 'environmental' && w2 == 'door' or 'seal') return 2;
              return 1;
          ],
          description
              "The blast door maintains the environmental seal for the ship, preventing oxygen from escaping.",
          before [;
              Attack:
                  return PDE();
              Close:
                  "That's already sealed shut.";
              Open, Unlock:
                  if (second == prybar) "The pry bar slips away as you try to break the seal.";
                  "There's no way to force the seal open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static;

! 02/27/07

  OutRch  vp_impact "impact crater"
    with  name 'impact' 'crater' 'huge' 'large' 'wide' 'hole' 'permanent' 'scar',
          description
              "The wide hole of a huge impact crater, now burned into the planet, caused all the
              devastation around, changing the climate and killing everything off. Even the winds
              that blow across the wasteland cannot wear down this permanent scar.",
          found_in view_plat vplat_seats;

! 02/27/07

  OutRch  vp_desert "desert"
    with  name 'desert' 'wasteland' 'wind' 'winds' 'landscape' 'planet',
          description
              "Winds blow across the desert, but little else stirs out there.",
          found_in view_plat vplat_seats;

! 03/02/07

  OutRch  vplats_cliff "cliff"
    with  name 'cliff' 'cliffs',
          description [;
              if (player in view_plat) "The cliff drops off below the seats, you'll have to sit down to get a better view.";
              "Wind whips through your hair as you sit on the edge of a cliff, stomach knotting, looking down a thousand feet.";
          ],
          before [;
              Enter, Jump, JumpOver:
                  "It's a long way down.";
          ],
          found_in view_plat vplat_seats,
    has   open container;

! 03/02/07

  Object  vplats_mount "mountain"
    with  name 'mountain',
          description
              "The mountain's side blocks the balcony in, but only goes up another twenty feet to the opening for the chamber below.",
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
          found_in view_plat vplat_seats,
    has   concealed static;

! 03/02/07

  OutRch  vplats_chamber "chamber"
          with  name 'tranquility' 'chamber',
          description [;
              if (player in view_plat) {
                  if (adar has general) "Captain Adar smiles up at you and gives you a small wave, as you look down into the chamber below.";
                  "The tranquility chamber lies below.";
              }
              "You can't see that from here.";
          ],
          found_in view_plat vplat_seats;

! 03/05/07

  OutRcF  galley_crumbs "crumbs"
    with  name 'crumb' 'crumbs',
          description [;
              print "Crumbs can be seen underneath the meal synthesizer, but they're out of reach.^";
              if (robowash.working) Robotalk();
          ],
          before [;
              Blow:
                  print "They barely move at all.^";
                  if (robowash.working) Robotalk();
                  rtrue;
          ],
    has   pluralname;

! 03/06/07

  Skel    skeley_1;

! 03/06/07

  Skel    skeley_2;

! 03/06/07

  Skel    skeley_3;

! 05/16/07

  Object  blanket "blanket"
    with  name 'standard' 'government' 'issue' 'government-issue' 'blanket',
          before [;
              Examine, Search:
                  "It's a standard government-issue blanket. Thin, made of wool, and worn from use.
                  While it does itch considerably, it also keeps you warm in the cold of space.";
              Push, PushDir, Pull:
                  "You push the blanket to the other side of the rack.";
              Take, Remove:
                  "OK Linus, I think it would be best if you leave the blanket in the rack.
                  You might look a little strange walking around the ship with that thing.";
              Turn:
                  "You turn your blanket over in your rack.";
              Wrap:
                  if (second == player) "This is no time for getting comfortable.";
          ],
    has   concealed static;

! 07/26/07

  Object  cs_bulkhead "bulkhead"
    with  name 'bulkhead' 'bulkheads' 'sturdy' 'frame',
          description
              "The bulkheads make up the frame of the ship and look to be in good condition.",
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The sturdy frame can't be moved.";
          ],
          found_in crashed_ship air_lock sm_airlock
    has   concealed static;

! 07/27/07

  Object  jmetal "jagged metal"
    with  name 'pieces' 'of' 'jagged' 'metal',
          description
              "Jagged metal lies all over the floor, since you've opened up the cargo hatch.",
          before [;
              Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, GetOff, Grapple, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip:
                  "It's best to leave the jagged metal alone.";
              Push, PushDir, Pull, Read, Remove, Rub, Search, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "It's best to leave the jagged metal alone.";
          ],
    has   concealed static;

! 07/27/07

  Object  alhole "gaping hole"
    with  name 'gaping' 'hole',
          description
              "The cargo hatch is left with this gaping hole in the center of the door.",
          before [;
              Enter:
                  <<Enter al_door>>;
              Search:
                  "The hole looks out onto a harsh burnt desert, lifeless, and barren.";
              Open:
                  "You can't make the hole any bigger.";
              Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Exit, Fix, GetOff, Grapple, Hide, JumpOver, Kick, Listen, LookUnder, Plug, PlugItem, SwFlip:
                  "It's best to leave the hole alone.";
              Push, PushDir, Pull, Read, Remove, Rub, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "It's best to leave the hole alone.";
          ],
    has   concealed static;

! 07/27/07

  Object  cs_vent "ventilation shaft"
    with  name 'ventilation' 'vents' 'vent' 'shaft',
          before [;
              Attack, Kick, Cut:
                  return PHS();
              Examine, Search:
                  PHl();
                  "he ventilation shaft is used to circulate air while the ship's engines are engaged, providing fresh oxygen.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The ventilation shaft is built into the frame of the ship.";
          ],
          found_in crashed_ship air_lock sm_airlock
    has   concealed static;

! 07/31/07

  Object  cp_breaker "large breakers"
    with  name 'large' 'breakers',
          before [;
              Attack, Cut:
                  return PDE();
              Examine, Search:
                  print "Large circuit breakers are buried underneath ";
                  if (radar_room.flowoff) "the thousands of wires that control the circuitry operating them. They tripped when the power went off but, even if you knew how to reset them, it wouldn't bring the power back.";
                  "thousands of wires, while actually controlling them is handled through the flow regulator.";
              FlipOff, SwFlip, SwitchOn, SwitchOff, Trip:
                  "The large breakers are electronically controlled through the flow regulator.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PSH();
          ],
    has   concealed static pluralname;

! 07/31/07

  Object  cp_wires "wires"
    with  name 'thousands' 'of' 'wire' 'wires' 'circuitry',
          before [;
              Attack, Cut:
                  return PDE();
              Examine, Search:
                  "Thousands of wires control the circuitry to the circuit breakers lying beneath, which connects the flow regulator to the rest of the ship.";
              FlipOff, SwFlip, SwitchOn, SwitchOff:
                  <<SwitchOn cp_breaker>>;
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PSH();
          ],
    has   concealed static pluralname;

! 08/10/07

  Object  ship_plating "metal plating"
    with  name 'metal' 'plating',
          before [;
              Attack, Cut:
                  return PDE();
              Examine, Search:
                  "Metal plating covers the deck.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
              Touch:
                  if (pland < (plimit+15)) {
                      if (player in engine_room) "You feel the vibrations coming from the engines.";
                      "You can feel the ship's engines vibrating through the plating.";
                  }
          ],
          found_in crew_quarters main_junction galley radar_room under_desk bridge armory armory_backroom main_airlock cargo_hold hidden_compartment secondary_junction engine_room,
    has   concealed static;

! 09/10/07

  ORchSe  dd_trees "palm trees"
    with  name 'tall' 'leafy' 'palm' 'tree' 'trees' 'green',
          description
              "You can see tall stems and broad leaves, exactly like the palm trees back home.",
          found_in desert dunes
     has  scenery pluralname;

! 09/10/07

  ORchSe  dd_lake "lake"
    with  name 'oasis' 'pool' 'of' 'clear' 'blue' 'lake' 'water',
          description
              "You're sure the glint of blue on the horizon must mean there's water, hopefully an oasis.",
          before [;
              Enter:
                  "That's too far away.";
          ],
          found_in desert dunes
     has  scenery;

! 09/11/07

  Object  p_dsdoors "double sliding doors"
    with  name 'double' 'sliding' 'door' 'doors' 'transparent' 'polymer' 'glass',
          description [;
              print "Made of some transparent polymer, the doors open onto the broad expanse
              of the hangar floor, which is too dimly-lit for you to make out anything
              of consequence. You do, however, get a good view of yourself, reflected
              in the door. ";
              return PSY();
          ],
          before [;
              Enter:
                  <<Exit pantheon>>;
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull, Open, Close:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery pluralname;

! 09/11/07

  ORchSe  p_corridor "corridor"
    with  name 'corridor' 'north',
          description
              "Narrow and featureless, you've been assured it leads to the commissary.",
          before [;
              Enter:
                  return CorDeath();
          ],
     has  scenery;

! 09/11/07

  Object  p_couch "couches"
    with  name 'lumpy' 'couch' 'couches' 'coffee-stains' 'coffee' 'stain' 'stains' 'stripe' 'stripes' 'fabric' 'uncomfortable-looking' 'uncomfortable',
          description
              "Lumpy and covered in fabric featuring a stripes-and-coffee-stains motif.",
          before [;
              Enter, Sit:
                  "You wouldn't want to do that. Really.";
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery pluralname;

! 09/11/07

  Object  p_plant "ficus plant"
    with  name 'dead' 'depressed' 'wilting' 'ficus' 'plant',
          description
              "Very nearly dead, it was meant to cheer up the room but instead just makes you depressed.",
          before [;
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery;

! 09/11/07

  Object  p_poster "posters"
    with  name 'poster' 'posters' 'picture' 'pictures' 'recruiting' 'tropical' 'beaches' 'cool' 'clear' 'lake' 'lakes' 'sad-looking' 'sad',
          description
              "Anodyne pictures of tropical beaches and cool, clear lakes interspersed with recruiting posters.",
          before [;
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery pluralname;

! 09/11/07

  Object  p_magazine "magazines"
    with  name 'aged' 'magazine' 'magazines',
          description
              "Ancient and well-thumbed, you're not bored enough to actually try reading them.",
          before [;
              Search, Take, Touch, Remove, Read, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery pluralname;

! 09/11/07

  Object  p_rctable "table"
    with  name 'glass' 'glass-topped' 'table' 'transparent' 'polymer',
          description [;
              print "Topped with a transparent polymer, the table bears the scars of years of
              use along with the usual selection of aged magazines. Just as you're
              looking away, you catch sight of your reflection. ";
              return PSY();
          ],
          before [;
              Search, Take, Touch, Remove, Turn, PushDir, Push, Pull:
                  return CavTouch();
              Taste:
                  return CavTaste();
          ],
     has  static scenery;

! 09/11/07

  Object  mb_smdoor "small door"
    with  name 'small' 'door',
          description
              "Part of the hangar door has slid up out of the way, leaving an opening
              just the right size for you to step through.",
          before [;
              Close:
                  "Nothing happens.";
              Enter:
                  return PToPan();
              Open:
                  "It's already open.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
     has  static scenery;

! 09/12/07

  ORchSe  dd_building "building"
    with  name 'building' 'temple' 'tall' 'large' 'stepped' 'pyramid' 'roughly' 'triangular' 'boxy' 'stone' 'structure' 'settlement',
          description
              "A tall, roughly triangular stone building rises above the trees, but
              you're too far away to see more.",
          before [;
              Enter:
                  "That's too far away.";
          ],
          found_in desert dunes
     has  scenery;

! 05/14/08

  Object  et_con "electrical conduit"
    with  name 'electrical' 'conduit' 'mess' 'system' 'systems',
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  "That's already closed.";
              Examine, Search:
                  "The electrical conduit runs through out the ship. Some provide power, others data,
                  it's a real mess in here.";
              Open:
                  "That's the Chief Engineer's area of responsibility, it's better to leave it alone.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          found_in cq_etube br_etube rr_etube gl_etube er_etube ch_etube ar_etube ma_etube
    has   static scenery;
