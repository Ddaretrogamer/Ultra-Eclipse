Route1N_MapScripts::
	.byte 0


TrainerSchoolSign::
# 5 "data/maps/Route1N/scripts.pory"
	lock
# 6 "data/maps/Route1N/scripts.pory"
	msgbox TrainerSchoolSign_Text_0
# 10 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_Intro::
# 15 "data/maps/Route1N/scripts.pory"
	lock
# 16 "data/maps/Route1N/scripts.pory"
	getplayerxy VAR_TEMP_3, VAR_TEMP_4
# 17 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_3, 20
	goto_if_eq TrainersSchool_Intro_8
TrainersSchool_Intro_6:
# 21 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_3, 18
	goto_if_eq TrainersSchool_Intro_5
TrainersSchool_Intro_4:
# 26 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_Intro_Movement_2
# 27 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
TrainersSchool_Intro_1:
# 29 "data/maps/Route1N/scripts.pory"
	setvar VAR_IKITOWN_STATE, 22
# 30 "data/maps/Route1N/scripts.pory"
	startcutscene CUTSCENE_TRAINER_SCHOOL_INTRO
# 31 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_3
# 32 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 33 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_kukui, TrainersSchool_Intro_Movement_4
# 34 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_kukui
# 35 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Intro_Text_0
# 36 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_1, MSGBOX_AUTOCLOSE
# 42 "data/maps/Route1N/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 43 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 44 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_teacher, TrainersSchool_Intro_Movement_5
# 45 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_teacher
# 46 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_2, MSGBOX_AUTOCLOSE
# 48 "data/maps/Route1N/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 49 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Intro_Text_0
# 50 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_3
# 52 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_kukui, TrainersSchool_Intro_Movement_6
# 53 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 54 "data/maps/Route1N/scripts.pory"
	waitse
# 55 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 56 "data/maps/Route1N/scripts.pory"
	waitse
# 57 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 58 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_4
# 69 "data/maps/Route1N/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 70 "data/maps/Route1N/scripts.pory"
	giveitem ITEM_EXP_SHARE, 1
# 71 "data/maps/Route1N/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 72 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Intro_Text_0
# 73 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_5, MSGBOX_AUTOCLOSE
# 76 "data/maps/Route1N/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 77 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_teacher, TrainersSchool_Intro_Movement_4
# 78 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_teacher
# 79 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_6
# 88 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_teacher, TrainersSchool_Intro_Movement_6
# 89 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 90 "data/maps/Route1N/scripts.pory"
	waitse
# 91 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 92 "data/maps/Route1N/scripts.pory"
	waitse
# 93 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_7, MSGBOX_AUTOCLOSE
# 94 "data/maps/Route1N/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 95 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_teacher, TrainersSchool_Intro_Movement_7
# 96 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_teacher
# 97 "data/maps/Route1N/scripts.pory"
	removeobject trainerschool_teacher
# 98 "data/maps/Route1N/scripts.pory"
	setflag FLAG_HIDE_TRAINERSCHOOL_TEACHER
# 99 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_kukui, TrainersSchool_Intro_Movement_4
# 100 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_kukui
# 101 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Intro_Text_0
# 102 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_8
# 105 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_8
# 106 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 107 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_9, MSGBOX_AUTOCLOSE
# 118 "data/maps/Route1N/scripts.pory"
	endcutscene
# 119 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_kukui, TrainersSchool_Intro_Movement_6
# 120 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 121 "data/maps/Route1N/scripts.pory"
	waitse
# 122 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 123 "data/maps/Route1N/scripts.pory"
	waitse
# 124 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Intro_Text_10, MSGBOX_AUTOCLOSE
# 125 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_Intro_2:
# 18 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_Intro_Movement_0
# 19 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_Intro_1

TrainersSchool_Intro_3:
# 22 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_Intro_Movement_1
# 23 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_Intro_1

TrainersSchool_Intro_5:
# 21 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_4, 23
	goto_if_eq TrainersSchool_Intro_3
	goto TrainersSchool_Intro_4

TrainersSchool_Intro_8:
# 17 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_4, 23
	goto_if_eq TrainersSchool_Intro_2
	goto TrainersSchool_Intro_6


TrainersSchool_Intro_Skip::
# 130 "data/maps/Route1N/scripts.pory"
	closemessage
# 131 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 132 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_8
# 133 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 134 "data/maps/Route1N/scripts.pory"
	removeobject trainerschool_teacher
# 135 "data/maps/Route1N/scripts.pory"
	setflag FLAG_HIDE_TRAINERSCHOOL_TEACHER
# 136 "data/maps/Route1N/scripts.pory"
	special StopAllObjectMovements
