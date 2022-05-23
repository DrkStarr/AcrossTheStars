
! ---------------------------------------------------------------------------- !
!       The TUNNEL. 04/26/06
!
  Room    s_tunnel "Tunnel"
    with  description [;
              print "Foul air breathes down a short north-south tunnel, ";
              if (sandworm in self) {
                  st_deadspit.&name-->1 = '1626ph';
                  st_deadspit.&name-->2 = '1627ph';
                  st_deadspit.&name-->3 = '1628ph';
                  "as an angry widow-weave spitter blocks your path back down it. Sensory
                  glands hone in on the egg, as she patiently waits for an opening, backing
                  you up towards the foul-smelling cavern to the north.";
              }
              st_deadspit.&name-->1 = 'widow';
              st_deadspit.&name-->2 = 'weave';
              st_deadspit.&name-->3 = 'widow-weave';
              if (statue in pedestal) print "which ends at an east-west T-junction";
              else print "which takes a turn to the west";
              " here. In the middle of the tunnel a dead widow-weave spitter slowly decays,
              creating a stench of its own, while the floor is scattered with loose shale.";
          ],
          n_to [;
              <<Exit self>>;
          ],
          s_to [;
              if (sandworm in self) return PSB();
          ],
          e_to [;
              if (statue in pedestal) {
                  if (sandworm in self) return PSB();
                  if (adar has general) {
                      adar.grief = false;
                      print "Captain Adar follows as you walk through the door cautiously.^";
                      MoveAdar(5);
                  } else {
                      print "You walk through the door cautiously.^";
                  }
                  PlayerTo(secret_tunnel1,2);
                  rtrue;
              }
          ],
          w_to [;
              if (sandworm in self) return PSB();
              if (adar has general) {PAF(); MoveAdar(3);}
              return w_tunnel;
          ],
          cant_go [;
              if (sandworm in self) "You can only go north.";
              if (statue in pedestal) {
                  "You can only go north, east, or west.";
              }
              "You can only go north or west.";
          ],
          before [;
              Exit:
                  if (sandworm in self) {
                      move sandworm to cavern;
                      print "Wanting to get the egg back, the spitter follows you into the cavern.^";
                  }
                  if (adar has general) {PAF(); MoveAdar(1);}
                  PlayerTo(cavern);
                  rtrue;
              Listen:
                  if (sandworm in self) "The chattering from the spitter echoes down this tunnel.";
              Smell:
                  "The smell of the foul cavern mixes with the rotting corpse of the dead spitter.";
            ];

! 05/03/06

  RoomObj -> stunnelobj "tunnel"
    with  name 'tunnel' 'room',
          description [;
              <<Look s_tunnel>>;
          ];

! 04/28/06

  Object  -> pedestal "pedestal"
    with  name 'drab' 'looking' 'drab-looking' 'medium' 'sized' 'obelisk' 'pedestal' 'column' 'pillar' 'obsidian',
          description [;
                if (statue in self)
                    "It's a drab-looking pedestal, covered in lots of dust, with a crude parody
                    of a man made of poorly-baked clay placed on top of it.";
                "It's made from obsidian, and looks old. Going by the thick layer of dust, it hasn't
                been used in a very long time.";
          ],
          describe [;
                if (statue in self) "^There's also a small idol placed on top of the pedestal here.";
                "^There's also a rune carved into the south wall with a pedestal underneath it.";
          ],
          before [;
              Blow:
                  if (sandworm in s_tunnel) return PSB();
                  "A bunch of dust chokes your lungs as you blow it into the air.";
              Climb:
                  if (sandworm in s_tunnel) return PSB();
                  "This isn't a gymnasium.";
              Enter, Sit:
                  if (sandworm in s_tunnel) return PSB();
                  return PedDeath(1);
              LookUnder:
                  if (sandworm in s_tunnel) return PSB();
                  "You can't look under that, it goes straight into the ground.";
              Push, Touch:
                  if (sandworm in s_tunnel) return PSB();
                  return PedDeath(2);
              PushDir, Pull:
                  if (sandworm in s_tunnel) return PSB();
                  return PedDeath(3);
              Search:
                  if (sandworm in s_tunnel) return PSB();
                  if (statue in self) "The only thing that stands out is the crude man, made of poorly-baked clay, that rests atop of it.";
                  "The pedestal is only covered in dust.";
              Take, Remove:
                  if (sandworm in s_tunnel) return PSB();
                  "The pedestal won't budge.";
              Turn:
                  if (sandworm in s_tunnel) return PSB();
                  return PedDeath(4);
          ],
    has   supporter static;

