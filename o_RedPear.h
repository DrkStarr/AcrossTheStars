
! 04/24/06

  Movable r_fruit "juicy red pear"
    with  name 'juicy' 'red' 'pear' 'fruit' 'kor^s' 'kors',
          description
              "This is possibly the most perfect specimen of a pear you have ever seen.",
          describe [;
              rtrue;
          ],
          before [;
              Eat, UseItem:
                  print "(first taking the juicy red pear)^";
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
                  remove w_fruit;
                  remove m_guards;
                  remove m_maidens;
                  give gone_maidens male;
                  move gone_maidens to m_base;
                  m_base.ch_maidens = false;
                  m_base.fruiteaten = true;
                  gone_maidens.&name-->0 = 'kor';
                  gone_maidens.&name-->1 = 'handsome';
                  gone_maidens.&name-->2 = 'male';
                  gone_maidens.&name-->3 = 'him';
                  gone_maidens.&name-->4 = 'cloak';
                  gone_maidens.&name-->5 = 'hair';
                  gone_maidens.&name-->6 = 'black';
                  gone_maidens.&name-->7 = 'coal';
                  gone_maidens.&name-->8 = 'eyes';
                  gone_maidens.&name-->9 = 'muscular';
                  gone_maidens.&name-->10 = 'shoulder';
                  gone_maidens.&name-->11 = 'shoulders';
                  gone_maidens.&name-->12 = 'tan';
                  gone_maidens.&name-->13 = 'man';
                  gone_maidens.short_name = "Kor";
                  "As you take the pear, you briefly wonder where they keep their orchard. You give Kor a nod of
                  thanks and take a bite; it's every bit as good as it looks.
                  ^^A sudden gust of wind blinds you and sets you coughing. When you recover, Ral is gone. That
                  ought to seem odd, but for some reason it doesn't bother you.
                  ^^~Follow me,~ Kor says, smiling broadly as he turns to head back into the temple. Pleased at
                  his victory, perhaps?";
             ],
     has  edible;
