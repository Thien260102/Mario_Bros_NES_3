#pragma once
#include "GameObject.h"

#define ENEMY_WALKING_SPEED 0.01f

#define ENEMY_WALKING_RIGHT	20002
#define ENEMY_WALKING_LEFT	20003

#define ENEMY_BBOX_WIDTH 15
#define ENEMY_BBOX_HEIGHT 15

class CEnemy_WorldMap : public CGameObject
{
private:
	float _range;
	float old_x;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();


	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }

public:
	CEnemy_WorldMap(float x, float y, float range = 0) : CGameObject(x, y)
	{
		_range = range;
		vy = 0;
		vx = ENEMY_WALKING_SPEED;
		nx = 1;
		old_x = x;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};

