HauoliCityBeachfront_MapScripts::
	.byte 0


HauoliCityBeachfront_Trigger_EnterBeachfront::
# 4 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 5 "data/maps/HauoliCityBeachfront/scripts.pory"
	playse SE_PIN
# 6 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement beachfront_alola_girl, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_0
# 7 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 8 "data/maps/HauoliCityBeachfront/scripts.pory"
	getplayerxy VAR_TEMP_A, VAR_TEMP_B
# 9 "data/maps/HauoliCityBeachfront/scripts.pory"
	compare VAR_TEMP_B, 21
	goto_if_eq HauoliCityBeachfront_Trigger_EnterBeachfront_2
# 13 "data/maps/HauoliCityBeachfront/scripts.pory"
	compare VAR_TEMP_B, 22
	goto_if_eq HauoliCityBeachfront_Trigger_EnterBeachfront_3
# 17 "data/maps/HauoliCityBeachfront/scripts.pory"
	compare VAR_TEMP_B, 23
	goto_if_eq HauoliCityBeachfront_Trigger_EnterBeachfront_4
# 22 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement LOCALID_PLAYER, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_4
# 23 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
HauoliCityBeachfront_Trigger_EnterBeachfront_1:
# 25 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_0, MSGBOX_AUTOCLOSE
# 32 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement beachfront_alola_girl, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_5
# 33 "data/maps/HauoliCityBeachfront/scripts.pory"
	playse SE_LEDGE
# 34 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_1
# 35 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitse
# 36 "data/maps/HauoliCityBeachfront/scripts.pory"
	playse SE_LEDGE
# 37 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitse
# 38 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 39 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_2
# 43 "data/maps/HauoliCityBeachfront/scripts.pory"
	setvar VAR_IKITOWN_STATE, 25
# 44 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end

HauoliCityBeachfront_Trigger_EnterBeachfront_2:
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement LOCALID_PLAYER, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_1
# 11 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
	goto HauoliCityBeachfront_Trigger_EnterBeachfront_1

HauoliCityBeachfront_Trigger_EnterBeachfront_3:
# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement LOCALID_PLAYER, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_2
# 15 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
	goto HauoliCityBeachfront_Trigger_EnterBeachfront_1

HauoliCityBeachfront_Trigger_EnterBeachfront_4:
# 18 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement LOCALID_PLAYER, HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_3
# 19 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
	goto HauoliCityBeachfront_Trigger_EnterBeachfront_1


HauoliCityBeachfront_Trigger_AlolaNPC1::
# 49 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 50 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement beachfront_alola_girl, HauoliCityBeachfront_Trigger_AlolaNPC1_Movement_0
# 51 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 53 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_AlolaNPC1_Text_0
# 54 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_2
# 58 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_WingullNPCguy::
# 63 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 64 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 65 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WingullNPCguy_Text_0
# 68 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_WomanInFrontOfBuilding::
# 73 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 74 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 75 "data/maps/HauoliCityBeachfront/scripts.pory"
	goto_if_unset FLAG_HAUOLI_BEACHFRONT_NPC_POTION, HauoliCityBeachfront_WomanInFrontOfBuilding_2
# 101 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_4
HauoliCityBeachfront_WomanInFrontOfBuilding_1:
# 104 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end

HauoliCityBeachfront_WomanInFrontOfBuilding_2:
# 76 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_0
# 80 "data/maps/HauoliCityBeachfront/scripts.pory"
	dynmultichoice 22, 8, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, HauoliCityBeachfront_WomanInFrontOfBuilding_Text_1, HauoliCityBeachfront_WomanInFrontOfBuilding_Text_2
# 81 "data/maps/HauoliCityBeachfront/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq HauoliCityBeachfront_WomanInFrontOfBuilding_5
# 90 "data/maps/HauoliCityBeachfront/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq HauoliCityBeachfront_WomanInFrontOfBuilding_6
	goto HauoliCityBeachfront_WomanInFrontOfBuilding_1

HauoliCityBeachfront_WomanInFrontOfBuilding_5:
# 82 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_3
# 85 "data/maps/HauoliCityBeachfront/scripts.pory"
	giveitem ITEM_POTION, 1
# 86 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_4
# 88 "data/maps/HauoliCityBeachfront/scripts.pory"
	setflag FLAG_HAUOLI_BEACHFRONT_NPC_POTION
	goto HauoliCityBeachfront_WomanInFrontOfBuilding_1

HauoliCityBeachfront_WomanInFrontOfBuilding_6:
# 91 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_3
# 94 "data/maps/HauoliCityBeachfront/scripts.pory"
	giveitem ITEM_POTION, 1
# 95 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WomanInFrontOfBuilding_Text_4
# 97 "data/maps/HauoliCityBeachfront/scripts.pory"
	setflag FLAG_HAUOLI_BEACHFRONT_NPC_POTION
	goto HauoliCityBeachfront_WomanInFrontOfBuilding_1


HauoliCityBeachfront_MovesGuy::
# 109 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 110 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 111 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_MovesGuy_Text_0
# 119 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_TanningWoman::
# 124 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 125 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 126 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_TanningWoman_Text_0
# 133 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_Pyukumuku::
# 138 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 139 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 140 "data/maps/HauoliCityBeachfront/scripts.pory"
	playmoncry SPECIES_PYUKUMUKU, 0