# 137 "data/maps/Route1N/scripts.pory"
	special CloseScriptMenus
# 138 "data/maps/Route1N/scripts.pory"
	hideitemdescription
# 139 "data/maps/Route1N/scripts.pory"
	checkitem ITEM_EXP_SHARE, 1
# 140 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq TrainersSchool_Intro_Skip_2
TrainersSchool_Intro_Skip_1:
# 143 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 144 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_Intro_Skip_2:
# 141 "data/maps/Route1N/scripts.pory"
	additem ITEM_EXP_SHARE, 1
	goto TrainersSchool_Intro_Skip_1


TrainersSchool_BattleVs_Hiromi::
# 149 "data/maps/Route1N/scripts.pory"
	lock
# 150 "data/maps/Route1N/scripts.pory"
	goto_if_not_defeated TRAINER_LASS_HIROMI, TrainersSchool_BattleVs_Hiromi2
# 151 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Hiromi_Text_0, MSGBOX_AUTOCLOSE
# 159 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_BattleVs_Hiromi2::
# 164 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 165 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lass1, TrainersSchool_Intro_Movement_5
# 166 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lass1
# 167 "data/maps/Route1N/scripts.pory"
	waitse
# 168 "data/maps/Route1N/scripts.pory"
	trainerbattle_single TRAINER_LASS_HIROMI, TrainersSchool_BattleVs_Hiromi2_Text_0, TrainersSchool_BattleVs_Hiromi2_Text_1, music = FALSE
# 169 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Hiromi_Text_0, MSGBOX_AUTOCLOSE
# 177 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_RockPaperScissors::
# 182 "data/maps/Route1N/scripts.pory"
	lock
# 183 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 184 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_1
# 185 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 186 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_3
# 187 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 188 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littleboy, TrainersSchool_Intro_Movement_5
# 189 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_Intro_Movement_5
# 190 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 191 "data/maps/Route1N/scripts.pory"
	waitse
# 192 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 193 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_4
# 195 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littleboy, TrainersSchool_Intro_Movement_8
# 196 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_Intro_Movement_8
# 197 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 198 "data/maps/Route1N/scripts.pory"
	random 2
# 199 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool_RockPaperScissors_2
# 225 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool_RockPaperScissors_3
# 251 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool_RockPaperScissors_4
TrainersSchool_RockPaperScissors_1:
# 277 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littleboy, TrainersSchool_Intro_Movement_3
# 278 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_RockPaperScissors_Movement_0
# 279 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 280 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_RockPaperScissors_2:
# 200 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 201 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_5, MSGBOX_AUTOCLOSE
# 203 "data/maps/Route1N/scripts.pory"
	dynmultichoice 22, 6, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool_RockPaperScissors_Text_6, TrainersSchool_RockPaperScissors_Text_7, TrainersSchool_RockPaperScissors_Text_8
# 204 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool_RockPaperScissors_8
# 209 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool_RockPaperScissors_9
# 214 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool_RockPaperScissors_10
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_3:
# 226 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 227 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_11, MSGBOX_AUTOCLOSE
# 229 "data/maps/Route1N/scripts.pory"
	dynmultichoice 22, 6, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool_RockPaperScissors_Text_6, TrainersSchool_RockPaperScissors_Text_7, TrainersSchool_RockPaperScissors_Text_8
# 230 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool_RockPaperScissors_14
# 240 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool_RockPaperScissors_15
# 245 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool_RockPaperScissors_16
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_4:
# 252 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 253 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_12, MSGBOX_AUTOCLOSE
# 255 "data/maps/Route1N/scripts.pory"
	dynmultichoice 22, 6, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool_RockPaperScissors_Text_6, TrainersSchool_RockPaperScissors_Text_7, TrainersSchool_RockPaperScissors_Text_8
# 256 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool_RockPaperScissors_20
# 261 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool_RockPaperScissors_21
# 271 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool_RockPaperScissors_22
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_8:
# 205 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 206 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_9:
# 210 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 211 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_10:
# 215 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_Intro_Movement_6
# 216 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 217 "data/maps/Route1N/scripts.pory"
	waitse
# 218 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 219 "data/maps/Route1N/scripts.pory"
	waitse
# 220 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 221 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_10
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_14:
# 231 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_Intro_Movement_6
# 232 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 233 "data/maps/Route1N/scripts.pory"
	waitse
# 234 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 235 "data/maps/Route1N/scripts.pory"
	waitse
# 236 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 237 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_10
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_15:
# 241 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 242 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_16:
# 246 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_0
# 247 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_20:
# 257 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 258 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_21:
# 262 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_littlegirl, TrainersSchool_Intro_Movement_6
# 263 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 264 "data/maps/Route1N/scripts.pory"
	waitse
