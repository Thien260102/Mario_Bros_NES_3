#pragma once

#include "GameObject.h"

#define GIFT_FLYING_SPEED 0.02f

#define GIFT_TYPE_MUSHROOM	1
#define GIFT_TYPE_FLOWER	2
#define GIFT_TYPE_STAR		3

#define ID_ANI_GIFT_MUSHROOM	11100
#define ID_ANI_GIFT_FLOWER		11101
#define ID_ANI_GIFT_STAR		11102

#define SWITCH_GIFT_TIME 100
#define SWITCHING_SCENE_TIME 2000
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	int giftType;

	ULONGLONG switchGift_start;
	ULONGLONG switchScene_start;

	float width;
	float height; 

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

	void SwitchScene();
	int IsSwitchingScene() { return switchScene_start; }
};