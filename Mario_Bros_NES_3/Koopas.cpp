#include "Koopas.h"

#include "Goomba.h"
#include "Mario.h"

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
	}
	// only change direction when Koopas blocked by brick
	if (e->obj->IsBlocking() && e->nx != 0)
	{
		vx = -vx;

		float p_vx, p_vy;
		phaseCheck->GetSpeed(p_vx, p_vy);

		if (p_vx >= this->vx)
			phaseCheck->SetPosition(x - KOOPAS_BBOX_WIDTH, y);
		else
			phaseCheck->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
	}


	// phaseCheck is falling ?
	float px, py;
	phaseCheck->GetPosition(px, py);
	if (state == KOOPAS_STATE_WALKING && py - this->y > 10)
	{
		vx = -vx;

		if (px <= this->x)
			phaseCheck->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
		else
			phaseCheck->SetPosition(x - KOOPAS_BBOX_WIDTH, y);

	}

	phaseCheck->SetSpeed(vx, 1);


	if (state != KOOPAS_STATE_ATTACKING)
		return;

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	if (state == KOOPAS_STATE_ATTACKING)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE_1)
		{
			goomba->SetState(GOOMBA_STATE_DIE_2);
		}
	}
}

void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (state == KOOPAS_STATE_ATTACKING)
	{
		if (koopas->GetState() != KOOPAS_STATE_DIE)
		{
			if (koopas->GetState() == KOOPAS_STATE_ATTACKING)
				this->SetState(KOOPAS_STATE_DIE);
			koopas->SetState(KOOPAS_STATE_DIE);
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(state == KOOPAS_STATE_WALKING)
		phaseCheck->Update(dt, coObjects);

	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPAS_STATE_SHELL) && (GetTickCount64() - shellForm_start > KOOPAS_SHELL_TIMEOUT))
	{
		SetLevel(KOOPAS_LEVEL_NORMAL);
		SetState(KOOPAS_STATE_WALKING);
		shellForm_start = -1;
		return;
	}
	if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	{
		isDeleted = true;
		phaseCheck->Delete();
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	if(state == KOOPAS_STATE_WALKING)
		phaseCheck->RenderBoundingBox();

	int aniId = GetAniId();
	

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	float px, py;
	phaseCheck->GetPosition(px, py);
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		SetLevel(KOOPAS_LEVEL_SHELL);
		shellForm_start = GetTickCount64();
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_ATTACKING:
		vx = (nx >= 0) ? -KOOPAS_ATTACKING_SPEED : KOOPAS_ATTACKING_SPEED;
		break;
	case KOOPAS_STATE_DIE:
		die_start = GetTickCount64();
		vy = -KOOPAS_DIE_DEFLECT;
		vx = 0;//KOOPAS_WALKING_SPEED;
		ax = 0;
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
		if (GetTickCount64() - shellForm_start >= 4000)
			aniId = ID_ANI_KOOPAS_REFORM;
	}
	else if (state == KOOPAS_STATE_ATTACKING)
	{
		aniId = ID_ANI_KOOPAS_ATTACKING;
	}

	return aniId;
}