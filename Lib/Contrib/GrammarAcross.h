! ==============================================================================
!   GRAMMAR:  Grammar table entries for the standard verbs library.
!
!   Supplied for use with Inform 6 -- Release 6/11 -- Serial number 040227
!
!   Copyright Graham Nelson 1993-2004 but freely usable (see manuals)
!
!   In your game file, Include three library files in this order:
!       Include "Parser";
!       Include "VerbLib";
!       Include "Grammar";
! ==============================================================================

System_file;

! ------------------------------------------------------------------------------
!  The "meta-verbs", commands to the game rather than in the game, come first:
! ------------------------------------------------------------------------------

Verb meta 'brief' 'normal'
    *                                           -> LMode1;
Verb meta 'verbose' 'long'
    *                                           -> LMode2;
Verb meta 'superbrief'
    *                                           -> LMode3;
Verb meta 'notify'
    *                                           -> NotifyOn
    * 'on'                                      -> NotifyOn
    * 'off'                                     -> NotifyOff;
Verb meta 'pronouns' 'nouns'
    *                                           -> Pronouns;
Verb meta 'quit' 'q//' 'die'
    *                                           -> Quit;
Verb meta 'recording'
    *                                           -> CommandsOn
    * 'on'                                      -> CommandsOn
    * 'off'                                     -> CommandsOff;
Verb meta 'replay'
    *                                           -> CommandsRead;
Verb meta 'restart'
    *                                           -> Restart;
Verb meta 'restore'
    *                                           -> Restore;
Verb meta 'save'
    *                                           -> Save;
Verb meta 'score'
    *                                           -> Score;
Verb meta 'fullscore' 'full'
    *                                           -> FullScore
    * 'score'                                   -> FullScore;
Verb meta 'script' 'transcript'
    *                                           -> ScriptOn
    * 'on'                                      -> ScriptOn
    * 'off'                                     -> ScriptOff;
Verb meta 'noscript' 'unscript'
    *                                           -> ScriptOff;
Verb meta 'verify'
    *                                           -> Verify;
Verb meta 'version'
    *                                           -> Version;

#Ifndef NO_PLACES;
Verb meta 'objects'
    *                                           -> Objects;
Verb meta 'places'
    *                                           -> Places;
#Endif; ! NO_PLACES

! ------------------------------------------------------------------------------
!  Debugging grammar
! ------------------------------------------------------------------------------

#Ifdef DEBUG;
Verb meta 'actions'
    *                                           -> ActionsOn
    * 'on'                                      -> ActionsOn
    * 'off'                                     -> ActionsOff;
Verb meta 'changes'
    *                                           -> ChangesOn
    * 'on'                                      -> ChangesOn
    * 'off'                                     -> ChangesOff;
Verb meta 'gonear'
    * noun                                      -> Gonear;
Verb meta 'goto'
    * number                                    -> Goto;
Verb meta 'random'
    *                                           -> Predictable;
Verb meta 'routines' 'messages'
    *                                           -> RoutinesOn
    * 'on'                                      -> RoutinesOn
    * 'off'                                     -> RoutinesOff;
Verb meta 'scope'
    *                                           -> Scope
    * noun                                      -> Scope;
Verb meta 'showobj'
    *                                           -> Showobj
    * number                                    -> Showobj
    * multi                                     -> Showobj;
Verb meta 'showverb'
    * special                                   -> Showverb;
Verb meta 'timers' 'daemons'
    *                                           -> TimersOn
    * 'on'                                      -> TimersOn
    * 'off'                                     -> TimersOff;
Verb meta 'trace'
    *                                           -> TraceOn
    * number                                    -> TraceLevel
    * 'on'                                      -> TraceOn
    * 'off'                                     -> TraceOff;
Verb meta 'abstract'
    * noun 'to' noun                            -> XAbstract;
Verb meta 'purloin'
    * multi                                     -> XPurloin;
Verb meta 'tree'
    *                                           -> XTree
    * noun                                      -> XTree;

#Ifdef TARGET_GLULX;
Verb meta 'glklist'
    *                                           -> Glklist;
