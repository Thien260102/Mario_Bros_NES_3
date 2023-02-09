#include "Enemy_WorldMap.h"

void CEnemy_WorldMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ENEMY_BBOX_WIDTH / 2;
	top = y - ENEMY_BBOX_HEIGHT / 2;
	right = left + ENEMY_BBOX_WIDTH;
	bottom = top + ENEMY_BBOX_HEIGHT;
}

void CEnemy_WorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	if (abs(old_x - x) >= _range)
	{
		nx = -nx;
		vx = -vx;
		old_x = x;
	}
}

void CEnemy_WorldMap::Render()
{
	int aniId = ENEMY_WALKING_RIGHT;
	if (nx < 0)
		aniId = ENEMY_WALKING_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}