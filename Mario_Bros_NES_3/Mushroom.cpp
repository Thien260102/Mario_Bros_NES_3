#include "Mushroom.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Hud.h"
#include "Effect.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y)
{
	old_y = 0;
	time_start = 0;
	this->type = type;
	if (type == MUSHROOM_TYPE_SUPER_LEAF)
	{
		time_start = GetTickCount64();
	}

	this->ay = MUSHROOM_GRAVITY;
	vx = MUSHROOM_WALKING_SPEED;

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
	vy += ay * dt;

	switch (type)
	{
	case MUSHROOM_TYPE_SUPER_LEAF:
		if (vy > 0) // created time out
		{
			if (vx == 0) // time deflect out
			{
				vx = MUSHROOM_WALKING_SPEED;
				time_start = GetTickCount64();
			}

			IsDiversion();
			vy = ay * dt;

			vector<LPGAMEOBJECT> object;
			if (dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene()))
			{
				CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
				object.push_back(mario);
				CCollision::GetInstance()->Process(this, dt, &object);

			}
			else
				CCollision::GetInstance()->Process(this, dt, &object);
			return;
		}

		break;

	default:
		if ((old_y - y) >= MUSHROOM_DEFLECT_MAX_HEIGHT) // created time out
		{
			ay = MUSHROOM_GRAVITY;
			vx = MUSHROOM_WALKING_SPEED;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int spriteId;
	if (type == MUSHROOM_TYPE_SUPER)
		spriteId = ID_SPRITE_SUPERMUSHROOM;
	else if (type == MUSHROOM_TYPE_1UP)
		spriteId = ID_SPRITE_1UPMUSHROOM;
	else
	{
		if (vx > 0)
			spriteId = ID_SPRITE_SUPERLEAF_RIGHT;
		else
			spriteId = ID_SPRITE_SUPERLEAF_LEFT;
	}
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
	if (isDeleted) return;

	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (type == MUSHROOM_TYPE_1UP)
		{
			// + 1 up
			CHud::GetInstance()->Collect_1upMushroom();
			CEffect::GetInstance()->pushEffectIntoQueue(x, y, ID_SPRITE_POINTS_1UP, true, true);
		}
		else
		{
			/*if (mario->GetLevel() != MARIO_LEVEL_RACCOON)
				mario->SetTransform_start();*/

			switch (mario->GetLevel())
			{
			case MARIO_LEVEL_SMALL:
				mario->SetLevel(MARIO_LEVEL_BIG);
				break;
			case MARIO_LEVEL_BIG:
				mario->SetLevel(MARIO_LEVEL_RACCOON);
				break;
			}

			CHud::GetInstance()->CollectScore(SCORE_SUPER_MUSHROOM_LEAF);
			CEffect::GetInstance()->pushEffectIntoQueue(x, y, ID_SPRITE_POINTS_1000, true, true);
		}
		this->Delete();
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (brick->IsAttacking())
		{
			this->Deflected();
			this->vx = -vx;
		}
	}

	if (!e->obj->IsBlocking() 
		|| (dynamic_cast<CGoomba*>(e->obj)) 
		|| (dynamic_cast<CMushroom*>(e->obj)))
		return;


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
	if (GetTickCount64() - time_start >= TIME_LEAF_DIVERT)
	{
		vx = -vx;
		time_start = GetTickCount64();
	}
}

void CMushroom::CreatedByBrick()
{
	old_y = y;

	if (type == MUSHROOM_TYPE_SUPER_LEAF)
	{
		Deflected();
		return;
	}

	ay = 0;
	vx = 0;
	vy = -MUSHROOM_CREATE_SPEED;
}

void CMushroom::Deflected(int direction)
{
	vy = -MUSHROOM_DEFLECT_SPEED;
	vx *= direction;
}