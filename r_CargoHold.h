
! ---------------------------------------------------------------------------- !
!       The CARGO HOLD. 04/16/06
!
  RoomShp cargo_hold "Cargo Hold"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              if (cargo_hatch.hatchopen) {
                  print "The main cargo hatch in the starboard bulkhead is now open, letting in
                  the blinding light and boiling heat of what looks to be a desert outside, judging by the
                  sand that has drifted in. There's ";
                  if (s_panel.sopen) {
                      print "an open ";
                  } else {
                      print "a closed ";
                  }
                  print "panel in the fore bulkhead, while an open hatchway to the aft leads back to the
                  secondary junction.";
              } else {
                  if (s_panel in cargo_hold) {
                      print "This space is vast; big enough to carry supplies and equipment for several
                      regiments, but all that's left is one large un-strapped crate in the corner
                      of the room. The crate has been pushed back from the wall, exposing a secret
                      panel in the fore bulkhead. An open hatchway lies aft, while an enormous
                      cargo hatch is to starboard.";
                  } else {
                      if (web_netting.nettingopen) {
                            print "This space is vast; big enough to carry supplies and equipment for several
                          regiments, but all that's left is one large un-strapped crate in the corner
                          of the room. An open hatchway lies aft, while an enormous cargo hatch is to
                          starboard.";
                      } else {
                          print "This space is vast; big enough to carry supplies and equipment for
                          several regiments. Earlier today, that's exactly what it did carry, but it's
                          all in the hands of the pirates now. All, that is, except for one large crate,
                          strapped down with a high-security web net that must have defeated the pirates.";
                          if (prybar in self) print " They tried, though, as a pry bar lying beside it testifies.";
                          print "^^Set into the port wall, there is a badge reader: just a small display and an ident
                          slot. An open hatchway lies aft, while an enormous cargo hatch is to starboard.";
                      }
                  }
              }
              print " Also, the engineering access cover is ";
              if (ch_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          n_to [;
              if ((web_netting.nettingopen && s_panel in self) || self.cpland) {
                  if (s_panel.sopen) {
                      print "You crawl into the hidden compartment.^";
                      return hidden_compartment;
                  } else {
                      s_panel.sopen = true;
                      print "(first opening the secret panel)
                      ^You crawl into the hidden compartment.^";
                      return hidden_compartment;
                  }
              }
          ],
          s_to secondary_junction,
          e_to [;
              if (cargo_hatch.hatchopen) <<Enter cargo_hatch>>;
              "You can't go that way; the cargo hatch is closed.";
          ],
          in_to [;
              if ((web_netting.nettingopen && s_panel in self) || self.cpland) {
                  if (s_panel.sopen) {
                      print "You crawl into the hidden compartment.^";
                      return hidden_compartment;
                  } else {
                      s_panel.sopen = true;
                      print "(first opening the secret panel)
                      ^You crawl into the hidden compartment.^";
                      return hidden_compartment;
                  }
              }
              <<Enter ch_eacover>>;
          ],
          cant_go [;
              if (cargo_hatch.hatchopen) "You can only go through the aft hatchway, or exit out the cargo hatch to your starboard.";
              "You can go through the aft hatchway or into the e-tube.";
          ],
          before [;
              Exit:
                  if (noun == cargo_hatch) "Please use normal navigation directions. FORWARD, AFT, PORT, and STARBOARD.";
                  if (cargo_hatch.hatchopen) <<Enter cargo_hatch>>;
                  PlayerTo(secondary_junction);
                  rtrue;
          ],
          cpland false;

! 04/28/06

  RoomObj -> cargoobj "cargo hold"
    with  name 'hold' 'ship' 'room',
          description [;
              <<Look cargo_hold>>;
          ];

! 04/17/06

  Object  -> large_crate "large crate"
    with  name 'large' 'crate' 'cargo' 'base' 'writing',
          description [;
              if (web_netting.nettingopen) {
                  if (self.movedaft) {
                      print "The large crate has been pushed back from the wall,";
                  } else {
                      print "The large crate sits in the corner,";
                  }
                  " surrounded by the web net. Now that the net is free, you can see that the crate
                  is protected with a quantum entanglement lock. These are fantastically expensive,
                  so they're only used on the most valuable items; all of which makes you think that
                  the words ~Imperial Mint~ imprinted on the sides of the crate probably don't mean
                  peppermint candy.";
              } else {
                  "The large crate is strapped down with automatic web netting, securing it in
                  the corner. Something is written on the crate, but you can't see what it is due
                  to the netting obscuring the writing.";
              }
          ],
          before [;
              Attack:
                  return PDE();
              Climb:
                  if (web_netting.nettingopen) "There's no reason to climb up the crate, you'll never open the lock.";
                  "You'll never open the net climbing all over it.";
              LookBehind:
                  return PRB();
              LookUnder:
                  "With all the mechanics in the way, you can't see underneath the large crate.";
              Open:
                  if (web_netting.nettingopen) "You can't open the crate; it's locked with a quantum lock.";
                  "You can't access the large crate; it's strapped down.";
              Push, Pull, PushDir:
                  if (web_netting.nettingopen) {
                      if (self.movedaft) "The crate has already been moved aft.";
                      if (s_panel notin cargo_hold) {
                          if (self.lc_scored) {
                              self.lc_scored = false;
                              if (pland < plimit && pland > (plimit-25)) plimit = plimit + 25;
                              web_netting.netopen = false;
                              score = score + 5;
                              thinkpos = 14;
                          }
                          move s_panel to cargo_hold;
                      }
                      self.movedaft = true;
                      if (s_panel.sopen) {
                          "With great effort you manage to push the crate a little aft, revealing an opening
                          in the fore bulkhead due to a panel which has been set aside.";
                      } else {
                          "With great effort you manage to push the crate a little aft, revealing a panel that
                          blends almost perfectly into the wall; if you hadn't been looking for it, you'd have
                          missed it. This must be the bolthole the Captain was talking about during your initial
                          orientation.";
                      }
                  }
                  if (web_netting.nettingon == false) "You can't move the large crate; it's still strapped down.";
                  "You can't access the large crate; it's strapped down.";
              Read:
                    if (web_netting.nettingopen) "~Imperial Mint~ is imprinted upon the side. Looks like this crate wasn't going to a regiment like you thought.";
                    "The netting is obscuring the writing.";
              Search:
                    if (web_netting.nettingopen) "You can get into the crate because it's sealed shut with a quantum lock.";
                    "You can't get into the crate. The automatic web netting makes it inaccessible.";
              Take, Remove, Turn:
                  if (web_netting.nettingopen) <<Push self>>;
                  "The automatic web netting holds it in place.";
              Unlock:
                    if (web_netting.nettingopen) "You can't unlock the crate; it's locked with a quantum lock.";
                  if (second == prybar) {
                      "The pry bar is useless against the automatic web net; the pirates would have the
                      cargo by now if this were not true.";
                  }
                  "You can't access the large crate; it's strapped down.";
              UnStrap:
                  <<Open web_netting>>;
          ],
          lc_scored true,
          movedaft false,
    has   scenery lockable locked static;

! 04/17/06

  Object  -> web_netting "automatic web netting"
    with  name 'automatic' 'web' 'netting' 'net' 'webbing' 'strap' 'straps' 'high-security' 'security',
          description [;
              print "The automatic web netting is designed to keep cargo secure during deep space transport";
              if (self.nettingopen) ", but it's now open and the cargo is unsecured.";
              ". Covering the cargo, it's secured to the floor with a series of clamps.";
          ],
          before [;
              Attack:
                  return PDE();
              Climb:
                  if (self.nettingopen) "But it's up and out of the way.";
                  "You'll never open the net climbing all over it.";
              Cut:
                  "The netting is made of woven carbon nanofibres and is far too strong to
                  be cut by hand, or even by the kind of equipment the pirates carry.";
              Open, Unlock, Unstrap:
                  if (self.nettingopen) "The netting is already opened.";
                  if (self.nettingon) {
                      if ((ident_badge in player || parent(ident_badge) in player || (ident_badge in milpack && milpack in player or uniform) || (parent(ident_badge) in milpack && milpack in player or uniform)) && (wrench in player || (wrench in milpack && milpack in player or uniform))) {
                          give self ~on;
                          self.nettingon = false;
                          self.nettingopen = true;
                          move ident_badge to web_netting;
                          if (wrench in milpack) give milpack open;
                          if (space_lock notin cargo_hold) move space_lock to cargo_hold;
                          PAC();
                          PXB();
                          print "(using the universal tool)^";
                          return POW();
                      }
                      if (ident_badge in player || parent(ident_badge) in player || (ident_badge in milpack && milpack in player or uniform) || (parent(ident_badge) in milpack && milpack in player or uniform)) {
                          give self ~on;
                          self.nettingon = false;
                          move ident_badge to web_netting;
                          PAC();
                          PXB();
                          "You need to open the netting with some sort of tool.";
                      }
                      if (self.badgeblow) return PNetFOpen();
                      "You need to turn the netting off first, using the Captain's ident badge.";
                  }
                  if (wrench in player || (wrench in milpack && milpack in player or uniform)) {
                      self.nettingopen = true;
                      if (wrench in milpack) give milpack open;
                      if (space_lock notin cargo_hold) move space_lock to cargo_hold;
                      if (second == wrench) return POW();
                      print "(using the universal tool)^";
                      return POW();
                  }
                  if (second == prybar) {
                      "The pry bar is useless against the automatic web net; the pirates would have the
                      cargo by now if this were not true.";
                  }
                  "You need to open the netting with some sort of tool.";
              Search:
                  if (self.nettingopen) "You can't see through the net with it retracted.";
                  "As you look through the net, you can see that it's securing a large crate;
                  but you'll have to open it in order to get to the cargo.";
              SwFlip, SwitchOn, Push, PushDir, Pull, UseItem:
                  if (self.nettingopen) return PSH();
                  <<Open self>>;
              FlipOff, SwitchOff:
                  if (ident_badge in player || parent(ident_badge) in player || (ident_badge in milpack && milpack in player or uniform) || (parent(ident_badge) in milpack && milpack in player or uniform)) {
                      give self ~on;
                      self.nettingon = false;
                      move ident_badge to web_netting;
                      PXB();
                      rtrue;
                  }
                  return PSH();
              Take, Remove:
                  if (self.nettingopen) "It's not only bulky, but it's government property and you can't think of a use for it.";
                  <<Open self>>;
              Turn:
                  return PAG();
          ],
          netopen true,
          nettingon true,
          badgeblow false,
          nettingopen false,
    has   scenery static lockable locked container open on;

! 04/17/06

  Object  -> ch_chipreader "badge reader"
    with  parse_name [w1 w2 w3;
              w1 = NextWord();
              if (w1 ~= 'badge' or 'reader' or 'readout' or 'screen' or 'small' or 'slot' or 'ident' or 'display') return 0;
              w2 = NextWord();
              w3 = NextWord();
              if (w1 == 'small' && w2 == 'readout' && w3 == 'screen') return 3;
              if (w1 == 'badge' or 'small' or 'readout' or 'ident' && w2 == 'reader' or 'readout' or 'display' or 'screen' or 'slot') return 2;
              if (w1 == 'slot' or 'display') return 3;
              return 1;
          ],
          description [;
              if (web_netting.nettingopen) "Inside the chip reader the Captain's ident badge has opened up the automatic web netting.";
              if (web_netting.nettingon == false) "The small display reads: ~Manual override engaged.~";
              "Badge readers are simple devices, with a slot for an ident badge and a small readout screen. According to the display, this one controls the clamps on the automatic web netting, and requires a Level 5 ident to deactivate.";
          ],
          before [;
              Attack:
                  "You can't seem to break open the chip reader.";
              Open, Unlock, Unstrap:
                  if (web_netting.nettingopen) return PSH();
                  "You need to open the webbing, not the chip reader.";
              Read:
                  if (ident_badge in web_netting) {
                      print "The readout displays:^^";
                      style fixed;
                      print "** Manual override engaged **";
                      style roman;
                      "";
                  }
                  "The readout is blank.";
              SwFlip, Push, UseItem:
                  if (web_netting.nettingopen) <<SwitchOn self>>;
                  <<SwitchOff web_netting>>;
              Scan:
                  if (omni_trans notin player) "You need to use an OmniTrans to scan the chip reader.";
                        if (ident_badge in web_netting) {
                      POT();
                      style fixed;
                      print "** Manual override engaged **";
                      style roman;
                      "";
                  }
              Search:
                  "A simple device, the chip reader has a slot for an ident badge, along with a small readout screen.";
              SwitchOn:
                  if (web_netting.nettingopen) {
                      web_netting.nettingopen = false;
                      give web_netting on;
                      move ident_badge to player;
                      web_netting.nettingon = true;
                      if (s_panel in cargo_hold) remove s_panel;
                      if (space_lock in cargo_hold) remove space_lock;
                      "Turning on the chip reader, you pull out the Captain's ident badge. This causes the
                      automatic web netting to kick in, as it wraps itself around the crate once again.";
                  }
                  return PSH();
              FlipOff, SwitchOff:
                  <<SwitchOff web_netting>>;
              Take, Remove, Turn, PushDir, Pull:
                  return PSH();
          ],
    has   concealed container open static;

! 04/17/06

  Object  -> tiedown_claps "tie-down clamps"
    with  name 'tie' 'down' 'tie-down' 'clamp' 'clamps' 'unbreakable' 'alloy' 'mechanics',
          description
              "These clamps are the top-of-the line model, with the new remote authorization
              feature: access can be controlled wirelessly via an external security terminal,
              such as an ident badge reader. Whatever they're protecting must be valuable.",
          before [;
              Attack:
                  return PDE();
              Open, Unlock:
                  if (web_netting.nettingon == false) <<Open web_netting>>;
                  if (second == wrench) return PNetFOpen();
                  if (second == prybar)
                      "The pry bar is useless against the tie-down clamps; the pirates would have the
                      cargo by now if this were not true.";
                  "The clamps are locked in position, which probably means they require
                  authorization from the badge reader to unlock.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static pluralname;

! 04/17/06

  Object  -> system_n_reader "ratcheting system"
    with  name 'strange' 'ratchet' 'ratchets' 'ratcheting' 'system',
          description
              "The ratcheting system is able to sense pitch and yaw, knowing when the cargo's in
              deep space. This keeps the mechanics engaged and everything tightly in place.",
          before [;
              Attack, Cut:
                  return PDE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static;

! 04/22/06

  Object  -> cargo_hatch "cargo hatch"
    with  name 'cargo' 'hatch' 'large' 'bay' 'door' 'sealed',
          description [;
              if (self.hatchopen) "The cargo hatch is a large, open, bay door taking up most the starboard bulkhead.";
              "The cargo hatch is a large, sealed, bay door taking up most the starboard bulkhead.";
          ],
          before [;
              Attack:
                  return PDE();
              Enter:
                  if (self.hatchopen) {
                      u_obj.&name-->4 = 'sky';
                      PlayerTo(desert);
                      rtrue;
                  }
              Open:
                  if (self.hatchopen) "That's already open.";
                  if (pland >= (plimit+10)) "You would have to be insane to try to open the cargo hatch during reentry.";
                  "That would expose the hold to the vacuum of space; why don't you wait until there's some atmosphere outside?";
              Close:
                  return PSH();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          hatchopen false,
    has   concealed static;

! 05/10/08

  Object  -> ch_rivets "rivets"
    with  name 'rivet' 'rivets',
          description [;
              if (s_panel in cargo_hold) "The panel by the large crate is studded in two rivet intervals.";
              "The rivet spacing looks normal on all of the bulkheads.";
          ],
          before [;
              Attack, Cut:
                  return PDE();
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
    has   concealed static pluralname;

! 09/23/06

  Object  -> ch_hatchways "hatchway"
    with  name 'hatchway' 'hatchways' 'hatchway^s' 'door' 'doors',
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
    has   concealed static enterable openable;

! 05/13/08

  EACovr  -> ch_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph',
          before [;
              Enter:
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(ch_etube);
                  rtrue;
          ],
          panopn false;
