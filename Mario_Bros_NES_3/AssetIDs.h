#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_MISC2 21


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_PLATFORM_ANIMATE 6
#define OBJECT_TYPE_PLANT 8
#define OBJECT_TYPE_TELEPORT 10

#define OBJECT_TYPE_PORTAL	50

#pragma region Intro
#define ID_SPRITE_INTRO 0

#define ID_SPRITE_STAGE	0
#define ID_SPRITE_BLACKSCREEN	1
#define ID_SPRITE_GAMENAME		2

#define ID_SPRITE_NUMBER3_1		3
#define ID_SPRITE_NUMBER3_2		4
#define ID_SPRITE_NUMBER3_3		5
#define ID_SPRITE_NUMBER3_4		6

#define ID_SPRITE_TM			7

#define ID_SPRITE_CURTAIN	(ID_SPRITE_INTRO + 10)
#define ID_SPRITE_CURTAIN_1	(ID_SPRITE_CURTAIN + 0)
#define ID_SPRITE_CURTAIN_2	(ID_SPRITE_CURTAIN + 1)
#define ID_SPRITE_CURTAIN_3	(ID_SPRITE_CURTAIN + 2)

#define ID_SPRITE_TREE			(ID_SPRITE_INTRO + 20)
#define ID_SPRITE_TREE_LEFT		(ID_SPRITE_TREE + 0)
#define ID_SPRITE_TREE_RIGHT	(ID_SPRITE_TREE + 1)

#define ID_SPRITE_CLOUD			(ID_SPRITE_INTRO + 30)
#define ID_SPRITE_CLOUD_BIG		(ID_SPRITE_CLOUD + 0)
#define ID_SPRITE_CLOUD_SMALL	(ID_SPRITE_CLOUD + 1)

#define ID_SPRITE_1PLAYERGAME	(ID_SPRITE_INTRO + 40)


#pragma endregion Intro


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)

#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)

#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)

#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_BIG_KICK (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_KICK_LEFT (ID_SPRITE_MARIO_BIG_KICK + 10)
#define ID_SPRITE_MARIO_BIG_KICK_RIGHT (ID_SPRITE_MARIO_BIG_KICK + 20)

#define ID_SPRITE_MARIO_BIG_HOLD_STAND		(ID_SPRITE_MARIO_BIG + 800)
#define ID_SPRITE_MARIO_BIG_HOLD_RUN_RIGHT	(ID_SPRITE_MARIO_BIG_HOLD_STAND + 20)
#define ID_SPRITE_MARIO_BIG_HOLD_RUN_LEFT	(ID_SPRITE_MARIO_BIG_BRACE + 10)

#define ID_SPRITE_MARIO_BIG_GETINTO_PIPE (ID_SPRITE_MARIO_BIG + 900)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

///////	SPRITE MARIO SMALL	/////////
#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

//#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
//#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
//#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_KICK_LEFT (ID_SPRITE_MARIO_SMALL + 523)
#define ID_SPRITE_MARIO_SMALL_KICK_RIGHT (ID_SPRITE_MARIO_SMALL + 527)

#define ID_SPRITE_MARIO_SMALL_HOLD_LEFT (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_HOLD_RIGHT (ID_SPRITE_MARIO_SMALL + 700)

#define ID_SPRITE_MARIO_SMALL_GETINTO_PIPE (ID_SPRITE_MARIO_SMALL + 800)

/////////	SPRITE MARIO RACCOON	/////////////
#define ID_SPRITE_MARIO_RACCOON (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACCOON_IDLE (ID_SPRITE_MARIO_RACCOON + 100)
#define ID_SPRITE_MARIO_RACCOON_IDLE_LEFT (ID_SPRITE_MARIO_RACCOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACCOON_IDLE_RIGHT (ID_SPRITE_MARIO_RACCOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACCOON_WALKING (ID_SPRITE_MARIO_RACCOON + 200)
#define ID_SPRITE_MARIO_RACCOON_WALKING_LEFT (ID_SPRITE_MARIO_RACCOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACCOON_WALKING_RIGHT (ID_SPRITE_MARIO_RACCOON_WALKING + 20)
#define ID_SPRITE_MARIO_RACCOON_RUNNING (ID_SPRITE_MARIO_RACCOON + 300)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_LEFT (ID_SPRITE_MARIO_RACCOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_RIGHT (ID_SPRITE_MARIO_RACCOON_RUNNING + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP (ID_SPRITE_MARIO_RACCOON + 400)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK (ID_SPRITE_MARIO_RACCOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN (ID_SPRITE_MARIO_RACCOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_RACCOON_SIT (ID_SPRITE_MARIO_RACCOON + 500)
#define ID_SPRITE_MARIO_RACCOON_SIT_LEFT (ID_SPRITE_MARIO_RACCOON_SIT + 10)
#define ID_SPRITE_MARIO_RACCOON_SIT_RIGHT (ID_SPRITE_MARIO_RACCOON_SIT + 20)

