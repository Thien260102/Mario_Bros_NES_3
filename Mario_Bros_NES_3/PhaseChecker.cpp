#include "PhaseChecker.h"

void CPhaseChecker::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}

void CPhaseChecker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	// use this case if tail of Mario over the attack range
	if (_type == PHASECHECK_BY_MARIO && abs(x + vx * dt - old_x) > 4 * width)
	{
		if (vx >= 0)
		{
			vx = (PHASECHECK_ATTACK_RANGE * width + old_x - x) / dt;
		}
		else
		{
			vx = (old_x - PHASECHECK_ATTACK_RANGE * width - x) / dt;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPhaseChecker::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	if (_type == PHASECHECK_BY_KOOPAS || e->nx == 0)
		return;

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if ((CKoopas*)(e->obj))
		OnCollisionWithKoopas(e);
}


void CPhaseChecker::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	switch (brick->GetType())
	{
	case BRICK_TYPE_GOLD:
		brick->SetType(BRICK_TYPE_BREAK);
		break;

	case BRICK_TYPE_QUESTION:
		brick->SetType(BRICK_TYPE_EMPTY);
		break;
	}

}

void CPhaseChecker::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	goomba->SetState(GOOMBA_STATE_DIE_2);
	if (e->nx > 0)
		goomba->Deflected(DEFLECT_DIRECTION_LEFT);
	else
		goomba->Deflected(DEFLECT_DIRECTION_RIGHT);
}

void CPhaseChecker::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	e->obj->SetState(200); // KOOPAS_STATE_SHELL 200
	if (e->nx > 0)
		e->obj->Deflected(DEFLECT_DIRECTION_LEFT);
	else
		e->obj->Deflected(DEFLECT_DIRECTION_RIGHT);
}

void CPhaseChecker::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}

void CPhaseChecker::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
