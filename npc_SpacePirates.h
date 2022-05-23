
! 05/14/08

  Object  space_pirates "pirates"
    with  name 'pirates',
          daemon [;
              spmove++;
              switch (spmove) {
                  3, 7: move self to main_junction;
                     if (player in main_junction) return PirateDeath(1);
                     if (spmove == 7) print "^You hear the pirates enter the main junction as they start to climb down to the secondary one.^";
                     else print "^You hear metal-clad boots cross the main junction.^";
                     if (player in crew_quarters or bridge or galley or radar_room) return PirateDeath(2);
                  4: move self to galley;
                     if (player in galley) return PirateDeath(1);
                     if (player in gl_etube && gl_eacover.panopn) return PirateDeath(6);
                     if (DownBelow()) "^From the galley you hear a brief conversation, but you're too far away to make it out.";
                     "^~Looks like the seal's holding Captain,~ you hear coming from the galley as the pirates enter it.
                     ^^~You think I care about the seal, we're looking for that damn bilge rat,~ the other retorts.";
                  5: move self to radar_room;
                     if (player in radar_room) return PirateDeath(1);
                     if (player in rr_etube && rr_eacover.panopn) return PirateDeath(6);
                     if (player in cargo_hold or ch_etube) "^You hear metal-clad boots cross the main junction overhead, as the pirates enter the DMC searching it.";
                     "^You hear metal-clad boots cross the main junction, as the pirates enter the DMC.";
                  6: move self to crew_quarters;
                     if (player in crew_quarters) return PirateDeath(1);
                     if (player in berth) {
                         if (rack.curtain_open) return PirateDeath(3);
                         return PirateDeath(4);
                     }
                     if (player in cq_etube && cq_eacover.panopn) return PirateDeath(6);
                     rack.curtain_open = true;
                     if (player in cq_etube) "^You hear the pirates cross the main junction as they enter the crew quarters, opening up a few curtains, looking for anyone hiding in the bunks.";
                     "^You hear the pirates cross the main junction, entering the crew quarters. But only faint sounds can be heard in there, you're too far away to make anything out.";
                  8: move self to secondary_junction;
                     if (player in secondary_junction) return PirateDeath(7);
                     print "^You hear the pirates finish climbing down to the secondary junction.^";
                     if (player in engine_room or armory or cargo_hold) return PirateDeath(2);
                     if (player in main_airlock) {
                         if (uniform in mal_spacesuit && mal_spacesuit.malopn == false) rtrue;
                         return PirateDeath(2);
                     }
                  9: move self to engine_room;
                     if (player in engine_room) return PirateDeath(1);
                     if (player in er_etube && er_eacover.panopn) return PirateDeath(6);
                     "^You hear the pirates enter the engine room, as they push a few parts around looking for any clues.";
                  10, 12: move self to armory;
                      if (player in armory) return PirateDeath(1);
                      if (player in ar_etube && ar_eacover.panopn) return PirateDeath(6);
                      if (player in secondary_junction && spmove == 12) return PirateDeath(8);
                      if (spmove == 12) "^As the pirates return to the armory, they rattle the security gate as they thoroughly search the area.";
                      "^Metal-clad boots cross the secondary junction and bang into the security gate as the pirates enter the armory.";
                  11: move self to armory_backroom;
                      if (player in armory_backroom) return PirateDeath(1);
                      "^Loud banging can be heard coming from the store room.";
                  13: move self to main_airlock;
                      if (player in main_airlock) {
                          if (uniform in mal_spacesuit && mal_spacesuit.malopn == false) return PirateDeath(5);
                          return PirateDeath(1);
                      }
                      if (player in ma_etube && ma_eacover.panopn) return PirateDeath(6);
                      "^The pirates cross the secondary junction as they enter the airlock, pushing aside a few deep-space suits, looking for you.";
                  14: move self to cargo_hold;
                      if (player in cargo_hold) return PirateDeath(1);
                      if (player in ch_etube && ch_eacover.panopn) return PirateDeath(6);
                      StopDaemon(self);
                      thinkpos = 13;
                      remove self;
                      if (DownBelow())
                          print "^The pirates cross the secondary junction for the last time, as the party stops
                          in the cargo hold. You can barely make out their conversation, as one of them says,
                          ~Looks like it was just a glitch Captain, I don't see no one on board.~
                          ^^~Yeah Captain, it must be a glitch,~ another agrees.
                          ^^~It better be mates,~ the leader retorts, ~because if it's not, Stokar will have my head.~
                          ^^After that";
                          else print "^The pirates cross the secondary junction for the last time, as the party stops
                          in the cargo hold. You hear some sort of conversation coming up from below, but you're too
                          far away to make any of it out.^^Once they're done";
                      ", the pirates beam off the ship leaving you alone.";
              }
          ],
    has   concealed;