#define ID_SPRITE_MARIO_RACCOON_BRACE (ID_SPRITE_MARIO_RACCOON + 600)
#define ID_SPRITE_MARIO_RACCOON_BRACE_LEFT (ID_SPRITE_MARIO_RACCOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACCOON_BRACE_RIGHT (ID_SPRITE_MARIO_RACCOON_BRACE + 20)

#define ID_SPRITE_MARIO_RACCOON_GETINTO_SEWER (ID_SPRITE_MARIO_RACCOON + 700)

#define ID_SPRITE_MARIO_RACCOON_FLY (ID_SPRITE_MARIO_RACCOON + 1000)
#define ID_SPRITE_MARIO_RACCOON_FLY_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY + 1)
#define ID_SPRITE_MARIO_RACCOON_FLY_LEFT (ID_SPRITE_MARIO_RACCOON_FLY + 100)
#define ID_SPRITE_MARIO_RACCOON_FLOAT_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY + 200)
#define ID_SPRITE_MARIO_RACCOON_FLOAT_LEFT (ID_SPRITE_MARIO_RACCOON_FLY + 300)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_NORMAL_GOOMBA (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_NORMAL_GOOMBA_WALK (ID_SPRITE_NORMAL_GOOMBA + 100)
#define ID_SPRITE_NORMAL_GOOMBA_DIE (ID_SPRITE_NORMAL_GOOMBA + 200)

#define ID_SPRITE_RED_GOOMBA (ID_SPRITE_GOOMBA + 2000)
#define ID_SPRITE_RED_GOOMBA_WALK (ID_SPRITE_RED_GOOMBA + 100)
#define ID_SPRITE_RED_GOOMBA_DIE (ID_SPRITE_RED_GOOMBA + 200)


#define ID_SPRITE_RED_WING_GOOMBA (ID_SPRITE_GOOMBA + 3000)
#define ID_SPRITE_RED_WING_GOOMBA_FLY (ID_SPRITE_RED_WING_GOOMBA + 100)
#define ID_SPRITE_RED_WING_GOOMBA_WALK (ID_SPRITE_RED_WING_GOOMBA + 200)


#define ID_SPRITE_RED_KOOPAS 35000
#define ID_SPRITE_RED_KOOPAS_WALK_LEFT	(ID_SPRITE_KOOPAS + 100)
#define ID_SPRITE_RED_KOOPAS_WALK_RIGHT (ID_SPRITE_RED_KOOPAS_WALK_LEFT + 10)
#define ID_SPRITE_RED_KOOPAS_SHELL_DOWN (ID_SPRITE_KOOPAS + 200)
#define ID_SPRITE_RED_KOOPAS_SHELL_UP	(ID_SPRITE_RED_KOOPAS_SHELL_DOWN + 10)

#define ID_SPRITE_GREEN_KOOPAS 35300
#define ID_SPRITE_GREEN_KOOPAS_WALK_LEFT	(ID_SPRITE_GREEN_KOOPAS + 1)
#define ID_SPRITE_GREEN_KOOPAS_WALK_RIGHT	(ID_SPRITE_GREEN_KOOPAS_WALK_LEFT + 10)
#define ID_SPRITE_GREEN_KOOPAS_SHELL_DOWN	(ID_SPRITE_GREEN_KOOPAS + 100)
#define ID_SPRITE_GREEN_KOOPAS_SHELL_UP		(ID_SPRITE_GREEN_KOOPAS_SHELL_DOWN + 10)

