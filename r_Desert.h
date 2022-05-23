
! ---------------------------------------------------------------------------- !
!       The DESERT. 04/23/06
!
  Room    desert "Desert"
    with  initial [;
              thinkpos = 5;
              if (self.firstime) {
                  print "As you step out of the ship into the blazing desert sun, you watch the black pirate
                  ship blast off from the surface and shoot high into the atmosphere, leaving you stranded.
                  Slowly, the enormity of your situation begins to sink in: the ship is crippled, there
                  won't be any equipment left worth speaking of -- certainly nothing you could use to
                  contact anybody -- and ";
                  if (galley.pgseen) {
                      print "it looks like they've taken the food and water as well";
                  } else {
                      print "the chances are they'll have taken the food and water as well";
                  }
                  if (hs_mre in player || hs_mre in milpack) ". At least you have a pack of MREs with you.";
                  ".";
              }
          ],
          description [;
              thinkpos = 5;
              if (self.firstime) {
                  self.firstime = false;
                  if (hs_mre in player || hs_mre in milpack) print "The other";
                  else print "The only";
                  " piece of good news is that the desert isn't completely featureless: in
                  the eastern distance, there might be a settlement of some kind. There's certainly a
                  boxy stone structure surrounded by -- just maybe -- a stand of trees. You seriously
                  hope it's not a mirage.";
              }
              "The sun beats mercilessly down on you from above, making you sweat profusely even
              though you're in the shade from your fallen ship. A hot western wind has also kicked up;
              you won't be able to stay here long. You can see a building off to the east, and the
              wreck of your ship to the west, but that's about it. Just sand, sand and more sand,
              in rolling dunes as far as you can see.";
          ],
          n_to [;
              if (noun == fore_obj) "You're not aboard ship now, matey.";
          ],
          s_to [;
              if (noun == aft_obj) "You're not aboard ship now, matey.";
          ],
          e_to [;
              if (noun == starboard_obj) "You're not aboard ship now, matey.";
              DeleteCompassObjects();
              return dunes;
          ],
          w_to [;
              if (noun == port_obj) "You're not aboard ship now, matey.";
              <<Exit self>>;
          ],
          in_to [;
              <<Exit self>>;
          ],
          cant_go [;
              "You could go that way, but it's a landscape only a sandophile could love, and you're
              dehydrating rapidly. Have you considered all that the building to the east has to offer,
              or possibly returning west to the remains of your ship?";
          ],
          before [;
              Exit:
                  thinkpos = 7;
                  u_obj.&name-->4 = '7840ph';
                  print "You walk aboard the trans-stellar transport.^";
                  PlayerTo(cargo_hold,2);
                  rtrue;
              Listen:
                  "There's nothing but the rush of the harsh wind past your ears.";
          ],
          firstime true;

! 04/23/06

  Object  -> transport_ship "trans-stellar transport"
    with  name 'transport' 'ship' 'trans' 'stellar' 'ss' '26' 'trans-stellar' 'transstellar' 'wreck' 'large' 'gray',
          description
              "It's a large gray trans-stellar transport, ravaged by pirates that have looted
              everything onboard.",
          describe [;
              "^The wreck of your trans-stellar transport lies here.";
          ],
          before [;
              Enter:
                  <<Exit desert>>;
              Listen:
                  "There's nothing but the rush of the harsh wind past your ears.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PNH();
          ],
    has   static scenery;
