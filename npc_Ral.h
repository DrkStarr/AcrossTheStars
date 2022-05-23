
! 04/24/06

  Object  m_maidens "Ral" m_base
    with  name 'ral' 'beautiful' 'woman' 'her' 'cloak' 'women' 'raven-black' 'raven' 'black' 'long' 'hair' 'eyes' 'tan',
          description
              "Her cloak may be simply-made and demure, but she's making sure that it doesn't hide much
              where it counts. Her hair is long and raven-black, complementing her eyes, and her skin is
              deeply tanned. She looks like a model from a shampoo ad, and you wonder what she's doing here.
              ^^She is holding out a juicy red apple, as perfect as her hand.",
          before [;
              AskChar, TellTo:
                  return MaidenReply();
              Attack, Kick:
                  "~Please, do not hurt me,~ she begs, ~I only want to make your dreams come true.~";
              Eat:
                  "Mmm... Only if you could.";
              Follow:
                  "But she's waiting for you to eat her fruit.";
              Hug:
                  "~Oh, I bet you want to do more than that,~ Ral says, with a coy smile, ~partake of my gift and you can.~";
              Kiss:
                  "~Eat and strengthen yourself before our love,~ Ral says, with a wanting gaze.";
              Push, PushDir:
                  "You push Ral away, telling her to get back.
                  ^^~Please,~ she says, ~please partake of the red apple.~";
          ],
          life [;
              Answer:
                  return MaidenAnswer(noun);
              AnswerDir:
                  return MaidenAnswer(second);
              Ask, Tell:
                  switch(second) {
                      t_fruit:
                          "~It is truly beautiful,~ she smiles, ~eat and you will see.~";
                  }
                  return MaidenReply();
          ],
          orders [;
              Give:
                  if (noun == r_fruit) "~I am not offended, if you choose to be with Kor so be it,~ says Ral plainly.";
                  if (noun == w_fruit) "~Why not take what is offered to you,~ asks Ral with an inviting smile.";
              Hello:
                  "~It is my pleasure,~ Ral says, with a smile, ~ecstasy is within the gift that I offer.~";
              No:
                  "~I am sure I can change your mind,~ she responds, with a coy smile.";
              Yes:
                  "~Then enjoy its nectar,~ Ral says, offering you the red apple.";
          ],
     has  concealed container open animate proper female;

! 06/09/07

  Object  gone_maidens
    with  name 'ral' 'beautiful' 'woman' 'her' 'cloak' 'women' 'raven-black' 'raven' 'black' 'long' 'hair' 'eyes' 'tan' '1933ph',
          description
              "You can't see any such thing.",
          short_name "Ral",
          before [;
              Follow:
                  return PToPan();
              AskChar, TellTo, Attack, Blow, Burn, Buy, Climb, Close, Cut, CrawlOver, Dig, Drink, Eat, Empty, Enter, Exit, Fix, GetOff, Hide, JumpOver, Kick, Listen, LookUnder, Open, Plug, PlugItem, SwFlip, FlipOff:
                  "You can't see any such thing.";
              Push, PushDir, Pull, Read, Remove, Rub, Search, Set, SetTo, ShortOut, Sit, Smash, Smell, Squeeze, Stand, Strap, Swing, SwitchOn, SwitchOff, Take, Taste, Tie, Touch, Transfer, Turn, Unlock, Unplug, Unstrap, Use, UseItem, Wave:
                  "You can't see any such thing.";
          ],
          life [;
              Answer, AnswerDir, Ask, Tell:
                  "You can't see any such thing.";
          ],
     has  concealed animate;
