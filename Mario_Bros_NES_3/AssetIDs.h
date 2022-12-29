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
#define OBJECT_TYPE_PLANT 8

#define OBJECT_TYPE_PORTAL	50


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

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

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


#define ID_SPRITE_KOOPAS 35000
#define ID_SPRITE_KOOPAS_WALK (ID_SPRITE_KOOPAS + 100)
#define ID_SPRITE_KOOPAS_SHELL (ID_SPRITE_KOOPAS + 200)

#define ID_SPRITE_PLANT 37000

#define ID_SPRITE_BULLET 38000

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_PIPE 45000

#define ID_SPRITE_PSWITCH 47000
#define ID_SPRITE_PSWITCH_ACTIVED (ID_SPRITE_PSWITCH + 10)

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_SUPERMUSHROOM 60000
#define ID_SPRITE_1UPMUSHROOM (ID_SPRITE_SUPERMUSHROOM + 1000)
#define ID_SPRITE_SUPERLEAF_RIGHT (ID_SPRITE_SUPERMUSHROOM + 2000)
#define ID_SPRITE_SUPERLEAF_LEFT (ID_SPRITE_SUPERLEAF_RIGHT + 100)

#pragma region Effect

#define ID_SPRITE_TAIL_MARIO_ATTACK 65400

#define ID_SPRITE_BIG_MARIO_EAT_SUPERLEAF 65410
#define ID_SPRITE_BIG_MARIO_EAT_SUPERLEAF 65411
#define ID_SPRITE_BIG_MARIO_EAT_SUPERLEAF 65412

#define ID_ANI_BIG_MARIO_EATING_SUPERLEAF 9000

#define ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES 9100

#pragma endregion