#Endif; ! TARGET_

#Endif; ! DEBUG

! ------------------------------------------------------------------------------
!  And now the game verbs.
! ------------------------------------------------------------------------------

[ ADirection; if (noun in compass) rtrue; rfalse; ];

Verb 'ask'
    * creature 'about' topic                    -> Ask
    * creature 'for' noun                       -> AskFor
    * creature 'to' topic                       -> AskTo
    * 'that' creature topic                     -> AskTo;
Verb 'attack' 'break' 'crack' 'destroy'
     'fight' 'hit' 'kill' 'murder' 'punch'
     'smash' 'thump' 'torture' 'wreck'
    * noun                                      -> Attack
	* 'open' noun                               -> Attack
	* noun 'on' noun                            -> Attack
	* noun 'with' noun                          -> Attack;
Verb 'bother' 'curses' 'darn' 'drat'
    *                                           -> Mild
    * topic                                     -> Mild;
Verb 'buy' 'purchase'
    * noun                                      -> Buy;
Verb 'close' 'cover' 'shut'
    * noun                                      -> Close
    * 'up' noun                                 -> Close
    * 'off' noun                                -> SwitchOff;
Verb 'consult'
    * noun 'about' topic                        -> Consult
    * noun 'on' topic                           -> Consult;
Verb 'dig'
    * noun                                      -> Dig
    * noun 'with' held                          -> Dig;
Verb 'drop' 'discard'
    * multiheld                                 -> Drop
    * multiexcept 'in'/'into'/'down' noun       -> Insert
    * multiexcept 'on'/'onto' noun              -> Drop
    * held 'at'/'against'/'on'/'onto' noun      -> ThrowAt;
Verb 'eat'
    * noun                                      -> Eat;
Verb 'empty'
    * noun                                      -> Empty
    * 'out' noun                                -> Empty
    * noun 'out'                                -> Empty
    * noun 'to'/'into'/'on'/'onto' noun         -> EmptyT;
Verb 'enter' 'cross'
    *                                           -> GoIn
    * noun                                      -> Enter;
Verb 'examine' 'x//' 'check' 'describe' 'watch'
    * noun                                      -> Examine;
Verb 'exit' 'out' 'outside'
    *                                           -> Exit
    * noun                                      -> Exit;
Verb 'give' 'feed' 'offer' 'pay'
    * held 'to' creature                        -> Give
    * creature held                             -> Give reverse
    * 'over' held 'to' creature                 -> Give;
Verb 'go' 'run' 'walk'
    *                                           -> VagueGo
    * noun=ADirection                           -> Go
    * noun                                      -> Enter
    * 'into'/'in'/'inside'/'through' noun       -> Enter;
Verb 'in' 'inside'
    *                                           -> GoIn;
Verb 'insert'
    * multiexcept 'in'/'into' noun              -> Insert;
Verb 'inventory' 'invent' 'inv' 'i//'
    *                                           -> Inv
    * 'tall'                                    -> InvTall
    * 'wide'                                    -> InvWide;
Verb 'jump' 'hop' 'skip'
    *                                           -> Jump
    * 'over' noun                               -> JumpOver;
Verb 'kiss'
    * creature                                  -> Kiss;
Verb 'leave'
    *                                           -> VagueGo
    * noun=ADirection                           -> Go
    * noun                                      -> Exit
    * 'into'/'in'/'inside'/'through' noun       -> Enter;
Verb 'listen' 'hear'
    *                                           -> Listen
    * noun                                      -> Listen
    * 'to' noun                                 -> Listen;
Verb 'lock'
    * noun 'with' held                          -> Lock;
Verb 'no'
    *                                           -> No;
Verb 'peel'
    * noun                                      -> Take
    * 'off' noun                                -> Take;
Verb 'pick'
    * 'up' multi                                -> Take
    * multi 'up'                                -> Take;
Verb 'pray'
    *                                           -> Pray;
Verb 'pull' 'drag'
    * noun                                      -> Pull;
