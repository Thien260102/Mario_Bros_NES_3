#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define PLANT_RISING_DOWNING_SPEED 0.02f

#define PLANT_TYPE_GREEN 1
#define PLANT_TYPE_GREEN_FIRE 2
#define PLANT_TYPE_RED_FIRE 3


#define PLANT_STATE_RISE 111
#define PLANT_STATE_DOWN 222
#define PLANT_STATE_ATTACK 333
#define PLANT_STATE_IDLE 444

#define PLANT_GREEN_BBOX_WIDTH 15
#define PLANT_GREEN_BBOX_HEIGHT 23

#define PLANT_RED_BBOX_WIDTH 15
#define PLANT_RED_BBOX_HEIGHT 31

#define DISTANCE_BETWEEN_MARIO_AND_PLANT 30 // Plant only rise when distance 30 from Mario

#define ID_ANI_PLANT_GREEN 7000

#define ID_ANI_PLANT_GREEN_FIRE	7100
#define ID_ANI_PLANT_GREEN_TARGET_TOP 7101
#define ID_ANI_PLANT_GREEN_TARGET_BOT 7102

#define ID_ANI_PLANT_RED_FIRE 7200
#define ID_ANI_PLANT_RED_TARGET_TOP 7201
#define ID_ANI_PLANT_RED_TARGET_BOT 7202

#define PLANT_ATTACK_IDLE_TIME 3000

class CPlant:public CGameObject
{
protected:
	float ay;
	int _type;
	float old_y; //save original y value

	float Mario_x, Mario_y;

	ULONGLONG time_start;
	CGameObject* _bullet;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();


	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt) {}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}
	int GetAniId();
public:
	CPlant(float x, float y, int type) :CGameObject(x, y)
	{
		_type = type;
		old_y = y;
		time_start = 0;
		Mario_x = 0;
		Mario_y = 0;
		vy = 0;
		vx = 0;
		ay = 0;
		SetState(PLANT_STATE_RISE);
		_bullet = NULL;
	}

	virtual void SetState(int state);
};

