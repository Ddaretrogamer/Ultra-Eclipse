TrainerSchool2FTeachersLounge_MapScripts::
	.byte 0


TrainerSchool2FTeachersLounge_Slowpoke::
# 4 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	lock
# 5 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	faceplayer
# 6 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, 0
# 7 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	msgbox TrainerSchool2FTeachersLounge_Slowpoke_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	release
	end


TrainerSchool2FTeachersLounge_Guy::
# 13 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	lock
# 14 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	faceplayer
# 15 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	msgbox TrainerSchool2FTeachersLounge_Guy_Text_0, MSGBOX_AUTOCLOSE
# 22 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	release
	end


TrainerSchool2FTeachersLounge_Slowpoke_Text_0:
# 7 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	.string "Ya-a-awn…$"

TrainerSchool2FTeachersLounge_Guy_Text_0:
# 15 "data/maps/TrainerSchool2FTeachersLounge/scripts.pory"
	.string "Slowpoke's Yawn is a move that can put\n"
	.string "your opponent to sleep in battle.\p"
	.string "When a Pokémon is asleep, it can't do\n"
	.string "anything until it wakes up, so it can\l"
	.string "give you a chance against a Pokémon\l"
	.string "you're having trouble with.$"
