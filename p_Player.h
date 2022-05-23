
! ---------------------------------------------------------------------------- !
!       Player's Object
!

! 05/25/06

  Object  SelfPlayer "self"
    with  short_name [; return L__M(##Miscellany, 18); ],
          name 'yourself' 'xultheen' 'xulthe^en' 'darington' 'dan' 'ann' 'al',
          capacity MAX_CARRIED,
          description [;
              if (player in dreambridge) "You look down, but fail to see the body that should be supporting you.";
              if (uniform in self && uniform has worn) "Since enlisting in the Xulthe'en Armada as a fresh-faced youth, you've learned to keep yourself squared away at all times. You get into less trouble that way.";
              if (uniform in spacesuit or mal_spacesuit) "Covering up your uniform, the deep-space suit is bulky and hard to move around in.";
              if (player in berth) "You're wearing your skivvies.";
              "Presently you're out of uniform and if the Captain caught you, he'd have you scrubbing the grout in the head with your toothbrush.";
          ],
          each_turn [ iran;
              if (ma_airlock.alflowoff == false) icmove++;
              if (icmove == 6) {
                  icmove = 0;
                  iclk4++;
                  if (iclk4 == 10) {
                      iclk4 = 0;
                      iclk3++;
                  }
                  if (iclk3 == 10) {
                      iclk3 = 0;
                      iclk2++;
                  }
                  if (iclk3 == 6 && iclk4 == 0) {
                      iclk3 = 0;
                      iclk2 ++;
                  }
                  if (iclk2 == 10) {
                      iclk2 = 0;
                      iclk1++;
                  }
                  if (iclk1 == 2 && iclk2 == 5) {
                      iclk1 = 0;
                      iclk2 = 0;
                  }
              }
              if (self.plprt) {
                  iprtpl++;
                  if (iprtpl == 20) {
                      iprtpl = 0;
                      print "^The ship ";
                      iran = random(4);
                      while ((ioldrun == ilastrun) && (ilastrun == iran)) {
                          iran = random(4);
                      }
                      switch(iran) {
                          1: print "lists port";
                          2: print "lists starboard";
                          3: print "tips forwards";
                          4: print "tips backwards";
                      }
                      ioldrun = ilastrun;
                      ilastrun = iran;
                      " as the pirates' tractor beam pulls the Supalace back on course.";
                  }
              }
          ],
          before [;
              Attack, Cut:
                  return PKY();
              Kick:
                  "You might need a good boot up your ass, but your own?";
              Touch, Play:
                  "This might not be the right time to do that sort of thing.";
              WakeOther:
                  <<Wake location>>;
              WrapRev:
                  if (second == blanket) "This is no time for getting comfortable.";
          ],
          plprt false,
          orbtke false,
          runaway false,
          droplist false,
    has   animate concealed proper transparent;