! 05/17/06

  Object  -> runes "rune"
    with  name 'rune' 'runes' 'cave' 'wall' 'stick' 'figure',
          before [;
              Examine, Search, Read:
                  "A stick figure has been crudely carved into the cave wall.";
              Scan:
                  if (sandworm in s_tunnel) return PSB();
                  if (omni_trans notin player) return PNR();
                  if (lc_mrune.haveread) {
                      POT();
                      style fixed;
                      print "The man conveys the concept of nine for the people that once lived here.
                      Represented by the binary number 1001, it means Earthly God and is one of four
                      holy numbers they consider balanced.";
                      style roman;
                      "";
                  }
                  return PNE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (sandworm in s_tunnel) return PSB();
                  return PNH();
              Touch:
                  if (sandworm in s_tunnel) return PSB();
                  "The wall is made of a solid stone.";
          ],
    has   scenery static;

! 04/28/06

  Dust    -> st_dust "dust"
    with  description
              "Time has covered the pedestal in a layer of dust.";

! 08/14/06

  StaticShale -> st_shale "shale"
    with  name 'loose' 'shale' 'rubble';

! 04/07/08

  Object  -> st_deadspit "dead spitter"
    with  name 'dead' 'widow' 'weave' 'widow-weave' 'spitter' 'rotting' 'corpse' 'decomposing' 'decomposed' 'flesh' 'bone',
          before [;
              Eat:
                  "You just can't seem to bring yourself to take a mouthful of the decomposed flesh.";
              Examine, Search, Read:
                  "By the looks of it, this spitter was male, bright red marks across the forehead giving
                  it away. But it's been dead for awhile, flesh decomposing, slowly rotting off the bone.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  if (sandworm in s_tunnel) return PSB();
                  "Just leave the creature in peace.";
              Taste:
                  if (sandworm in s_tunnel) return PSB();
                  "You can't seem to bring yourself to sample rotten flesh.";
              Touch:
                  if (sandworm in s_tunnel) return PSB();
                  "You might never get the stink off if you did.";
          ],
    has   scenery static;

! ---------------------------------------------------------------------------- !
!       The TUNNEL. 04/26/06
!
  Room    w_tunnel "Tunnel"
    with  description [;
              if (sandworm in self) {
                  print "Loud clicks from the spitter's mandibles echo down the tunnel as the large creature blocks
                  the path into her lair";
                  if (wt_depression.foundsecret) print " and the passage";
                  print ", weaving back and forth, trying to sense an opening. Your only way out is east, to the ";
                  if (statue in pedestal) {
                      print "junction";
                  } else {
                      print "bend in the tunnel";
                  }
                  ".";
              }
              print "This tunnel turns south, into a small cave";
              if (wt_depression.foundsecret) print "; while another passage, lower and narrower, cuts west";
              print ". The walls look to have been crudely excavated, and the floor is covered with loose shale";
              if (wt_depression.foundsecret) {
              } else {
                  print "; while a cracked depression in the western wall is filled with rubble";
              }
              if (torch in self) {
                  if (torch.onfire) print ". An old torch hangs on the northern wall, providing light";
                  else print ". An old torch hangs on the northern wall, unlit";
                  if (wt_depression.foundsecret) print ".";
                  else print ", as something about the depression catches your eye.";
              } else {
                  if (wt_depression.foundsecret) {
                      print ".";
                  } else {
                      if (torch.onfire) print ". By the light of the torch";
                      else print ". In this poor light";
                      print ", something about the depression catches your eye.";
                  }
              }
              if (Spitter()) print " Fearfully, you can hear a steady grinding sound coming from the cave to the south.";
              print "^^You can head ";
              if (wt_depression.foundsecret) print "west into the low passageway, ";
              print "east to the ";
              if (statue in pedestal) {
                  print "junction";
              } else {
                  print "bend in the tunnel";
              }
              if (wt_depression.foundsecret) print ",";
              print " or south into the small cave";
              if (Spitter()) print ", if you feel brave enough";
              ".";
          ],
          s_to [;
              if (sandworm in self) return PSB();
              if (adar has general) {PAF(); MoveAdar(4);}
              return small_room;
          ],
          w_to [;
              if (wt_depression.foundsecret) {
                  if (sandworm in self) return PSB();
                  if (adar has general) {PAF(); MoveAdar(15);}
                  return secret_tunnel3;
              }
          ],
          e_to [;
              <<Exit self>>;
          ],
          cant_go [;
              if (sandworm in self) "You can only go east.";
              if (wt_depression.foundsecret) "You can only go south, east, or west.";
              "You can only go east or south.";
          ],
          before [;
              Exit:
                  if (sandworm in self) {
                      move sandworm to s_tunnel;
                      print "Wanting to get the egg back, the spitter follows you into the tunnel.^";
                    }
                  if (adar has general) {PAF(); MoveAdar(2);}
                  PlayerTo(s_tunnel);
                  rtrue;
              Listen:
                  if (sandworm in self) "The chattering from the spitter echoes down this tunnel.";
                  if (Spitter()) "The grinding sound reminds you of gravel being crushed.";
              Smell:
                  print "The smell of the foul cavern mixes with the stench of rotten eggs";
                  if (wt_depression.foundsecret) ", as fresh air does little to alleviate the odor.";
                  ".";
          ],
          hastorch true;

