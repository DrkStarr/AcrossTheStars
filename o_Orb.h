
! 04/28/06

  Movable orb "glowing orb"
    with  name 'red' 'glow' 'radiant' 'orb' 'heavy' 'golden' 'lamp' 'glowing' 'light' 'ornate' 'three-legged' 'stand' 'gold',
          description [;
              if (player in air_lock || player in sm_airlock) {
                  if (e_beacon.eb_notseen) "Through the swirling black smoke, the radiant orb glows bright red providing light, making the place feel comfortable.";
              }
              if (self in tc_shrine && tc_shrine.fieldon) "A rich cobalt blue emanates from the glowing orb, feeding the force field with its energy. A streamer of brilliant blue shoots high into the air, creating an energy barrier that blocks out the sun. While the shrine's blue-green force field swirls around the orb.";
                if (self in player) "Encased in a golden lamp, the radiant orb glows a bright red.";
              if (self in tc_shrine) "A rich cobalt blue emanates from the glowing orb, feeding the force field with its energy. A streamer of brilliant blue shoots high into the air, creating an energy barrier that blocks out the sun.";
              if (self in secret_chamber or secret_tunnel2 or unholy_shrine) "The radiant orb glows bright red providing light, making the place feel comfortable.";
              if (self in sa_bobelisk) {
                  if (self.gllkat) "You see that the orb is attached to an ornate three-legged stand, apparently made of gold.";
                  self.gllkat = true;
                  "At first, you see only a large, transparent sphere, suffused with bright red light. As your eyes adjust, though, you see that the orb is attached to an ornate three-legged stand, apparently made of gold.";
              }
              "The glowing orb tries to provide light, but doesn't do a good job.";
          ],
          after [;
              PutOn:
                  if (second == jagged_rock) {
                      move self to player;
                      "The jagged rock is out of your reach.";
                  }
                  if (second == tc_bsrail) {
                      move self to player;
                      "The broken stone railing is out of your reach.";
                  }
                  if (second == tc_shrine) {
                      move self to tc_shrine;
                      move lc_ffield to cavern;
                      move tc_ffield to tranquility_chamber;
                      "The red of the orb changes to a bright cobalt blue as you place it on top of the shrine.
                      A force field starts to build, slowly at first, stretching out from the altar until it
                      covers the entire chamber, blocking out the sun. Where once the stones of the chamber
                      were illuminated by warming sunlight, they're now lit and eerie cobalt blue.";
                  }
          ],
          before [;
              Give:
                  if (self in player or milpack) {
                      if (second == adar) {
                          if (player in crashed_ship) return GameEnd(1);
                          "~I don't want to carry your stuff,~ retorts Captain Adar.";
                      }
                      if (second == lc_vampires) "~Return it, you foul beast,~ they scream, spraying ethereal matter.";
                  }
              PutOn:
                  if (self in player) {
                      if (second == pedestal) return PedestalEnds(12);
                      if (second == sa_bobelisk && lc_vampires in secret_chamber) {
                          TestThink();
                          give self concealed;
                          move self to sa_bobelisk;
                          lc_vampires.anger = false;
                          "As you put the orb back, the spirits start to calm down until they finally return to their eerie circular pattern.";
                      }
                      if (second == sa_bobelisk) give self concealed;
                  }
              Push, PushDir, Pull, Transfer:
                  if (self in sa_bobelisk) {
                      if (lc_vampires in secret_chamber) return OrbDeath(0);
                      give self ~concealed;
                      move self to secret_chamber;
                      "The glowing orb is heavy, and takes quit a bit of effort to push off the obelisk.
                      Hitting the ground seems to do no damage to it at all.";
                  }
              Remove:
                  <<Take self>>;
              Search:
                  print "As you look into the orb you see a glowing ball of red plasma";
                  if (OrbLoc()) " that emanates throughout the room.";
                  ".";
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT) {
                      if (milpack in player or uniform) {
                          print "(first moving ";
                          FirstPrint();
                          AndPrint();
                          print " to the field pack)^";
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
                  if (self in sa_bobelisk) {
                      move self to player;
                      give self ~concealed;
                      if (self.orbtaken) {
                           self.orbtaken = false;
                           score = score + 5;
                      }
                      if (lc_vampires in secret_chamber) return SpAnger(0);
                      "The orb is heavy, and it takes quite a bit of effort to lift it off the obelisk, but finally you manage to haul it free.";
                  }
                  if (self in tc_shrine) {
                      remove lc_ffield;
                      remove tc_ffield;
                      move self to player;
                      "The cobalt force field crumbles away as you take the glowing orb off the shrine,
                      letting the sunlight back into the room.";
                  }
              ThrowAt:
                  if (self in player) {
                      if (second == deadp_obj) {
                          move self to unholy_shrine;
                          "You throw ", (the) self, " into the pit.";
                      }
                  }
              Touch:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  "The glowing orb is slightly warm to the touch.";
          ],
          gllkat false,
          orbtaken true,
    has   light concealed;