# 265 "data/maps/Route1N/scripts.pory"
	playse SE_LEDGE
# 266 "data/maps/Route1N/scripts.pory"
	waitse
# 267 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 268 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_10
	goto TrainersSchool_RockPaperScissors_1

TrainersSchool_RockPaperScissors_22:
# 272 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_RockPaperScissors_Text_2
# 273 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_RockPaperScissors_Text_9
	goto TrainersSchool_RockPaperScissors_1


TrainersSchool_BattleVs_Joey::
# 285 "data/maps/Route1N/scripts.pory"
	lock
# 286 "data/maps/Route1N/scripts.pory"
	goto_if_not_defeated TRAINER_YOUNGSTER_JOEY, TrainersSchool_BattleVS_joey2
# 287 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joey_Text_0, MSGBOX_AUTOCLOSE
# 293 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_BattleVS_joey2::
# 298 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 299 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_joey, TrainersSchool_BattleVS_joey2_Movement_0
# 300 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_joey
# 301 "data/maps/Route1N/scripts.pory"
	waitse
# 302 "data/maps/Route1N/scripts.pory"
	trainerbattle_single TRAINER_YOUNGSTER_JOEY, TrainersSchool_BattleVS_joey2_Text_0, TrainersSchool_BattleVS_joey2_Text_1, music = FALSE
# 304 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joey_Text_0, MSGBOX_AUTOCLOSE
# 310 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_Lillie::
# 315 "data/maps/Route1N/scripts.pory"
	lock
# 316 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Lillie_Movement_0
# 317 "data/maps/Route1N/scripts.pory"
	specialvar VAR_RESULT, IsPlayerPartyFullyHealed
# 318 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TrainersSchool_Lillie_2
# 330 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 331 "data/maps/Route1N/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 332 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Lillie_Text_2
# 334 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 335 "data/maps/Route1N/scripts.pory"
	playfanfare MUS_HEAL
# 336 "data/maps/Route1N/scripts.pory"
	special HealPlayerParty
# 337 "data/maps/Route1N/scripts.pory"
	waitfanfare
# 338 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 339 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 340 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Lillie_Text_3
# 344 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_Lillie_2:
# 319 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 320 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Lillie_Text_1
# 325 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_Kukui::
# 349 "data/maps/Route1N/scripts.pory"
	lock
# 350 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_kukui, TrainersSchool_Lillie_Movement_0
# 351 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Intro_Text_0
# 352 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_Kukui_Text_0, MSGBOX_AUTOCLOSE
# 365 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_BattleVs_Joseph::
# 371 "data/maps/Route1N/scripts.pory"
	lock
# 372 "data/maps/Route1N/scripts.pory"
	faceplayer
# 373 "data/maps/Route1N/scripts.pory"
	goto_if_not_defeated TRAINER_YOUNGSTER_JOEY, TrainersSchool_BattleVs_Joseph2
# 374 "data/maps/Route1N/scripts.pory"
	goto_if_not_defeated TRAINER_LASS_HIROMI, TrainersSchool_BattleVs_Joseph2
# 375 "data/maps/Route1N/scripts.pory"
	goto_if_not_defeated TRAINER_SCHOOLKID_MIA, TrainersSchool_BattleVs_Joseph2
# 376 "data/maps/Route1N/scripts.pory"
	goto_if_defeated TRAINER_SCHOOLKID_JOSEPH, TrainersSchool_BattleVs_Joseph3
# 377 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 378 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_joseph, TrainersSchool_BattleVS_joey2_Movement_0
# 379 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_joseph
# 380 "data/maps/Route1N/scripts.pory"
	waitse
# 381 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 382 "data/maps/Route1N/scripts.pory"
	hidefollower
# 383 "data/maps/Route1N/scripts.pory"
	getplayerxy VAR_TEMP_A, VAR_TEMP_B
# 384 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_A, 13
	goto_if_eq TrainersSchool_BattleVs_Joseph_15
TrainersSchool_BattleVs_Joseph_13:
# 388 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_A, 14
	goto_if_eq TrainersSchool_BattleVs_Joseph_12
TrainersSchool_BattleVs_Joseph_10:
# 392 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_A, 14
	goto_if_eq TrainersSchool_BattleVs_Joseph_9
TrainersSchool_BattleVs_Joseph_7:
# 396 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_A, 15
	goto_if_eq TrainersSchool_BattleVs_Joseph_6
TrainersSchool_BattleVs_Joseph_1:
# 400 "data/maps/Route1N/scripts.pory"
	delay 30