#define ID_SPRITE_GREEN_WING_KOOPAS 35500
#define ID_SPRITE_GREEN_WING_KOOPAS_FLY_LEFT	(ID_SPRITE_GREEN_WING_KOOPAS + 0)
#define ID_SPRITE_GREEN_WING_KOOPAS_FLY_RIGHT	(ID_SPRITE_GREEN_WING_KOOPAS + 10)

#define ID_SPRITE_PLANT 37000
#define ID_SPRITE_PLANT_RED_FIRE	(ID_SPRITE_PLANT + 100)
#define ID_SPRITE_PLANT_GREEN		(ID_SPRITE_PLANT + 200)
#define ID_SPRITE_PLANT_GREEN_FIRE	(ID_SPRITE_PLANT + 300)

#define ID_SPRITE_BULLET 38000

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_PIPE 45000
#define ID_SPRITE_PIPE_GREEN_TOP_LEFT	45001
#define ID_SPRITE_PIPE_GREEN_TOP_RIGHT	45002
#define ID_SPRITE_PIPE_GREEN_BODY_LEFT	45101
#define ID_SPRITE_PIPE_GREEN_BODY_RIGHT	45102
#define ID_SPRITE_PIPE_BLACK_TOP_LEFT	45003
#define ID_SPRITE_PIPE_BLACK_TOP_RIGHT	45004
#define ID_SPRITE_PIPE_BLACK_BODY_LEFT	45103
#define ID_SPRITE_PIPE_BLACK_BODY_RIGHT	45104

#define ID_SPRITE_RECTANGLE_PINK 46000
#define ID_SPRITE_RECTANGLE_PINK_TOP_LEFT	(ID_SPRITE_RECTANGLE_PINK + 1)
#define ID_SPRITE_RECTANGLE_PINK_TOP_MID	(ID_SPRITE_RECTANGLE_PINK + 2)
#define ID_SPRITE_RECTANGLE_PINK_TOP_RIGHT	(ID_SPRITE_RECTANGLE_PINK + 3)
#define ID_SPRITE_RECTANGLE_PINK_MID_LEFT	(ID_SPRITE_RECTANGLE_PINK + 4)
#define ID_SPRITE_RECTANGLE_PINK_MID_MID	(ID_SPRITE_RECTANGLE_PINK + 5)
#define ID_SPRITE_RECTANGLE_PINK_MID_RIGHT	(ID_SPRITE_RECTANGLE_PINK + 6)
#define ID_SPRITE_RECTANGLE_PINK_BOT_LEFT	(ID_SPRITE_RECTANGLE_PINK + 7)
#define ID_SPRITE_RECTANGLE_PINK_BOT_MID	(ID_SPRITE_RECTANGLE_PINK + 8)
#define ID_SPRITE_RECTANGLE_PINK_BOT_RIGHT	(ID_SPRITE_RECTANGLE_PINK + 9)

#define ID_SPRITE_RECTANGLE_BLU 46010
#define ID_SPRITE_RECTANGLE_BLU_TOP_LEFT	(ID_SPRITE_RECTANGLE_BLU + 1)
#define ID_SPRITE_RECTANGLE_BLU_TOP_MID	(ID_SPRITE_RECTANGLE_BLU + 2)
#define ID_SPRITE_RECTANGLE_BLU_TOP_RIGHT	(ID_SPRITE_RECTANGLE_BLU + 3)
#define ID_SPRITE_RECTANGLE_BLU_MID_LEFT	(ID_SPRITE_RECTANGLE_BLU + 4)
#define ID_SPRITE_RECTANGLE_BLU_MID_MID	(ID_SPRITE_RECTANGLE_BLU + 5)
#define ID_SPRITE_RECTANGLE_BLU_MID_RIGHT	(ID_SPRITE_RECTANGLE_BLU + 6)
#define ID_SPRITE_RECTANGLE_BLU_BOT_LEFT	(ID_SPRITE_RECTANGLE_BLU + 7)
#define ID_SPRITE_RECTANGLE_BLU_BOT_MID	(ID_SPRITE_RECTANGLE_BLU + 8)
#define ID_SPRITE_RECTANGLE_BLU_BOT_RIGHT	(ID_SPRITE_RECTANGLE_BLU + 9)