! 04/14/06

  Object  pirates_board "pirates",
    with  name 'pirates',
          daemon [;
              pattack = pattack + 1;
              switch(pattack) {
                  3: under_desk.patk = true;
                     if (player in galley) {
                         deadflag = 1;
                         "^All of a sudden, the port bulkhead is torn open as something strikes your
                         ship. Everything that is not bolted down in this room gets sucked out the
                         huge gaping hole that has been opened up, including you!";
                     } else {
                         thinkpos = 3;
                         bridge.dstop = false;
                         bridge.bridgealarm = true;
                               bridge_alarm.alarmon = true;
                               radar_room.enterbridge = true;
                               radar_room.captainknow = false;
                         StartDaemon(bridge_alarm);
                         "^Suddenly, something strikes the port side of the ship with a loud thud and
                         a screech of bolts, snapping you back to reality.";
                     }
                  4: if (player in bridge)
                         "^The sound of men boarding the ship can be heard echoing down the aft
                          corridor; you can't fight, so you'd better hide -- fast.";
                     if (player in crew_quarters)
                         "^The sound of men boarding the ship can be heard echoing down the forward
                         corridor; you can't fight, so you'd better hide -- fast.";
                     if (PLocTest()) "^The sound of men boarding the ship can be heard echoing down the port corridor.";
                     if (player notin outside_airlock or ontopofship)
                     "^The sound of men boarding the ship can be heard echoing down the port corridor;
                     you can't fight, so you'd better hide -- fast.";
                  5: if (player notin outside_airlock or ontopofship) {
                           print "^You can hear the sound of metal-clad boots getting closer, as men begin to fan out throughout the ship";
                           if (PLocTest()) ".";
                           "; there's not much time left!";
                     }
                  6: if (player notin outside_airlock or ontopofship) {
                           print "^You can hear more yelling and shouting as men fan out through out the ship. It's hard
                           to be sure what they're searching for";
                           if (PLocTest()) ".";
                           "; you better hurry!";
                     }
                  7: if (player notin outside_airlock or ontopofship) {
                           print "^More cries can be heard echoing down the corridor, as men search throughout
                           the ship. It's hard to be sure, but they seem to be headed for the cargo hold";
                           if (PLocTest()) ".";
                           "; if they find you, you're dead!";
                     }
                  8: if (player in engine_room or secondary_junction or armory or armory_backroom) return PSrchDeth();
                      if (player in main_airlock) {
                          if (blastdoor in main_airlock) {
                          } else {
                              return PSrchDeth();
                          }
                      }
                      if (player notin outside_airlock or ontopofship) {
                         print "^The thundering footsteps seem to be heading this way, amid more angry shouting";
                         if (player in under_desk || (player in berth && rack.curtain_open == false) || (player in main_airlock && blastdoor in main_airlock)) ".";
                         "; surely they're close!";
                     }
                  9: under_desk.patk = false;
                     if (player in under_desk) return PirateHide(1);
                     if (player in outside_airlock or ontopofship) return PirateAttack();
                     if (player in berth && rack.curtain_open == false) return PirateHide(1);
                     if (player in main_airlock && blastdoor in main_airlock) return PirateHide(2);
                     if (PTubeTest()) return PirateHide(3);
                     deadflag = 1;
                     if (location == berth) location = crew_quarters;
                     if (location == armory_backroom) location = armory;
                     print "^All of a sudden, a group of space pirates barge into ", (the) location;
                     ". ~Aye,~ one of them says, ~looks like we got us a live one here.~ A
                     roar of laughter breaks out as the pirates grab hold of you, throwing
                     you out their airlock.";
                       10: StopDaemon(self);
              };
          ];