Verb 'rub' 'clean' 'dust' 'polish' 'scrub'
     'shine' 'sweep' 'wipe'
    * noun                                      -> Rub;
Verb 'search'
    * noun                                      -> Search;
Verb 'shed' 'disrobe' 'doff'
    * held                                      -> Disrobe;
Verb 'damn' 'fuck' 'sod'
    *                                           -> Strong
    * topic                                     -> Strong;
Verb 'sing'
    *                                           -> Sing;
Verb 'sleep' 'nap'
    *                                           -> Sleep;
Verb 'smell' 'sniff'
    *                                           -> Smell
    * noun                                      -> Smell;
Verb 'sorry'
    *                                           -> Sorry;
Verb 'squeeze' 'squash'
    * noun                                      -> Squeeze;
Verb 'swim' 'dive'
    *                                           -> Swim;
Verb 'swing'
    * noun                                      -> Swing
    * 'on' noun                                 -> Swing;
Verb 'taste'
    * noun                                      -> Taste;
Verb 'tell'
    * creature 'about' topic                    -> Tell
    * creature 'to' topic                       -> AskTo;
Verb 'touch' 'feel' 'fondle' 'grope'
    * noun                                      -> Touch;
Verb 'transfer'
    * noun 'to' noun                            -> Transfer;
Verb 'wear' 'don'
    * noun                                      -> Wear;
Verb 'yes' 'y//'
    *                                           -> Yes;
Verb 'unlock'
    * noun 'with' held                          -> Unlock;
Verb 'wait' 'z//'
    *                                           -> Wait;
Verb 'wake' 'awake' 'awaken'
    *                                           -> Wake
    * 'up'                                      -> Wake
    * creature                                  -> WakeOther
    * creature 'up'                             -> WakeOther
    * 'up' creature                             -> WakeOther;

! ------------------------------------------------------------------------------
!  This routine is no longer used here, but provided to help existing games
!  which use it as a general parsing routine:

[ ConTopic w;
    consult_from = wn;
    do w = NextWordStopped();
    until (w == -1 || (w == 'to' && action_to_be == ##Answer));
    wn--;
    consult_words = wn - consult_from;
    if (consult_words == 0) return -1;
    if (action_to_be == ##Answer or ##Ask or ##Tell) {
        w = wn; wn = consult_from; parsed_number = NextWord();
        if (parsed_number == 'the' && consult_words > 1) parsed_number = NextWord();
        wn = w;
        return 1;
    }
    return 0;
];

! ------------------------------------------------------------------------------
!  Final task: provide trivial routines if the user hasn't already:
! ------------------------------------------------------------------------------

#Stub AfterLife         0;
#Stub AfterPrompt       0;
#Stub Amusing           0;
#Stub BeforeParsing     0;
#Stub ChooseObjects     2;
#Stub DarkToDark        0;
#Stub DeathMessage      0;
#Stub GamePostRoutine   0;
#Stub GamePreRoutine    0;
#Stub InScope           1;
#Stub LookRoutine       0;
#Stub NewRoom           0;
#Stub ParseNumber       2;
#Stub ParserError       1;
#Stub PrintTaskName     1;
#Stub PrintVerb         1;
#Stub TimePasses        0;
#Stub UnknownVerb       1;

#Ifdef TARGET_GLULX;
#Stub HandleGlkEvent    2;
#Stub IdentifyGlkObject 4;
#Stub InitGlkWindow     1;
#Endif; ! TARGET_GLULX

#Ifndef PrintRank;
! Constant Make__PR;
! #Endif;
! #Ifdef Make__PR;
[ PrintRank; "."; ];
#Endif;

#Ifndef ParseNoun;
! Constant Make__PN;
! #Endif;
! #Ifdef Make__PN;
[ ParseNoun obj; obj = obj; return -1; ];
#Endif;

#Default Story 0;
#Default Headline 0;

#Ifdef INFIX;
#Include "infix";
#Endif;

! ==============================================================================

Constant LIBRARY_GRAMMAR;       ! for dependency checking

! ==============================================================================
