#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Hud.h"
 
#define MARIO_WORLDMAP_WALKING_SPEED 0.1f

#define MARIO_WM_STATE_WALKING_RIGHT	1
#define MARIO_WM_STATE_WALKING_LEFT	2
#define MARIO_WM_STATE_WALKING_UP		3
#define MARIO_WM_STATE_WALKING_DOWN	4

#define ID_ANI_MARIO_SMALL_WORLDMAP 1222
#define ID_ANI_MARIO_BIG_WORLDMAP 444
#define ID_ANI_MARIO_RACCOON_WORLDMAP 1777

#define MARIO_BBOX_WIDTH 7
#define MARIO_BBOX_HEIGHT 15

#define MARIO_CROSSING_RANGE 15

class CMario_WorldMap :public CGameObject
{
protected:
	int level;
	int ny;
	int canGoIntoPortal;

	int absolutely_touching;
	ULONGLONG crossing_start;
	
	float old_pos;
public:
	CMario_WorldMap(float x, float y) : CGameObject(x, y)
	{
		level = CHud::GetInstance()->GetLevel();
		vx = 0;
		vy = 0;

		nx = 1;
		ny = 0;
		absolutely_touching = 0;
		crossing_start = 0;
		old_pos = 0;
		
		canGoIntoPortal = 0;
	}

	void SetCanGoIntoPortal(int is) { canGoIntoPortal = is; }

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int State);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWith(LPGAMEOBJECT o);
	void OnNoCollision(DWORD dt);

	void Render();
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }

	int IsMoving()
	{
		if (vx != 0 || vy != 0 || crossing_start != 0)
			return 1;
		
		return 0;
	}
};

