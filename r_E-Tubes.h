
! ---------------------------------------------------------------------------- !
!       E-TUBE - CREW QUARTERS. 05/13/08
!
  ETubes  cq_etube "E-Tube"
    with  description [;
              if (cq_eacover.panopn) cq_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          n_to [;
              <<Exit self>>;
          ],
          e_to [;
              return rr_etube;
          ],
          w_to [;
              return gl_etube;
          ],
          d_to [;
              return er_etube;
          ],
          before [;
              Exit:
                  if (cq_eacover.panopn == false) {
                      cq_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(crew_quarters);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> cqetobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look cq_etube>>;
          ];

! 05/13/08

  Object  -> cq_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'crew' 'quarters' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (cq_eacover.panopn) {
                      cq_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      cq_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (cq_eacover.panopn) "open, giving you access to the crew quarters.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (cq_eacover.panopn) "That's already open.";
                  cq_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  cq_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the crew quarters.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit cq_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - BRIDGE. 05/13/08
!
  ETubes  br_etube "E-Tube"
    with  description [;
              if (br_eacover.panopn) br_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          s_to [;
              <<Exit self>>;
          ],
          e_to [;
              return rr_etube;
          ],
          w_to [;
              return gl_etube;
          ],
          d_to [;
              return ch_etube;
          ],
          before [;
              Exit:
                  if (br_eacover.cvrlck) "The access cover seems to be locked from the other side.";
                  if (br_eacover.panopn == false) {
                      br_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(bridge);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> bretobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look br_etube>>;
          ];

! 05/13/08

  Object  -> br_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'bridge' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (br_eacover.cvrlck) "The access cover seems to be locked from the other side.";
                  if (br_eacover.panopn) {
                      br_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      br_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (br_eacover.panopn) "open, giving you access to the bridge.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (br_eacover.panopn) "That's already open.";
                  if (br_eacover.cvrlck) "The access cover seems to be locked from the other side.";
                  br_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  br_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the bridge.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit br_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - GALLEY. 05/13/08
!
  ETubes  gl_etube "E-Tube"
    with  description [;
               if (gl_eacover.panopn) gl_etcvr.&name-->3 = 'opening';
               return PET();
          ],
          n_to [;
              return br_etube;
          ],
          s_to [;
              return cq_etube;
          ],
          e_to [;
              <<Exit self>>;
          ],
          d_to [;
              return ar_etube;
          ],
          before [;
              Exit:
                  if (gl_eacover.panopn == false) {
                      gl_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  if (pattack > 2 && pattack < 9) {
                      deadflag = 1;
                      "^You step into on a bunch of space pirates as they're boarding the ship.
                      ~Aye,~ one of them says, ~looks like we got us a live one here.~ A roar
                      of laughter breaks out as the pirates grab hold of you, throwing you out
                      their airlock.";
                  }
                  PlayerTo(galley);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> gletobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look gl_etube>>;
          ];

! 05/13/08

  Object  -> gl_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'galley' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (gl_eacover.panopn) {
                      gl_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      gl_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (gl_eacover.panopn) "open, giving you access to the galley.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (gl_eacover.panopn) "That's already open.";
                  gl_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  gl_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the galley.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit gl_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - DATA MINING CENTER. 05/13/08
!
  ETubes  rr_etube "E-Tube"
    with  description [;
              if (rr_eacover.panopn) rr_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          n_to [;
              return br_etube;
          ],
          s_to [;
              return cq_etube;
          ],
          w_to [;
              <<Exit self>>;
          ],
          d_to [;
              return ma_etube;
          ],
          before [;
              Exit:
                  if (rr_eacover.panopn == false) {
                      rr_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(radar_room);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> rretobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look rr_etube>>;
          ];

! 05/13/08

  Object  -> rr_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'dmc' 'data' 'mining' 'center' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (rr_eacover.panopn) {
                      rr_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      rr_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (rr_eacover.panopn) "open, giving you access to the DMC.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (rr_eacover.panopn) "That's already open.";
                  rr_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  rr_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the DMC.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit rr_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - ENGINE ROOM. 05/13/08
!
  ETubes  er_etube "E-Tube"
    with  description [;
              if (er_eacover.panopn) er_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          n_to [;
              <<Exit self>>;
          ],
          e_to [;
              return ma_etube;
          ],
          w_to [;
              return ar_etube;
          ],
          u_to [;
              return cq_etube;
          ],
          before [;
              Exit:
                  if (er_eacover.panopn == false) {
                      er_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(engine_room);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> eretobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes',
          description [;
              <<Look er_etube>>;
          ];

! 05/13/08

  Object  -> er_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'engine' 'room' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (er_eacover.panopn) {
                      er_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      er_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (er_eacover.panopn) "open, giving you access to the engine room.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (er_eacover.panopn) "That's already open.";
                  er_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  er_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the engine room.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit er_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - CARGO HOLD. 05/13/08
!
  ETubes  ch_etube "E-Tube"
    with  description [;
              if (ch_eacover.panopn) ch_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          s_to [;
              <<Exit self>>;
          ],
          e_to [;
              return ma_etube;
          ],
          w_to [;
              return ar_etube;
          ],
          u_to [;
              return br_etube;
          ],
          before [;
              Exit:
                  if (small_crates in secondary_junction) "There seems to be something blocking the access cover on the other side.";
                  if (ch_eacover.panopn == false) {
                      ch_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(cargo_hold);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> chetobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look ch_etube>>;
          ];

! 05/13/08

  Object  -> ch_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'cargo' 'hold' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (ch_eacover.panopn) {
                      ch_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      ch_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (ch_eacover.panopn) "open, giving you access to the cargo hold.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (ch_eacover.panopn) "That's already open.";
                  if (small_crates in secondary_junction) "There seems to be something blocking the access cover on the other side.";
                  ch_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  ch_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the cargo hold.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit ch_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - ARMORY. 05/13/08
!
  ETubes  ar_etube "E-Tube"
    with  description [;
              if (ar_eacover.panopn) ar_etcvr.&name-->3 = 'opening';
              return PET();
          ],
          n_to [;
              return ch_etube;
          ],
          s_to [;
              return er_etube;
          ],
          e_to [;
              <<Exit self>>;
          ],
          u_to [;
              return gl_etube;
          ],
          before [;
              Exit:
                  if (ar_eacover.panopn == false) {
                      ar_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(armory);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> aretobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look ar_etube>>;
          ];

! 05/13/08

  Object  -> ar_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'armory' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (ar_eacover.panopn) {
                      ar_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      ar_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (ar_eacover.panopn) "open, giving you access to the armory.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (ar_eacover.panopn) "That's already open.";
                  ar_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  ar_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the armory.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit ar_etube>>;
          ],
    has   static;

! ---------------------------------------------------------------------------- !
!       E-TUBE - MAIN AIRLOCK. 05/13/08
!
  ETubes  ma_etube "E-Tube"
    with  description [;
               if (ma_eacover.panopn) ma_etcvr.&name-->3 = 'opening';
               return PET();
          ],
          n_to [;
              return ch_etube;
          ],
          s_to [;
              return er_etube;
          ],
          w_to [;
              <<Exit self>>;
          ],
          u_to [;
              return rr_etube;
          ],
          before [;
              Exit:
                  if (ma_eacover.panopn == false) {
                      ma_eacover.panopn = true;
                      print "(first opening the engineering access cover)^";
                  }
                  print "You exit the e-tube.^";
                  PlayerTo(main_airlock);
                  rtrue;
          ];

! 05/13/08

  RoomObj -> maetobj "e-tube"
    with  name 'tube' 'tubes' 'e-tube' 'e-tubes' 'room',
          description [;
              <<Look ma_etube>>;
          ];

! 05/13/08

  Object  -> ma_etcvr "engineering access cover"
    with  name 'engineering' 'access' 'cover' '1351ph' 'airlock' 'panel',
          describe [;
              rtrue;
          ],
          before [;
              Attack, Cut, Kick:
                  return PDE();
              Close:
                  if (ma_eacover.panopn) {
                      ma_eacover.panopn = false;
                      self.&name-->3 = '1351ph';
                      ma_eacover.&name-->7 = '1351ph';
                      "You close the access cover.";
                  }
                  "That's already closed.";
              Examine, Search:
                  print "The engineering access cover is ";
                  if (ma_eacover.panopn) "open, giving you access to the airlock.";
                  "closed.";
              Open, Remove, Turn, PushDir, Push, Pull:
                  if (ma_eacover.panopn) "That's already open.";
                  ma_eacover.panopn = true;
                  self.&name-->3 = 'opening';
                  ma_eacover.&name-->7 = 'opening';
                  "You open the access cover, giving you access to the airlock.";
              Take:
                  "It would only slow you down.";
              Enter:
                  <<Exit ma_etube>>;
          ],
    has   static;