! 04/21/06

  Object  pirates_land "pirates",
    with  name 'pirates',
          daemon [;
              pland = pland + 1;
              if (pland == (plimit-1)) player.plprt = false;
              if (pland == plimit) {
                  if (player in ontopofship) move bu_planet to ontopofship;
                  else move bu_planet to outside_airlock;
                  if (player in outside_airlock or ontopofship) {
                      "^You start to feel the ship enter gravity again, as a small red planet come closer into view.";
                  } else {
                      "^You start to feel the ship enter gravity again, as you're pulled down towards a planet.";
                  }
              }
              if (pland == (plimit+5)) {
                  if (player in outside_airlock or ontopofship) {
                      "^You feel the gravity pulling you down even more as you get closer to the red planet.";
                  } else {
                      "^You feel the gravity pulling you down even more as you get closer to the planet.";
                  }
              }
              if (pland == (plimit+10)) {
                  if (player in outside_airlock or ontopofship) {
                      deadflag = 1;
                      "^As the ship hits the atmosphere, the force of the air blows you off it.
                      You free fall for a little bit, but burn up soon afterwards in the friction of this
                      celestial expanse.";
                  }
                  "^The pull from the planet feels unusually strong as you break atmosphere.";
              }
              if (pland == (plimit+15)) {
                  if (r_planet in bridge) remove r_planet;
                  if (player in hidden_compartment) "^All of a sudden, you feel the ship land, as you're bounced around in the hidden compartment.";
                  "^All of a sudden, you feel the ship land, as you're bounced off the deck and lose your footing.";
              }
              if (pland == (plimit+17)) {
                  if (player in cargo_hold) {
                      deadflag = 1;
                      "^All of a sudden, the cargo hatch opens before you, and the pirates that
                      have taken over the ship give you a quick once over.
                      ^^~Aye,~ says one of them, ~guess we didn't get 'em all, but I say we make
                      an example out of this one.~ The leader grabs you, as a few pirates plant
                      four stakes in the ground, and tie you down under a blazing hot sun, in the
                      middle of a desert. They laugh to themselves going back to looting the ship,
                      as you start to slowly bake on this deserted planet.
                      ^^Maybe you should've found a better place to hide.";
                  } else {
                      "^You can hear the cargo hatch open.";
                  }
              }
              if (pland == (plimit+18)) {
                  if (player in cargo_hold) {
                      deadflag = 1;
                      "^All of a sudden, you run into the pirates that have boarded the ship
                      again.
                      ^^~Aye,~ says one of the pirates, ~I knew we couldn't have gotten
                      'em all. There like blood ticks on a ship, always another one under
                      a panel or behind a bulkhead.~ The other pirates grunt in approval.
                      ~I say we strap this one to the hull of our ship, and see how they
                      do in deep space.~
                      ^^As they drag you off and strap you up, you can only think that it would
                      have been a good idea to find a better hiding spot.";
                  } else {
                      if (web_netting.nettingopen && large_crate in cargo_hold) {
                          if (player in hidden_compartment) {
                              if (s_panel.sopen) {
                                  print "^Sitting in the confines of this hidden room, you hear the cargo hatch
                                  open as the space pirates begin to loot the ship. With the large crate
                                  pushed back and the secret panel open, the pirates notice you right away.
                                  Immediately they pull you out of there by one of your ears.";
                              } else {
                                  print "^Trapped in the darkness of this hidden room, you hear the cargo hatch
                                  open as the space pirates begin to loot the ship. Seeing that the crate
                                  is out of place they open the secret panel and pull you out of there by
                                  one of your ears.";
                              }
                              deadflag = 1;
                              "^^~Aye,~ says one of the pirates, ~we don't got time for this one.~ So he
                              pulls out his saber, and runs you through the gut. Slowly you bleed out
                              on the floor.
                              ^^Maybe you should have gotten the crate back into place so the pirates
                              wouldn't have known you were there.";
                          }
                      }
                  }
                  "^You can hear the pirates start to make noise as they come aboard the ship.";
              }
              if (pland == (plimit+19)) {
                  deadflag = 1;
                  if (location == berth) location = crew_quarters;
                  if (location == under_desk) location = radar_room;
                  if (location == armory_backroom) location = armory;
                  print "^All of a sudden, the group of space pirates that took over the ship ";
                  if (PTubeTest())  print "make their way to ";
                  else print "barged into ";
                  print (the) location, ".^^~Look,~ shouts the leader, ~Like a rat
                  on a sinking ship, and this makes the second stray we sunk today boys!~ The
                  other pirates cheer him on. ~I say we strap this one to our hull and see
                  how they do in deep space.~^";
                  "^As they drag you off and strap you up to their ship, it's hard not to
                  reflect on the fact that you needed a better place to hide.";
              }
          ];
