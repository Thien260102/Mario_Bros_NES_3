#include "Goomba.h"
#include "debug.h"
#include "Brick.h"
#include "Koopas.h"
#include "Platform.h"

CGoomba::CGoomba(float x, float y, int type, int l):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	time_start = -1;
	_type = type;
	jump_count = 0;
	redWing_start = -1;
	vx = -GOOMBA_WALKING_SPEED;
	SetLevel(l);

	if (level != GOOMBA_LEVEL_WING)
		SetState(GOOMBA_STATE_WALKING);
	else
		SetState(GOOMBA_STATE_JUMPING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE_1)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		if (level == GOOMBA_LEVEL_WING)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_WING_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_WING_BBOX_HEIGHT;
		}
		else
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}

}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		// solve collision with new Platform
		if (dynamic_cast<CPlatform*>(e->obj))
		{
			CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
			switch (platform->GetType())
			{
			case PLATFORM_TYPE_BLOCK:
				vy = 0;
				break;
			case PLATFORM_TYPE_NORMAL:
				if (e->ny < 0)
					vy = 0;
			}

		}
		else if (e->obj->IsBlocking())
			vy = 0;
		
	}
	else if (e->nx != 0)
	{
		// solve collision with new Platform
		if (dynamic_cast<CPlatform*>(e->obj))
		{
			if (dynamic_cast<CPlatform*>(e->obj)->GetType() == PLATFORM_TYPE_BLOCK)
			{
				vx = -vx;
			}
		}
		else if (e->obj->IsBlocking())
			vx = -vx;
	}

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CGoomba::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (brick->IsAttacking() && brick->IsBrokenByMarioJump() && e->ny != 0)
	{
		this->SetState(GOOMBA_STATE_DIE_2);

		float bx, by;
		brick->GetPosition(bx, by);

		if (bx < x)
			this->Deflected(DEFLECT_DIRECTION_RIGHT);
		else
			this->Deflected(DEFLECT_DIRECTION_LEFT);
	}
}

void CGoomba::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->state == GOOMBA_STATE_DIE_1 || goomba->state == GOOMBA_STATE_DIE_2)
		return;

	if (e->nx != 0)
	{
		goomba->vx = this->vx;
		this->vx = -this->vx;
	}
}

void CGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	switch (koopas->GetState())
	{
	case KOOPAS_STATE_ATTACKING:
		this->SetState(GOOMBA_STATE_DIE_2);
		
		if (e->nx >= 0)
			this->Deflected(DEFLECT_DIRECTION_RIGHT);
		else
			this->Deflected(DEFLECT_DIRECTION_LEFT);
		break;

	case KOOPAS_STATE_SHELL:
		if (koopas->IsHeld())
		{
			DebugOut(L"Goomba collide Koopas\n");
			koopas->SetState(KOOPAS_STATE_DIE);
			this->SetState(GOOMBA_STATE_DIE_2);
		}

	}

}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE_1 || state == GOOMBA_STATE_DIE_2) && (GetTickCount64() - time_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	
	if (level == GOOMBA_LEVEL_WING)
	{
		//DebugOut(L"State: %d\n", state);
		switch (state)
		{
		case GOOMBA_STATE_JUMPING:
			if (jump_count >= 3)
			{
				SetState(GOOMBA_STATE_FLYING);
				jump_count = 0;
				redWing_start = GetTickCount64();
			}
			else if (vy == ay * dt && (GetTickCount64() - redWing_start) > GOOMBA_RED_WING_RELEASE_JUMP_TIME)
				SetState(GOOMBA_STATE_JUMPING);
			break;

		case GOOMBA_STATE_FLYING:
			if (redWing_start == -1) //Goomba On Platform
			{
				SetState(GOOMBA_STATE_WALKING);
				redWing_start = GetTickCount64();
			}
			else if (vy == ay * dt)
			{
				redWing_start = -1;
			}
			break;

		case GOOMBA_STATE_WALKING:
			if (GetTickCount64() - redWing_start > GOOMBA_RED_WING_WALK_TIME)
			{
				SetState(GOOMBA_STATE_JUMPING);
				redWing_start = -1;
			}
			break;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = GetAniId();

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE_1:
			if (level == GOOMBA_LEVEL_WING)
			{
				SetLevel(GOOMBA_LEVEL_NORMAL);
				SetState(GOOMBA_STATE_WALKING);
				return;
			}
			time_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_DIE_2:
			time_start = GetTickCount64();
			break;
		case GOOMBA_STATE_WALKING: 
			
			break;
		case GOOMBA_STATE_FLYING:
			vy = -GOOMBA_FLY_SPEED_Y;
			break;
		case GOOMBA_STATE_JUMPING:
			redWing_start = GetTickCount64();
			vy = -GOOMBA_JUMP_SPEED_Y;
			jump_count += 1;
			break;
	}
}

int CGoomba::GetAniId()
{
	int aniId = ID_ANI_GOOMBA_WALKING;

	switch (_type)
	{
	case GOOMBA_TYPE_NORMAL:
		aniId = ID_ANI_GOOMBA_WALKING;

		if (state == GOOMBA_STATE_DIE_1)
			aniId = ID_ANI_GOOMBA_DIE_1;
		else if (state == GOOMBA_STATE_DIE_2)
			aniId = ID_ANI_GOOMBA_DIE_2;

		break;

	case GOOMBA_TYPE_RED:
		aniId = ID_ANI_RED_GOOMBA_WALKING;

		if (level == GOOMBA_LEVEL_NORMAL)
		{

			if (state == GOOMBA_STATE_DIE_1)
				aniId = ID_ANI_RED_GOOMBA_DIE_1;
			else if (state == GOOMBA_STATE_DIE_2)
				aniId = ID_ANI_RED_GOOMBA_DIE_2;
		}
		else
			if (state == GOOMBA_STATE_DIE_2)
				aniId = ID_ANI_RED_GOOMBA_DIE_2;
			else if (state == GOOMBA_STATE_FLYING)
				aniId = ID_ANI_RED_WING_GOOMBA_FLYING;
			else if (state == GOOMBA_STATE_JUMPING)
				aniId = ID_ANI_RED_WING_GOOMBA_JUMPING;
			else if (state == GOOMBA_STATE_WALKING)
				aniId = ID_ANI_RED_WING_GOOMBA_WALKING;

		break;
	}

	return aniId;
}

void CGoomba::Deflected(int Direction)
{
	vy = -GOOMBA_DIE_DEFLECT;
	ay = GOOMBA_GRAVITY;

	vx = Direction * GOOMBA_WALKING_SPEED;
	ax = 0;
}

void CGoomba::SetLevel(int l)
{
	if (level == GOOMBA_LEVEL_WING)
	{
		y -= (GOOMBA_WING_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT);
	}

	level = l;
}