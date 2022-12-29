#include "PhaseChecker.h"
#include "Brick.h"
#include "debug.h"

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


	if (_type == PHASECHECK_BY_MARIO && x != old_x)
		DebugOut(L"x: %f, old_x: %f\n", x, old_x);

	if (attack_start != 0)
	{
		/*if (vy == ay * dt)
			vy = 0;*/
		if ((GetTickCount64() - attack_start > PHASECHECK_ATTACK_TIME))
		{
			vx = 0;
			vy = 0;
		}
		// use this case if tail of Mario over the attack range
		else if (_type == PHASECHECK_BY_MARIO && abs(x + vx * dt - old_x) > PHASECHECK_ATTACK_RANGE * width)
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
		else if (isAttackBehind == false && ((GetTickCount64() - attack_start) < PHASECHECK_ATTACK_TIME / 4))
		{
			CCollision::GetInstance()->Process(this, coObjects);
		}


		if (isAttackedFront == false)
			CCollision::GetInstance()->Process(this, dt, coObjects);

		return;
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

	isAttackedFront = true;
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if ((CKoopas*)(e->obj))
		OnCollisionWithKoopas(e);
	else
		isAttackedFront = false;
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
	if (goomba->GetState() == GOOMBA_STATE_DIE_1 || goomba->GetState() == GOOMBA_STATE_DIE_2)
		return;

	goomba->SetState(GOOMBA_STATE_DIE_2);
	if (e->nx > 0)
		goomba->Deflected(DEFLECT_DIRECTION_LEFT);
	else
		goomba->Deflected(DEFLECT_DIRECTION_RIGHT);
}

void CPhaseChecker::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	e->obj->SetState(200); // KOOPAS_STATE_SHELL 200

	float kx, ky;
	e->obj->GetPosition(kx, ky);
	if (kx <= x)
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


void CPhaseChecker::OnCollisionWith(LPGAMEOBJECT obj)
{
	isAttackBehind = true;
	if (dynamic_cast<CBrick*>(obj))
	{
		DebugOut(L"Hello brick\n");
		obj->Delete();

	}
	else if (dynamic_cast<CGoomba*>(obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
		if (goomba->GetState() == GOOMBA_STATE_DIE_1 || goomba->GetState() == GOOMBA_STATE_DIE_2)
			return;
		DebugOut(L"Hello goomba\n");
		goomba->SetState(GOOMBA_STATE_DIE_2);
		float gx, gy;
		obj->GetPosition(gx, gy);
		if (gx < x)
			goomba->Deflected(DEFLECT_DIRECTION_LEFT);
		else
			goomba->Deflected(DEFLECT_DIRECTION_RIGHT);
	}
	else if (dynamic_cast<CPlant*>(obj))
	{
		DebugOut(L"Hello plant\n");
		obj->Delete();
	}
	else if ((CKoopas*)obj)
	{
		obj->SetState(200); // KOOPAS_STATE_SHELL 200
		DebugOut(L"Hello koopas\n");
		float kx, ky;
		obj->GetPosition(kx, ky);
		if (kx <= x)
			obj->Deflected(DEFLECT_DIRECTION_LEFT);
		else
			obj->Deflected(DEFLECT_DIRECTION_RIGHT);
	}

	//draw collision effect
}