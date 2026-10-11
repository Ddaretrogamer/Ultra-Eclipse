TrainerSchool2F_MapScripts::
	.byte 0


TeachersLoungeDoor::
# 4 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_DOOR
# 5 "data/maps/TrainerSchool2F/scripts.pory"
	warp MAP_TRAINER_SCHOOL2FTEACHERS_LOUNGE, 0
	end


ClassroomDoor2F::
# 10 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_DOOR
# 11 "data/maps/TrainerSchool2F/scripts.pory"
	warp MAP_TRAINER_SCHOOL2FCLASSROOM, 0
	end


TrainerSchool2F_BattleVsTeacher::
# 16 "data/maps/TrainerSchool2F/scripts.pory"
	lock
# 17 "data/maps/TrainerSchool2F/scripts.pory"
	faceplayer
# 18 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_0, MSGBOX_YESNO
# 28 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TrainerSchool2F_BattleVsTeacher_1
# 204 "data/maps/TrainerSchool2F/scripts.pory"
	release
	end

TrainerSchool2F_BattleVsTeacher_1:
# 29 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_STARTER_MON, 0
	goto_if_eq TrainerSchool2F_BattleVsTeacher_5
TrainerSchool2F_BattleVsTeacher_4:
# 40 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_STARTER_MON, 1
	goto_if_eq TrainerSchool2F_BattleVsTeacher_8
TrainerSchool2F_BattleVsTeacher_7:
# 51 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_STARTER_MON, 2
	goto_if_eq TrainerSchool2F_BattleVsTeacher_11
TrainerSchool2F_BattleVsTeacher_10:
# 62 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_5
# 69 "data/maps/TrainerSchool2F/scripts.pory"
	giveitem ITEM_GREAT_BALL, 5
# 70 "data/maps/TrainerSchool2F/scripts.pory"
	startcutscene CUTSCENE_TRAINER_SCHOOL_TEACHER_BATTLE
# 71 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_6, MSGBOX_AUTOCLOSE
# 74 "data/maps/TrainerSchool2F/scripts.pory"
	setobjectxy trainerschool2f_kukui, 18, 9
# 75 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_DOOR
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_kukui, TrainerSchool2F_BattleVsTeacher_Movement_0
# 77 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 78 "data/maps/TrainerSchool2F/scripts.pory"
	setobjectxy trainerschool2f_ilima, 18, 9
# 79 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_DOOR
# 80 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_ilima, TrainerSchool2F_BattleVsTeacher_Movement_1
# 81 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 82 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_7
# 83 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_8
# 85 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement LOCALID_PLAYER, TrainerSchool2F_BattleVsTeacher_Movement_2
# 86 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_teacher, TrainerSchool2F_BattleVsTeacher_Movement_2
# 87 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 88 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_kukui, TrainerSchool2F_BattleVsTeacher_Movement_3
# 89 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 90 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_9
# 91 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_ilima, TrainerSchool2F_BattleVsTeacher_Movement_3
# 92 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 93 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_10
# 94 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_11
# 103 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_kukui, TrainerSchool2F_BattleVsTeacher_Movement_3
# 104 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 105 "data/maps/TrainerSchool2F/scripts.pory"
	checkplayergender
# 106 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq TrainerSchool2F_BattleVsTeacher_14
# 116 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_7
# 117 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_13
TrainerSchool2F_BattleVsTeacher_13:
# 124 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_ilima, TrainerSchool2F_BattleVsTeacher_Movement_3
# 125 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 126 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_10
# 127 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_14, MSGBOX_AUTOCLOSE
# 151 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_ilima, TrainerSchool2F_BattleVsTeacher_Movement_4
# 152 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 153 "data/maps/TrainerSchool2F/scripts.pory"
	setobjectxy trainerschool2f_ilima, 16, 7
# 154 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_EXIT
# 155 "data/maps/TrainerSchool2F/scripts.pory"
	waitse
# 156 "data/maps/TrainerSchool2F/scripts.pory"
	delay 30
