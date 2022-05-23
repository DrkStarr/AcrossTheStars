
! ---------------------------------------------------------------------------- !
!       The NORTHERN CELL. 09/25/06
!
  Cell    north_cell "Northern Cell"
    with  description [;
              CellDescript();
              if (skeley_1 in ncell_straw || skeley_2 in ncell_straw || skeley_3 in ncell_straw) PSkl();
              else PCli();
              PCell();
              if (stonecount == 1) return PTree();
              if (rubycount == 1) return PFire();
              if (pearlcount == 1) return PSky();
              return PCube();
          ],
          s_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go south.",
          before [;
              SitDown:
                  <<Sit ncell_straw>>;
            ],
            skelscore true;

! 09/25/06

  RoomObj -> nc_obj "northern cell"
    with  name 'northern' 'cell' 'room',
          description [;
              <<Look north_cell>>;
          ];

! 09/25/06

  TblObj  -> ncell_table "~table~";

! 09/25/06

  Object  -> ncell_straw "~bed~"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'straw' or 'bed' or 'matting' or '~bed~' or 'bedding') return 0;
              if (w1 == 'straw' or 'matting') {
                  self.nstraw = true;
                  return 1;
              }
              self.nstraw = false;
              return 1;
          ],
          description [;
              if (self.nstraw) return PStraw();
              PBed();
          ],
          before [;
              Attack, Kick, Touch, Take, Remove, Turn:
                  return PSS();
              Enter:
                  return PEBed();
              PushDir, Push, Pull:
                  return PPuStr();
              Sit:
                  return PSitBd();
          ],
          nstraw false,
    has   supporter static scenery;

! 09/25/06

  Pict    -> ncell_picture "picture"
    with  name 'picture' '01fill' '02fill' '3999ph' 'painting',
            description [;
                PPict();
                if (stonecount == 1) return PaTree();
                if (rubycount == 1) return PaFire();
                if (pearlcount == 1) return PaSky();
                return PaCube();
            ];

! 09/25/06

  Object  cell_bowl "stone bowl"
    with  name 'stone' 'bowl' 'empty',
          description
              "The stone bowl is empty, lined with dead insects, while an unlit candle stands next to it.",
          before [;
              Attack, Kick, Touch, Empty:
                  return PSS();
              Drink:
                  "There's nothing to drink.";
              Search:
                  "There are only dead insects inside the bowl.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PBP();
          ],
          found_in north_cell south_cell east_cell west_cell
    has   edible static open concealed;

! 09/25/06

  Object  cell_candle "candle"
    with  name 'unlit' 'candle',
          description
              "The unlit candle stands next to the stone bowl.",
          before [;
              Attack, Kick, Touch:
                  return PSS();
               Burn, Take, Remove, Turn, PushDir, Push, Pull:
                  return PBP();
          ],
          found_in north_cell south_cell east_cell west_cell
    has   static concealed;

! 09/26/06

  Object  cell_insect "dead insects"
    with  name 'dead' 'insect' 'insects',
          description [;
              "The dead insects line the edges of the stone bowl.";
          ],
          before [;
              Attack, Kick, Touch, Take, Remove, Turn, PushDir, Push, Pull:
                  return PSS();
              Eat, Taste:
                  return PDL();
          ],
          found_in north_cell south_cell east_cell west_cell
    has   edible concealed static pluralname;

! ---------------------------------------------------------------------------- !
!       The SOUTHERN CELL. 09/25/06
!
  Cell    south_cell "Southern Cell"
    with  description [;
              CellDescript();
              if (skeley_1 in scell_straw || skeley_2 in scell_straw || skeley_3 in scell_straw) PSkl();
              else PCli();
              PCell();
              if (stonecount == 2) return PTree();
              if (rubycount == 2) return PFire();
              if (pearlcount == 2) return PSky();
              return PCube();
          ],
          n_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go north.",
          before [;
              SitDown:
                  <<Sit scell_straw>>;
          ];

! 09/25/06

  RoomObj -> sc_obj "southern cell"
    with  name 'southern' 'cell' 'room',
          description [;
              <<Look south_cell>>;
          ];

! 09/25/06

  TblObj  -> scell_table "~table~";

