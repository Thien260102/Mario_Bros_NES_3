#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Tail.h"
#include "Koopas.h"
#include "Hud.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_WALKING_SPEEDUP	0.15f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0001f
#define MARIO_ACCEL_CHANGE_DIRECTION 0.0007f

#define MARIO_JUMP_SPEED_Y		0.38f
#define MARIO_JUMP_RUN_SPEED_Y	0.45f

#define MARIO_FLY_SPEED_Y 0.2f
#define MARIO_FLOAT_SPEED_Y 0.06f

#define MARIO_GRAVITY			0.001f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_ATTACK		700

#define MARIO_STATE_KICK		710

#define MARIO_STATE_READY_HOLD		800
#define MARIO_STATE_HOLD_RELEASE	810

#define MARIO_STATE_FLY 900
#define MARIO_STATE_RELEASE_FLY 901


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501
#define ID_ANI_MARIO_WALKING_SPEEDUP_RIGHT 502
#define ID_ANI_MARIO_WALKING_SPEEDUP_LEFT 503

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 1002
#define ID_ANI_MARIO_KICK_LEFT 1003

#define ID_ANI_MARIO_HOLD_RUN_RIGHT 1004
#define ID_ANI_MARIO_HOLD_RUN_LEFT 1005

#define ID_ANI_MARIO_HOLD_STAND_RIGHT 1006
#define ID_ANI_MARIO_HOLD_STAND_LEFT 1007

#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 1008
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 1009

#define ID_ANI_MARIO_GETINTO_PIPE 1010

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201
#define ID_ANI_MARIO_SMALL_WALKING_SPEEDUP_RIGHT 1202
#define ID_ANI_MARIO_SMALL_WALKING_SPEEDUP_LEFT 1203

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1610
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1611

#define ID_ANI_MARIO_SMALL_HOLD_RUN_RIGHT 1650
#define ID_ANI_MARIO_SMALL_HOLD_RUN_LEFT 1651
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1652
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1653

#define ID_ANI_MARIO_SMALL_HOLD_STAND_RIGHT 1660
#define ID_ANI_MARIO_SMALL_HOLD_STAND_LEFT 1661

#define ID_ANI_MARIO_SMALL_TRANSFORM_BIG_RIGHT 1688
#define ID_ANI_MARIO_SMALL_TRANSFORM_BIG_LEFT 1689

#define ID_ANI_MARIO_SMALL_GETINTO_PIPE 1699

//	RACCOON MARIO	//
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801
#define ID_ANI_MARIO_RACCOON_WALKING_SPEEDUP_RIGHT 1802
#define ID_ANI_MARIO_RACCOON_WALKING_SPEEDUP_LEFT 1803

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_UP_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_UP_LEFT 2001
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_DOWN_RIGHT 2002
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_DOWN_LEFT 2003

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_UP_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_UP_LEFT 2101
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_DOWN_RIGHT 2102
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_DOWN_LEFT 2103

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2201

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCOON_GETINTO_SEWER 2302

#define ID_ANI_MARIO_RACCOON_ATTACK_RIGHT 2400
#define ID_ANI_MARIO_RACCOON_ATTACK_LEFT 2401

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 2500
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 2501

#define ID_ANI_MARIO_RACCOON_HOLD_STAND_RIGHT 2600
#define ID_ANI_MARIO_RACCOON_HOLD_STAND_LEFT 2601

#define ID_ANI_MARIO_RACCOON_HOLD_RUN_RIGHT 2700
#define ID_ANI_MARIO_RACCOON_HOLD_RUN_LEFT 2701
#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT 2702
#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT 2703

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 2801
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 2802
#define ID_ANI_MARIO_RACCOON_FLOAT_RIGHT 2811
#define ID_ANI_MARIO_RACCOON_FLOAT_LEFT 2812
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON 3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 13

#define MARIO_RACCOON_BBOX_WIDTH (MARIO_BIG_BBOX_WIDTH)
#define MARIO_RACCOON_BBOX_HEIGHT 25
#define MARIO_RACCOON_SITTING_BBOX_WIDTH (MARIO_BIG_SITTING_BBOX_WIDTH + 0)
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 16

#define MARIO_TAIL_WIDTH 10
#define MARIO_TAIL_HEIGHT 5
#define MARIO_TAIL_POSTION_ADJUST 5

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_ATTACK_TIME 300
#define MARIO_KICK_TIME 200
#define MARIO_FLY_TIME 4000
#define MARIO_REFLOAT_TIME 200
#define MARIO_TRANSFORMATION_TIME 600

#define MARIO_GETINTO_PIPE_DOWN 1
#define MARIO_GETINTO_PIPE_UP	2

class CMario : public CGameObject
{
	CKoopas* _koopas;
	CGameObject* _tail;

	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int canGetIntoPipe;

	int old_level;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int holdable;
	int coin; 

	int flag;
	ULONGLONG time_start; // to manage render time of some states (attack, kick), animations
	ULONGLONG fly_start;
	ULONGLONG float_start;
	ULONGLONG transform_start;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = CHud::GetInstance()->GetLevel();
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		
		flag = 0;
		time_start = 0;
		
		holdable = 0;
		_koopas = NULL;

		_tail = new CTail(x, y);
		fly_start = 0;
		float_start = 0;
		transform_start = 0;

		canGetIntoPipe = 0;
	}

	void SetGravity(float gravity) { ay = gravity; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	int IsUntouchable() { return untouchable; }
	int GetLevel() { return level; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsHolding() { return _koopas != NULL; }

	BOOLEAN IsOnPlatform() { return isOnPlatform; }

	bool IsFlying() { return fly_start != 0; }
	bool IsFloating() { return float_start != 0; }

	void SetTransform_start() { transform_start = GetTickCount64(); }
	bool IsTransforming() { return transform_start != 0; }

	void SetcanGetIntoPipe(int var) { canGetIntoPipe = var; } // to determine DIK_UP(OnKeyDown or OnKeyUp) to get into pipe
	int IsCanGetIntoPipe() { return canGetIntoPipe; }

	void SetMaxVx(float v) { maxVx = v; }
};