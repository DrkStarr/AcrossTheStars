
! 04/21/06

  Object  omni_trans
    with  parse_name [w1 w2;
              w1 = NextWord();
              if (w1 ~= 'omnitrans' or 'omni' or 'trans' or 'translator' or 'slot' or 'slots' or 'display' or 'shoulder' or 'strap') return 0;
              w2 = NextWord();
              if (w1 == 'omni' or 'shoulder' && w2 == 'trans' or 'translator' or 'strap') return 2;
              return 1;
          ],
          short_name "OmniTrans",
          description [;
	          if (self in tc_shrine && tc_shrine.fieldon) return PSL();
	          PHt();
	          print "he one gadget no Xulthe'en crewman would ever be without, the OmniTrans
	          doubles as a translator and portable database, all in a slab a little
	          bigger than your hand with a handy shoulder strap. It has two slots for datacards; at the moment, ";
              if (og_datacard in self && zipchip in self) {
                  print "the first is occupied by the Omnibus Galacticus, while the second by the zipchip.";
              } else {
                  if (og_datacard in self && ident_badge in self) {
                      print "the first is occupied by the Omnibus Galacticus, while the second by the Captain's ident badge.";
                  } else {
                      if (og_datacard in self) {
                          print "the first is occupied by the Omnibus Galacticus, while the second is empty.";
                      } else {
                          if (zipchip in self) {
                              print "the first is empty, while the zipchip occupies the second.";
                          } else {
                              if (ident_badge in self) {
                                  print "the first is empty, while the second is occupied by the Captain's ident badge.";
                              } else {
                                  print "both slots are empty.";
                              }
                          }
                      }
                  }
              }
	          print "^^The OmniTrans will translate anything written in any known form of language;
	          simply SCAN the writing (or the object it is written on) and a translation will
	          appear on the display.";
	          if (og_datacard in self) " Alternatively, you can read about all sorts of other interesting people,
	          places, and things by looking them up in the Omnibus Galacticus.";
	          new_line;
          ],
          describe [;
              if (uniform notin player) rtrue;
              if (self.transtaken) "^Your OmniTrans is on the edge of your berth.";
          ],
          invent [;
              if (self in player) rfalse;
              print "an OmniTrans";
              rtrue;
          ],
          after [;
              Attack:
                  return PDE();
              Drop:
                  move self to player;
                  "No good crewman would ever leave their OmniTrans behind.";
              Insert:
                  if (second == milpack) {
                      give milpack open;
                      move self to milpack;
                      "You put ", (the) self, " into the field pack.";
                  }
                  move self to player;
                  "No good crewman would ever leave their OmniTrans behind.";
              PutOn:
                  move self to player;
                  "No good crewman would ever leave their OmniTrans behind.";
          ],
          before [ w1 w2 w3;
              Consult:
                  if (self notin player) "You need to be holding the OmniTrans to look something up, how else can you read the display?";
                  if (og_datacard notin self) "You need the Omnibus Galacticus datacard inserted into the OmniTrans to be able to perform this function.";
                  wn = consult_from;
                  w1 = NextWord();
                  w2 = NextWord();
                  w3 = NextWord();
                  if (w1 == 'data') {
                      if (w2 == 'mining' or 'center' or 'gathering' or 'operations') return PDMC();
                  }
                  if (w1 == 'imperial') {
                      if ((w2 == 'high' && w3 == 'court') || (w2 == 'court')) return PICourt();
                      if ((w2 == 'galactic' && w3 == 'consul') || (w2 == 'consul')) return PIConsul();
                      if ((w2 == 'high' && w3 == 'senate') || (w2 == 'senate')) return PISenate();
                  }
                  if (w1 == 'stokar' or 'the' or 'infamous' or 'famous' && w2 == 'the' or 'pirate' && w3 == 'pirate' or 'stokar') return PStkrP();
                  if (w1 == 'infamous' or 'pirate' or 'the' or 'infamous-pirate' or 'famous' && w2 == 'stokar' or 'pirate') return PStkrP();
                  if (w1 == 'high') {
                      switch (w2) {
                          'court':
                              return PICourt();
                          'senate':
                              return PISenate();
                      }
                  }
                  if (w1 == 'xultheen' or 'xulthe^en' or 'xultheens' or 'xulthe^en^s') {
                      switch (w2) {
                          'armada', 'navy', 'navel':
                              return PXArmada(0);
                          'empire':
                              return PXEmpire();
                          'emperor':
                              return PXEmperor();
                          'military', 'army':
                              return PXMilitary();
                      }
                  }
                  if (w1 == 'rigel' && w2 == 'run') {
                      print "You look up the ";
                      style underline;
                      print "Rigel Run";
                      style roman;
                      print " in the Omnibus Galacticus, and find an interesting section. It says the ";
                      style underline;
                      print "Rigel Run";
                      style roman;
                      print " is a smuggler's route between ";
                      style underline;
                      print "Rigel";
                      style roman;
                      print " & ";
                      style underline;
                      print "Stokar";
                      style roman;
                      print ". Even though it's one of the few location within the ";
                      style underline;
                      print "inner core";
                      style roman;
                      print " that is not patrolled by the ";
                      style underline;
                      print "Empire";
                      style roman;
                      print ", ";
                      style underline;
                      print "pirates";
                      style roman;
                      " do not attack within this self governed area.";
                  }
                  if (w1 == 'space' && w2 == 'pirate' or 'pirates') return PSPirates();
                  switch (w1) {
                      '393', '393-z6', 'z6':
                          return PZ6();
                      'across', 'game':
                          print "You look up ";
                          style underline;
                          print "Across The Stars";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small
                          section about the game. It says that the game contains a total of ", GTOTALROOMS,
                          " rooms, with ", GTOTALOBJS, " objects, words: 1,", GTWORDS, ". OpCode length:
                          ", GPLOPCODE, ",", GOPCPH, GOPCSPH, GOPCODE, ".^^";
                          return GameCredits();
                      'andraxceon', 'andraxceons':
                          print "You look up ";
                          style underline;
                          print "Andraxceon";
                          style roman;
                          print " within the Omnibus Galacticus, and find a small note. It says that the ";
                          style underline;
                          print "Zrok Corporation";
                          style roman;
                          " hasn't been able to collect any information
                            about this race. All the correspondents keep dying on their home world, making it
                          impossible to report back about them. Interestingly enough, it also states that
                          if you have information about this race to contact the Corporation.";
                      'armada', 'navy', 'navel':
                          return PXArmada(0);
                      'atomaton', 'detonator', 'bomb':
                          print "You look up ";
                          style underline;
                          print "atomaton detonator";
                          style roman;
                          " in the Omnibus Galacticus, and find an small section.
                          It says that this type of bomb is great for concussion explosions, causing a tremendous
                          amount of damage in a small area. The effects of the concussion is wide though, and
                          if used in the wrong type of area, can even cause an avalanche.";
                      'atris':
                          print "You look up the ";
                          style underline;
                          print "Atris System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It states
                          that this star system sits on the ";
                          style underline;
                          print "frontier";
                          style roman;
                          print " of the ";
                          style underline;
                          print "Xuthe'en Empire";
                          style roman;
                          print ". Though isolated, it is still considered a part of the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print ". An agricultural settlement, its main export is ";
                          style underline;
                          print "trillium";
                          style roman;
                          ".";
                      'automatic', 'web', 'netting':
                          print "You look up ";
                          style underline;
                          print "automatic web netting";
                          style roman;
                          " in the Omnibus Galacticus, and find an small section. It says that the netting is
                          used for deep-space transport, to keep the cargo contained during flight, and that
                          you should never open it while in deep space.";
                      'berth', 'rack', 'crew', 'quarters':
                          print "You look up ";
                          style underline;
                          print "crew quarters";
                          style roman;
                          " in the Omnibus Galacticus, and find a small section. It goes on to say that they're smelly,
                          nasty, places, and to try to stay out of them if at all possible.";
                      'boreium':
                          print "You look up ";
                          style underline;
                          print "boreium";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that boreium is a rare component
                          used in some ";
                          style underline;
                          print "meal synthesizers";
                          style roman;
                          " to create exotic alien cuisines.";
                      'brakis':
                          print "You look up the ";
                          style underline;
                          print "Brakis System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that Brakis is a dead star system
                          located within the ";
                          style underline;
                          print "Rigel Run";
                          style roman;
                          ".";
                      'centria':
                          print "You look up ";
                          style underline;
                          print "Centria";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that Centria is the Capital City of ";
                          style underline;
                          print "Xul";
                          style roman;
                          print " spanning twenty-thousand ";
                          style underline;
                          print "millaunits";
                          style roman;
                          " across two continents and one ocean.";
                      'cubit':
                          print "You look up ";
                          style underline;
                          print "cubit";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that a cubit is a small coin used
                          as currency by the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          print ", and represents a quarter of a ";
                          style underline;
                          print "credit";
                          style roman;
                          ".";
                      'dmc':
                                return PDMC();
                      'main', 'computer', 'computers':
                          print "You look up ";
                          style underline;
                          print "onboard computers";
                          style roman;
                          print " in the Omnibus Galacticus, and only find a small note. It says that all ships use onboard
                          computers, powered by the ";
                          style underline;
                          print "engines";
                          style roman;
                          " like all things aboard any starship.";
                      'court':
                          return PICourt();
                      'credit', 'credits':
                          print "You look up ";
                          style underline;
                          print "credit";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says that credits are the base
                          form of currency for all societies, whose treasuries are based out of ";
                          style underline;
                          print "Rigel";
                          style roman;
                          print ". For the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          ", credits are store digitally and can be accessed through any banking terminal.";
                      'darington', 'me', 'self':
                          print "You look up ";
                          style underline;
                          print "Darington";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says that Darington is one of many
                          surnames that came about after the ";
                          style underline;
                          print "Third Vlaxion Conflict";
                          style roman;
                          " in which a number of self sacrificing hero's crippled their homeworld, ending the wars.
                          These men passed into legend, as stories got bolder, along with their names.";
                      'datacard', 'datacards', 'data', 'card', 'cards':
                          return PChip(0);
                      'deca', 'decaunit', 'decaunits':
                          print "You look up ";
                          style underline;
                          print "decaunit";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that the decaunit is made up of one hundred ";
                          style underline;
                          print "units";
                          style roman;
                          ".";
                      'dialis', 'dialianium', 'crystal', 'calcium':
                          print "You look up ";
                          style underline;
                          print "dialianium";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that dialis crystals are very
                          common, once ground into a fine dust they create dialianium, which is the basic calcium
                          constitute used in most ";
                          style underline;
                          print "meal synthesizers";
                          style roman;
                          ".";
                      'durainium':
                          print "You look up ";
                          style underline;
                          print "durainium";
                          style roman;
                          " in the Omnibus Galacticus, and find a small note. It says
                          that durainium is a hardened steel that is used in most starship construction.";
                      'eds':
                          print "You look up ";
                          style underline;
                          print "EDS";
                          style roman;
                          " in the Omnibus Galacticus, and find a small note. It says that most ships come with
                          some sort of Equipment Destruction Sequence in order to deter piracy.";
                      'emperor', 'lucius', 'winterson':
                          return PXEmperor();
                      'empire':
                          return PXEmpire();
                      'engine', 'engines', 'acardiolytic':
                          print "You look up ";
                          style underline;
                          print "acardiolytic engine";
                          style roman;
                          " in the Omnibus Galacticus, and find an
                          interesting section. Acardiolytic engines are a refinement of an earlier,
                          or ~cardiolytic~, design. Cardiolytic engines -- the name is a fusion of
                          ~cardio~, meaning ~heart~, and ~lysis~, meaning ~dissolution~ -- used a
                          pumping action to maintain fuel flow and hence the upquark-downquark
                          fission reaction that generated the power. The newer acardolytic models,
                          by contrast, dispense with the pumping action in favor of strong-force
                          confinement, thereby eliminating many of the moving parts.";
                      'enrys':
                          print "You look up the ";
                          style underline;
                          print "Enrys System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a interesting note.
                          It says that Enrys is located near ";
                          style underline;
                          print "Rigel";
                          style roman;
                          print " and is in a state of civil war. Even though the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          " denies working with the rebels, it's believed they are re-supplying
                          them, trying to overthrow the local regime.";
                      'flebeon', 'flebeons':
                          print "You look up ";
                          style underline;
                          print "Flebeons";
                          style roman;
                          " within the Omnibus Galacticus, and find a small entry. It says
                          that they're high strung, nervous, creatures that have some strange sexual
                          pleasures. They enjoy letting figgil worms burrow into their skin.";
                      'frontier':
                          print "You look up the ";
                          style underline;
                          print "frontier";
                          style roman;
                          print " in the Omnibus Galacticus, and find a rather large section. It says that the
                          frontier is the uncharted space beyond the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print " and the ";
                          style underline;
                          print "outer rim";
                          style roman;
                          print ". Home to other ";
                          style underline;
                          print "species";
                          style roman;
                          print ", the area is not patrolled by the ";
                          style underline;
                          print "Empire";
                          style roman;
                          " and is hazardous to travel through. It also states that amongst this chaos, small
                          outposts have managed to survive.";
                      'gajrogan', 'ga^jrogan', 'gajrogans', 'ga^jrogans', 'ga', 'jrogan':
                          print "You look up ";
                          style underline;
                          print "Ga'Jrogans";
                          style roman;
                          " within the Omnibus Galacticus, and find a rather interesting section. It says that
                          they're an aristocratic society that thinks they're better than any other race. They
                          can be rude and think it beneath themselves to talk to anybody other than a Ga'Jrogan.";
                      'galaxy', 'milkyway', 'milky', 'universe', 'space':
                          print "You look up the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          " in the Omnibus Galacticus, and find a small entry. It says that with all the
                          advancements in technology and physics, it's still impossible to leave the Milky Way.";
                      'galactic', 'consul':
                          return PIConsul();
                      'grand', 'commander':
                          return PXArmada(1);
                      'hitchhiker', 'hitchhikers', 'hitchhiker^s', 'guide', 'don^t', 'dont', 'panic':
                          print "You look up ";
                          style underline;
                          print "The Hitchhiker's Guide To The Galaxy";
                          style roman;
                          print " in the Omnibus Galacticus, and find a interesting entry. It says that, this is a classic
                          work of science fiction created over twenty five thousand years ago, that still sees a
                          fair amount of download off the ";
                          style underline;
                          print "Sat-Net";
                          style roman;
                          ".";
                      'imp', 'imps', 'imp^s', 'implementer', 'implementor', 'darkstar':
                          print "You look up the ";
                          style underline;
                          print "Implementor";
                          style roman;
                          " in the Omnibus Galacticus, and find a small note from Dark Star. It says that while
                          writing a game like this can be daunting, it was an honor for him to be able to work on it.";
                      'infamous-pirate':
                          return PStkrP();
                      'infocom':
                          print "You look up ";
                          style underline;
                          print "Infocom";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section about a company that no
                          longer exists. It states that, though they no longer exist, their influence can still be felt on ";
                          style underline;
                          print "Xulthe'en";
                          style roman;
                          print " culture. The creators of the original ~text-adventure~ game, they started a craze of
                          independent writers that produce their own adventures for anyone to download off the ";
                          style underline;
                          print "Sat-Net";
                          style roman;
                          ".";
                      'inner', 'core':
                          print "You look up the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says that the inner core is a
                          collection of star systems that span one hundred and twenty light years, from ";
                          style underline;
                          print "Atris";
                          style roman;
                          print " to ";
                          style underline;
                          print "Lylth";
                          style roman;
                          print ", making up the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          ".";
                      'known', 'race', 'races', 'specie', 'species':
                          print "You look up ";
                          style underline;
                          print "species";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section. There are six known species within the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print ": ";
                          style underline;
                          print "Andraxceons";
                          style roman;
                          print ", ";
                          style underline;
                          print "Flebeons";
                          style roman;
                          print ", ";
                          style underline;
                          print "Ga'jrogans";
                          style roman;
                          print ", ";
                          style underline;
                          print "Vlaxions";
                          style roman;
                          print ", ";
                          style underline;
                          print "Xulthe'ens";
                          style roman;
                          print ", and ";
                          style underline;
                          print "Zoliens";
                          style roman;
                          ".";
                      'lylth':
                          print "You look up the ";
                          style underline;
                          print "Lylth System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It states
                          that this star system sits on the ";
                          style underline;
                          print "frontier";
                          style roman;
                          print " of the ";
                          style underline;
                          print "Xuthe'en Empire";
                          style roman;
                          print ". Though isolated, it is still considered a part of the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print ". A mining settlement, its main export is ";
                          style underline;
                          print "durainium";
                          style roman;
                          ".";
                      'meal', 'synthesizer', 'synthesizers', 'food', 'replicator', 'replicators':
                          print "You look up ";
                          style underline;
                          print "meal synthesizers";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section. It says that most meal
                          synthesizers use a total of three components to create their food. ";
                          style underline;
                          print "Veareium";
                          style roman;
                          print " for protein, ";
                          style underline;
                          print "dialianium";
                          style roman;
                          print " for calcium, and ";
                          style underline;
                          print "trillium";
                          style roman;
                          print " for fiber. On some of the higher end models there's even a fourth component, ";
                          style underline;
                          print "boreium";
                          style roman;
                          print ", used to make exotic alien cuisines. It also states that military models use only one component, ";
                          style underline;
                          print "trillium";
                          style roman;
                          print ", creating a substandard food, but saves cost and storage for the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          ".";
                      'military', 'army':
                          return PXMilitary();
                      'milla', 'millaunit', 'millaunits':
                          print "You look up ";
                          style underline;
                          print "millaunit";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that the millaunit is made up of ten ";
                          style underline;
                          print "decaunits";
                          style roman;
                          ".";
                      'omnibus', 'galacticus':
                          print "You look up the ";
                          style underline;
                          print "Omnibus Galacticus";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section about the datacard you're
                          using. It says that it's the latest design from the ";
                          style underline;
                          print "Zrok Corporation";
                          style roman;
                          ", with built in features like linked indexing and auto focusing (for people with bad eyes).";
                      'omnitrans':
                          print "You look up the ";
                          style underline;
                          print "OmniTrans";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting note. It says that this is another
                          product produced by the ";
                          style underline;
                          print "Zrok Corporation";
                          style roman;
                          ", which can access and verify datacards, along with translating text against an internal database.";
                      'outer', 'rim':
                          print "You look up the ";
                          style underline;
                          print "outer rim";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says that the outer rim is a
                          sort of no man's land between the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print " and the ";
                          style underline;
                          print "frontier";
                          style roman;
                          print ". It is not patrolled by the ";
                          style underline;
                          print "Empire";
                          style roman;
                          print " and is believed to be the home of many ";
                          style underline;
                          print "pirates";
                          style roman;
                          ".";
                      'pirate', 'pirates':
                          return PSPirates();
                      'planet', 'planets':
                          print "You try to look up ";
                          style underline;
                          print "planet";
                          style roman;
                          print " in the Omnibus Galacticus, but all it says is that there are many planets within the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          ", and that you'll have to look them up by the individual system name.";
                      'proxtar', 'prox-tar', 'prox', 'tar', 'teletype', 'machine', 'proximity', 'detector', 'detectors':
                          print "You look up the ";
                          style underline;
                          print "prox-tar";
                          style roman;
                          print " in the Omnibus Galacticus, and find a notation about the unit. It says that proximity
                          detectors are older devices outputting their reports to ";
                          style underline;
                          print "datacards";
                          style roman;
                          ", securing the information for the ship's Captain.";
                      'ralckor', 'ralckors':
                          print "You look up ";
                          style underline;
                          print "Ralckor";
                          style roman;
                          print " within the Omnibus Galacticus, and find a large section about the beast.
                          It states that Ralckors lay their eggs in rock, creating nests in asteroids, small
                          moons or large planetary bodies. If they bear their young on planet they can stay
                          there for many generations until returning to space to further conquer the galaxy.
                          Extremely dangerous, this burrowing creature has no form of apparent society. Their
                          feeding habits vary from large mammals to rich mineral veins. Also, there have been
                          reports the creature will suppress certain senses, like sight, with some sort of
                          mind-inducing spell. Watch out, this trance can become very surreal. Becoming harder
                          to wake out of, the longer you're underneath it. It goes on to say that the natural
                          enemy of these creatures are ";
                          style underline;
                          print "widow-weave spitters";
                          style roman;
                          " who will viciously fight to protect their hatchling's nursing area.";
                      'rigel':
                          print "You look up the ";
                          style underline;
                          print "Rigel System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a large section. It says that Rigel is the
                          financial center of the galaxy. Handling everything from interstellar banking to the
                          creation of ";
                          style underline;
                          print "credits";
                          style roman;
                          print ", this planet is home to most financial institutions including the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          ". Also, less scrupulous clients have no problem conducting business.";
                      'robo', 'robot', 'robots', 'robo-wash', 'bot', 'bots', 'house-bot':
                          print "You look up ";
                          style underline;
                          print "robots";
                          style roman;
                          " in the Omnibus Galacticus, and find an interesting section. It says that many robots
                          are used throughout the galaxy, from robotic pilots to astral-repair bots. There's even
                          a model for doing dishes, the robo-wash, and the house-bot can take care of home and
                          automotive repairs.";
                      'sat', 'net', 'satnet', 'sat-net', 'satellite', 'network':
                          print "You look up the ";
                          style underline;
                          print "Sat-Net";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section. It says that the Sat-Net
                          is the most popular way to share information across the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          ". Connecting all civilizations and races to one centralized computer hub.";
                      'segment', 'segments':
                          print "You look up ";
                          style underline;
                          print "segment";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says that a segment is the
                          smallest common-size that the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          print " uses for measurement, and that ten of them make up a ";
                          style underline;
                          print "unit";
                          style roman;
                          ".";
                      'senate':
                          return PISenate();
                      'ship', 'ships', 'ship^s':
                          if (self.ogz6) return PZ6();
                          return PTranstellar();
                      'small', 'magnetic', 'rechargeable', 'battery':
                          print "You look up ";
                          style underline;
                          print "small magnetic rechargeable battery";
                          style roman;
                          print " in the Omnibus Galacticus, and find a short section. It says that these are some of the
                          most popular batteries used in starship construction. Charged by the magnetic swipe of a ";
                          style underline;
                          print "datacard";
                          style roman;
                          print ", these batteries save power drain on the ";
                          style underline;
                          print "engines";
                          style roman;
                          ".";
                      'starcross', 'zork', 'stationfall', 'planetfall', 'sorcerer', 'leather', 'goddesses', 'phobos', 'lurking', 'horror':
                          print "You look up the ";
                          style underline;
                          print "game";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section about something that was
                          written over twenty five thousand years ago. It says that this ~text-adventure~ fell
                          into obscurity many millennia ago, but still seems to live on in the ";
                          style underline;
                          print "Sat-Net";
                          style roman;
                          " due to avid gamers that refuse to let the genre go.";
                      'stokar':
                          print "You look up the ";
                          style underline;
                          print "Stokar System";
                          style roman;
                          print " in the Omnibus Galacticus, and find an intriguing section.
                          It says that Stokar is a terra-formed system that sits on the edge of the ";
                          style underline;
                          print "outer rim";
                          style roman;
                          print ", controlled by smugglers and ";
                          style underline;
                          print "pirates";
                          style roman;
                          print ". Founded by the ";
                          style underline;
                          print "infamous-pirate Stokar";
                          style roman;
                          print ", this settlement is well within the ";
                          style underline;
                          print "inner core";
                          style roman;
                          print ", but the ";
                          style underline;
                          print "Empire";
                          style roman;
                          " no longer patrols the area letting the criminal element govern itself.";
                      'xss', 'supalace':
                          print "You look up the ";
                          style underline;
                          print "XSS Supalace";
                          style roman;
                          print " in the Omnibus Galacticus, and find an small note. It says that it's a ";
                          style underline;
                          print "trans-stellar transport";
                          style roman;
                          print " registered out of ";
                          style underline;
                          print "Tyrr";
                          style roman;
                          print " and licensed to the ";
                          style underline;
                          print "Xulthe'en Armada";
                          style roman;
                          ", support and supply division.";
                      'super-carrier', 'super', 'inferno':
                          print "You look up the ";
                          style underline;
                          print "super-carrier Inferno";
                          style roman;
                          print " in the Omnibus Galacticus, and find an small note. It says that this ship is used by the ";
                          style underline;
                          print "infamous-pirate Stokar";
                          style roman;
                          print ", to conduct his illegal activities of space piracy. For anybody that captures and
                          turns in this ship to the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          print ", there's a reward of ten million ";
                          style underline;
                          print "credits";
                          style roman;
                          ".";
                      't8', 'trans', 'stellar', 'trans-stellar', 'transstellar', 'transport':
                          return PTranstellar();
                      'transport', 'transporter', 'transporters', 'beam', 'beams':
                          print "You look up ";
                          style underline;
                          print "transport beam";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that transport beams
                          are hazardous and should not be used. When the beam reconstitutes on the other side,
                          any object placed within the beam will become a part of the transported object. i.e. If a ";
                          style underline;
                          print "pirate";
                          style roman;
                          " beams over, place your clipboard in the middle of the beam. When he fully materializes,
                          he'll be cut in half.";
                      'trillium', 'fiber':
                          print "You look up ";
                          style underline;
                          print "trillium";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that
                          trillium is the basic fiber constitute used in all ";
                          style underline;
                          print "meal synthesizers";
                          style roman;
                          ".";
                      'tyrr':
                          print "You look up the ";
                          style underline;
                          print "Tyrr System";
                          style roman;
                          print " in the Omnibus Galacticus, and find an intriguing section. It says that
                          Tyrr is the archival center for all the data that is collected across the 120
                          light years that make up the ";
                          style underline;
                          print "Empire";
                          style roman;
                          print ". It's also the primary server of the ";
                          style underline;
                          print "Sat-Net";
                          style roman;
                          ".";
                      'unit', 'units':
                          print "You look up ";
                          style underline;
                          print "unit";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small section. It says
                          that a unit is about the length from your elbow to your wrist, or ten ";
                          style underline;
                          print "segments";
                          style roman;
                          ".";
                      'veareium', 'protein':
                          print "You look up ";
                          style underline;
                          print "veareium";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that
                          veareium is the basic protein constitute used in most ";
                          style underline;
                          print "meal synthesizers";
                          style roman;
                          ".";
                      'vlaxion', 'vlaxions', 'third', 'conflict':
                          print "You look up ";
                          style underline;
                          print "Vlaxions";
                          style roman;
                          " in the Omnibus Galacticus, and find a lot of detailed
                          information about the race. But the most interesting section says that they are
                          best known for the three major galactic wars they started, each spanning over a
                          hundred years. It also states that they seem to have settled.";
                      'widow', 'weave', 'widow-weave', 'spitter', 'spitters':
                          print "You look up ";
                          style underline;
                          print "widow-weave spitter";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section. It says
                          spitters are large spider-like creatures that thrive within tropical climates.
                          Their relationship with their mates can be deadly, with the female taking the
                          life of the male after mating. Giving her substance to feed on while she tends
                          the eggs, only being eaten herself once they hatch. These creatures have a
                          terrible hatred of ";
                          style underline;
                          print "Ralckors";
                          style roman;
                          " who can fight for dominance of their nesting areas.";
                      'xul', 'sol', 'earth', 'old':
                          print "You look up the ";
                          style underline;
                          print "Xul System";
                          style roman;
                          print " in the Omnibus Galacticus, and find a small note. It says that Xul is the homeworld of the ";
                          style underline;
                          print "Xulthe'en";
                          style roman;
                          print " people and the ";
                          style underline;
                          print "Xulthe'en Empire";
                          style roman;
                          ". Founded on the Earth of old, it is also referred to as the old Earth, Sol, and Xul three.";
                      'xultheen', 'xulthe^en', 'xultheens', 'xulthe^en^s':
                          print "You look up the ";
                          style underline;
                          print "Xulthe'en";
                          style roman;
                          print " in the Omnibus Galacticus, and find a large section about
                          the name. The name is derived from ";
                          style underline;
                          print "Xul";
                          style roman;
                          print ", the name of the star in the primary Xulthe'en system. Strangely, the name was not
                          coined by the Xulthe'en, but instead by the ";
                          style underline;
                          print "Zal'tacs";
                          style roman;
                          print ", the first aliens to pass through the system. (In the ";
                          style underline;
                          print "Zal'tac";
                          style roman;
                          print " tongue, it translates as ~Children of Xul~.) It is conjectured that the Xulthe'en,
                          not having hitherto felt the need to give their species a name, accepted the ";
                          style underline;
                          print "Zal'tac";
                          style roman;
                          " term as a sign of friendship.";
                      'xyzzy':
                          print "You look up ";
                          style underline;
                          print "XYZZY";
                          style roman;
                          " in the Omnibus Galacticus and find an interesting section.
                          It states this organization is the leading promoter of interactive fiction, having
                          produced the natural language parser along with true vocal synthesis of textual
                          output. Their Sultry Servant was a real hit. They still hold annual awards with
                          some of the biggest names in literature attending yearly.";
                      'zal^tac', 'zal^tacs', 'zaltac', 'zaltacs':
                          print "You look up ";
                          style underline;
                          print "Zal'tacs";
                          style roman;
                          print " within the Omnibus Galacticus, and find an interesting note. An insectoid race -- that
                          had formed closer to the center of the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          print ", now driven by the black hole -- passed through the ";
                          style underline;
                          print "Xul System";
                          style roman;
                          print " twenty thousand years ago. Needing re-supplies, they traded technology for food
                          and resources before continuing at sub-light speed, exiting the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          ".";
                      'zipchip', 'zip', 'chip', 'chips':
                          return PChip(1);
                      'zrok', 'corporation':
                          print "You look up the ";
                          style underline;
                          print "Zrok Corporation";
                          style roman;
                          print " in the Omnibus Galacticus, and find an interesting section. It says that Z. Corp. is
                          the leader in advanced technology, and has been now for several years. They create
                          everything from simple data pads to advanced spacecraft, and even the ";
                          style underline;
                          print "OmniTrans";
                          style roman;
                          " itself is produced by the Zrok Corporation.";
                      'zolien', 'zoliens':
                          print "You look up ";
                          style underline;
                          print "Zoliens";
                          style roman;
                          print " within the Omnibus Galacticus, and find a short note. It says that they're a mean-tempered,
                          nasty, race that has just mastered space travel recently. Ever since, they've spread throughout the ";
                          style underline;
                          print "galaxy";
                          style roman;
                          " rather quickly.";
                      default:
                          "You try to look that up in the Omnibus Galacticus, but it doesn't look like
                          there's a data entry for that topic.";
                  }
              Drop:
                  if (player in outside_airlock or ontopofship) return PLD();
              Give:
                  if (self in player) {
                      if (second == adar) "~Thanks,~ smiles Captain Adar, ~but I'd rather collect the information on my own datacard.~";
                      "No good crewman would ever give away their OmniTrans.";
                  }
              Insert:
                  if (second == smallcrate or sm_scrate) "No good crewman would ever leave their OmniTrans behind.";
              PutOn:
                  if (player in outside_airlock or ontopofship) return PLD();
              Remove:
                  if (self has worn) {
                      give self ~worn;
                      "You take off the OmniTrans.";
                  }
                  <<Take self>>;
              FlipOff, SwFlip, SwitchOn, SwitchOff, Push, Read, UseItem:
                  if (self in player) {
                      print "The OmniTrans will translate anything written in any known form of language;
                      simply SCAN the writing (or the object it is written on) and a translation will
                      appear on the display.";
                      if (og_datacard in self) " Alternatively, you can read about all sorts of other interesting people,
                      places, and things by looking them up in the Omnibus Galacticus.";
                      new_line;
                  }
                  return PYC();
              Scan, ScanC1, ScanC2, ScanC3, ScanC4, ScanC5, ScanC6, ScanC7, ScanC8, ScanC9, ScanC10, ScanC11, ScanC12, ScanC13, ScanC14, ScanC15, ScanC16:
                  "The OmniTrans can't scan itself.";
              Take:
                  if (self in player) "You already have that.";
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  self.transtaken = false;
              ThrowAt:
                  if (self in player) return PFD();
              Use:
                  <<Scan second>>;
              Wear:
                  if (self has worn) "You're already wearing that!";
                  if (self notin player) {
                      move self to player;
                      PFT();
                  }
                  give self worn;
                  "You sling the OmniTrans over your shoulder.";
          ],
          ogz6 false,
          transtaken true,
    has   container open clothing;
