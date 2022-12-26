#include "Koopas.h"

#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"
#include "Plant.h"
#include "Platform.h"

CKoopas::CKoopas(float x, float y, int type) :CGameObject(x, y)
{
	phaseChecker = new CPhaseChecker(x - KOOPAS_BBOX_WIDTH - KOOPAS_PHASE_CHECK_WIDTH / 2, y,
		KOOPAS_PHASE_CHECK_WIDTH, KOOPAS_PHASE_CHECK_HEIGHT, PHASECHECK_BY_KOOPAS);
	phaseChecker->SetSpeed(0, KOOPAS_WALKING_SPEED);

	_type = type;
	this->ay = KOOPAS_GRAVITY;
	time_start = -1;

	if (_type == KOOPAS_TYPE_GREEN_FLY)
		SetState(KOOPAS_STATE_FLYING);
	else
		SetState(KOOPAS_STATE_WALKING);

	vx = -KOOPAS_WALKING_SPEED;

	isHeld = false;
	isUp = false;
	deflection_start = 0;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_ATTACKING || state == KOOPAS_STATE_DIE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPAS_STATE_SHELL && deflection_start == 0)
	{
		vx = 0;
	}

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
	////
	//if (this->isHeld && e->obj->IsBlocking())
	//	return;
	//change direction when Koopas blocked by brick
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

		float p_vx, p_vy;
		phaseChecker->GetSpeed(p_vx, p_vy);

		if (p_vx >= this->vx)
			phaseChecker->SetPosition(x - KOOPAS_BBOX_WIDTH, y);
		else
			phaseChecker->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
		
	}


	// phaseCheck is falling ?
	float px, py;
	phaseChecker->GetPosition(px, py);
	if (py - this->y > 10 && _type != KOOPAS_TYPE_GREEN_FLY) // Wing Koopas don't need to solve phaseChecker.
	{
		vx = -vx;

		if (px <= this->x)
			phaseChecker->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
		else
			phaseChecker->SetPosition(x - KOOPAS_BBOX_WIDTH, y);

	}

	phaseChecker->SetSpeed(vx, 1);

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (brick->IsAttacking() && brick->IsBrokenByMarioJump() && e->ny != 0)
	{
		this->SetState(KOOPAS_STATE_SHELL);

		float bx, by;
		brick->GetPosition(bx, by);

		if (bx < x)
			this->Deflected(DEFLECT_DIRECTION_RIGHT);
		else
			this->Deflected(DEFLECT_DIRECTION_LEFT);
	}
	if (state == KOOPAS_STATE_ATTACKING && e->nx != 0)
	{
		if (brick->GetType() == BRICK_TYPE_GOLD)
			brick->SetType(BRICK_TYPE_BREAK);
		else if (brick->GetType() == BRICK_TYPE_QUESTION)
			brick->SetType(BRICK_TYPE_EMPTY);
	}
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	if (goomba->GetState() == GOOMBA_STATE_DIE_1 || goomba->GetState() == GOOMBA_STATE_DIE_2)
		return;
	
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
	case KOOPAS_STATE_SHELL:
		float g_vx, g_vy;
		goomba->GetSpeed(g_vx, g_vy);

		goomba->SetSpeed(-g_vx, g_vy);

		this->vx = -this->vx;
		break;

	case KOOPAS_STATE_ATTACKING:
		goomba->SetState(GOOMBA_STATE_DIE_2);

		float gx, gy;
		goomba->GetPosition(gx, gy);
		if (gx >= x)
			goomba->Deflected(DEFLECT_DIRECTION_RIGHT);
		else
			goomba->Deflected(DEFLECT_DIRECTION_LEFT);
		break;
	}
}

void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (koopas->state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE)
		return;

	int flag = 0;

	if (koopas->state == KOOPAS_STATE_ATTACKING)
		flag = 1;
	else if (koopas->state == KOOPAS_STATE_SHELL && koopas->isHeld)
		flag = 2;

	switch (state)
	{
	case KOOPAS_STATE_ATTACKING:
		koopas->SetState(KOOPAS_STATE_DIE);

		if (flag)
			this->SetState(KOOPAS_STATE_DIE);

		if (koopas->x >= x)
		{
			if (state == KOOPAS_STATE_DIE)
				this->Deflected(DEFLECT_DIRECTION_LEFT);

			koopas->Deflected(DEFLECT_DIRECTION_RIGHT);
		}
		else
		{
			if (state == KOOPAS_STATE_DIE)
				this->Deflected(DEFLECT_DIRECTION_RIGHT);

			koopas->Deflected(DEFLECT_DIRECTION_LEFT);
		}


		break;

	case KOOPAS_STATE_SHELL:
	case KOOPAS_STATE_WALKING:
		this->vx = -vx;
		if (vx < 0)
		{
			this->phaseChecker->SetPosition(x - KOOPAS_BBOX_WIDTH, y);
		}
		else
			this->phaseChecker->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
		if (koopas->state == KOOPAS_STATE_WALKING)
		{
			koopas->vx = -koopas->vx;
			if (koopas->vx < 0)
			{
				koopas->phaseChecker->SetPosition(koopas->x - KOOPAS_BBOX_WIDTH, koopas->y);
			}
			else
				koopas->phaseChecker->SetPosition(koopas->x + KOOPAS_BBOX_WIDTH, koopas->y);
		}

		if (flag)
		{
			this->SetState(KOOPAS_STATE_DIE);
			if (flag == 2)
				koopas->SetState(KOOPAS_STATE_DIE);
			else
				if (x >= koopas->x)
					this->Deflected(DEFLECT_DIRECTION_RIGHT);
				else
					this->Deflected(DEFLECT_DIRECTION_LEFT);
		}
		break;
	}


}