# 157 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_teacher, TrainerSchool2F_BattleVsTeacher_Movement_5
# 158 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_LEDGE
# 159 "data/maps/TrainerSchool2F/scripts.pory"
	waitse
# 160 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_LEDGE
# 161 "data/maps/TrainerSchool2F/scripts.pory"
	waitse
# 162 "data/maps/TrainerSchool2F/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 163 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_15
# 167 "data/maps/TrainerSchool2F/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 168 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_kukui, TrainerSchool2F_BattleVsTeacher_Movement_3
# 169 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 170 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_7
# 171 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_16
# 173 "data/maps/TrainerSchool2F/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 174 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_17
# 176 "data/maps/TrainerSchool2F/scripts.pory"
	playse SE_DING_DONG
# 177 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_kukui, TrainerSchool2F_BattleVsTeacher_Movement_6
# 178 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement trainerschool2f_teacher, TrainerSchool2F_BattleVsTeacher_Movement_6
# 179 "data/maps/TrainerSchool2F/scripts.pory"
	applymovement LOCALID_PLAYER, TrainerSchool2F_BattleVsTeacher_Movement_6
# 180 "data/maps/TrainerSchool2F/scripts.pory"
	waitmovement 0
# 181 "data/maps/TrainerSchool2F/scripts.pory"
	waitse
# 182 "data/maps/TrainerSchool2F/scripts.pory"
	delay 15
# 183 "data/maps/TrainerSchool2F/scripts.pory"
	checkplayergender
# 184 "data/maps/TrainerSchool2F/scripts.pory"
	endcutscene
# 185 "data/maps/TrainerSchool2F/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainerSchool2F_BattleVsTeacher_18
# 192 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_19
TrainerSchool2F_BattleVsTeacher_17:
# 197 "data/maps/TrainerSchool2F/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 198 "data/maps/TrainerSchool2F/scripts.pory"
	setflag FLAG_HIDE_TRAINERSCHOOL_LILLIE_KUKUI
# 199 "data/maps/TrainerSchool2F/scripts.pory"
	setvar VAR_IKITOWN_STATE, 23
# 200 "data/maps/TrainerSchool2F/scripts.pory"
	warpsilent MAP_ROUTE1N, 19, 14
# 201 "data/maps/TrainerSchool2F/scripts.pory"
	waitstate
	return

TrainerSchool2F_BattleVsTeacher_5:
# 30 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_1
# 38 "data/maps/TrainerSchool2F/scripts.pory"
	trainerbattle_no_intro TRAINER_SCHOOLTEACHER_EMILY_LITTEN, TrainerSchool2F_BattleVsTeacher_Text_2
	goto TrainerSchool2F_BattleVsTeacher_4

TrainerSchool2F_BattleVsTeacher_8:
# 41 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_3
# 49 "data/maps/TrainerSchool2F/scripts.pory"
	trainerbattle_no_intro TRAINER_SCHOOLTEACHER_EMILY_POPPLIO, TrainerSchool2F_BattleVsTeacher_Text_2
	goto TrainerSchool2F_BattleVsTeacher_7

TrainerSchool2F_BattleVsTeacher_11:
# 52 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_4
# 60 "data/maps/TrainerSchool2F/scripts.pory"
	trainerbattle_no_intro TRAINER_SCHOOLTEACHER_EMILY_ROWLET, TrainerSchool2F_BattleVsTeacher_Text_2
	goto TrainerSchool2F_BattleVsTeacher_10

TrainerSchool2F_BattleVsTeacher_14:
# 107 "data/maps/TrainerSchool2F/scripts.pory"
	speakername TrainerSchool2F_BattleVsTeacher_Text_7
# 108 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_12
	goto TrainerSchool2F_BattleVsTeacher_13

TrainerSchool2F_BattleVsTeacher_18:
# 186 "data/maps/TrainerSchool2F/scripts.pory"
	msgbox TrainerSchool2F_BattleVsTeacher_Text_18
	goto TrainerSchool2F_BattleVsTeacher_17


TrainersSchool_Teacher_Battle_Skip::
# 210 "data/maps/TrainerSchool2F/scripts.pory"
	closemessage
