#pragma once
#ifndef CKOOPAS_H
#define CKOOPAS_H

#include "GameObject.h"
#include "PhaseChecker.h"



#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.04f
#define KOOPAS_ATTACKING_SPEED 0.2f
#define KOOPAS_FLY_SPEED_Y 0.2f

#define KOOPAS_DIE_DEFLECT  0.3f

#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_DIE 15	//height die, shell, attack

#define KOOPAS_PHASE_CHECK_HEIGHT 24
#define KOOPAS_PHASE_CHECK_WIDTH 14

#define KOOPAS_SHELL_TIMEOUT 5000
#define KOOPAS_DIE_TIMEOUT 500
#define KOOPAS_FLY_TIMEOUT 300

#define KOOPAS_STATE_FLYING 99
#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_ATTACKING 150
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_DIE 400

#define KOOPAS_TYPE_RED	10
#define KOOPAS_TYPE_GREEN 11

#define KOOPAS_LEVEL_NORMAL 1
#define KOOPAS_LEVEL_WING 2

#define ID_ANI_RED_KOOPAS_WALKING_LEFT 6000
#define ID_ANI_RED_KOOPAS_WALKING_RIGHT 6001
#define ID_ANI_RED_KOOPAS_SHELL_DOWN 6010
#define ID_ANI_RED_KOOPAS_SHELL_UP 6011
#define ID_ANI_RED_KOOPAS_REFORM_DOWN 6020
#define ID_ANI_RED_KOOPAS_REFORM_UP 6021
#define ID_ANI_RED_KOOPAS_ATTACKING 6030

#define ID_ANI_GREEN_KOOPAS_WALKING_LEFT 6100
#define ID_ANI_GREEN_KOOPAS_WALKING_RIGHT 6101
#define ID_ANI_GREEN_KOOPAS_SHELL_DOWN 6110
#define ID_ANI_GREEN_KOOPAS_SHELL_UP 6111
#define ID_ANI_GREEN_KOOPAS_REFORM_DOWN 6120
#define ID_ANI_GREEN_KOOPAS_REFORM_UP 6121
#define ID_ANI_GREEN_KOOPAS_ATTACKING 6130

#define ID_ANI_GREEN_WING_KOOPAS_FLYING_LEFT 6200
#define ID_ANI_GREEN_WING_KOOPAS_FLYING_RIGHT 6201

class CKoopas :public CGameObject
{
protected:
	CGameObject* phaseChecker;

	bool isUp;
	float ay;
	bool isHeld;
	int _type;
	int level;

	ULONGLONG time_start; // use in case Koopas die, Koopas flying, and Koopas shell to Koopas walking
	ULONGLONG deflection_start; // Mario Raccoon'tail attack
	
	virtual int IsCollidable() { return state != KOOPAS_STATE_DIE && isHeld == false; }
	virtual int IsBlocking() { return 0; }

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	int GetAniId();
public:
	CKoopas(float x, float y, int type, int l);
	void SetState(int state);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetLevel(int l);
	int GetLevel() { return level; }
	int GetNx() { return nx; }
	void SetNx(int nx) { this->nx = nx; }

	bool IsHeld() { return isHeld; }
	void isHold() { isHeld = true; }

	virtual void Deflected(int Direction);
};


#endif // !CKOOPAS_H