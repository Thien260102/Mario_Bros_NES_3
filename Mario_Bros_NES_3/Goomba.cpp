#include "Goomba.h"
#include "debug.h"
#include "Brick.h"
#include "Koopas.h"

CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	time_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE_1)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
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
		vy = 0;

		
	}
	else if (e->nx != 0)
	{
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
		goomba->vx = -this->vx;
		this->vx = this->vx;
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
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}

int CGoomba::GetAniId()
{
	int aniId = ID_ANI_GOOMBA_WALKING;

	if (state == GOOMBA_STATE_DIE_1) aniId = ID_ANI_GOOMBA_DIE_1;
	


	return aniId;
}

void CGoomba::Deflected(int Direction)
{
	vy = -GOOMBA_DIE_DEFLECT;
	ay = GOOMBA_GRAVITY;

	vx = Direction * GOOMBA_WALKING_SPEED;
	ax = 0;
}