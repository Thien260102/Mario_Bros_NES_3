#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.001f
#define GOOMBA_WALKING_SPEED 0.04f

#define GOOMBA_JUMP_SPEED_Y 0.08f
#define GOOMBA_FLY_SPEED_Y 0.3f

#define GOOMBA_DIE_DEFLECT  0.2f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_WING_BBOX_HEIGHT 20

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_JUMPING 49
#define GOOMBA_STATE_FLYING 50
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE_1 200	// by Mario jump on the head
#define GOOMBA_STATE_DIE_2 300	// attack by Koopas, Mario Raccoon attack or collision with brick

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE_1 5001 // die by mario jump on the head
#define ID_ANI_GOOMBA_DIE_2 5002 // die by Mario Racoon's tail attack

#define ID_ANI_RED_GOOMBA_WALKING 5100
#define ID_ANI_RED_GOOMBA_DIE_1 5101 // die by mario jump on the head
#define ID_ANI_RED_GOOMBA_DIE_2	5102 // die by Mario Racoon's tail attack

#define ID_ANI_RED_WING_GOOMBA_FLYING 5200
#define ID_ANI_RED_WING_GOOMBA_WALKING 5201
#define ID_ANI_RED_WING_GOOMBA_JUMPING 5202

#define GOOMBA_TYPE_NORMAL 1
#define GOOMBA_TYPE_RED 2
#define GOOMBA_TYPE_RED_WING 3

#define GOOMBA_JUMP 3

#define GOOMBA_RED_WING_WALK_TIME 1000
#define GOOMBA_RED_WING_RELEASE_JUMP_TIME 100

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	int _type;

	ULONGLONG time_start; // use in case Goomba Die

	int jump_count;
	ULONGLONG redWing_start; // use for Red Wing Goomba

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();


	virtual int IsCollidable() { return state != GOOMBA_STATE_DIE_1 && state != GOOMBA_STATE_DIE_2; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	int GetAniId();

public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);

	virtual void Deflected(int Direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};