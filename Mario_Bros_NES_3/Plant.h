#pragma once
#include "GameObject.h"

#define PLANT_RISING_DOWNING_ACCEL 0.001f

#define PLANT_TYPE_GREEN 1
#define PLANT_TYPE_GREEN_FIRE 2
#define PLANT_TYPE_RED_FIRE 3


#define PLANT_STATE_RISE 111
#define PLANT_STATE_DOWN 222
#define PLANT_STATE_ATTACK 333

#define PLANT_GREEN_BBOX_WIDTH 15
#define PLANT_GREEN_BBOX_HEIGHT 23

#define PLANT_RED_BBOX_WIDTH 15
#define PLANT_RED_BBOX_HEIGHT 31

#define ID_ANI_PLANT_GREEN 7000
#define ID_ANI_PLANT_GREEN_FIRE	7001
#define ID_ANI_PLANT_RED_FIRE 7002

class CPlant:public CGameObject
{
protected:
	float ay;
	int _type;

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
		vy = 0;
		vx = 0;
		ay = 0;
		SetState(PLANT_STATE_RISE);
	}

	virtual void SetState(int state);
};