# 401 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 402 "data/maps/Route1N/scripts.pory"
	trainerbattle_single TRAINER_SCHOOLKID_JOSEPH, TrainersSchool_BattleVs_Joseph_Text_0, TrainersSchool_BattleVs_Joseph_Text_1, TrainersSchool_BattleVs_Joseph4, music = FALSE
# 403 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_BattleVs_Joseph_2:
# 385 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph_Movement_0
# 386 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_BattleVs_Joseph_1

TrainersSchool_BattleVs_Joseph_3:
# 389 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph_Movement_1
# 390 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_BattleVs_Joseph_1

TrainersSchool_BattleVs_Joseph_4:
# 393 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph_Movement_2
# 394 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_BattleVs_Joseph_1

TrainersSchool_BattleVs_Joseph_5:
# 397 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph_Movement_3
# 398 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
	goto TrainersSchool_BattleVs_Joseph_1

TrainersSchool_BattleVs_Joseph_6:
# 396 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_B, 19
	goto_if_eq TrainersSchool_BattleVs_Joseph_5
	goto TrainersSchool_BattleVs_Joseph_1

TrainersSchool_BattleVs_Joseph_9:
# 392 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_B, 18
	goto_if_eq TrainersSchool_BattleVs_Joseph_4
	goto TrainersSchool_BattleVs_Joseph_7

TrainersSchool_BattleVs_Joseph_12:
# 388 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_B, 20
	goto_if_eq TrainersSchool_BattleVs_Joseph_3
	goto TrainersSchool_BattleVs_Joseph_10

TrainersSchool_BattleVs_Joseph_15:
# 384 "data/maps/Route1N/scripts.pory"
	compare VAR_TEMP_B, 19
	goto_if_eq TrainersSchool_BattleVs_Joseph_2
	goto TrainersSchool_BattleVs_Joseph_13


TrainersSchool_BattleVs_Joseph2::
# 408 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph2_Text_0, MSGBOX_AUTOCLOSE
# 413 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_BattleVs_Joseph3::
# 418 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph3_Text_0
# 432 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_BattleVs_Joseph4::
# 437 "data/maps/Route1N/scripts.pory"
	setflag FLAG_HIDE_TRAINERSCHOOL_BLOCKINGMEOWTH
# 438 "data/maps/Route1N/scripts.pory"
	startcutscene CUTSCENE_TRAINER_SCHOOL_JOSEPH_BATTLE
# 439 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_0, MSGBOX_AUTOCLOSE
# 451 "data/maps/Route1N/scripts.pory"
	giveitem ITEM_TM01
# 452 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph3_Text_0, MSGBOX_AUTOCLOSE
# 466 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_BattleVs_Joseph4_Movement_0
# 467 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 468 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_BattleVs_Joseph4_Movement_1
# 469 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph4_Movement_1
# 470 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 471 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 472 "data/maps/Route1N/scripts.pory"
	playse SE_DING_DONG
# 473 "data/maps/Route1N/scripts.pory"
	waitse
# 474 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_4
# 475 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 476 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 477 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_1, MSGBOX_AUTOCLOSE
# 478 "data/maps/Route1N/scripts.pory"
	delay 30
# 479 "data/maps/Route1N/scripts.pory"
	setflag FLAG_SUPPRESS_SPEAKER_NAME
# 480 "data/maps/Route1N/scripts.pory"
	playse SE_DING_DONG
# 481 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_BattleVs_Joseph4_Movement_1
# 482 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph4_Movement_1
# 483 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 484 "data/maps/Route1N/scripts.pory"
	waitse
# 485 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_2
# 491 "data/maps/Route1N/scripts.pory"
	clearflag FLAG_SUPPRESS_SPEAKER_NAME
# 492 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_4
# 493 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BattleVs_Joseph4_Movement_2
# 494 "data/maps/Route1N/scripts.pory"
	waitmovement 0
# 495 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 496 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_3
# 498 "data/maps/Route1N/scripts.pory"
	dynmultichoice 20, 8, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool_BattleVs_Joseph4_Text_4, TrainersSchool_BattleVs_Joseph4_Text_5
# 499 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool_BattleVs_Joseph4_2
# 509 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 510 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_5
# 511 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 512 "data/maps/Route1N/scripts.pory"
	waitse
# 513 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 514 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_7
TrainersSchool_BattleVs_Joseph4_1:
# 516 "data/maps/Route1N/scripts.pory"
	endcutscene
# 517 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_BattleVs_Joseph4_2:
# 500 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 501 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_5
# 502 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 503 "data/maps/Route1N/scripts.pory"
	waitse
# 504 "data/maps/Route1N/scripts.pory"
	speakername TrainersSchool_Lillie_Text_0
