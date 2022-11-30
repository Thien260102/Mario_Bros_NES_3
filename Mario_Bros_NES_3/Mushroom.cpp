#include "Mushroom.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->type = type;
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


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int spriteId;
	if (type == MUSHROOM_SUPER)
		spriteId = ID_SPRITE_SUPERMUSHROOM;
	else
		spriteId = ID_SPRITE_1UPMUSHROOM;
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
