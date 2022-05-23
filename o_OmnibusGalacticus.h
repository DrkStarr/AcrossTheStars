
! 09/18/06

  Movable og_datacard "Omnibus Galacticus datacard"
    with  parse_name [w1 w2 w3;
                w1 = NextWord();
                if (w1 ~= 'omnibus' or 'galacticus' or 'datacard' or 'data' or 'card' or 'encyclopedia' or 'database' or 'index') return 0;
                if (w1 ~= 'omnibus' or 'galacticus' or 'encyclopedia' or 'database' or 'index') {
                    if (datacard in player) return 0;
                    if (player in radar_room) return 0;
                }
                w2 = NextWord();
                w3 = NextWord();
                if (w2 == 'galacticus' && w3 == 'datacard' or 'data' or 'card') return 3;
                if (w2 == 'galacticus' or 'datacard' or 'data' or 'card') return 2;
                return 1;
            ],
            description [;
                if (self in tc_shrine && tc_shrine.fieldon) return PSL();
                if (self notin omni_trans) "When inserted into the OmniTrans, the Omnibus Galacticus contains a wealth of information.";
                PHt();
                "he Omnibus Galacticus datacard is inserted into the OmniTrans, unleashing a wealth of information.
                You can read about all sorts of other interesting people, places, and things by looking them up in
                this database.";
            ],
            after [;
                Insert:
                    if (second == omni_trans) {
                        move self to omni_trans;
                        "Sluggishly, the card slides into the slot.";
                    }
                    if (second == controlpanel or al_circuit) {
                        move self to player;
                        return PDP();
                    }
                PutOn:
                    if (second == pedestal) return PedestalEnds(16);
            ],
            before [;
                Attack:
                    if (self in tc_shrine) return PYC();
                    return PDE();
                Consult:
                    if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) {
                        PFT();
                        return PBS();
                    }
                    if (self notin omni_trans) "The datacard needs to be inserted into the OmniTrans to do that.";
                    <<Consult omni_trans>>;
                Drop, PutOn:
                    if (player in outside_airlock or ontopofship) return PLD();
                    if (second == sa_bobelisk or us_altar) "No good crewman would ever leave part of their OmniTrans behind.";
                Read:
                    if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) {
                        PFT();
                        return PBS();
                    }
                    "It would take a lifetime to read the entire Omnibus Galacticus. It would be
                    better to LOOK UP <subject> in OMNITRANS to bring up all relevant information
                    stored on the inserted datacards.";
                Remove:
                    <<Take self>>;
                Scan:
                    if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) {
                         PFT();
                         return PBS();
                    }
                    "It would be better to LOOK UP <subject> in OMNITRANS to bring up all relevant
                    information stored on the inserted datacards.";
                Take:
                    if ((self in tc_shrine || parent(self) in tc_shrine) && tc_shrine.fieldon) return PBS();
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
                ThrowAt:
                    if (self in player) {
                        if (second == deadp_obj) {
                            move self to unholy_shrine;
                            "You throw ", (the) self, " into the pit.";
                        }
                    }
            ];
