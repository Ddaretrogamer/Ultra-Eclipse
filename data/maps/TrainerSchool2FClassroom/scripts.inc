TrainerSchool2FClassroom_MapScripts::
	.byte 0


TrainersSchool2FClassroom_Teacher::
# 4 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 5 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	faceplayer
# 6 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Teacher_Text_0, MSGBOX_DEFAULT
# 15 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Student1::
# 20 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 21 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	faceplayer
# 22 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	goto_if_unset FLAG_LILLIPUP_PICKUP_ITEM, TrainersSchool2FClassroom_Student1_2
# 38 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student1_Text_1, MSGBOX_AUTOCLOSE
TrainersSchool2FClassroom_Student1_1:
# 48 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end

TrainersSchool2FClassroom_Student1_2:
# 23 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student1_Text_0, MSGBOX_AUTOCLOSE
# 25 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	giveitem ITEM_POTION
# 26 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student1_Text_1, MSGBOX_AUTOCLOSE
# 34 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	setflag FLAG_LILLIPUP_PICKUP_ITEM
	goto TrainersSchool2FClassroom_Student1_1


TrainersSchool2FClassroom_Student2::
# 53 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 54 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	faceplayer
# 55 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student2_Text_0, MSGBOX_AUTOCLOSE
# 59 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Student3::
# 64 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 65 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	faceplayer
# 66 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student3_Text_0, MSGBOX_AUTOCLOSE
# 76 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Student4::
# 81 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 82 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	faceplayer
# 83 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Student4_Text_0, MSGBOX_AUTOCLOSE
# 92 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Blackboard::
# 97 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	lock
# 98 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_0
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	dynmultichoice 22, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool2FClassroom_Blackboard_Text_1, TrainersSchool2FClassroom_Blackboard_Text_2, TrainersSchool2FClassroom_Blackboard_Text_3, TrainersSchool2FClassroom_Blackboard_Text_4, TrainersSchool2FClassroom_Blackboard_Text_5, TrainersSchool2FClassroom_Blackboard_Text_6
# 105 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool2FClassroom_Blackboard_2
# 118 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool2FClassroom_Blackboard_3
# 129 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool2FClassroom_Blackboard_4
# 140 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq TrainersSchool2FClassroom_Blackboard_5
# 148 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 4
	goto_if_eq TrainersSchool2FClassroom_Blackboard_6
# 156 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_eq TrainersSchool2FClassroom_Blackboard_7
TrainersSchool2FClassroom_Blackboard_1:
# 160 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end

TrainersSchool2FClassroom_Blackboard_2:
# 106 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_7
# 116 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard_1

TrainersSchool2FClassroom_Blackboard_3:
# 119 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_8
# 127 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard_1

TrainersSchool2FClassroom_Blackboard_4:
# 130 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_9
# 138 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard_1

TrainersSchool2FClassroom_Blackboard_5:
# 141 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_10
# 146 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard_1

TrainersSchool2FClassroom_Blackboard_6:
# 149 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_11
# 154 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard_1

TrainersSchool2FClassroom_Blackboard_7:
# 157 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Blackboard2::
# 165 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard2_Text_0
# 166 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	dynmultichoice 22, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrainersSchool2FClassroom_Blackboard_Text_1, TrainersSchool2FClassroom_Blackboard_Text_2, TrainersSchool2FClassroom_Blackboard_Text_3, TrainersSchool2FClassroom_Blackboard_Text_4, TrainersSchool2FClassroom_Blackboard_Text_5, TrainersSchool2FClassroom_Blackboard_Text_6
# 167 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_2
# 180 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_3
# 191 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_4
# 202 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_5
# 210 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 4
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_6
# 218 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_eq TrainersSchool2FClassroom_Blackboard2_7
TrainersSchool2FClassroom_Blackboard2_1:
# 222 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end

TrainersSchool2FClassroom_Blackboard2_2:
# 168 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_7
# 178 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard2_1

TrainersSchool2FClassroom_Blackboard2_3:
# 181 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_8
# 189 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard2_1

TrainersSchool2FClassroom_Blackboard2_4:
# 192 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_9
# 200 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard2_1

TrainersSchool2FClassroom_Blackboard2_5:
# 203 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_10
# 208 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard2_1

TrainersSchool2FClassroom_Blackboard2_6:
# 211 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	msgbox TrainersSchool2FClassroom_Blackboard_Text_11
# 216 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	call TrainersSchool2FClassroom_Blackboard2
	goto TrainersSchool2FClassroom_Blackboard2_1

