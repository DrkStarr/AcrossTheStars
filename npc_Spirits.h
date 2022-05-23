
! 08/16/06

  Object  lc_vampires "four ethereal spirits" secret_chamber
    with  name 'four' 'matter' 'ethereal' 'spirit' 'spirits' 'spirit^s' 'fog' 'ghost' 'ghosts' 'ghost^s',
          article "the",
          description [;
              if (self.anger)
                  "The four spirits cry out, in an agonizing pain that chills your very core, while
                  whipping about the room in a stirred up fury that you can only hope to calm down.";
              "The four spirits drift like an ethereal fog upon the stillness of this chamber,
              as an overwhelming feeling of helplessness and frustration overcomes you.
              The pain these spirits feel is undeniable, as they endlessly encircle
              a golden orb placed upon the black obelisk in the center of the room.";
          ],
          before [;
              Attack, Cut, Push, PushDir, Pull, Take, Remove, Touch:
                  if (second ~= nothing && second in player) "Since they're ethereal, ", (the) second, " passes right through them.";
                  "Since they're ethereal, your hand passes right through them.";
              AskChar, TellTo:
                  if (self.anger) return PRS();
                  "The spirits don't seem to notice you, as they gaze deeply into the golden orb.";
              Eat, Taste:
                   return PDL();
              Follow:
                  if (self.anger) "You can't fly around like that.";
                  "As you walk around the obelisk, it feels strange to come in contact the ethereal matter;
                  but since they fail to notice or take any interest, you cease following the spirits.";
              Hug:
                  if (self.anger) "There has to be a better way to bring peace to these tormented spirits.";
                  "Your efforts do little to bring peace to these spirits.";
              Kiss, Kick:
                  "Since they're ethereal, you pass right through them.";
          ],
          life [;
              Answer:
                  if (self.anger) return PRS();
                  return SpiritAnswer(noun);
              AnswerDir:
                  if (self.anger) return PRS();
                  return SpiritAnswer(second);
              Ask:
                  if (self.anger) return PRS();
                  switch(second) {
                      t_lamp:
                          "~The orb is sacred,~ one of the spirits snaps furiously, ~only the Protector is worthy to deliver it to the Lydinae.~";
                      t_lydinae:
                          "~We have severed the Lydinae all our lives,~ the spirits say with mournful reflection, ~though we seem to have lost our place.~";
                      t_protector:
                          "~The Protector is great and strong, he will come soon, yes soon,~ the spirits say comforting themselves. ~He will take the orb to the Lydinae, and all will be right again.~";
                      t_scube:
                          "~The cube, yes the solace cube,~ cry the spirits to themselves, ~we protected it once, but now it is gone from our sight.~";
                      t_sucored:
                          "~His holy scripture is more than you could ever understand,~ the spirits say mysteriously.";
                      t_test:
                          "~You think we would give up our secret rituals?~ asks a spirit with a harsh laughter that runs down your spine, chilling your core as goose bumps run wild.";
                      t_tome:
                          "~A book unlike any you've ever seen before,~ says one of the spirits, ~handed down by Sucored Himself.~";
                      t_vampire:
                          "~We know nothing of spirits haunting these ancient halls,~ states an apparition, only to follow her sisters in the unending pattern.";
                      default:
                          "~We suffer and suffer,~ all the spirits cry out, ~why do you continue this torment?~";
                  }
              Tell:
                  if (self.anger) return PRS();
                  switch(second) {
                      t_lamp, t_lydinae, t_protector, t_sucored, t_test, t_tome:
                          "~You know nothing of that which is holy,~ cries out a spirit, dismissing you before looping back round into the endless pattern.";
                      t_scube:
                          if (solace_cube in player or milpack) "~You have the cube? How can this be?~ cries a spirit in frustration, ~surely you are not worthy enough to pass the test.~";
                          "~You could never pass the test in order to get the solace cube,~ laughs a spirit to herself, returning to the endless pattern.";
                      t_vampire:
                          "~You mean we're the disembodied spirits? How can that be?~ questions one of the spirits in disbelief as she passes.";
                      default:
                          "~What do you know?~ the spirits retort, ~Do you know how to save the Lydinae, do you know how to heal this wound?~";
                  }
          ],
          orders [;
              Give:
                  if (self.anger) return PRS();
                  if (noun == orb) "~Unclean beast get away!~ all the spirits cry out, ~you are not the Protector and shall never have Sucored's last shard!~";
              Hello:
                  "One of the spirits slightly looks up, but as a group they pay you no mind as they encircle the golden orb.";
              No:
                  "~It is a shame, but our life is full of sadness,~ responds one of the spirits.";
              Yes:
                  "~What you think you know, I doubt you do,~ says one of the spirits before she returns to the circle.";
          ],
          anger false,
          enraged false,
    has   animate female pluralname scenery;