#define ID_SPRITE_RECTANGLE_GREEN 46020
#define ID_SPRITE_RECTANGLE_GREEN_TOP_LEFT	(ID_SPRITE_RECTANGLE_GREEN + 1)
#define ID_SPRITE_RECTANGLE_GREEN_TOP_MID	(ID_SPRITE_RECTANGLE_GREEN + 2)
#define ID_SPRITE_RECTANGLE_GREEN_TOP_RIGHT	(ID_SPRITE_RECTANGLE_GREEN + 3)
#define ID_SPRITE_RECTANGLE_GREEN_MID_LEFT	(ID_SPRITE_RECTANGLE_GREEN + 4)
#define ID_SPRITE_RECTANGLE_GREEN_MID_MID	(ID_SPRITE_RECTANGLE_GREEN + 5)
#define ID_SPRITE_RECTANGLE_GREEN_MID_RIGHT	(ID_SPRITE_RECTANGLE_GREEN + 6)
#define ID_SPRITE_RECTANGLE_GREEN_BOT_LEFT	(ID_SPRITE_RECTANGLE_GREEN + 7)
#define ID_SPRITE_RECTANGLE_GREEN_BOT_MID	(ID_SPRITE_RECTANGLE_GREEN + 8)
#define ID_SPRITE_RECTANGLE_GREEN_BOT_RIGHT	(ID_SPRITE_RECTANGLE_GREEN + 9)

#define ID_SPRITE_RECTANGLE_WHITE 46030
#define ID_SPRITE_RECTANGLE_WHITE_TOP_LEFT	(ID_SPRITE_RECTANGLE_WHITE + 1)
#define ID_SPRITE_RECTANGLE_WHITE_TOP_MID	(ID_SPRITE_RECTANGLE_WHITE + 2)
#define ID_SPRITE_RECTANGLE_WHITE_TOP_RIGHT	(ID_SPRITE_RECTANGLE_WHITE + 3)
#define ID_SPRITE_RECTANGLE_WHITE_MID_LEFT	(ID_SPRITE_RECTANGLE_WHITE + 4)
#define ID_SPRITE_RECTANGLE_WHITE_MID_MID	(ID_SPRITE_RECTANGLE_WHITE + 5)
#define ID_SPRITE_RECTANGLE_WHITE_MID_RIGHT	(ID_SPRITE_RECTANGLE_WHITE + 6)
#define ID_SPRITE_RECTANGLE_WHITE_BOT_LEFT	(ID_SPRITE_RECTANGLE_WHITE + 7)
#define ID_SPRITE_RECTANGLE_WHITE_BOT_MID	(ID_SPRITE_RECTANGLE_WHITE + 8)
#define ID_SPRITE_RECTANGLE_WHITE_BOT_RIGHT	(ID_SPRITE_RECTANGLE_WHITE + 9)

#pragma region DECORATION
#define ID_SPRITE_RECTANGLE_WHITE_TOP_LEFT	60100
#define ID_SPRITE_RECTANGLE_WHITE_TOP_MID	(ID_SPRITE_RECTANGLE_WHITE_TOP_LEFT + 1)
#define ID_SPRITE_RECTANGLE_WHITE_TOP_RIGHT	(ID_SPRITE_RECTANGLE_WHITE_TOP_LEFT + 2)
#define ID_SPRITE_RECTANGLE_WHITE_BOT_LEFT	60200
#define ID_SPRITE_RECTANGLE_WHITE_BOT_MID	(ID_SPRITE_RECTANGLE_WHITE_BOT_LEFT + 1)
#define ID_SPRITE_RECTANGLE_WHITE_BOT_RIGHT	(ID_SPRITE_RECTANGLE_WHITE_BOT_LEFT + 2)

#define ID_SPRITE_FLOWER	60300
#define ID_SPRITE_STAR		60301
#define ID_SPRITE_MUSHROOM	60302

#define ID_SPRITE_SHORT_TREE	61000

#define ID_SPRITE_TALL_TREE_TOP_LEFT	61100
#define ID_SPRITE_TALL_TREE_TOP_RIGHT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 1)
#define ID_SPRITE_TALL_TREE_BOT_LEFT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 2)
#define ID_SPRITE_TALL_TREE_BOT_RIGHT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 3)
#define ID_SPRITE_TALL_TREE_BODY		(ID_SPRITE_TALL_TREE_TOP_LEFT + 4)

