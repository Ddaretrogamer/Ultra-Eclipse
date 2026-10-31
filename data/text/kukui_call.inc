@ New Game opens to computer background
@ Video Call app icon starts ringing
@ After 3 rings (rings continue while YouHaveACall is visible)
gText_Kukui_YouHaveACall::
	.string "You have a message from the Alola\n"
	.string "region's own Professor Kukui!\p"
	.string " $"

@ After a beat of no ringing, the Video Call app icon is "selected", and the Call Window "launches"
@ Via a 2-stage fade from white, Call_Background1 and Kukui1 become visible
@ After a beat, Kukui1 transitions to Kukui2
@ While JustASec begins printing, Call_Background1 and Kukui2 transition to Call_Background2 and Kukui3
gText_Kukui_JustASec::
	.string "Hang on, now.\n"
	.string "Gimme just a sec...\p"
	.string " $"

@ Kukui3 to Kukui4
@ While HeyThere is printing, Kukui4 to Kukui5
gText_Kukui_HeyThere::
	.string "Hey there! Good afternoon!\p"
	.string "So the day has finally come that you're\n"
	.string "moving to Alola!\p"
	.string " $"

@ Kukui5 to Kukui6
@ As AlolaIsARegion is printing, *maybe* show some region map visual? - try to match, rotate through island maps, or go to map view scene?
gText_Kukui_AlolaIsARegion::
	.string "Alola is a region made up of several\n"
	.string "islands.\p"
	.string "That could be the reason the region is\n"
	.string "chock full of nothin' but rare\l"
	.string "Pokémon, yeah!\p"
	.string " $"

@ Kukui6 to Kukui5
@ As CoolPokemon is printing, Kukui5 to Kukui7
gText_Kukui_CoolPokemon::
	.string "There's no shortage of cool Pokémon\n"
	.string "out here in Alola, either!\p"
	.string "Such mysterious creatures!\p"
	.string " $"

@ Kukui7 to Kukui8 (*maybe* a blue light and sparkles?)
@ Kukui8 to Kukui5a (shifted 2 tiles left) and Rockruff appears (*maybe* animate it falling into frame?)
@ AllOver prints
gText_Kukui_AllOver::
	.string "You'll find 'em all over.\n"
	.string "In the grass, in the caves,\l"
	.string "in the sky and sea…\p"
	.string " $"

@ As LoveOurPokemon prints, Kukui5a to Kukui6 and Rockruff to Rockruff_a (hFlipped within the call window) (this arrangement is an alternative to needing more but more faithful art)
@ (might like new art specifically for "I'll play with you later, so cool your jets!")
gText_Kukui_LoveOurPokemon::
	.string "Here in Alola we love our Pokémon,\n"
	.string "and we depend on them heaps, too.\p"
	.string "Some of us even battle with 'em, if\n"
	.string "we call ourselves Pokémon Trainers!\p"
	.string "Rockruff! I'll play with you later,\n"
	.string "so cool your jets!\p"
	.string " $"

@ Kukui6 to Kukui5 and Rockruff_a disappears
@ AndYouAre prints
gText_Kukui_AndYouAre::
	.string "All right.\p" 
	.string "I gotta ask you some questions\n"
	.string "about yourself so I can introduce\l"
	.string "you to everybody!\p"
	.string " $"

@ Fades to black, switches to Photo Selection screen
@ OR just replace Call_Background2 and Kukui5 with it?
gText_Kukui_WhichPhoto::
	.string "So which photo should I use for your\n"
	.string "Trainer Passport?$"

@ Photo Selection screen to multichoice w/ selected photo
gText_Kukui_ChoiceOK::
	.string "You OK with the one you chose, yeah?$"

@ Photo Selection screen disappears
@ After WhatsYourName prints, switches to Naming Screen
gText_Kukui_WhatsYourName::
	.string "All right then, I'll let you\n"
	.string "spell out your name for me.\p $"

@ Naming screen multichoice
gText_Kukui_SoItsPlayer::
	.string "So, you go by {PLAYER}{KUN}?$"

@ Fades to black, switches to Computer_Background1, Call_Background2, and Kukui5, now with selected photo sprite visible
gText_Kukui_YourePlayer::
	.string "10-4, good buddy! I'll let everybody out\n"
	.string "here know you're on your way!\p"
	.string " $"

@ Kukui5a (shifts 2 tiles left), Rockruff appears
gText_Kukui_AreYouReady::
	.string "{PLAYER}{KUN}!\p"
	.string "Yeah, that's a name that hits you like a\n"
	.string "Trop Kick right to the head! Woo!\p"
	.string "Can't wait to see you here in person\n"
	.string "then, cousin!\p"
	.string " $"
@ Kukui5a to Kukui4a and Rockruff to Rockruff_b (Rockruff hFlipped, both shifted so 1 non-empty tile-column of each is offscreen)
@ After a beat, Rockruff_b disappears and Kukui4a to Kukui3
@ Another beat, Call Window closes
@ One last beat, scene fades to black, game starts

gText_Kukui_Nameplate::
	.string "Kukui$"
