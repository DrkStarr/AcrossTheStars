
! ---------------------------------------------------------------------------- !
!       The SECRET ALCOVE. 04/26/06
!
  Object  secret_chamber "Secret Alcove"
    with  description [;
              if (lc_vampires in self && lc_vampires.anger) {
                  print "The four ethereal spirits fly around the room, crying out for the travesty
                  committed against them. Refusing to let you go, they whip past your face causing
                  the air to sting";
                  if (orb in player) print " and making it hard to hold the heavy orb";
                  print ". ";
                  if (adar has general) {
                      print "Captain Adar tries";
                  } else {
                      print "You try";
                  }
                  " to bat them away, as the spirits only cry out more, chilling you to the bone.";
              }
              adar.seenspirit = true;
              print "Though the alcove is small and Spartan, it feels like a ceremonial chamber.
              It's empty but for a large black obelisk standing in the center of the room";
              if (orb in sa_bobelisk) print ", with a glowing orb sitting atop it";
              if (lc_vampires in self) print ". In the shimmering bright-red light of the orb,
              four spirts slowly encircle the shrine creating an ethereal fog that chokes the air";
              print ". Carefully engraved into the dark stone, two runes show what great care these
              people had for ";
              if (orb in sa_bobelisk)  print "this artifact";
              else print "the object that once adorned it";
              print ".^^The only way out of here is back to the north.^";
              if (self.firstimein) {
                  adar.adaroff = true;
                  adar.knowlamp = true;
                  self.firstimein = false;
                  if (adar in self) "^~Be careful,~ says Captain Adar, ~I've got a feeling that we're moths, and that's the flame.~";
              }
          ],
          n_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go north.",
          before [;
              Exit:
                  if (lc_vampires in self && lc_vampires.anger)
                      "As you try leaving the alcove, the spirits whip around in a fury, forming a seemingly
                      impenetrable barrier. ~Return Sucored's last shard to its rightful place,~ they say
                      with a hateful shriek, ~and we will forget this trespass.~";
                  if (adar has general) {PAF(); MoveAdar(13);}
                  PlayerTo(secret_tunnel2);
                  rtrue;
              Listen:
                  if (lc_vampires in self && lc_vampires.anger) "The ethereal spirits cry out, chilling you to the bone.";
              Sing:
                  if (lc_vampires in self) {
                      if (lc_vampires.anger) "The spirits only seem to enrage more at your abominable singing.";
                      "The spirits pay no attention to your abominable screeching.";
                  }
              Smell:
                  if (lc_vampires in self) "The ethereal fog chokes your lungs, as you expel noxious ether.";
                  "You can faintly smell the foul cavern back in this alcove, the noxious fumes now gone.";
          ],
          firstimein true;

! 05/03/06

  RoomObj -> secretchamberobj "secret alcove"
    with  name 'secret' 'alcove' 'room',
          description [;
              <<Look secret_chamber>>;
          ];

! 09/16/06

  Object  -> sa_bobelisk "black obelisk"
    with  name 'large' 'black' 'obelisk' 'rune' 'runes' 'star' 'half' 'circle' 'pointing' 'down' 'two' 'shrine',
          description [;
              if (orb in self or player or secret_chamber || torch in self or player or secret_chamber) {
                  print "The obsidian stone stands like a monolith to a god that is no longer there, ";
                  if (orb in sa_bobelisk) print "with a bright-red orb shining down like the sun, providing an eerie light";
                  else print "as the glowing orb provides an eerie light throughout the room";
                  if (lc_vampires in secret_chamber) print ", as four ethereal spirits encircle it";
                  ". Engraved upon the obelisk's face are two runes: a star and half a circle, pointing down.";
              }
              "Two runes have been engraved upon the face of the barely visible obsidian stone, a star and half a circle, pointing down.";
          ],
          before [;
              Climb:
                  "This isn't a gymnasium.";
              Read:
                  print "You can see a star and a half circle, pointing down, engraved upon the obelisk's face.";
                  if (omni_trans in player or milpack) " Perhaps your OmniTrans can translate it.";
                  new_line;
                  rtrue;
              Scan:
                  if (omni_trans notin player) return PNR();
                  if (lc_srune.haveread && lc_hlfcrune.haveread) {
                      POT();
                      style fixed;
                      print "The image of the star represented the number one for the people that once
                      lived here. Depicted as 0001 using their favored binary number system, it meant
                      ~Universal God~ and embodies the concept of energy and light.";
                      print "^^The image of a half circle (pointing down) represented the number of seven
                      for the people that once lived here. Depicted as 0111 using their favored binary
                      number system, it meant ~Part of God~ and embodies their concept of the shard.";
                      print "^^Closest translation: Sucored's shard.";
                      style roman;
                      "";
                  }
                  return PNE();
              Search:
                  "It's made of a thick obsidian stone, and looks untouched by time.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  "Firmly in place, the black obelisk refuses to move.";
              Touch:
                  "Runes have been carved into the face of the obelisk, giving it an uneven feeling.";
          ],
    has   static scenery supporter;
