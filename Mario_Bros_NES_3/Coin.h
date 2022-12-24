#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define COIN_DEFLECT  0.4f //use when Mario jump into Brick from below
#define COIN_GRAVITY 0.001f //use when Mario jump into Brick from below

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_DEFLECT 11001

//#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 15
#define COIN_BBOX_HEIGHT 15

class CCoin : public CGameObject {
private:
	float ay;
public:
	CCoin(float x, float y) : CGameObject(x, y) { ay = 0; vy = 0; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Deflected(int direction);
};