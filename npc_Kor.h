
! 09/05/07

  Object  m_guards "Kor" m_base
    with  name 'kor' 'handsome' 'male' 'man' 'him' 'cloak' 'hair' 'black' 'coal' 'eyes' 'muscular' 'shoulder' 'shoulders' 'tan',
          description
              "His cloak hangs well from his muscular shoulders, not because it's a masterpiece of
              the tailor's art, but because his is the sort of physique that would look good in anything,
              up to and including the proverbial sackcloth and ashes. His hair is as black as coal, like
              his eyes, and he has a deep desert tan.
              ^^He is holding out a juicy red pear, as perfect as his hand.",
          before [;
              AskChar, TellTo:
                  return GuardReply();
              Attack, Kick:
                  "~I do not want to bring harm to you,~ he says, ~I only want to meet all your needs.~";
              Eat:
                  "Mmm... Only if you could.";
              Follow:
                  "But he's waiting for you to eat his fruit.";
              Hug:
                  "~Is that all you want to do,~ Kor asks, ~take of my fruit and you can have more.~";
              Kiss:
                  "~Renew your energy, before our love,~ Kor says, offering the red pear.";
              Push, PushDir:
                  "You push Kor away, telling him to get back.
                  ^^~Please,~ he says, ~take my gift and I will take care of you.~";
          ],
          life [;
              Answer:
                  return KorAnswer(noun);
              AnswerDir:
                  return KorAnswer(second);
              Ask, Tell:
                  switch(second) {
                      t_fruit:
                          "~Its color is the power that flows through my veins,~ Kor states in a commanding voice,
                          ~Eat of it and you will feel a power unlike none other!~";
                      }
                      return GuardReply();
          ],
          orders [;
              Give:
                  if (noun == w_fruit) "~But that is Ral's, and I'll not offend her,~ states Kor.";
                  if (noun == r_fruit) "~Afraid to take the pear from my hand,~ asks Kor with a coy smile.";
              Hello:
                  "~The honor is mine,~ Kor says, with a bow, ~enjoy the gift I offer.~";
              No:
                  "~It is my charge to change your mind,~ he responds.";
              Yes:
                  "~I am glad that you will enjoy its nectar,~ he says, offering you the red pear.";
               ],
     has  concealed container open animate proper male;
