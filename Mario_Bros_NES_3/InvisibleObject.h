#pragma once
/*****************************
Using this in case: when I should update Wing Koopas
****************************/

#include "GameObject.h"
#include "debug.h"

#define INVISIBLE_BBOX_WIDTH 10
#define INVISIBLE_BBOX_HEIGHT 500

class CInvisibleObject : public CGameObject
{
private:
	int isActived;
public:

	CInvisibleObject(float x, float y) : CGameObject(x, y)
	{
		isActived = 0;
	}
	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Activating() { isActived = 1; }
	int IsActived() { DebugOut(L"isActived: %d\n", isActived); return isActived; }
};

