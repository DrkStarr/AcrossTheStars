
! ---------------------------------------------------------------------------- !
!       The DUNES. 04/24/06
!
  Room    dunes "Dunes"
    with  description [;
              hs_mre.pchungry = true;
              coffee_cup.pcdunes = true;
              "Here amid the burning sand, it's so hot you can barely see, let alone think straight.
              Between the sand and the sweat rolling from your forehead, you have to look around a
              blink at a time. To the east, fairly close, you can see a large stone building surrounded
              by trees. It's barely credible, but in among the trees you can see a pool of clear blue water.
              ^^You can't see it from here, but you seem to remember that your ship is back west.";
          ],
          e_to m_base,
          w_to [;
              self.triedwest = true;
              "With water and possibly some form of intelligent life this close? You'd never make it back
              to your ship now.";
          ],
          cant_go [;
              print "You could go that way, but it's a landscape only a sandophile could love, and you're
              dehydrating rapidly. Have you considered all that the building to the east has to offer";
              if (self.triedwest) {
                  "?";
              } else {
                  ", or possibly returning west to the remains of your ship?";
              }
          ],
          before [;
              Listen:
                  "There's nothing but the rush of the harsh wind past your ears.";
          ],
          triedwest false;
