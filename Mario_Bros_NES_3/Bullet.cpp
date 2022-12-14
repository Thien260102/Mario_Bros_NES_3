#include "Bullet.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;

}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	float cx, cy, cw, ch;

	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x < cx || (x > cx + 320) || y < cy || (y > cy + 240))
		this->Delete();
	
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CBullet::Render()
{
	int aniId = ID_ANI_BULLET_FIRE;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