# 211 "data/maps/TrainerSchool2F/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 212 "data/maps/TrainerSchool2F/scripts.pory"
	setflag FLAG_HIDE_TRAINERSCHOOL_LILLIE_KUKUI
# 213 "data/maps/TrainerSchool2F/scripts.pory"
	setvar VAR_IKITOWN_STATE, 23
# 214 "data/maps/TrainerSchool2F/scripts.pory"
	special StopAllObjectMovements
# 215 "data/maps/TrainerSchool2F/scripts.pory"
	special CloseScriptMenus
# 216 "data/maps/TrainerSchool2F/scripts.pory"
	warpsilent MAP_ROUTE1N, 19, 14
# 217 "data/maps/TrainerSchool2F/scripts.pory"
	waitstate
# 218 "data/maps/TrainerSchool2F/scripts.pory"
	release
	end


# 76 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_0:
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	walk_down
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	walk_down
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	delay_16
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	delay_16
# 76 "data/maps/TrainerSchool2F/scripts.pory"
	face_right
	step_end

# 80 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_1:
# 80 "data/maps/TrainerSchool2F/scripts.pory"
	walk_down
# 80 "data/maps/TrainerSchool2F/scripts.pory"
	face_right
	step_end

# 85 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_2:
# 85 "data/maps/TrainerSchool2F/scripts.pory"
	face_left
	step_end

# 88 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_3:
# 88 "data/maps/TrainerSchool2F/scripts.pory"
	walk_in_place_right
# 88 "data/maps/TrainerSchool2F/scripts.pory"
	walk_in_place_right
	step_end

# 151 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_4:
# 151 "data/maps/TrainerSchool2F/scripts.pory"
	walk_up
	step_end

# 157 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_5:
# 157 "data/maps/TrainerSchool2F/scripts.pory"
	jump_in_place_left
# 157 "data/maps/TrainerSchool2F/scripts.pory"
	jump_in_place_left
	step_end

# 177 "data/maps/TrainerSchool2F/scripts.pory"
TrainerSchool2F_BattleVsTeacher_Movement_6:
# 177 "data/maps/TrainerSchool2F/scripts.pory"
	emote_exclamation_mark
# 177 "data/maps/TrainerSchool2F/scripts.pory"
	face_up
	step_end

TrainerSchool2F_BattleVsTeacher_Text_0:
# 18 "data/maps/TrainerSchool2F/scripts.pory"
	.string "{PLAYER}…\p"
	.string "I can't believe that you{PAUSE 10}.{PAUSE 10}.{PAUSE 10}.\n"
	.string "beat all of my students! Fantastic!\p"
	.string "After seeing such a performance, I\n"
	.string "think I'd like to battle you myself!\p"
	.string "What do you say?\n"
	.string "{PAUSE 15}Are you ready to take me on?$"

TrainerSchool2F_BattleVsTeacher_Text_1:
# 30 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Good.\p"
	.string "I heard about you from Professor\n"
	.string "Kukui.\p"
	.string "I'll be challenging you with a\n"
	.string "Pokémon that has a type advantage\l"
	.string "against that Rowlet you chose!$"

TrainerSchool2F_BattleVsTeacher_Text_2:
# 38 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Sensational!$"

TrainerSchool2F_BattleVsTeacher_Text_3:
# 41 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Good.\p"
	.string "I heard about you from Professor\n"
	.string "Kukui.\p"
	.string "I'll be challenging you with a\n"
	.string "Pokémon that has a type advantage\l"
	.string "against that Litten you chose!$"

TrainerSchool2F_BattleVsTeacher_Text_4:
# 52 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Good.\p"
	.string "I heard about you from Professor\n"
	.string "Kukui.\p"
	.string "I'll be challenging you with a\n"
	.string "Pokémon that has a type advantage\l"
	.string "against that Popplio you chose!$"

TrainerSchool2F_BattleVsTeacher_Text_5:
# 62 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Nice! Maybe you'd like to take over\n"
	.string "as teacher here for me!\p"
	.string "All joking aside, though, I do want you\n"
	.string "to take these from me…\p"
	.string "It's a little reward for beating me.$"

