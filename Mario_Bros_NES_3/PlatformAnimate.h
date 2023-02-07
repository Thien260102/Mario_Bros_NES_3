#pragma once
#include "GameObject.h"

#define PLATFORM_ANIMATE_BBOX_WIDTH 15
#define PLATFORM_ANIMATE_BBOX_HEIGHT 15

#define PLATFORM_ANIMATE_TYPE_BLOCK 1 //Blocking
#define PLATFORM_ANIMATE_TYPE_GATE	2 //can crossed by Mario
#define PLATFORM_ANIMATE_TYPE_NO_COLLISION	3

class CPlatformAnimate : public CGameObject
{
protected:
	int aniOrsprite;
	int _type;
	int isAni; // 1: animation, 0: sprite

	virtual int IsBlocking() { return _type != PLATFORM_ANIMATE_TYPE_NO_COLLISION; }
public:
	CPlatformAnimate(float x, float y, int AniOrSprite, int type = 1, int IsAni = 1) : CGameObject(x, y)
	{
		aniOrsprite = AniOrSprite;
		_type = type;
		isAni = IsAni;
	}
	
	int GetType() { return _type; }

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