void CKoopas::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	if ((state == KOOPAS_STATE_ATTACKING))
		e->obj->Delete();
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (deflection_start != 0 && vy == 0)
	{
		deflection_start = 0;
	}

	if(state == KOOPAS_STATE_WALKING)
		phaseChecker->Update(dt, coObjects);

	if (isHeld == true)
		ay = 0;
	else
		ay = KOOPAS_GRAVITY;

	vy += ay * dt;

	if ((state == KOOPAS_STATE_SHELL) && (GetTickCount64() - time_start > KOOPAS_SHELL_TIMEOUT))
	{
		SetState(KOOPAS_STATE_WALKING);
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE);
		time_start = -1;
		return;
	}
	else if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - time_start > KOOPAS_DIE_TIMEOUT))
	{
		isDeleted = true;
		phaseChecker->Delete();
		return;
	}
	else if (state == KOOPAS_STATE_FLYING && (GetTickCount64() - time_start) > KOOPAS_FLY_TIMEOUT
		&& vy == ay * dt) // Koopas only fly when it on platform
	{
		time_start = -1;
		SetState(KOOPAS_STATE_FLYING);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	if(state == KOOPAS_STATE_WALKING)
		phaseChecker->RenderBoundingBox();

	int aniId = GetAniId();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	float px, py;
	phaseChecker->GetPosition(px, py);
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	isHeld = false;
	isUp = false;
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		time_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		phaseChecker->SetPosition(x - KOOPAS_BBOX_WIDTH - KOOPAS_PHASE_CHECK_WIDTH / 2, y);
		break;
	case KOOPAS_STATE_ATTACKING:
		time_start = -1;
		vx = (nx >= 0) ? -KOOPAS_ATTACKING_SPEED : KOOPAS_ATTACKING_SPEED;
		break;
	case KOOPAS_STATE_DIE:
		time_start = GetTickCount64();
		break;
	case KOOPAS_STATE_FLYING:
		time_start = GetTickCount64();
		vy = -KOOPAS_FLY_SPEED_Y;
		break;
	}
}

int CKoopas::GetAniId()
{
	int aniId = ID_ANI_RED_KOOPAS_WALKING_LEFT;

	switch (_type)
	{
	case KOOPAS_TYPE_RED:
		if (vx >= 0)
			aniId = ID_ANI_RED_KOOPAS_WALKING_RIGHT;

		if (state == KOOPAS_STATE_DIE)
		{
			aniId = ID_ANI_RED_KOOPAS_SHELL_UP;
		}
		else if (state == KOOPAS_STATE_SHELL)
		{
			switch (isUp)
			{
			case true:
				aniId = ID_ANI_RED_KOOPAS_SHELL_UP;
				if (GetTickCount64() - time_start >= 4000)
					aniId = ID_ANI_RED_KOOPAS_REFORM_UP;
				break;

			case false:
				aniId = ID_ANI_RED_KOOPAS_SHELL_DOWN;

				if (GetTickCount64() - time_start >= 4000)
					aniId = ID_ANI_RED_KOOPAS_REFORM_DOWN;
				break;
			}
			
		}
		else if (state == KOOPAS_STATE_ATTACKING)
		{
			aniId = ID_ANI_RED_KOOPAS_ATTACKING;
		}
		break;

	case KOOPAS_TYPE_GREEN:
		aniId = ID_ANI_GREEN_KOOPAS_WALKING_LEFT;
		if (vx >= 0)
			aniId = ID_ANI_GREEN_KOOPAS_WALKING_RIGHT;

		if (state == KOOPAS_STATE_DIE)
		{
			aniId = ID_ANI_GREEN_KOOPAS_SHELL_UP;
		}
		else if (state == KOOPAS_STATE_SHELL)
		{
			switch (isUp)
			{
			case true:
				aniId = ID_ANI_GREEN_KOOPAS_SHELL_UP;
				if (GetTickCount64() - time_start >= 4000)
					aniId = ID_ANI_GREEN_KOOPAS_REFORM_UP;
				break;

			case false:
				aniId = ID_ANI_GREEN_KOOPAS_SHELL_DOWN;

				if (GetTickCount64() - time_start >= 4000)
					aniId = ID_ANI_GREEN_KOOPAS_REFORM_DOWN;
				break;
			}
		}
		else if (state == KOOPAS_STATE_ATTACKING)
		{
			aniId = ID_ANI_GREEN_KOOPAS_ATTACKING;
		}
		break;

	case KOOPAS_TYPE_GREEN_FLY:
		if (vx >= 0) aniId = ID_ANI_GREEN_WING_KOOPAS_FLYING_RIGHT;
		else aniId = ID_ANI_GREEN_WING_KOOPAS_FLYING_LEFT;

		break;
	}

	

	return aniId;
}

void CKoopas::Deflected(int Direction)
{
	vy = -KOOPAS_DIE_DEFLECT;
	ay = KOOPAS_GRAVITY;

	vx = Direction * KOOPAS_WALKING_SPEED;
	deflection_start = GetTickCount64();
	isUp = true;

	if (_type == KOOPAS_TYPE_GREEN_FLY)
		_type = KOOPAS_TYPE_GREEN;
}