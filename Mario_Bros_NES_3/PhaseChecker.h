#pragma once
#ifndef CPHASECHECKER_H
#define CPHASECHECKER_H


#include "GameObject.h"
#include "Goomba.h"
#include "Brick.h"
#include "Plant.h"

#define PHASECHECK_GRAVITY 0.001f
#define PHASECHECK_ATTACK_SPEED	1.5f
#define PHASECHECK_ATTACK_RANGE 3.0f

#define PHASECHECK_BY_KOOPAS 10
#define PHASECHECK_BY_MARIO 20

#define PHASECHECK_ATTACK_TIME 300

class CKoopas;

class CPhaseChecker : public CGameObject
{
protected:
	int width;
	int height;

	float old_x;
	int isAttackedFront;
	int isAttackedBehind;

	int _type;

	float ax;
	float ay;
	ULONGLONG attack_start;

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }


	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWith(LPGAMEOBJECT o);

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
public:
	//CPhaseCheck() : CGameObject() {}
	CPhaseChecker(float x, float y, int Width, int Height, int type) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = PHASECHECK_GRAVITY;
		vy = 0;
		width = Width;
		height = Height;
		_type = type;
		old_x = x;
		attack_start = 0;
		isAttackedFront = 0;
		isAttackedBehind = 0;
	}

	void Attack(int direction) 
	{ 
		vx += PHASECHECK_ATTACK_SPEED * direction;
		old_x = x;
		isAttackedFront = 0; // only attack 1 gameobject in front of Mario
		isAttackedBehind = 0;  // only attack 1 gameobject(except Block, Platform) behide Mario

		nx = direction;
	}

	bool IsAttacking() { return attack_start != 0; }

	void SetAttackTime(ULONGLONG time) 
	{ 
		attack_start = time; 
	}

	int GetType() { return _type; }

};

#endif // !CPHASECHECKER_H