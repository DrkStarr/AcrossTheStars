
! ---------------------------------------------------------------------------- !
!       The BERTH. 04/11/06
!
  RoomShp berth
    with  short_name [;
              print "Your Berth ";
              style roman;
              print "(on the bunk)";
              rtrue;
          ],
          description [;
              move pillow to rack;
              move blanket to rack;
              print "Your berth is small and cramped";
              if (rack.curtain_open == false) print ", especially with the curtains closed";
              print ". The space is little bigger than a coffin; life aboard this deep-space transport has little use for unnecessary luxury. ";
              if (berth_alarm.alarmon) {
                  if (rack.lighton) {
                      "Above you, the wall-mounted light is on.";
                  } else {
                      berth_alarm.alarmskip = true;
                      "Above you, the wall-mounted light is off, leaving the compartment dim, though not peaceful; the ~blip, blip, blip~ of your alarm is ringing insistently.";
                  }
              }
              if (rack.lighton) "Above you, the wall-mounted light is on.";
              "Above you, the wall-mounted light is off, leaving the compartment dim.";
          ],
          u_to [;
              return ExitBerth();
          ],
          d_to [;
              return ExitBerth();
          ],
          cant_go
              "You need to get out of your berth first.",
          before [;
              ClimbDown, Exit, GetOff, GetDown, SUp:
                  return ExitBerth();
              HideRoom:
                  if (rack.curtain_open) return CloseCurt();
                  "No one is going to find you in here.";
              Jump:
                  "You can't jump while lying in the berth.";
              Smell:
                  if (rack.curtain_open) {
                      "Unwashed socks, overused underwear, and stale cologne linger strongly in
                      the air. I guess these guys need to bathe a little more often.";
                  } else {
                      "You start to smell an odor creep up on you.";
                  }
          ],
          fore false,
          firsttime true,
          crewquarters false;

! 04/28/06

  RoomObj -> berthobj "berth"
    with  name 'ship' 'room',
          description [;
              <<Look berth>>;
          ],
          before [;
              Hide:
                  <<HideRoom berth>>;
              Search:
                    <<Search rack>>;
          ];

! 04/11/06

  Object  -> rack "bunk"
    with  name 'bunk' 'berth' 'rack' 'bed' 'mat' 'your',
          article "your",
          description [;
              if (self.lighton) print "Your berth's bathed in a warm reading light, illuminating a blanket and pillow; and while it might not be";
              else print "Your berth's made of some unpronounceable alloy, equipped with a blanket and pillow; and even though it's not";
              " the most comfortable bunk in the 'verse, it is large enough to call home.";
          ],
          describe [;
              rtrue;
          ],
          before [;
              Attack:
                    return PDE();
              Close, Open:
                  "It's not that type of berth.";
              Enter, Sit, Climb:
                  "But you're already in your bunk.";
              Hide:
                  <<HideRoom berth>>;
              Make:
                  "You have to get out of the berth if you want to do that.";
              Search:
                  if (self.lighton == false && self.curtain_open == false) "You can't find anything, as you search around in the darkness.";
                  if (berth_uniform in berth) "You see that you've placed your uniform at the foot of your bunk.";
                  if (RackTest() == 0) "You only find a blanket and pillow.";
                  print "You see that you've placed";
                  SelfPlayer.droplist = true;
                  WriteListFrom(child(berth), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                  " at the foot of your bunk.";
              Take, Remove, Turn, PushDir, Push, Pull:
                  return PAG();
          ],
          lighton false,
          curtain_open false,
    has   supporter static scenery;

! 04/13/06

  BrthObj -> rack_light "wall-mounted light"
    with  name 'wall-mounted' 'built-in' 'wall' 'mounted' 'light' 'lights' 'warm' 'reading' 'built' 'in' 'securely' 'encased' 'shock' 'proof' 'switch',
          description "It's a standard government-issue, securely encased, shock proof light.",
          before [ itest;
              SwFlip, SwitchOn, UseItem:
                  if (self.poweroff) "The light fails to work due to the power being disabled.";
                  if (self.flowregoff) "The light fails to work due to the flow regulator cutting the power off.";
                  if (rack.lighton) "The light is already on.";
                  give self light;
                  give self on;
                  rack.lighton = true;
                  itest = RackTest();
                  if (rack.curtain_open) {
                      print "As you turn on the switch, the berth is bathed in a warm reading light";
                      if (itest == 0) ".";
                      print ". Also, you can see that you've placed";
                  } else {
                      print "As you turn on the switch, the berth is bathed in a warm reading light, leaving you blinking";
                      if (itest == 0 && berth_uniform.unimoved == false) ".";
                      print ". As your eyes adjust, you see that you've placed";
                  }
                  if (berth_uniform.unimoved) {
                      berth_uniform.unimoved = false;
                      move berth_uniform to berth;
                      " your uniform at the foot of your bunk.";
                  }
                  if (berth_uniform in berth) " your uniform at the foot of your bunk.";
                  SelfPlayer.droplist = true;
                  WriteListFrom(child(berth), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                  " at the foot of your bunk.";
              FlipOff, SwitchOff:
                  if (~~rack.lighton) "The light is already off.";
                  give self ~light;
                  give self ~on;
                  rack.lighton = false;
                  if (rack.curtain_open) "You shut off the wall-mounted light.";
                  "The berth now becomes dark as you feel the cold reaches of space slowly begin to creep in.";
          ],
          poweroff false,
          flowregoff false,
    has   ~on ~light;

! 04/13/06

  BrthObj -> rack_curtain "curtains"
          with  name 'curtains' 'curtain' 'black' 'polymer' 'stain-proof' 'stain' 'proof',
          description [;
              print "The black polymer stain-proof curtains ";
              if (rack.curtain_open) {
                  "are open and shimmer in the light.";
              } else {
                  if (rack.lighton) "are closed and shimmer in the light.";
                  "are closed and shimmer in the darkness.";
              }
          ],
          before [;
              Close:
                  if (rack.curtain_open) return CloseCurt();
                  "The curtains to your berth are already closed.";
              Open:
                  if (rack.curtain_open) "The curtains to your berth are already open.";
                  rack.curtain_open = true;
                  move b_hatchway to berth;
                  move overhead_light to berth;
                  if (berth_uniform.unimoved) {
                      berth_uniform.unimoved = false;
                      move berth_uniform to berth;
                      "As you open the curtains, you see your uniform lying at the end of the bunk.";
                  }
                  "You open the curtains to your berth.";
              Tear, Rip:
                  return PDE();
          ],
          firsttime true,
    has   pluralname;

! 09/18/06

  BrthObj -> berth_alarm "alarm"
          with  name 'alarm',
          before [;
              Examine, Search:
                  if (self.alarmon) "A red light blinks above you, signaling the need to report for duty.";
                  "The alarm is off and shows no sign of activity.";
              SwFlip, SwitchOn:
                  return PSH();
              FlipOff, SwitchOff, Push, Use, UseItem:
                  if (self.alarmon) {
                      "Unfortunately, the Captain realized long ago that crewmen who switched off
                       their alarms sometimes went back to sleep and turned up late for their shifts.";
                  }
                  "The alarm was shut off automatically when you got out of your berth.";
          ],
          daemon [;
              if (self.alarmskip) {
                  self.alarmskip = false;
                  rtrue;
              }
              if (player in berth) "^The ~blip, blip, blip~ of your alarm is ringing insistently.";
          ],
          alarmon true,
          alarmskip false;
