
! 09/08/06

  Movable cry_stand "patina-covered stand"
    with  name 'patina-covered' 'patina' 'covered' 'worn' 'hazy-green' 'hazy' 'green' 'stand' 'hook' 'three-pronged' 'pronged',
          description [;
              if (self in tc_shrine && tc_shrine.fieldon) return PSL();
              PHt();
              print "he three-pronged, worn, hazy-green, stand";
              if ((player in air_lock || player in sm_airlock) && e_beacon.eb_notseen) ", resembling a hook.";
              print " resembles a hook";
              if (trans_crystal in self) {
                  print "; while placed in the center sits a beautiful red crystal";
                  if (self in ncell_table or scell_table or ecell_table or wcell_table) ", becoming a focal point for the priestess to meditate upon.";
              }
              ".";
          ],
          invent [;
              if (trans_crystal in self) {
                  print "a patina-covered stand (containing a clear-red crystal)";
                  return true;
              }
          ],
          after [;
              PutOn:
                  if (second == pedestal) return PedestalEnds(39);
          ],
          before [;
              Remove:
                  <<Take self>>;
              Take:
                  if (self in tc_shrine && tc_shrine.fieldon) return PBS();
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  if (self in us_altar) {
                      if (USAltarTest()) {
                          return TakenIdol();
                      }
                  }
              Touch:
                  "The stand feels cold to the touch.";
              Use:
                  if (self in player) {
                      if (second == rope) return MkGrp();
                      "Using the patina-covered stand by itself won't be much help.";
                  }
                  return PYC();
              UseItem:
                  if (self in player) return PYN();
                  return PYC();
          ],
          havecrystal false,
     has  container open;
