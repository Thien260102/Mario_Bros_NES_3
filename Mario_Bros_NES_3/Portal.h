#pragma once

#include "GameObject.h"
#include "AssetIDs.h"

#define GIFT_FLYING_SPEED 0.02f

#define GIFT_TYPE_MUSHROOM	1
#define GIFT_TYPE_FLOWER	2
#define GIFT_TYPE_STAR		3

#define ID_ANI_GIFT_MUSHROOM	11100
#define ID_ANI_GIFT_FLOWER		11101
#define ID_ANI_GIFT_STAR		11102

#define SWITCH_GIFT_TIME 100
#define SWITCHING_SCENE_TIME 2000

#define PORTAL_TYPE_PLAYSCENE_TO_ANOTHER 1
#define PORTAL_TYPE_ANOTHER_TO_PLAYSCENE 2
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	int _type;

	int giftType;

	ULONGLONG switchGift_start;
	ULONGLONG switchScene_start;

	float width;
	float height; 

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CPortal(float l, float t, float r, float b, int scene_id , int type = 1);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

	void SwitchScene();
	int IsSwitchingScene() { return switchScene_start; }

	int GetSpriteGift() 
	{ 
		switch (giftType)
		{
		case GIFT_TYPE_MUSHROOM:
			return ID_SPRITE_GIFT_MUSHROOM;
		case GIFT_TYPE_FLOWER:
			return ID_SPRITE_GIFT_FLOWER;
		default:
			return ID_SPRITE_GIFT_STAR;
		}
	}
};