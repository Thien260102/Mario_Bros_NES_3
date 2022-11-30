#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Brick.h"
#include "Goomba.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_SUPER 1
#define MUSHROOM_1UP 2


class CMushroom: public CGameObject
{
protected:
	float ax;
	float ay;
	int type;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y, int type);
	int getType() { return type; }
};

