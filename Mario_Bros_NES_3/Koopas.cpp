#include "Koopas.h"

#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"

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
	//

	if (e->ny != 0)
	{
		vy = 0;
		if (time_start != -1)
			vx = 0;

	}
	//change direction when Koopas blocked by brick
	if (e->obj->IsBlocking() && e->nx != 0)
	{
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
	if (state == KOOPAS_STATE_WALKING && py - this->y > 10)
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
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (brick->IsAttacking() && e->ny != 0)
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
	case KOOPAS_STATE_SHELL:
		goomba->SetState(GOOMBA_STATE_DIE_2);
		goomba->Deflected(0);
		this->SetState(KOOPAS_STATE_DIE);
		this->Deflected(0);
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

	if (koopas->state == KOOPAS_STATE_DIE)
		return;

	switch (state)
	{
	case KOOPAS_STATE_ATTACKING:
		float kx, ky;
		koopas->GetPosition(kx, ky);

		if ((koopas->state == KOOPAS_STATE_ATTACKING) || (koopas->state == KOOPAS_STATE_SHELL && koopas->isHeld))
		{
			this->SetState(KOOPAS_STATE_DIE);

			if (kx >= x)
				this->Deflected(DEFLECT_DIRECTION_LEFT);
			else
				this->Deflected(DEFLECT_DIRECTION_RIGHT);
		}
		koopas->SetState(KOOPAS_STATE_DIE);
		koopas->Deflected(this->vx);

		break;

	default:
		if (koopas->state == KOOPAS_STATE_SHELL && koopas->isHeld)
		{
			koopas->SetState(KOOPAS_STATE_DIE);
			this->SetState(KOOPAS_STATE_DIE);
		}
		break;
	}

	if (state == KOOPAS_STATE_ATTACKING)
	{

		float kx, ky;
		koopas->GetPosition(kx, ky);

		if (koopas->GetState() == KOOPAS_STATE_ATTACKING)
		{
			this->SetState(KOOPAS_STATE_DIE);

			if (kx >= x)
				this->Deflected(DEFLECT_DIRECTION_LEFT);
			else
				this->Deflected(DEFLECT_DIRECTION_RIGHT);
		}
		koopas->SetState(KOOPAS_STATE_DIE);
		koopas->Deflected(this->vx);

	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(state == KOOPAS_STATE_WALKING)
		phaseChecker->Update(dt, coObjects);

	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPAS_STATE_SHELL) && (GetTickCount64() - time_start > KOOPAS_SHELL_TIMEOUT))
	{
		SetLevel(KOOPAS_LEVEL_NORMAL);
		SetState(KOOPAS_STATE_WALKING);
		time_start = -1;
		return;
	}
	if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - time_start > KOOPAS_DIE_TIMEOUT))
	{
		isDeleted = true;
		phaseChecker->Delete();
		return;
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
	isHeld = 0;
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		SetLevel(KOOPAS_LEVEL_SHELL);
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
	}
}

void CKoopas::SetLevel(int level)
{
	if (this->level == KOOPAS_LEVEL_SHELL)
	{
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
	}

	this->level = level;
}

int CKoopas::GetAniId()
{
	int aniId = ID_ANI_KOOPAS_WALKING;

	if (state == KOOPAS_STATE_DIE)
	{
		aniId = ID_ANI_KOOPAS_SHELL;
	}
	else if (state == KOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPAS_SHELL;
		if (GetTickCount64() - time_start >= 4000)
			aniId = ID_ANI_KOOPAS_REFORM;
	}
	else if (state == KOOPAS_STATE_ATTACKING)
	{
		aniId = ID_ANI_KOOPAS_ATTACKING;
	}

	return aniId;
}

void CKoopas::Deflected(int Direction)
{
	vy = -KOOPAS_DIE_DEFLECT;
	ay = KOOPAS_GRAVITY;

	vx = Direction * KOOPAS_WALKING_SPEED;
	ax = 0;
}