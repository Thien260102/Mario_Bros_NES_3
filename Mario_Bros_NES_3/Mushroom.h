#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Brick.h"
#include "Goomba.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_WALKING_SPEED 0.065f
#define MUSHROOM_CREATE_SPEED 0.02f
#define MUSHROOM_DEFLECT_SPEED 0.3f

#define MUSHROOM_DEFLECT_MAX_HEIGHT 16.0f

#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_TYPE_SUPER 1
#define MUSHROOM_TYPE_1UP 2
#define MUSHROOM_TYPE_SUPER_LEAF 3

#define TIME_LEAF_DIVERT 500

class CMushroom: public CGameObject
{
protected:
	float ay;
	int type;
	ULONGLONG time_start;
	float old_y;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void IsDiversion();
	virtual void Deflected(int direction = 0);
public:
	CMushroom(float x, float y, int type);
	int getType() { return type; }
	void CreatedByBrick();
};