#define ID_SPRITE_EDGE 65000

#define ID_SPRITE_BLACK_TALL_TREE_TOP_LEFT	65100
#define ID_SPRITE_BLACK_TALL_TREE_TOP_RIGHT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 1)
#define ID_SPRITE_BLACK_TALL_TREE_BOT_LEFT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 10)
#define ID_SPRITE_BLACK_TALL_TREE_BOT_RIGHT	(ID_SPRITE_TALL_TREE_TOP_LEFT + 11)
#define ID_SPRITE_BLACK_TALL_TREE_BODY		(ID_SPRITE_TALL_TREE_TOP_LEFT + 100)

#pragma endregion DECORATION


#define ID_SPRITE_PSWITCH 47000
#define ID_SPRITE_PSWITCH_ACTIVED (ID_SPRITE_PSWITCH + 10)


#define ID_SPRITE_GROUND 50000
#define ID_SPRITE_GROUND_TOP_BEGIN (ID_SPRITE_GROUND + 1000)
#define ID_SPRITE_GROUND_TOP_MIDDLE (ID_SPRITE_GROUND + 2000)
#define ID_SPRITE_GROUND_TOP_END (ID_SPRITE_GROUND + 3000)
#define ID_SPRITE_GROUND_TOP_BEGIN (ID_SPRITE_GROUND_TOP_END + 100)
#define ID_SPRITE_GROUND_TOP_MIDDLE (ID_SPRITE_GROUND_TOP_END + 200)
#define ID_SPRITE_GROUND_TOP_END (ID_SPRITE_GROUND_TOP_END + 300)

#define ID_SPRITE_CLOUD 54000


#define ID_SPRITE_SUPERMUSHROOM 60000
#define ID_SPRITE_1UPMUSHROOM (ID_SPRITE_SUPERMUSHROOM + 1000)
#define ID_SPRITE_SUPERLEAF_RIGHT (ID_SPRITE_SUPERMUSHROOM + 2000)
#define ID_SPRITE_SUPERLEAF_LEFT (ID_SPRITE_SUPERLEAF_RIGHT + 100)



#define ID_SPRITE_GIFT_BOX 65300
#define ID_SPRITE_GIFT_MUSHROOM 65310
#define ID_SPRITE_GIFT_MUSHROOM_ONHUD 65312
#define ID_SPRITE_GIFT_FLOWER 65320
#define ID_SPRITE_GIFT_FLOWER_ONHUD 65322
#define ID_SPRITE_GIFT_STAR 65330
#define ID_SPRITE_GIFT_STAR_ONHUD 65332

#define ID_SPRITE_GOAL	65500

#pragma region Effect

#define ID_SPRITE_TAIL_MARIO_ATTACK 65400

#define ID_SPRITE_BIG_MARIO_EAT_SUPERLEAF 65410

#define ID_ANI_BIG_MARIO_EATING_SUPERLEAF 9000

#define ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES 9100

#pragma endregion


#pragma region HUD&FONT
////		HUD			////
#define ID_SPRITE_HUD	70000
#define ID_SPRITE_GIFT_BOX_BLU	(ID_SPRITE_HUD + 1)

#define ID_SPRITE_SYMBOL_M	(ID_SPRITE_HUD + 10)
#define ID_SPRITE_SYMBOL_L	(ID_SPRITE_SYMBOL_M + 1)

#define ID_SPRITE_ARROW_WHITE	(ID_SPRITE_HUD + 20)
#define ID_SPRITE_ARROW_BLACK	(ID_SPRITE_ARROW_WHITE + 1)
#define ID_SPRITE_P_WHITE		(ID_SPRITE_ARROW_WHITE + 5)
#define ID_SPRITE_P_BLACK		(ID_SPRITE_ARROW_WHITE + 6)

////		FONT		////
#define ID_SPRITE_FONT	75000