! 09/25/06

  Object  -> scell_straw "~bed~"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'straw' or 'bed' or 'matting' or '~bed~' or 'bedding') return 0;
              if (w1 == 'straw' or 'matting') {
                  self.sstraw = true;
                  return 1;
              }
              self.sstraw = false;
              return 1;
          ],
          description [;
              if (self.sstraw) return PStraw();
              PBed();
          ],
          before [;
              Attack, Kick, Touch, Take, Remove, Turn:
                  return PSS();
              Enter:
                  return PEBed();
              PushDir, Push, Pull:
                  return PPuStr();
              Sit:
                  return PSitBd();
          ],
          sstraw false,
    has   supporter static scenery;

! 09/25/06

  Pict    -> scell_picture "picture"
    with  name 'picture' '01fill' '02fill' '3999ph' 'painting',
          description [;
              PPict();
              if (stonecount == 2) return PaTree();
              if (rubycount == 2) return PaFire();
              if (pearlcount == 2) return PaSky();
              return PaCube();
          ];

! ---------------------------------------------------------------------------- !
!       The EASTERN CELL. 09/25/06
!
  Cell    east_cell "Eastern Cell"
    with  description [;
              CellDescript();
              if (skeley_1 in ecell_straw || skeley_2 in ecell_straw || skeley_3 in ecell_straw) PSkl();
              else PCli();
              PCell();
              if (stonecount == 3) return PTree();
              if (rubycount == 3) return PFire();
              if (pearlcount == 3) return PSky();
              return PCube();
          ],
          w_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go west.",
          before [;
              SitDown:
                  <<Sit ecell_straw>>;
          ];

! 09/25/06

  RoomObj -> ec_obj "eastern cell"
    with  name 'eastern' 'cell' 'room',
          description [;
              <<Look east_cell>>;
          ];

! 09/25/06

  TblObj  -> ecell_table "~table~";

! 09/25/06

  Object  -> ecell_straw "~bed~"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'straw' or 'bed' or 'matting' or '~bed~' or 'bedding') return 0;
              if (w1 == 'straw' or 'matting') {
                  self.estraw = true;
                  return 1;
              }
              self.estraw = false;
              return 1;
          ],
          description [;
              if (self.estraw) return PStraw();
              PBed();
          ],
          before [;
              Attack, Kick, Touch, Take, Remove, Turn:
                  return PSS();
              Enter:
                  return PEBed();
              PushDir, Push, Pull:
                  return PPuStr();
              Sit:
                  return PSitBd();
          ],
          estraw false,
    has   supporter static scenery;

! 09/25/06

  Pict    -> ecell_picture "picture"
    with  name 'picture' '01fill' '02fill' '3999ph' 'painting',
          description [;
              PPict();
              if (stonecount == 3) return PaTree();
              if (rubycount == 3) return PaFire();
              if (pearlcount == 3) return PaSky();
              return PaCube();
          ];

! ---------------------------------------------------------------------------- !
!       The WESTERN CELL. 09/25/06
!
  Cell    west_cell "Western Cell"
    with  description [;
              CellDescript();
              if (skeley_1 in wcell_straw || skeley_2 in wcell_straw || skeley_3 in wcell_straw) PSkl();
              else PCli();
              PCell();
              if (stonecount == 4) return PTree();
              if (rubycount == 4) return PFire();
              if (pearlcount == 4) return PSky();
              return PCube();
          ],
          e_to [;
              <<Exit self>>;
          ],
          cant_go
              "You can only go east.",
          before [;
              SitDown:
                  <<Sit wcell_straw>>;
          ];

! 09/25/06

  RoomObj -> wc_obj "western cell"
    with  name 'western' 'cell' 'room',
              description [;
              <<Look east_cell>>;
          ];

! 09/25/06

  TblObj  -> wcell_table "~table~";

! 09/25/06

  Object  -> wcell_straw "~bed~"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'straw' or 'bed' or 'matting' or '~bed~' or 'bedding') return 0;
              if (w1 == 'straw' or 'matting') {
                  self.wstraw = true;
                  return 1;
              }
              self.wstraw = false;
              return 1;
          ],
          description [;
              if (self.wstraw) return PStraw();
              PBed();
          ],
          before [;
              Attack, Kick, Touch, Take, Remove, Turn:
                  return PSS();
              Enter:
                  return PEBed();
              PushDir, Push, Pull:
                  return PPuStr();
              Sit:
                  return PSitBd();
          ],
          wstraw false,
    has   supporter static scenery;

! 09/25/06

  Pict    -> wcell_picture "picture"
    with  name 'picture' '01fill' '02fill' '3999ph' 'painting',
          description [;
              PPict();
              if (stonecount == 4) return PaTree();
              if (rubycount == 4) return PaFire();
              if (pearlcount == 4) return PaSky();
              return PaCube();
          ];