# 505 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BattleVs_Joseph4_Text_6
	goto TrainersSchool_BattleVs_Joseph4_1


TrainersSchool_BlockingTauros::
# 522 "data/maps/Route1N/scripts.pory"
	lock
# 523 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_tauros, TrainersSchool_Lillie_Movement_0
# 524 "data/maps/Route1N/scripts.pory"
	waitmovement
# 525 "data/maps/Route1N/scripts.pory"
	playmoncry SPECIES_TAUROS, 0
# 526 "data/maps/Route1N/scripts.pory"
	msgbox TrainersSchool_BlockingTauros_Text_0, MSGBOX_AUTOCLOSE
# 527 "data/maps/Route1N/scripts.pory"
	waitmoncry
# 528 "data/maps/Route1N/scripts.pory"
	playse SE_PIN
# 529 "data/maps/Route1N/scripts.pory"
	applymovement LOCALID_PLAYER, TrainersSchool_BlockingTauros_Movement_0
# 530 "data/maps/Route1N/scripts.pory"
	waitmovement LOCALID_PLAYER
# 531 "data/maps/Route1N/scripts.pory"
	release
	end


TrainersSchool_Joseph_Battle_Skip::
# 536 "data/maps/Route1N/scripts.pory"
	closemessage
# 537 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 538 "data/maps/Route1N/scripts.pory"
	setobjectxy trainerschool_lillie, 12, 16
# 539 "data/maps/Route1N/scripts.pory"
	applymovement trainerschool_lillie, TrainersSchool_Intro_Movement_8
# 540 "data/maps/Route1N/scripts.pory"
	waitmovement trainerschool_lillie
# 541 "data/maps/Route1N/scripts.pory"
	special StopAllObjectMovements
# 542 "data/maps/Route1N/scripts.pory"
	special CloseScriptMenus
# 543 "data/maps/Route1N/scripts.pory"
	hideitemdescription
# 544 "data/maps/Route1N/scripts.pory"
	checkitem ITEM_TM01, 1
# 545 "data/maps/Route1N/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq TrainersSchool_Joseph_Battle_Skip_2
TrainersSchool_Joseph_Battle_Skip_1:
# 548 "data/maps/Route1N/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 549 "data/maps/Route1N/scripts.pory"
	release
	end

TrainersSchool_Joseph_Battle_Skip_2:
# 546 "data/maps/Route1N/scripts.pory"
	additem ITEM_TM01, 1
	goto TrainersSchool_Joseph_Battle_Skip_1


# 18 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_0:
# 18 "data/maps/Route1N/scripts.pory"
	walk_up
# 18 "data/maps/Route1N/scripts.pory"
	walk_left
# 18 "data/maps/Route1N/scripts.pory"
	face_up
	step_end

# 22 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_1:
# 22 "data/maps/Route1N/scripts.pory"
	walk_up
# 22 "data/maps/Route1N/scripts.pory"
	walk_right
# 22 "data/maps/Route1N/scripts.pory"
	face_up
	step_end

# 26 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_2:
# 26 "data/maps/Route1N/scripts.pory"
	walk_up
	step_end

# 31 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_3:
# 31 "data/maps/Route1N/scripts.pory"
	face_left
	step_end

# 33 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_4:
# 33 "data/maps/Route1N/scripts.pory"
	walk_in_place_down
# 33 "data/maps/Route1N/scripts.pory"
	walk_in_place_down
	step_end

# 44 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_5:
# 44 "data/maps/Route1N/scripts.pory"
	emote_exclamation_mark
	step_end

# 52 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_6:
# 52 "data/maps/Route1N/scripts.pory"
	jump_in_place_down
# 52 "data/maps/Route1N/scripts.pory"
	jump_in_place_down
	step_end

# 95 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_7:
# 95 "data/maps/Route1N/scripts.pory"
	walk_up
# 95 "data/maps/Route1N/scripts.pory"
	walk_up
# 95 "data/maps/Route1N/scripts.pory"
	walk_up
# 95 "data/maps/Route1N/scripts.pory"
	walk_up
	step_end

# 105 "data/maps/Route1N/scripts.pory"
TrainersSchool_Intro_Movement_8:
# 105 "data/maps/Route1N/scripts.pory"
	face_down
	step_end

# 278 "data/maps/Route1N/scripts.pory"
TrainersSchool_RockPaperScissors_Movement_0:
# 278 "data/maps/Route1N/scripts.pory"
	face_right
	step_end

# 299 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVS_joey2_Movement_0:
# 299 "data/maps/Route1N/scripts.pory"
	emote_exclamation_mark
# 299 "data/maps/Route1N/scripts.pory"
	face_player
	step_end

