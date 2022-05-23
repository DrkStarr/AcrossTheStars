
! ---------------------------------------------------------------------------- !
!       The ARMORY. 09/22/06
!
  RoomShp armory "Armory"
    with  description [;
              if (space_pirates in self) return PirateDeath(0);
              print "The Armory is usually spotless and locked up tight. Say what you like about
              Ensign Striker, the officer in charge -- and everyone does, behind his back -- he's
              efficient. If he was here now, he'd have someone's head for this. The place has been
              ransacked, probably by desperate crew members, and there's nothing left. The port
              security gate, which is normally locked, has been forced open half way, and an open
              hatchway leads back out to starboard. Also, the engineering access cover is ";
              if (ar_eacover.panopn) "opened, giving you access to the e-tubes.";
              "closed.";
          ],
          e_to [;
              return secondary_junction;
          ],
          w_to [;
              <<Enter armory_gate>>;
          ],
          in_to [;
              <<Enter ar_eacover>>;
          ],
          cant_go
              "You can go into the e-tube, or, port or starboard.",
          before [;
              Exit:
                  PlayerTo(secondary_junction);
                  rtrue;
          ];

! 09/23/06

  RoomObj -> armoryobj "armory"
    with  name 'armory' 'armoury' 'ship' 'room',
          description [;
              <<Look armory>>;
          ];

! 05/11/08

  OutRch  -> arm_bckrm "back room"
    with  name 'back' 'room',
          before [;
              Enter:
                  <<Enter armory_gate>>;
              Examine, Search:
                    "It looks like the lockers have been torn into, but you'll have to enter it to get a better look.";
          ];

! 05/13/08

  EACovr  -> ar_eacover "engineering access cover"
    with  name 'engineering' 'access' 'cover' 'tube' 'tubes' 'e-tube' 'e-tubes' '1351ph' 'panel',
          before [;
              Enter:
                  if (self.panopn == false) {
                      self.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You enter the e-tube.^";
                  PlayerTo(ar_etube);
                  rtrue;
          ],
          panopn false;

! 10/25/06

  Object  armory_gate "security gate"
    with  name 'partially' 'forced' 'open' 'security' 'gate' 'broken' 'jammed',
          description [;
              if (player in armory) "The security gate has been ripped into and forced open, just far enough to access the back room.";
              "The security gate has been ripped into and forced open, just far enough to access this room.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                    return PDE();
              Close:
                    "The gate is jammed open and you can't seem to shut it.";
              Enter:
                    print "It's a tight fit, but you manage to make your way through the broken security gate.^";
                    if (player in armory) {
                        PlayerTo(armory_backroom);
                        rtrue;
                    }
                    PlayerTo(armory);
                    rtrue;
              Open, Fix, PushDir, Push, Pull, Remove, Turn:
                    "That's already open.";
              Search:
                    "It looks like crew members forced the gate open in their state of panic.";
              Take:
                  "It would only slow you down.";
          ],
          found_in armory armory_backroom
    has   static;