#define ID_SPRITE_NUMBER	(ID_SPRITE_FONT + 100)
#define ID_SPRITE_NUMBER_0	(ID_SPRITE_NUMBER + 0)
#define ID_SPRITE_NUMBER_1	(ID_SPRITE_NUMBER + 1)
#define ID_SPRITE_NUMBER_2	(ID_SPRITE_NUMBER + 2)
#define ID_SPRITE_NUMBER_3	(ID_SPRITE_NUMBER + 3)
#define ID_SPRITE_NUMBER_4	(ID_SPRITE_NUMBER + 4)
#define ID_SPRITE_NUMBER_5	(ID_SPRITE_NUMBER + 5)
#define ID_SPRITE_NUMBER_6	(ID_SPRITE_NUMBER + 6)
#define ID_SPRITE_NUMBER_7	(ID_SPRITE_NUMBER + 7)
#define ID_SPRITE_NUMBER_8	(ID_SPRITE_NUMBER + 8)
#define ID_SPRITE_NUMBER_9	(ID_SPRITE_NUMBER + 9)

#define ID_SPRITE_POINTS		(ID_SPRITE_FONT + 200)
#define ID_SPRITE_POINTS_100	(ID_SPRITE_POINTS + 1)
#define ID_SPRITE_POINTS_200	(ID_SPRITE_POINTS + 2)
#define ID_SPRITE_POINTS_400	(ID_SPRITE_POINTS + 3)
#define ID_SPRITE_POINTS_800	(ID_SPRITE_POINTS + 4)
#define ID_SPRITE_POINTS_1000	(ID_SPRITE_POINTS + 5)
#define ID_SPRITE_POINTS_2000	(ID_SPRITE_POINTS + 6)
#define ID_SPRITE_POINTS_4000	(ID_SPRITE_POINTS + 7)
#define ID_SPRITE_POINTS_8000	(ID_SPRITE_POINTS + 8)
#define ID_SPRITE_POINTS_1UP	(ID_SPRITE_POINTS + 9)

#define ID_SPRITE_PAUSE	(ID_SPRITE_FONT + 300)
#pragma endregion

#pragma region World Map GrassLand
#define ID_SPRITE_WORLD_MAP 80000

#define ID_SPRITE_SYMBOL_START	(ID_SPRITE_WORLD_MAP + 0)

#define ID_SPRITE_SCENE		(ID_SPRITE_WORLD_MAP + 10)
#define ID_SPRITE_SCENE_1	(ID_SPRITE_SCENE + 0)
#define ID_SPRITE_SCENE_2	(ID_SPRITE_SCENE + 1)
#define ID_SPRITE_SCENE_3	(ID_SPRITE_SCENE + 2)
#define ID_SPRITE_SCENE_4	(ID_SPRITE_SCENE + 3)
#define ID_SPRITE_SCENE_5	(ID_SPRITE_SCENE + 4)
#define ID_SPRITE_SCENE_6	(ID_SPRITE_SCENE + 5)
#define ID_SPRITE_SCENE_7	(ID_SPRITE_SCENE + 6)
#define ID_SPRITE_SCENE_8	(ID_SPRITE_SCENE + 7)
#define ID_SPRITE_SCENE_9	(ID_SPRITE_SCENE + 8)
#define ID_SPRITE_SCENE_10	(ID_SPRITE_SCENE + 9)

#define ID_SPRITE_SYMBOL_ACE	 (ID_SPRITE_WORLD_MAP + 20)
#define ID_SPRITE_GATE			 (ID_SPRITE_SYMBOL_ACE + 1)
#define ID_SPRITE_DOOR			 (ID_SPRITE_SYMBOL_ACE + 2)
#define ID_SPRITE_MUSHROOM_HOUSE (ID_SPRITE_SYMBOL_ACE + 3)
#define ID_SPRITE_CASTLE_BODY	 (ID_SPRITE_SYMBOL_ACE + 4)
#define ID_SPRITE_CASTLE_TOP	 (ID_SPRITE_SYMBOL_ACE + 5)
#define ID_SPRITE_SYMBOL_HELP	 (ID_SPRITE_SYMBOL_ACE + 6)