# 316 "data/maps/Route1N/scripts.pory"
TrainersSchool_Lillie_Movement_0:
# 316 "data/maps/Route1N/scripts.pory"
	face_player
	step_end

# 385 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph_Movement_0:
# 385 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 385 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 385 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 385 "data/maps/Route1N/scripts.pory"
	face_right
	step_end

# 389 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph_Movement_1:
# 389 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 389 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 389 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 389 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 389 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 389 "data/maps/Route1N/scripts.pory"
	face_right
	step_end

# 393 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph_Movement_2:
# 393 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 393 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 393 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 393 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 393 "data/maps/Route1N/scripts.pory"
	walk_faster_down
# 393 "data/maps/Route1N/scripts.pory"
	face_right
	step_end

# 397 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph_Movement_3:
# 397 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 397 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 397 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 397 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 397 "data/maps/Route1N/scripts.pory"
	walk_faster_left
# 397 "data/maps/Route1N/scripts.pory"
	face_right
	step_end

# 466 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph4_Movement_0:
# 466 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 466 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 466 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 466 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 466 "data/maps/Route1N/scripts.pory"
	walk_faster_up
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
# 466 "data/maps/Route1N/scripts.pory"
	walk_left
	step_end

# 468 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph4_Movement_1:
# 468 "data/maps/Route1N/scripts.pory"
	face_up
# 468 "data/maps/Route1N/scripts.pory"
	emote_exclamation_mark
	step_end

# 493 "data/maps/Route1N/scripts.pory"
TrainersSchool_BattleVs_Joseph4_Movement_2:
# 493 "data/maps/Route1N/scripts.pory"
	face_up
	step_end

# 529 "data/maps/Route1N/scripts.pory"
TrainersSchool_BlockingTauros_Movement_0:
# 529 "data/maps/Route1N/scripts.pory"
	emote_exclamation_mark
# 529 "data/maps/Route1N/scripts.pory"
	lock_facing_direction
# 529 "data/maps/Route1N/scripts.pory"
	jump_right
	step_end

TrainerSchoolSign_Text_0:
# 6 "data/maps/Route1N/scripts.pory"
	.string "Let's learn and grow.\n"
	.string "Let's grow and train.\l"
	.string "Unsullied, enjoyable, and academic.\l"
	.string "Everyone starts at the beginning!$"

TrainersSchool_Intro_Text_0:
# 35 "data/maps/Route1N/scripts.pory"
	.string "Kukui$"

TrainersSchool_Intro_Text_1:
# 36 "data/maps/Route1N/scripts.pory"
	.string "Hey there, {PLAYER}!\n"
	.string "I must've passed you somehow, yeah?\p"
	.string "But welcome to the Trainers' School,\n"
	.string "the place to learn how to be a\l"
	.string "Pokémon Trainer!$"

TrainersSchool_Intro_Text_2:
# 46 "data/maps/Route1N/scripts.pory"
	.string "Professor Kukui!\n"
	.string "Is this the child you told me about?$"

TrainersSchool_Intro_Text_3:
# 50 "data/maps/Route1N/scripts.pory"
	.string "Yeah. {PLAYER}'s a tough one,too.\n"
	.string "Put em through the wringer good, Teach!$"

TrainersSchool_Intro_Text_4:
# 58 "data/maps/Route1N/scripts.pory"
	.string "Four Trainers!\p"
	.string "You've got to beat four Pokémon\n"
	.string "Trainers at the school, {PLAYER}!\p"
	.string "The experience will surely help you\n"
	.string "and your Pokemon grow stronger,\l"
	.string "yeah.\p"
	.string "Actually… Speaking of experience,\n"
	.string "why don't you take this.$"

TrainersSchool_Intro_Text_5:
# 73 "data/maps/Route1N/scripts.pory"
	.string "If you keep that Exp. Share on, yeah,\n"
	.string "all the Pokémon on your team can get\l"
	.string "Exp. Points from battle.$"

TrainersSchool_Intro_Text_6:
# 79 "data/maps/Route1N/scripts.pory"
	.string "The Trainers who will take part in this\n"
	.string "lesson may be inside or outside the\l"
	.string "school.\p"
	.string "You may also want to visit our\n"
	.string "classrooms.\p"
	.string "You'll learn things there that will\n"
	.string "help on your journey, I'd say.$"

TrainersSchool_Intro_Text_7:
# 93 "data/maps/Route1N/scripts.pory"
	.string "All right. Let the lesson begin!$"

TrainersSchool_Intro_Text_8:
# 102 "data/maps/Route1N/scripts.pory"
	.string "She may not look all that tough, but\n"
	.string "that each trains her kids right!\l"
	.string "One of her students is even a captain!$"

