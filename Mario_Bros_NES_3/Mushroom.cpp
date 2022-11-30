#include "Mushroom.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	if (type == SUPER_LEAF)
	{
		this->ax = MUSHROOM_WALKING_SPEED / 1000;
		this->ay = MUSHROOM_GRAVITY / 6;
		start = GetTickCount64();
	}

	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vx = -MUSHROOM_WALKING_SPEED;

}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;

	if (type == SUPER_LEAF)
	{
		OnNoCollision(dt);
		IsDiversion();
		vy = ay * dt;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int spriteId;
	if (type == MUSHROOM_SUPER)
		spriteId = ID_SPRITE_SUPERMUSHROOM;
	else if (type == MUSHROOM_1UP)
		spriteId = ID_SPRITE_1UPMUSHROOM;
	else
		spriteId = ID_SPRITE_SUPERLEAF;
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
	//RenderBoundingBox();
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}


}

void CMushroom::IsDiversion()
{
	if (GetTickCount64() - start >= TIME_LEAF_DIVERT)
	{
		vx = -vx;
		start = GetTickCount64();
	}
}