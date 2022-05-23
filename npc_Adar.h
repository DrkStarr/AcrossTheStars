
! ---------------------------------------------------------------------------- !
!       CAPTAIN ADAR
!

! 04/28/06

  Object  adar "Captain Adar"
    with  name 'captain' 'adar' 'man' 'male' 'him' 'broken' 'arm',
          description [;
              print "Captain Adar is a striking officer with penetrating sky-blue eyes, though ";
              if (m_base.ch_maidens) {
                  print "her shoulder length jet-black hair";
              } else {
                  print "his crew cut";
              }
              print " is matted and soiled. ";
              if (m_base.ch_maidens) {
                  print "Her full ";
              } else {
                  print "His buff ";
              }
              print "figure is tightly wrapped by ";
              if (m_base.ch_maidens) {
                  print "her";
              } else {
                  print "his";
              }
              print " uniform, made of a polymer that can't quite hide the dirt upon it. ";
              if (m_base.ch_maidens) {
                  print "She's";
              } else {
                  print "He's";
              }
              print " currently cradling a ";
              if (self.healed) {
                  print "bandaged";
              } else {
                  print "broken";
              }
              print " arm with ";
              if (m_base.ch_maidens) {
                  print "her";
              } else {
                  print "his";
              }
              print " other hand";
              if (self.grief) {
              if (m_base.ch_maidens) " and gently weeps.";
              ", head hung low.";
              }
              print " and fighting to retain ";
              if (m_base.ch_maidens) {
                  print "her";
              } else {
                  print "his";
              }
              " composure.";
          ],
          describe [;
              if (self.adaroff) {
                  self.adaroff = false;
                  rtrue;
              }
          ],
          before [;
              Attack, Kick, PushDir, Push, Pull, Search:
                  if (second == deadp_obj) return AdartoPit();
                  print "~Keep your hands to yourself,~ ";
                  if (m_base.ch_maidens) {
                      print "she says as she";
                  } else {
                      print "he says as he";
                  }
                  " pushes back.";
              AskChar, TellTo:
                  AdarGrief();
                  switch(second) {
                      t_torch:
                          "~If that's not working for you, maybe you need another light source,~ suggests the Captain.";
                  }
                  print_ret (The) self, " seems slightly confused by your request.";
                  Insert, ThrowAt, Transfer:
                      if (second == deadp_obj) return AdartoPit();
              Eat:
                  "Have some decency.";
              Fix:
                  "You're going to have to tell me how.";
              FlipOff:
                  "~Hmm,~ Captain Adar snorts, ~rude too.~";
              Follow:
                  print "But ";
                  PHeShe();
                  "'s following you.";
              Hello:
                  AdarGrief();
                      "~Good day,~ smiles Captain Adar.";
              Hug:
                  if (self.grief) {
                      self.gtalk = true;
                      self.grief = false;
                      self.setgrief = false;
                      print "~Thanks a lot, I will be able to pull it together,~ ";
                      if (m_base.ch_maidens) {
                          "she says,  wiping away the tears.";
                      } else {
                          "he says, standing up straight.";
                      }
                  }
                  if (self.gtalk) "~I said I will be ok,~ Captain Adar says sternly.";
                  self.gtalk = true;
                  "~I'll be ok,~ says Captain Adar with trying to squeak out a smile.";
              WrapRev:
                  if (second == firstaidwraps) {
                      remove firstaidwraps;
                      score = score + 5;
                      self.healed = true;
                      self.grief = false;
                      print "You bandage Captain Adar's broken arm using the first-aid wraps. ~Thanks a lot,~ ";
                      PHeShe();
                      " says as you finish setting the arm into place. ~I didn't know you knew first aid too.~";
                  }
          ],
          life [;
              Answer:
                  return AdarAnswer(noun);
              AnswerDir:
                  return AdarAnswer(second);
              Ask:
                  AdarGrief();
                  switch(second) {
                      t_adar:
                          print "~Well, you know what they say,~ Captain Adar states with ";
                          if (m_base.ch_maidens) {
                              print "a blushing smile";
                          } else {
                              print "confidence";
                          }
                          ", ~I know this star system better than most nav-computers.~";
                      t_airlock:
                          if (self.fsfirstime) {
                              if (crashed_ship.airlockopen || al_door.albroken) "~You did great venting that smoke, really above and beyond the call of duty,~ smiles Captain Adar, ~but don't worry about the hatch, get the beacon running, who knows how long it will take 'til a transport finds us?~";
                              if (crashed_ship.smoking) "~You need to open the cargo hatch, if you want to keep those engines running in order to turn on the beacon,~ says Captain Adar, ~I hope it doesn't prove to be a problem.~";
                              if (cwire notin controlpanel) "~That cargo hatch has caused me a lot of problems before in the past,~ says Captain Adar. ~It's never worked properly; the control panel shorted out the last time I used it. I think I've got it fixed now, but my engineering skills aren't the best, so be careful with it.~";
                              if (al_arm.fixed == false) {
                                  if (player in air_lock or sm_airlock) {
                                      if (bolt in al_arm or sm_arm) "~It's never worked properly. See that hydraulic piston up there? It looks like the bolt is loose,~ says Captain Adar. ~I'd tighten it up before you risk opening the hatch.~";
                                      "~It's never worked properly. See that hydraulic piston up there? It looks like the bolt is missing,~ says Captain Adar. ~Put it back in there before you risk opening the hatch.~";
                                  }
                                  "~If you are having problems with the cargo hatch, check out the hydraulic piston,~ says Captain Adar. ~The main bolt always comes loose and you might have to tighten it before opening the hatch with the control panel.~";
                              }
                              if (autocoolant notin al_gen or sm_alelectric) {
                                  al_door.deseng = true;
                                  "~I have been having problems with the auxiliary power unit overheating,~ says Captain Adar, ~you might need to put something on it to keep the auxiliary power unit at a cooler temperature.~";
                              }
                              "~Try opening it with the control panel,~ the Captain suggests.";
                          }
                          "~What hatch are you talking about,~ asks Captain Adar.";
                      t_arm:
                          if (player in desert_crash or crashed_ship or air_lock or sm_airlock) "~I don't think that it will impede your way any more,~ says Captain Adar, ~sorry about that.~";
                          if (player in chasm) {
                              print "~You know that I fell trying to climb up this chasm to the safety of that cavern,~ Captain Adar says as ";
                              PHeShe();
                              print " pauses for a moment. ";
                              if (chasm.blown) {
                                  "~Thank Za'zail you have taken care of that problem and I do not have to worry about
                                  breaking my neck anymore.~";
                              }
                              "~I can't climb it again, so you're going to have to find another way to cross it. Do
                              something extreme, start an avalanche, I don't care. But I'm not risking my life after
                              making it this far.~";
                          }
                          self.grief = true;
                          self.tkcrw = true;
                          print "~I thought once we'd escaped the pirates we'd be over the worst of it, but then I
                          managed to break my arm making my way up out of the chasm,~ ";
                          PHeShe();
                          print " says with a wince. ~Talk about ~out of the frying pan and into the fire~, when I
                          did make it to the cavern, Zy'gnan was half eaten and Douglas... Douglas was trying to
                          fight it...~ Suddenly ";
                          if (m_base.ch_maidens) "she stops and breaks down again.";
                          "he stops and lowers his head.";
                      t_bolt, t_hpiston:
                          if (self.fsfirstime) {
                              if (al_arm.fixed == false) {
                                  if (player in air_lock or sm_airlock) "~See that hydraulic piston up there, it looks like the bolt is loose,~ says Captain Adar. ~Try tightening it before opening the hatch with the control panel.~";
                                  "~If you are having problems with the cargo hatch, check out the hydraulic piston,~ says Captain Adar. ~The main bolt always comes loose and you might have to tighten it before opening the hatch with the control panel.~";
                              }
                              if (crashed_ship.airlockopen || al_door.albroken) "~You really went above and beyond the call of duty on that one,~ smiles Captain Adar, ~but we still have to get the beacon running. Who knows how long it will take 'til a transport finds us?~";
                              "~You don't need to worry about the bolt,~ says Captain Adar, ~open that hatch somehow.~";
                          }
                          "~What bolt are you talking about,~ asks Captain Adar.";
                      t_bomb:
                          if (self.bgnoff) "~Thank God I don't have to worry about that anymore,~ says Captain Adar, ~sometimes you scare me.~";
                          "~Please be careful with that,~ says Captain Adar.";
                      t_brakis:
                          "~This planet has done in my career,~ says Captain Adar somberly, ~speak of it no more.~";
                      t_button:
                          if (self.fsfirstime) {
                              if (player in air_lock or sm_airlock) return PACPnl();
                          }
                          if (player in crashed_ship) return PABcn();
                          return PNS();
                      t_coolant:
                          if (self.fsfirstime) "~The autocoolant can be very useful,~ says Captain Adar, ~If you're feeling overheated, just put it on yourself.~";
                          return PNS();
                      t_cpanel:
                          if (self.fsfirstime) return PACPnl();
                          return PNS();
                      t_crew:
                          self.tkcrw = true;
                          "~Those guys were die hard,~ says Captain Adar, ~and I lead them straight into the mouth of hell.
                          I don't think I can ever forgive myself for that.~";
                      t_cup, t_datacard, t_pbar:
                          "~Why are you asking me about that,~ questions Captain Adar, ~it's your equipment.~";
                      t_cwire:
                          "~Greb, like the pirates didn't do enough damage,~ curses the Captain.";
                      t_douglas:
                          "~Never knew a better co-pilot,~ Captain Adar says, ~I don't think I can forgive myself for what I've done.~";
                      t_dpit:
                          if (player in deadly_pit) "~God this place is awful,~ complains Captain Adar, ~please get us out of here.~";
                          return PNS();
                      t_dpad, t_zchip:
                          self.grief = true;
                          print "~Dear God, this was Zy'gnan's data pad,~ ";
                          PHeShe();
                          print " says looking at all the damage inflicted";
                          if (m_base.ch_maidens) {
                              print ", fighting back tears. Suddenly she loses it, breaking down as she cries out";
                          } else {
                              print ". Lowering his head, he says";
                          }
                          ", ~what have I done to us?~";
                      t_ebeacon:
                          if (self.foundship) return PABcn();
                          return PNS();
                      t_eengine:
                          if (self.foundship) {
                              if (autocoolant notin al_gen or sm_alelectric) {
                                  al_door.deseng = true;
                                  print "~We use the APU to power the ship when we're on the ground.
                                  Problem is, it's been overheating lately and we haven't dared use it";
                                  if (player in air_lock or sm_airlock) ",~ says Adar.";
                                  ". If you want to take a look, it's down by the main drive,~ Adar says, pointing aft.";
                              }
                              if (crashed_ship.airlockopen || al_door.albroken) "~That was pretty cool Darington, great job venting the smoke, really above and beyond the call of duty,~ smiles the Captain, ~but don't worry about the auxiliary power unit, get the beacon running, who knows how long it will take 'til a transport finds us?~";
                              print "~I'd never have thought of using the Autocoolant. Well done!~ says Adar, grinning. ";
                              if (crashed_ship.smoking) "~Now all we need to do is get rid of the smoke.~";
                              "~You might just save us.~";
                          }
                          "~What power unit are you talking about,~ asks Captain Adar.";
                      t_eggs:
                          print "~Well, the ralckor was eating Douglas,~ recalls Captain Adar, ~and I needed a place to hide,
                          but when that spitter turned up, the eggs proved to be a bad idea.~ ";
                          if (m_base.ch_maidens) {
                              print "She";
                          } else {
                              print "He";
                          }
                          print " seems to try to shake away the thought as ";
                          PHeShe();
                          " says, ~Thanks, thanks again for saving me.~";
                      t_ghook:
                          "~Well, it's not mine,~ says Captain Adar, ~the pirates must have left it.~";
                      t_icore:
                          "~Well the inner core is what the Xulthe'en Empire has claimed for itself, even though the
                          Vlaxion's controlled part of the space for five thousand years prior.~";
                      t_idol:
                          if (self.haveidol && player in s_tunnel) "~The idol looks like it was of some importance to the tribe that once lived here,~ says Captain Adar. ~That crude little man reminds me of the rune over this pedestal.~";
                          if (self.haveidol) "~The idol looks like it was of some importance to the tribe that once lived here,~ says Captain Adar. ~That crude little man reminds me of one of the runes I've seen around here.~";
                          "~What idol are you talking about?~ asks Captain Adar.";
                      t_fpack:
                          "~Those packs are essential to field research teams,~ says Captain Adar.";
                      t_journal:
                          if (self.foundjournal) return PShowJournal();
                          "~What journal do you speak of?~ asks Captain Adar.";
                      t_knife:
                          if (knife in player) {
                              print "~Are you trying to compensate your ego with that thing,~ asks Captain Adar, as ";
                              if (m_base.ch_maidens) "she smiles to herself.";
                              "he smiles to himself.";
                          }
                          "~Why you asking me about it,~ questions Captain Adar, ~it's your equipment.~";
                      t_lamp:
                          if (self.lmptke) {
                              if (self in secret_chamber) "~Look, you've got rid of the spirits, so let's get out of here,~ says the Captain.";
                              "~I hope it was worth all the trouble to get it,~ states Captain Adar.";
                          }
                          if (self.knowlamp) {
                              if (self in secret_chamber && lc_vampires.anger) "~You need to calm these spirits down if you want to hold on to that thing,~ shouts Captain Adar over the roar of the spirits.";
                              if (lc_vampires.enraged) "~With the spirits acting up like that I'm not sure how you're going to get the orb,~ says Captain Adar. ~You'll have to calm them down first.~";
                              if (lc_vampires in secret_chamber) {
                                  print "~It's an interesting ceremonial piece, but those spirits are a little creepy,~ Captain Adar says";
                                  if (m_base.ch_maidens) " with a slight shiver.";
                                  ".";
                              }
                          }
                          if (player.orbtke) {
                              if (m_base.ch_maidens) print "~It's beautiful. M";
                              else print "~Never seen anything like that before, m";
                              "aybe it could be of some use to us,~ states Captain Adar.";
                          }
                          return PNS();
                      t_lox:
                          "~Be careful with that stuff,~ says Captain Adar, ~it can be deadly.~";
                      t_mkit:
                          if (self.fsfirstime) "~The med kit is not fully stocked,~ says Captain Adar, ~Sorry about that, but keeping this ship flying takes all the I have.~";
                      return PNS();
                      t_necklace:
                          if (self.cubetake) "~I'm glad you figured out what they are used for,~ says Captain Adar, ~that whole pedestal thing was a neat light show.~";
                          "~There seems to be a few of those around,~ says Captain Adar, ~and I wonder what they're used for.~";
                      t_ochip:
                          if (ochip.destroy) "~That's not going to be cheap to replace,~ says Captain Adar with a bit of scorn.";
                          "~I just replaced it, so it should work,~ says Captain Adar.";
                      t_oheat:
                          if (self.fsfirstime) {
                              if (autocoolant in al_gen or sm_alelectric) {
                                  print "~I'd never have thought of using the Autocoolant. Well done!~ says Adar, grinning. ";
                                  if (crashed_ship.smoking) "~Now all we need to do is get rid of the smoke.~";
                                  "~You might just save us.~";
                              }
                              "~The APU has been overheating, and since we've been out in the boondocks lately we haven't had a chance to get it fixed. If you want to take a look, it's down by the main drive,~ Adar says, pointing aft.";
                          }
                          return PNS();
                      t_otrans:
                          "~You know I wish I had mine,~ says Captain Adar, ~I've scanned a lot of data over the
                          years, this is a missed opportunity.~";
                      t_page:
                          "~I've never seen a script like that before,~ says Captain Adar, ~too bad I do not have my OmniTrans, then maybe I could read it.~";
                      t_pedestal:
                          if (player in s_tunnel) {
                              if (statue in pedestal) "~I guess it's not too hard figuring out that it goes there,~ says the Captain looking at the idol on top of the pedestal, ~but at least we're one step closer to making it out.~";
                              "~Looks harmless, but everything in this place is deceiving,~ says the Captain with a wary glace at the pedestal, ~I'm sure it's trapped.~";
                          }
                          return PNS();
                      t_pident:
                          "~Looks like you're a third class crewman, guess you can't get demoted,~ says Captain Adar with a smirk.";
                      t_playbeing:
                          "~Oh, you read that too,~ smiles Captain Adar, ~this months issue is pretty hot.~";
                      t_player:
                          "~Well, you saved my life, so you're a hero in my book,~ says Captain Adar with a quick wink, ~but other than that, I really know nothing about you.~";
                      t_pirates:
                          "~I'm going to get those guys, let me tell you what,~ Captain Adar says coldly. ~We got a
                          distress call coming in on our beacon, so I decided to check it out. They came at us out of
                          nowhere,~ the Captain recalls. ~The pirates disabled our thrusters, so I decided to land the
                          ship on the nearest planet, they only want to loot it anyways. I'll probably never fly again,
                          but at least I'm breathing.~";
                      t_ralckor:
                          print "~That beast almost killed me, and destroyed my crew,~ Captain Adar says as ";
                          if (m_base.ch_maidens) {
                              print "she lowers her";
                          } else {
                              self.grief = true;
                              print "he lowers his";
                          }
                          " head. ~Speak of it no more.~";
                      t_rchasm:
                          if (self.cblown) {
                              self.grief = false;
                              "~That was pretty slick,~ says Captain Adar with a slight wink and nod. ~Filling in the chasm was a great idea.~";
                          }
                          if (player in chasm) "~This is the chasm I broke my arm on,~ says Captain Adar with a slight shudder from the wind. ~I can't climb down it, not in this state, but I am sure that is not the only way across. That mountainside looks unstable, maybe there is a way to bring it down.~";
                          "~This planet has been nothing but trouble since I got here,~ says Captain Adar, ~not only did it
                          clam my ship and my crew; but I broke my arm on top of it, falling off that Godforsaken chasm.~";
                      t_rigel:
                          "~Oh my, what a beautiful place Rigel is,~ says Captain Adar. ~Wish I was drinking one of their Tiki-Maui specials right now.~";
                      t_trobe:
                          "~The tribe is long gone, I wonder how,~ asks Captain Adar.";
                      t_scrate:
                          if (self.scrttlk) {
                              print "You don't want to upset Captain Adar, it's best not ask ";
                              if (m_base.ch_maidens) {
                                  print "her";
                              } else {
                                  print "him";
                              }
                              " about the crate anymore.";
                          }
                          if (self.fsfirstime) {
                              self.scrttlk = true;
                              "~You should mind your own business,~ says Captain Adar with a penetrating glare, that stops you from continuing.";
                          }
                          return PNS();
                      t_scube:
                          "~I am sorry, I have no idea what that cube is for,~ replies Captain Adar.";
                      t_shale:
                          "~Well, there's a lot of that lying around,~ says Captain Adar.";
                      t_shelter:
                          "~If I had one we could combine them, but the tent would be pretty small,~ smiles the Captain.";
                      t_smoke:
                          if (crashed_ship.smoking) "~Wait for it to die down and you can go back into the ship,~ says Captain Adar.";
                          return PNS();
                      t_ssuit:
                          if (self.fsfirstime) "~It came with ship,~ says the Captain, ~but I've never gone on any EVAs.~";
                          return PNS();
                      t_stokar:
                          if (self.stkrtlk) "~Why don't we change the topic,~ say Captain Adar, avoiding the question.";
                          self.stkrtlk = true;
                          print "~What about Stokar,~ asks Captain Adar nervously, darting ";
                          if (m_base.ch_maidens) {
                              print "her";
                          } else {
                              print "his";
                          }
                          " eyes about and looking at the ground. ~I'm no smuggler, I've never been out there, and you should keep your accusations to yourself!~";
                      t_system:
                          if (self.foundship) {
                              if (crashed_ship.airlockopen || al_door.albroken) "~What are you, slow? Turn on the beacon while you have the chance,~ orders the Captain, ~who knows how long it will take 'til a transport finds us?~";
                              "~The pirates have done a pretty comprehensive job in here, and I bet they've disabled the main drive too. But,~ Adar brightens, ~they might not have bothered with the APU. If we could get if working again, that would be something.~";
                          }
                          return PNS();
                      t_tcrystal:
                          "~It's no diamond,~ smiles Captain Adar.";
                      t_tome:
                          if (self.foundtome) return PShowTome();
                          "~What tome do you speak of?~ asks Captain Adar.";
                      t_torch:
                          "~Well, if it's not working for you,~ says Captain Adar, ~find another light source.~";
                      t_tribe:
                          print "~I do not know much about the tribe that once lived on this planet,~ says Captain Adar";
                          if (player in chasm or desert_crash or crashed_ship or air_lock) ".";
                          ", ~but their runes seem to line the walls of this place, wish I had my OmniTrans.~";
                      t_uniform:
                          "~Well I have to admit, the crewman's uniform does look good on you,~ smiles the Captain.";
                      t_utool:
                          "~I have one of those,~ says Captain Adar, ~everyone within the core does.~";
                      t_vampire:
                          if (solace_cube.shimmering) {
                              print "~Great job Darington,~ smiles Captain Adar, as ";
                              PHeShe();
                              " gives you an approving wink.";
                          }
                          if (self in secret_chamber) {
                              if (lc_vampires.anger) {
                                  print "~Do something about them, before they kill us,~ Captain Adar says as ";
                                  if (m_base.ch_maidens) "she bats away the spirits.";
                                  else "he stands his ground.";
                              }
                              print "~They're beautiful, in a creepy sort of way,~ Captain Adar comments to ";
                              if (m_base.ch_maidens) {
                                  print "herself";
                              } else {
                                  print "himself";
                              }
                              " as much as to you.";
                          }
                          if (self.seenspirit) "~I have a bad feeling about them,~ Captain Adar says with a slight shudder.";
                          return PNS();
                      t_wraps:
                          if (self.fsfirstime) {
                              if (self.healed) "~Great job bandaging my arm Darington,~ says Captain Adar, ~thanks a lot.~";
                              "~Oh wow, you have wraps,~ says Captain Adar excitedly, ~you know my arm is broken, don't you?~";
                          }
                          return PNS();
                      t_zship:
                          if (crashed_ship.airlockopen || al_door.albroken) {
                              print "~You know, that cargo hatch seems to be the cause of so much trouble,~
                              Captain Adar says thinking to ";
                              if (m_base.ch_maidens) {
                                  print "herself";
                              } else {
                                  print "himself";
                              }
                              ", ~I probably should have gotten it fixed a long time ago. Now get that beacon up,
                              who knows how long it will take a transport to find us.~";
                          }
                          if (self.foundship) {
                              if (crashed_ship.smoking) {
                                  if (self.fsfirstime) "~You need to open the cargo hatch, if you want to keep those engines running in order to turn on the beacon,~ says Captain Adar, ~I hope it doesn't prove to be a problem.~";
                                  if (player in desert_crash) {
                                       print "~She's smoking pretty bad,~ Captain Adar states, watching the smoke pour out
                                      of the ship, ~you're going to have to wait till it dies down before you can get
                                      back inside.~ Taking a moment, ";
                                      PHeShe();
                                      print " comments to ";
                                      if (m_base.ch_maidens) {
                                          print "herself";
                                      } else {
                                          print "himself";
                                      }
                                      ", ~this is going to be bad.~";
                                  }
                                  "~Let's get back to the ship,~ states the Captain, ~we need to get off this rock!~";
                              }
                              if (self.fsfirstime) {
                                  print "~";
                              } else {
                                  if (self.zshipft) {
                                      self.zshipft = false;
                                      print "~Well it looks the pirates destroyed her, great! Now I've probably lost my cargo,
                                      there goes my license. We need to figure something out. ";
                                  } else {
                                      print "~";
                                  }
                              }
                              "Try getting the power going again, and turn the beacon on. If any ship passes within a half
                              a sa-tor from here they'll be able to pick up that transmission. It's hot and we don't have a
                              lot of time, so let's get moving,~ orders the Captain.";
                          }
                          if (player in desert_crash) {
                              move adar to crashed_ship;
                              move gone_adar to desert_crash;
                              print "~Well I know she doesn't look like much, but maybe she'll fly again,~ says Captain Adar.
                              ~Let us have a look,~ ";
                              if (m_base.ch_maidens) {
                                  print "she says as she";
                              } else {
                                  print "he says as he";
                              }
                              " walks into the ship.";
                          }
                          print "~Well,~ Adar says, taking a deep breath, ~We crashed about a klick east
                          of here, on the far side of a large meteor crater. At first, I thought
                          there was some sort of research station on the other side of the crater,
                          so we decided to head for that. We had no equipment or supplies, so it
                          was either that or die in the desert.
                          ^^The chasm wasn't that deep, but the walls were smoother than we thought
                          they'd be -- sand erosion, probably -- and I reached the bottom rather
                          faster than I'd planned,~ ";
                          PHeShe();
                          print " says ruefully, rubbing ";
                          if (m_base.ch_maidens) {
                              print "her";
                          } else {
                              print "his";
                          }
                          print " left arm. ~Nothing too serious, but for a while there I didn't think we'd
                          make it out again. Now I regret we did: the ~research station~ was pure
                          ralckor hypnotism. What a mess.~ ";
                          if (m_base.ch_maidens) {
                              print "She";
                          } else {
                              print "He";
                          }
                          " takes a shaky breath, then continues, ~The rest you know.~";
                      t_zygnan:
                          "~He was the best radar tech I've ever had,~ Captain Adar says, ~I'm going to carry his death with me forever.~";
                      default: "~Look, that doesn't matter, we have to get off this rock,~ states the Captain, avoiding the question.";
                  }
              Kiss:
                  print "With a hard slap across the face ";
                  PHeShe();
                  " says, ~Come now, we will be having none of that!~";
              Tell:
                  AdarGrief();
                  switch(second) {
                      t_airlock:
                          if (self.fsfirstime) {
                              if (crashed_ship.airlockopen || al_door.albroken) "~I'm glad you vented out all that smoke,~ says Captain Adar with a quick wink, ~you think the Zrok Corporation would produce a better product. Now get that beacon running, who knows how long it will take 'til a transport finds us.~";
                          if (crashed_ship.smoking) "~You need to open the cargo hatch, if you want to keep those engines running in order to turn on the beacon,~ says Captain Adar, ~I hope it doesn't prove to be a problem.~";
                          "~That hatch is pretty messed up,~ complains Captain Adar, ~started a fire last time I tried to use it.~";
                          }
                          "~What hatch are you talking about,~ asks Captain Adar.";
                      t_arm:
                          "~You do not have to tell me about it,~ says Captain Adar, ~it hurts.~";
                      t_journal:
                          if (self.foundjournal) {
                              if (ReadJournal()) return PJournalTell();
                              "You don't know enough about the journal to relate anything to Captain Adar.";
                          }
                          "~What journal do you speak of?~ asks Captain Adar.";
                      t_player:
                          "~Looks like you are pretty impressed with yourself, hmm,~ says Captain Adar.";
                      t_pirates, t_tship:
                          "~I am sorry to hear they attacked you too,~ says Captain Adar. ~The Empire needs to send the military out here to take care of this problem. I mean, we're in the inner core.~";
                      t_smoke:
                          if (crashed_ship.smoking) "~Wait for it to die down and you can go back into the ship,~ says Captain Adar.";
                          return PNS();
                      t_tribe:
                          if (ReadTome()) return PTomeTell();
                          if (ReadJournal()) return PJournalTell();
                          "You don't know enough about the tribe to relate anything to Captain Adar.";
                      t_tome:
                          if (self.foundtome) {
                              if (ReadTome()) return PTomeTell();
                              "You don't know enough about the tome to relate anything to Captain Adar.";
                          }
                          "~What tome do you speak of?~ asks Captain Adar.";
                      default:
                          print "~I hope that works out for you,~ Captain Adar says as ";
                          if (m_base.ch_maidens) {
                              print "she faces her";
                          } else {
                              print "he faces his";
                          }
                          " back to you.";
                  }
          ],
          orders [;
              Enter:
                  if (noun == deadp_obj or chasmobj) "~You're a funny one,~ the Captain says, laughing off your suggestion.";
              Follow:
                  "~I already am,~ snaps the Captain, ~now let's get moving.~";
              Hello:
                  "~Good day,~ smiles Captain Adar.";
              No:
                  "~You don't say,~ Captain Adar replies a little puzzled.";
              Open:
                  if (player in air_lock or sm_airlock) {
                      if (noun == al_door or airlock_obj) {
                          AdarGrief();
                          if (crashed_ship.airlockopen) "~That is already open,~ says Captain Adar, ~now try turning on that beacon.~";
                          "~I do not think I can help you,~ says Captain Adar. ~You are going to have to figure it out on your own.~";
                      }
                  }
              Unlock:
                  if (noun == smallcrate or sm_scrate) {
                      if (self.grief) self.grief = false;
                      "~I do not know why you're thinking about fooling around with my Class ~A~ cargo,~ says Captain Adar, ~but I'll tell you this, I won't tolerate it and you'll find yourself in a world of hurt. Leave it alone! That's an order, crewman.~";
                  }
                  "~I think you're being a little pushy there Darington,~ states the Captain.";
              Yes:
                  if (ALeave()) rtrue;
                  "~You don't say,~ Captain Adar replies a little puzzled.";
          ],
          gtalk false,
          grief false,
          tkcrw false,
          bgnoff false,
          cblown false,
          healed false,
          lmptke false,
          zshipft true,
          asksuit false,
          scrttlk false,
          stkrtlk false,
          setgrief true,
          adaroff false,
          cubetake false,
          haveidol false,
          knowlamp false,
          foundship false,
          foundtome false,
          fsfirstime false,
          seenspirit false,
          doorfrstime true,
          foundjournal false,
          unlockedairlock true,
     has  animate male transparent proper;

! 07/30/07

  Object  gone_adar "Captain Adar"
    with  name 'captain' 'adar' 'man' 'male' 'him' 'broken' 'arm',
          description
              "You can't see any such thing.",
          before [;
              Follow:
                  print "You follow Captain Adar into the crashed ship.^";
                  u_obj.&name-->4 = '7840ph';
                  remove self;
                  PlayerTo(crashed_ship,2);
                  rtrue;
              AskChar, TellTo, Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, GetOff, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip, FlipOff:
                  "You can't see any such thing.";
              Push, PushDir, Pull, Read, Remove, Rub, Search, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "You can't see any such thing.";
          ],
          life [;
              Answer, AnswerDir, Ask, Tell:
                  "You can't see any such thing.";
          ],
     has  concealed animate proper male;