TrainersSchool_Intro_Text_9:
# 107 "data/maps/Route1N/scripts.pory"
	.string "If you want a bit of advice from me,\n"
	.string "here's something that might help.\p"
	.string "Once you've fought a species of\n"
	.string "Pokémon once, You can easily see\l"
	.string "what types of moves will work best\l"
	.string "on it in your next battle.\p"
	.string "Wandering about in the tall grass to\n"
	.string "meet lots of different Pokémon'll\l"
	.string "help with that!$"

TrainersSchool_Intro_Text_10:
# 124 "data/maps/Route1N/scripts.pory"
	.string "Battle all the time, oh yeah!$"

TrainersSchool_BattleVs_Hiromi_Text_0:
# 151 "data/maps/Route1N/scripts.pory"
	.string "You can help your Pokémon win by using\n"
	.string "items at the right time.\p"
	.string "They can do more than just healing\n"
	.string "your Pokémon's HP too.\p"
	.string "You can even boost their stats and\n"
	.string "things like that.$"

TrainersSchool_BattleVs_Hiromi2_Text_0:
# 168 "data/maps/Route1N/scripts.pory"
	.string "If my previous Bonsly takes damage,\nI'll want to use a Potion on it!$"

TrainersSchool_BattleVs_Hiromi2_Text_1:
# 168 "data/maps/Route1N/scripts.pory"
	.string "Don't worry-I'll heal any pain that was\ncaused by our defeat!$"

TrainersSchool_RockPaperScissors_Text_0:
# 183 "data/maps/Route1N/scripts.pory"
	.string "Little Boy$"

TrainersSchool_RockPaperScissors_Text_1:
# 184 "data/maps/Route1N/scripts.pory"
	.string "Ready, and…$"

TrainersSchool_RockPaperScissors_Text_2:
# 185 "data/maps/Route1N/scripts.pory"
	.string "Little Girl$"

TrainersSchool_RockPaperScissors_Text_3:
# 186 "data/maps/Route1N/scripts.pory"
	.string "GRASS, FIRE, WATER!$"

TrainersSchool_RockPaperScissors_Text_4:
# 193 "data/maps/Route1N/scripts.pory"
	.string "Um…\n"
	.string "Which one wins again?$"

TrainersSchool_RockPaperScissors_Text_5:
# 201 "data/maps/Route1N/scripts.pory"
	.string "Which would win in a matchup between\n"
	.string "Grass type and Water type?$"

TrainersSchool_RockPaperScissors_Text_6:
# 203 "data/maps/Route1N/scripts.pory"
	.string "Fire$"

TrainersSchool_RockPaperScissors_Text_7:
# 203 "data/maps/Route1N/scripts.pory"
	.string "Water$"

TrainersSchool_RockPaperScissors_Text_8:
# 203 "data/maps/Route1N/scripts.pory"
	.string "Grass$"

TrainersSchool_RockPaperScissors_Text_9:
# 206 "data/maps/Route1N/scripts.pory"
	.string "You sure? I'm pretty sure it's not…\n"
	.string "Are you messing with us maybe?$"

TrainersSchool_RockPaperScissors_Text_10:
# 221 "data/maps/Route1N/scripts.pory"
	.string "Right, right! Yeah, that's it.\n"
	.string "You must be a great Trainer!$"

TrainersSchool_RockPaperScissors_Text_11:
# 227 "data/maps/Route1N/scripts.pory"
	.string "Which would win in a matchup between\n"
	.string "Fire type and Grass type?$"

TrainersSchool_RockPaperScissors_Text_12:
# 253 "data/maps/Route1N/scripts.pory"
	.string "Which would win in a matchup between\n"
	.string "Water type and Fire type?$"

TrainersSchool_BattleVs_Joey_Text_0:
# 287 "data/maps/Route1N/scripts.pory"
	.string "Grass-type Pokémon are immune to\n"
	.string "powder moves, like Poison Powder and\l"
	.string "Sleep Powder.\p"
	.string "But you can still poison 'em with Poison\n"
	.string "Gas!$"

TrainersSchool_BattleVS_joey2_Text_0:
# 302 "data/maps/Route1N/scripts.pory"
	.string "I'll show you my Grimer's best move!\nWith Poison Gas, it'll poison\leveryone that comes at us!$"

TrainersSchool_BattleVS_joey2_Text_1:
# 303 "data/maps/Route1N/scripts.pory"
	.string "No! The Grimer I found in the tall grass\nnear the school was defeated?$"

TrainersSchool_Lillie_Text_0:
# 319 "data/maps/Route1N/scripts.pory"
	.string "Lillie$"