TrainerSchool2F_BattleVsTeacher_Text_6:
# 71 "data/maps/TrainerSchool2F/scripts.pory"
	.string "They're Great Balls. Great Balls are\n"
	.string "better at catching Pokémon than\l"
	.string "normal Poké Balls.$"

TrainerSchool2F_BattleVsTeacher_Text_7:
# 82 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Kukui$"

TrainerSchool2F_BattleVsTeacher_Text_8:
# 83 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Know your Pokémon their moves.\n"
	.string "Those are the basics of being a Trainer!$"

TrainerSchool2F_BattleVsTeacher_Text_9:
# 90 "data/maps/TrainerSchool2F/scripts.pory"
	.string "How about it?$"

TrainerSchool2F_BattleVsTeacher_Text_10:
# 93 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Ilima$"

TrainerSchool2F_BattleVsTeacher_Text_11:
# 94 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Greetings!\n"
	.string "{COLOR RED}Captain {COLOR DARK_GRAY}Ilima here.\p"
	.string "I couldn't help but observe your\n"
	.string "battles.\p"
	.string "You looked so very delightful in\n"
	.string "battle that I had no choice but to\l"
	.string "summon you here.$"

TrainerSchool2F_BattleVsTeacher_Text_12:
# 108 "data/maps/TrainerSchool2F/scripts.pory"
	.string "This is {PLAYER}, who moved here to\n"
	.string "Alola from the Kanto region.\p"
	.string "He's got a real sense for how to use\n"
	.string "moves, and I think he's gonna go far\l"
	.string "as a trainer, yeah!$"

TrainerSchool2F_BattleVsTeacher_Text_13:
# 117 "data/maps/TrainerSchool2F/scripts.pory"
	.string "This is {PLAYER}, who moved here to\n"
	.string "Alola from the Kanto region.\p"
	.string "She's got a real sense for how to use\n"
	.string "moves, and I think she's gonna go far\l"
	.string "as a trainer, yeah!$"

TrainerSchool2F_BattleVsTeacher_Text_14:
# 127 "data/maps/TrainerSchool2F/scripts.pory"
	.string "I see!\n"
	.string "Then welcome, newcomer.\p"
	.string "I look forward to seeing the brilliance\n"
	.string "of your moves in my {COLOR RED}trial{COLOR DARK_GRAY}.\p"
	.string "Indeed! We captains are the ones who\n"
	.string "conduct the trails you will face on\l"
	.string "your way to challenging the island\l"
	.string "kahuna.\p"
	.string "My trial is held in Verdant Cavern.\n"
	.string "The trial of Captain Ilima.\p"
	.string "You can find Pokémon living everywhere,\n"
	.string "even in the patches of tall grass in\l"
	.string "Hau'oli City.\p"
	.string "Perhaps you'll want to fill out your\n"
	.string "team a bit before attempting my\l"
	.string "trial?\p"
	.string "I sincerely look forward to your\n"
	.string "challenge.$"

TrainerSchool2F_BattleVsTeacher_Text_15:
# 163 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Oh yeah!\p"
	.string "I reported to the folks upstairs about\n"
	.string "that Tauros blocking the road.$"

TrainerSchool2F_BattleVsTeacher_Text_16:
# 171 "data/maps/TrainerSchool2F/scripts.pory"
	.string "That guy's Tauros is pretty much a\n"
	.string "celebrity here on Melemele, you know?$"

TrainerSchool2F_BattleVsTeacher_Text_17:
# 174 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Well, I guess it's time that we dismiss\n"
	.string "you from school, {PLAYER}$"

TrainerSchool2F_BattleVsTeacher_Text_18:
# 186 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Attention, all students…\p"
	.string "{PLAYER} has completed his lesson at\n"
	.string "the Trainers' School!$"

TrainerSchool2F_BattleVsTeacher_Text_19:
# 192 "data/maps/TrainerSchool2F/scripts.pory"
	.string "Attention, all students…\p"
	.string "{PLAYER} has completed her lesson at\n"
	.string "the Trainers' School!$"