TrainersSchool2FClassroom_Blackboard2_7:
# 219 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	release
	end


TrainersSchool2FClassroom_Teacher_Text_0:
# 6 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Abilities are basically special skills all\n"
	.string "Pokémon have that can make special\l"
	.string "things happen.\p"
	.string "Take the Ability called Limber,\n"
	.string "for example…\p"
	.string "Any Pokémon who has that Ability won't\n"
	.string "ever be paralyzed by a foe's moves!$"

TrainersSchool2FClassroom_Student1_Text_0:
# 23 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "My Lillipup picked this up.\n"
	.string "Here, you take it.$"

TrainersSchool2FClassroom_Student1_Text_1:
# 26 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Lillipup's Ability is Pickup!\p"
	.string "It's an awesome Ability that works\n"
	.string "even when you're not in battle.\p"
	.string "I went all the way to Akala Island to\n"
	.string "find a Lillipup and catch it just to\l"
	.string "have this Ability.$"

TrainersSchool2FClassroom_Student2_Text_0:
# 55 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "When you begin to level up as a Trainer\n"
	.string "and learn advanced strategies, you'll\l"
	.string "want to pay attention to Abilities.\l"
	.string "They can be a huge help!$"

TrainersSchool2FClassroom_Student3_Text_0:
# 66 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Let's see here…\p"
	.string "If you view a Pokémon's summary,\n"
	.string "you can see what Ability it has.\p"
	.string "Underneath you can see what that\n"
	.string "Ability does.\p"
	.string "Maybe I'd remember it all better if the\n"
	.string "textbook wasn't so boring!$"

TrainersSchool2FClassroom_Student4_Text_0:
# 83 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "All Pokémon have some sort of Ability…\p"
	.string "But even members of the same species\n"
	.string "don't always have the same Ability\l"
	.string "as one another.\p"
	.string "Which Ability you'll want your Pokémon\n"
	.string "to have will depend somewhat on how\l"
	.string "you like to battle.$"

TrainersSchool2FClassroom_Blackboard_Text_0:
# 98 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "There is writing on the blackboard.\p"
	.string "It lists status changes that may\n"
	.string "affect Pokémon in battle.\p"
	.string "What would you like to read about?$"

TrainersSchool2FClassroom_Blackboard_Text_1:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Poisoning$"

TrainersSchool2FClassroom_Blackboard_Text_2:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Paralysis$"

TrainersSchool2FClassroom_Blackboard_Text_3:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Falling asleep$"

TrainersSchool2FClassroom_Blackboard_Text_4:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Getting Burned$"

TrainersSchool2FClassroom_Blackboard_Text_5:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Being Frozen$"

TrainersSchool2FClassroom_Blackboard_Text_6:
# 104 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "Never mind$"

TrainersSchool2FClassroom_Blackboard_Text_7:
# 106 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "If a Pokémon is poisoned, it will\n"
	.string "steadily lose HP.\p"
	.string "The effects of poison remain after\n"
	.string "a battle.\p"
	.string "A poisoned Pokémon's HP will drop\n"
	.string "while it is traveling.\p"
	.string "Heal a poisoning using an Antidote.$"

TrainersSchool2FClassroom_Blackboard_Text_8:
# 119 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "If a Pokémon becomes paralyzed,\n"
	.string "its Speed drops.\p"
	.string "It may also not be able to move while\n"
	.string "it is in battle.\p"
	.string "Paralysis remains after battle.\n"
	.string "Cure it using a Paralyze Heal.$"

TrainersSchool2FClassroom_Blackboard_Text_9:
# 130 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "If a Pokémon falls asleep, it will be\n"
	.string "unable to attack.\p"
	.string "A Pokémon may wake up on its own,\n"
	.string "but if a battle ends while it is\l"
	.string "sleeping, it will stay asleep.\p"
	.string "Wake it up using an Awakening.$"

TrainersSchool2FClassroom_Blackboard_Text_10:
# 141 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "A burn reduces Attack power, and it\n"
	.string "steadily reduces the victim's HP.\p"
	.string "A burn lingers after battle.\n"
	.string "Cure a burn using a Burn Heal.$"

TrainersSchool2FClassroom_Blackboard_Text_11:
# 149 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "If a Pokémon is frozen, it becomes\n"
	.string "completely helpless.\p"
	.string "It will remain frozen after battle.\n"
	.string "Thaw it out using an Ice Heal.$"

TrainersSchool2FClassroom_Blackboard2_Text_0:
# 165 "data/maps/TrainerSchool2FClassroom/scripts.pory"
	.string "What would you like to read about?$"