TrainersSchool_Lillie_Text_1:
# 320 "data/maps/Route1N/scripts.pory"
	.string "You can tell me anytime that you want\n"
	.string "your team's health restored.\p"
	.string "Seeing a Pokémon in pain makes my own\n"
	.string "heart seem to ache…$"

TrainersSchool_Lillie_Text_2:
# 332 "data/maps/Route1N/scripts.pory"
	.string "Let me take care of poor\n"
	.string "{STR_VAR_1}, OK?$"

TrainersSchool_Lillie_Text_3:
# 340 "data/maps/Route1N/scripts.pory"
	.string "Please try not to push your Pokémon\n"
	.string "too hard…\l"
	.string "Um…I mean…if you don't mind…$"

TrainersSchool_Kukui_Text_0:
# 352 "data/maps/Route1N/scripts.pory"
	.string "If you want a bit of advice from me,\n"
	.string "here's something that might help.\p"
	.string "Once you've fought a species of\n"
	.string "Pokémon once, You can easily see\l"
	.string "what types of moves will work best\l"
	.string "on it in your next battle.\p"
	.string "Wandering about in the tall grass to\n"
	.string "meet lots of different Pokémon'll\l"
	.string "help with that!\p"
	.string "Battle all the time, oh yeah!$"

TrainersSchool_BattleVs_Joseph_Text_0:
# 402 "data/maps/Route1N/scripts.pory"
	.string "Looks like you beat everyone else, huh?\pDon't think you'll beat me the same way!\nEkan's Ability is gonna get you!$"

TrainersSchool_BattleVs_Joseph_Text_1:
# 402 "data/maps/Route1N/scripts.pory"
	.string "Even after your Attack is lowered…\nAn indominable spirit indeed!$"

TrainersSchool_BattleVs_Joseph2_Text_0:
# 408 "data/maps/Route1N/scripts.pory"
	.string "You wanna know why I'm standing here?\n"
	.string "'Cause I'm the strongest, that's why!\p"
	.string "I won't even bother battling you\n"
	.string "unless you can beat everyone else here!$"

TrainersSchool_BattleVs_Joseph3_Text_0:
# 418 "data/maps/Route1N/scripts.pory"
	.string "OK. First thing to know about TMs.\p"
	.string "Technical Machines teach new moves.\n"
	.string "But if your Pokémon cant learn the\l"
	.string "move in a TM, then too bad.\p"
	.string "Second thing to know about TMs.\p"
	.string "You can use a TM as many times as you\n"
	.string "want, on as many different Pokémon as\l"
	.string "you want.\p"
	.string "They don't wear out or get used up.\n"
	.string "Pretty nice gift from me, huh?$"

TrainersSchool_BattleVs_Joseph4_Text_0:
# 439 "data/maps/Route1N/scripts.pory"
	.string "Intimidate is an Ability that lowers\n"
	.string "your opponent's Attack Stat.\p"
	.string "If you understand your Pokémon's\n"
	.string "Abilities, you can use the best\l"
	.string "strategies in battle.\p"
	.string "But fine! Whatever!\p"
	.string "I can admit it when I'm beat.\n"
	.string "I'll give you a reward even.\l"
	.string "Take this Technical Machine!$"

TrainersSchool_BattleVs_Joseph4_Text_1:
# 477 "data/maps/Route1N/scripts.pory"
	.string "Oh, that's the school bell.$"

TrainersSchool_BattleVs_Joseph4_Text_2:
# 485 "data/maps/Route1N/scripts.pory"
	.string "Attention all students…\p"
	.string "Would {PLAYER} please come to the\n"
	.string "office on 2F?\p"
	.string "{PLAYER} to the 2F office, please.$"

TrainersSchool_BattleVs_Joseph4_Text_3:
# 496 "data/maps/Route1N/scripts.pory"
	.string "What terrible thing did you do to get\n"
	.string "called to the office so soon?$"

TrainersSchool_BattleVs_Joseph4_Text_4:
# 498 "data/maps/Route1N/scripts.pory"
	.string "Nothing!$"

TrainersSchool_BattleVs_Joseph4_Text_5:
# 498 "data/maps/Route1N/scripts.pory"
	.string "Well…$"

TrainersSchool_BattleVs_Joseph4_Text_6:
# 505 "data/maps/Route1N/scripts.pory"
	.string "That's what you say…$"

TrainersSchool_BattleVs_Joseph4_Text_7:
# 514 "data/maps/Route1N/scripts.pory"
	.string "So you did do something?!$"

TrainersSchool_BlockingTauros_Text_0:
# 526 "data/maps/Route1N/scripts.pory"
	.string "Graah!$"
