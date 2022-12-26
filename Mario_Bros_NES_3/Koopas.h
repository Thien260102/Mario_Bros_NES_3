#pragma once
#ifndef CKOOPAS_H
#define CKOOPAS_H

#include "GameObject.h"
#include "PhaseChecker.h"



#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.04f
#define KOOPAS_ATTACKING_SPEED 0.2f

#define KOOPAS_DIE_DEFLECT  0.3f

#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_DIE 15	//height die, shell, attack

#define KOOPAS_PHASE_CHECK_HEIGHT 24
#define KOOPAS_PHASE_CHECK_WIDTH 14

#define KOOPAS_SHELL_TIMEOUT 5000
#define KOOPAS_DIE_TIMEOUT 500

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_ATTACKING 150
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_DIE 400

#define KOOPAS_LEVEL_SHELL 1
#define KOOPAS_LEVEL_NORMAL 2

#define ID_ANI_KOOPAS_WALKING 6000
#define ID_ANI_KOOPAS_SHELL 6001
#define ID_ANI_KOOPAS_REFORM 6002
#define ID_ANI_KOOPAS_ATTACKING 6003




class CKoopas :public CGameObject
{
protected:
	CGameObject* phaseChecker;

	float ay;
	int level;
	bool isHeld;

	ULONGLONG time_start; // use in case Koopas die, and Koopas shell to Koopas walking
	ULONGLONG deflection_start;
	
	virtual int IsCollidable() { return state != KOOPAS_STATE_DIE && isHeld == false; }
	virtual int IsBlocking() { return 0; }

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);

	int GetAniId();
public:
	CKoopas(float x, float y) :CGameObject(x, y)
	{
		phaseChecker = new CPhaseChecker(x - KOOPAS_BBOX_WIDTH - KOOPAS_PHASE_CHECK_WIDTH / 2, y,
			KOOPAS_PHASE_CHECK_WIDTH, KOOPAS_PHASE_CHECK_HEIGHT, PHASECHECK_BY_KOOPAS);
		phaseChecker->SetSpeed(0, KOOPAS_WALKING_SPEED);

		this->ay = KOOPAS_GRAVITY;
		time_start = -1;
		SetState(KOOPAS_STATE_WALKING);
		level = KOOPAS_LEVEL_NORMAL;
		isHeld = 0;

		deflection_start = 0;
	}
	void SetState(int state);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetLevel(int level);

	int GetNx() { return nx; }
	void SetNx(int nx) { this->nx = nx; }

	bool IsHeld() { return isHeld; }
	void isHold() { isHeld = true; }

	virtual void Deflected(int Direction);
};


#endif // !CKOOPAS_H