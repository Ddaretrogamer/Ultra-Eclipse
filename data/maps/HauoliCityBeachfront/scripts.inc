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
	faceplayer
# 51 "data/maps/HauoliCityBeachfront/scripts.pory"
	playse SE_LEDGE
# 52 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_1
# 53 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitse
# 54 "data/maps/HauoliCityBeachfront/scripts.pory"
	playse SE_LEDGE
# 55 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitse
# 56 "data/maps/HauoliCityBeachfront/scripts.pory"
	waitmovement 0
# 57 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_Trigger_EnterBeachfront_Text_2
# 61 "data/maps/HauoliCityBeachfront/scripts.pory"
	release
	end


HauoliCityBeachfront_WingullNPCguy::
# 66 "data/maps/HauoliCityBeachfront/scripts.pory"
	lock
# 67 "data/maps/HauoliCityBeachfront/scripts.pory"
	faceplayer
# 68 "data/maps/HauoliCityBeachfront/scripts.pory"
	msgbox HauoliCityBeachfront_WingullNPCguy_Text_0
# 71 "data/maps/HauoliCityBeachfront/scripts.pory"
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

HauoliCityBeachfront_WingullNPCguy_Text_0:
# 68 "data/maps/HauoliCityBeachfront/scripts.pory"
	.string "The Wingull fly…\n"
	.string "And their droppings fall…\l"
	.string "Ah, the beauty of nature!$"