#define ID_SPRITE_PATH						(ID_SPRITE_WORLD_MAP + 30)
#define ID_SPRITE_PATH_HORIZONTAL			(ID_SPRITE_PATH + 0)
#define ID_SPRITE_PATH_VERTICAL				(ID_SPRITE_PATH + 1)
#define ID_SPRITE_SEED						(ID_SPRITE_PATH + 1)
#define ID_SPRITE_PATH_HORIZONTAL_WITH_SEED	(ID_SPRITE_PATH + 3)
#define ID_SPRITE_PATH_VERTICAL_WITH_SEED	(ID_SPRITE_PATH + 4)
#define ID_SPRITE_PATH_HORIZONTAL_VERTICAL_WITH_SEED	(ID_SPRITE_PATH + 5)

#define ID_SPRITE_MAP_BORDER		(ID_SPRITE_WORLD_MAP + 100)
#define ID_SPRITE_MAP_BORDER_TOP_LEFT	(ID_SPRITE_MAP_BORDER + 0)
#define ID_SPRITE_MAP_BORDER_TOP_MID	(ID_SPRITE_MAP_BORDER + 1)
#define ID_SPRITE_MAP_BORDER_TOP_RIGHT	(ID_SPRITE_MAP_BORDER + 2)
#define ID_SPRITE_MAP_BORDER_MID_LEFT	(ID_SPRITE_MAP_BORDER + 10)
#define ID_SPRITE_MAP_BORDER_MID_RIGHT	(ID_SPRITE_MAP_BORDER + 11)
#define ID_SPRITE_MAP_BORDER_BOT_LEFT	(ID_SPRITE_MAP_BORDER + 20)
#define ID_SPRITE_MAP_BORDER_BOT_MID	(ID_SPRITE_MAP_BORDER + 21)
#define ID_SPRITE_MAP_BORDER_BOT_RIGHT	(ID_SPRITE_MAP_BORDER + 22)

#define ID_SPRITE_BACKGROUND_COLOR (ID_SPRITE_WORLD_MAP + 200)

#define ID_SPRITE_GRASS	(ID_SPRITE_WORLD_MAP + 300)
#define ID_SPRITE_GRASS_0	(ID_SPRITE_GRASS + 0)
#define ID_SPRITE_GRASS_1	(ID_SPRITE_GRASS + 1)
#define ID_SPRITE_GRASS_2	(ID_SPRITE_GRASS + 2)
#define ID_SPRITE_GRASS_3	(ID_SPRITE_GRASS + 3)
#define ID_ANI_GRASS_DANCING 20000

#define ID_SPRITE_MOUNTAIN	(ID_SPRITE_GRASS + 10)
#define ID_SPRITE_BRIDGE	(ID_SPRITE_GRASS + 20)

#define ID_SPRITE_DRAIN			(ID_SPRITE_WORLD_MAP + 400)
#define ID_SPRITE_DRAIN_TOP_0	(ID_SPRITE_DRAIN + 0)
#define ID_SPRITE_DRAIN_TOP_1	(ID_SPRITE_DRAIN + 1)
#define ID_SPRITE_DRAIN_TOP_2	(ID_SPRITE_DRAIN + 2)
#define ID_SPRITE_DRAIN_TOP_3	(ID_SPRITE_DRAIN + 3)
#define ID_SPRITE_DRAIN_MID1_0	(ID_SPRITE_DRAIN + 10)
#define ID_SPRITE_DRAIN_MID1_1	(ID_SPRITE_DRAIN + 11)
#define ID_SPRITE_DRAIN_MID1_2	(ID_SPRITE_DRAIN + 12)
#define ID_SPRITE_DRAIN_MID1_3	(ID_SPRITE_DRAIN + 13)
#define ID_SPRITE_DRAIN_MID2_0	(ID_SPRITE_DRAIN + 20)
#define ID_SPRITE_DRAIN_MID2_1	(ID_SPRITE_DRAIN + 21)
#define ID_SPRITE_DRAIN_MID2_2	(ID_SPRITE_DRAIN + 22)
#define ID_SPRITE_DRAIN_MID2_3	(ID_SPRITE_DRAIN + 23)
#define ID_SPRITE_DRAIN_BOT_0	(ID_SPRITE_DRAIN + 30)
#define ID_SPRITE_DRAIN_BOT_1	(ID_SPRITE_DRAIN + 31)
#define ID_SPRITE_DRAIN_BOT_2	(ID_SPRITE_DRAIN + 32)
#define ID_SPRITE_DRAIN_BOT_3	(ID_SPRITE_DRAIN + 33)

#pragma endregion
