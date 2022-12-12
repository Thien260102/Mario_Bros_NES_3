#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_ATTACKING_SPEED 0.2f

#define KOOPAS_DIE_DEFLECT  0.4f

#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_DIE 15	//height die, shell, attack

#define KOOPAS_PHASE_CHECK_SIZE 10

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

	float ax;
	float ay;

	int level;

	ULONGLONG shellForm_start;
	ULONGLONG die_start;
	
	virtual int IsCollidable() { return state != KOOPAS_STATE_DIE; }
	virtual int IsBlocking() { return 0; }

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);

	int GetAniId();
public:
	CKoopas(float x, float y) :CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPAS_GRAVITY;
		shellForm_start = -1;
		die_start = -1;
		SetState(KOOPAS_STATE_WALKING);
		level = KOOPAS_LEVEL_NORMAL;
	}
	void SetState(int state);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetLevel(int level);

	void SetNx(int nx) { this->nx = nx; }
};