! 05/03/06

  RoomObj -> wtunnelobj "tunnel"
    with  name 'tunnel' 'room',
          description [;
              <<Look w_tunnel>>;
          ];

! 08/14/06

  StaticShale -> wt_shale "shale"
    with  name 'loose' 'shale' 'rubble';

! 08/15/06

  Object  -> wt_depression
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'deep' or 'crack' or 'cracked' or 'depression' or 'sand' or 'mortar' or 'pile' or 'stones' or 'stone' or 'west' or 'western' or 'wall') return 0;
              w2 = NextWord();
              if (w1 == 'deep' or 'crack' or 'cracked' or 'depression' or 'west' or 'western' && w2 == 'depression' or 'deep' or 'crack' or 'wall') {
                  self.mortar = false;
                  self.short_name = "depression";
                  return 2;
              }
              w3 = NextWord();
              if (w1 == 'pile' && w2 == 'of' && w3 == 'stone' or 'stones') {
                  self.mortar = false;
                  self.short_name = "depression";
                  return 3;
              }
              if (w1 == 'sand' && w2 == 'mortar') {
                  self.mortar = true;
                  self.short_name = "sand mortar";
                  return 2;
              }
              if (w1 == 'sand' or 'mortar') {
                  self.mortar = true;
                  self.short_name = "sand mortar";
                  return 1;
              }
              if (w1 == 'west' or 'western') return 0;
              self.mortar = false;
              self.short_name = "depression";
              return 1;
          ],
          short_name "depression",
          description [;
              if (sandworm in w_tunnel) return PSB();
              if (self.mortar) {
                  if (self.foundsecret) "The mortar now is nothing more than dust.";
                  "The mortar is packed in tight, but the dry air has caused deep cracks to arise.";
              }
              LW_dep();
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack, Kick:
                  if (sandworm in w_tunnel) return PSB();
                  if (self.foundsecret) rfalse;
                  return DprOpen(2);
              Open:
                  if (sandworm in w_tunnel) return PSB();
                  if (second == prybar) return DprOpen(3);
              PushDir, Push:
                  if (sandworm in w_tunnel) return PSB();
                  if (self.foundsecret) "Nothing happens as you push down upon the depression.";
                  return DprOpen(1);
              Search:
                  if (sandworm in w_tunnel) return PSB();
                  if (self.mortar) {
                      if (self.foundsecret) "The mortar is nothing more than dust.";
                      "The mortar is packed in tight, but the dry air has caused deep cracks to arise.";
                  }
                  if (self.foundsecret) "The depression has fallen away revealing a secret passage towards the west.";
                  return LW_dep();
              Touch:
                  if (sandworm in w_tunnel) return PSB();
                  if (self.mortar) {
                      if (self.foundsecret) "The mortar is nothing more than dust.";
                      "The mortar is dry to the touch.";
                  }
                  if (self.foundsecret) "The depression is nothing more than dust.";
                  "The depression is fill with a mortar that's dry to the touch.";
              Take, Remove, Turn, Pull:
                  if (sandworm in w_tunnel) return PSB();
                  return PNH();
          ],
          mortar false,
          foundsecret false,
    has   static;

! 08/12/07

  Object  -> wt_holder "holder"
    with  name 'holder' 'small' 'hole',
          before [;
              Examine:
                  if (sandworm in w_tunnel) return PSB();
                  "The holder is nothing more than a small hole that the torch can fit into.";
              Search:
                  if (sandworm in w_tunnel) return PSB();
                  if (torch in w_tunnel) "The torch is inside the hole.";
                  "The small hole is empty.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  if (sandworm in w_tunnel) return PSB();
                  return PNH();
          ],
    has   static concealed open container;
