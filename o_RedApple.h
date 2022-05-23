
! 09/05/07

  Movable w_fruit "juicy red apple"
    with  name 'juicy' 'red' 'apple' 'fruit' 'ral^s' 'rals',
          description
              "This is possibly the most perfect specimen of an apple you have ever seen.",
          describe [;
              rtrue;
          ],
          before [;
              Eat, UseItem:
                  print "(first taking the juicy red apple)^";
                  <<Take self>>;
              Give, Show, ThrowAt, Use:
                  "You don't have that.";
              Take, Remove:
                  if (InventTotal() >= PMAX_WEIGHT + 1) {
                      if (milpack in player or uniform) {
                          InventMove(1);
                      } else {
                          return L__M(##Take, 12);
                      }
                  }
                  ifruit=0;
                  remove self;
                  remove r_fruit;
                  remove m_guards;
                  remove m_maidens;
                  give gone_maidens female;
                  move gone_maidens to m_base;
                  m_base.ch_maidens = true;
                  m_base.fruiteaten = true;
                  adar.&name-->2 = 'woman';
                  adar.&name-->3 = 'female';
                  adar.&name-->4 = 'her';
                  gone_adar.&name-->2 = 'woman';
                  gone_adar.&name-->3 = 'female';
                  gone_adar.&name-->4 = 'her';
                  give adar ~male;
                  give adar female;
                  give gone_adar ~male;
                  give gone_adar female;
                  "As you take the apple, you briefly wonder where they keep their orchard. You give Ral a nod
                  of thanks and take a bite; it's every bit as good as it looks.
                  ^^A sudden gust of wind blinds you and sets you coughing. When you recover, Kor is gone.
                  That ought to seem odd, but for some reason it doesn't bother you.
                  ^^~Follow me,~ Ral says, smiling broadly as she turns to head back into the temple. Pleased at
                  her victory, perhaps?";
          ],
     has  edible;