# 141 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Pyukumuku_Text_0
# 142 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmoncry
# 143 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_CoupleConversation::
# 148 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 149 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement hauolibeach_man, HauoliCityBeachfront_CoupleConversation_Movement_0
# 150 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 151 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_CoupleConversation_Text_0, MSGBOX_AUTOCLOSE
# 152 "data/maps/HauoliCityBeachfront/scripts.pory"
	applymovement hauolibeach_girl, HauoliCityBeachfront_CoupleConversation_Movement_1
# 153 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 154 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_CoupleConversation_Text_1, MSGBOX_AUTOCLOSE
# 161 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_SlowpokeNPC::
# 166 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 167 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 168 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_SlowpokeNPC_Text_0
# 178 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_Slowpoke::
# 183 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 184 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 185 "data/maps/HauoliCityBeachfront/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, 0
# 186 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Slowpoke_Text_0
# 187 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmoncry
# 188 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


# 6 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_0:
# 6 "data/maps/HauoliCityBeachfront/scripts.pory"
	face_player
# 6 "data/maps/HauoliCityBeachfront/scripts.pory"
	emote_question_mark
	step_end

# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_1:
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
# 10 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
	step_end

# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_2:
# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
# 14 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
	step_end

# 18 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_3:
# 18 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_down
# 18 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
# 18 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
	step_end

# 22 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_4:
# 22 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
# 22 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_left
	step_end

# 32 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_EnterBeachfront_Movement_5:
# 32 "data/maps/HauoliCityBeachfront/scripts.pory"
	jump_in_place_right
# 32 "data/maps/HauoliCityBeachfront/scripts.pory"
	jump_in_place_right
	step_end

# 50 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_Trigger_AlolaNPC1_Movement_0:
# 50 "data/maps/HauoliCityBeachfront/scripts.pory"
	face_player
	step_end

# 149 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_CoupleConversation_Movement_0:
# 149 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_in_place_right
# 149 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_in_place_right
	step_end

# 152 "data/maps/HauoliCityBeachfront/scripts.pory"
HauoliCityBeachfront_CoupleConversation_Movement_1:
# 152 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_in_place_left
# 152 "data/maps/HauoliCityBeachfront/scripts.pory"
	walk_in_place_left
	step_end

HauoliCityBeachfront_Trigger_EnterBeachfront_Text_0:
# 25 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Hey, you…\p"
	.string "You've come to Alola from someplace far\n"
	.string "off, haven't you? I can tell!\p"
	.string "Then let me teach you the proper way\n"
	.string "to greet someone in Alola!$"

HauoliCityBeachfront_Trigger_EnterBeachfront_Text_1:
# 34 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Alola!$"

HauoliCityBeachfront_Trigger_EnterBeachfront_Text_2:
# 39 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "You give it a try, too! Just like that:\n"
	.string "“Alola!”\p"
	.string "You'll make more friends if you say it!$"

HauoliCityBeachfront_Trigger_AlolaNPC1_Text_0:
# 53 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Alola!{PAUSE 15}$"

HauoliCityBeachfront_WingullNPCguy_Text_0:
# 65 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "The Wingull fly…\n"
	.string "And their droppings fall…\l"
	.string "Ah, the beauty of nature!$"

HauoliCityBeachfront_WomanInFrontOfBuilding_Text_0:
# 76 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Alola!\p"
	.string "You here on vacation, young friend?\n"
	.string "Or are you perhaps a trial-goer?$"

HauoliCityBeachfront_WomanInFrontOfBuilding_Text_1:
# 80 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "I guess I'm a trial-goer$"

HauoliCityBeachfront_WomanInFrontOfBuilding_Text_2:
# 80 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "I'm just sightseeing$"

HauoliCityBeachfront_WomanInFrontOfBuilding_Text_3:
# 82 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Well, you are most welcome to Alola\n"
	.string "either way!\l"
	.string "In fact, why don't you take this?$"

HauoliCityBeachfront_WomanInFrontOfBuilding_Text_4:
# 86 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Enjoy Hau'oli! Enjoy Alola!\n"
	.string "And most of all, enjoy Pokémon!$"

HauoliCityBeachfront_MovesGuy_Text_0:
# 111 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "If you want to study Pokémon moves…\p"
	.string "I'd have a look at those unbelievable\n"
	.string "moves that the island kahuna's\l"
	.string "Pokémon can use!\p"
	.string "There's gotta be some kinda secret to\n"
	.string "why they are so amazingly strong.$"

HauoliCityBeachfront_TanningWoman_Text_0:
# 126 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Ground-type moves won't reach Flying-\n"
	.string "type Pokémon, right?\l"
	.string "So they don't do any damage to them…\p"
	.string "But Water-type moves will wash away\n"
	.string "any Ground types.\l"
	.string "They're very effective at that.$"

HauoliCityBeachfront_Pyukumuku_Text_0:
# 141 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Pyu!$"

HauoliCityBeachfront_CoupleConversation_Text_0:
# 151 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Look! Catch!$"

HauoliCityBeachfront_CoupleConversation_Text_1:
# 154 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Would you stop?\p"
	.string "I know they're squishy, but that's no\n"
	.string "reason to throw Pyukumuku at me!\p"
	.string "Throw a Poké Ball if you must throw\n"
	.string "something!$"

HauoliCityBeachfront_SlowpokeNPC_Text_0:
# 168 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Slowpoke really has its own tempo,\n"
	.string "huh?\p"
	.string "It's never confused by other Pokémon's\n"
	.string "moves.\l"
	.string "It's too slow to get confused…or to\l"
	.string "take a hint.\p"
	.string "Leave me alone already, would you,\n"
	.string "Slowpoke?$"

HauoliCityBeachfront_Slowpoke_Text_0:
# 186 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "Slo-o-o-ow…$"
