#include "Tail.h"
#include "Brick.h"
#include "debug.h"
#include "Platform.h"
#include "AssetIDs.h"
#include "Koopas.h"
#include "TeleportGate.h"
#include "Hud.h"
#include "Effect.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	/*if (_type == PHASECHECK_BY_MARIO && x != old_x)
		DebugOut(L"x: %f, old_x: %f\n", x, old_x);*/

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
		else if (abs(x + vx * dt - old_x) > TAIL_ATTACK_RANGE * TAIL_BBOX_WIDTH)
		{
			if (vx >= 0)
			{
				vx = (TAIL_ATTACK_RANGE * TAIL_BBOX_WIDTH + old_x - x) / dt;
			}
			else
			{
				vx = (old_x - TAIL_ATTACK_RANGE * TAIL_BBOX_WIDTH - x) / dt;
			}
		}
		else if (isAttackedBehind == false && ((GetTickCount64() - attack_start) < TAIL_ATTACK_TIME / 4))
		{
			vector<LPGAMEOBJECT> objects;
			objects.clear();
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (dynamic_cast<CPlatform*>(coObjects->at(i))
					|| dynamic_cast<CTeleportGate*>(coObjects->at(i))
					|| dynamic_cast<CBrick*>(coObjects->at(i))
					|| dynamic_cast<CPhaseChecker*>(coObjects->at(i)))
					continue;

				objects.push_back(coObjects->at(i)); //just check collision with: Plant, Goomba, Koopas
			}

			CCollision::GetInstance()->Process(this, coObjects);
		}


		if (isAttackedFront == false)
			CCollision::GetInstance()->Process(this, dt, coObjects);

		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	if (e->nx == 0 || dynamic_cast<CPlatform*>(e->obj))
		return;

	isAttackedFront = true;
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else
		isAttackedFront = false;
}


void CTail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
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

	isAttackedFront = TAIL_COLLIDED_BRICK;
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE_1 || goomba->GetState() == GOOMBA_STATE_DIE_2)
		return;

	goomba->SetState(GOOMBA_STATE_DIE_2);
	if (e->nx > 0)
		goomba->Deflected(DEFLECT_DIRECTION_LEFT);
	else
		goomba->Deflected(DEFLECT_DIRECTION_RIGHT);

	isAttackedFront = TAIL_COLLIDED_GOOMBA;

	CHud::GetInstance()->CollectScore(SCORE_TAIL_ATTACKED_ENEMIES);

	float ox, oy;
	e->obj->GetPosition(ox, oy);
	CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
	CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_SPRITE_POINTS_100, true, true);
}

void CTail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	float kx, ky;
	e->obj->GetPosition(kx, ky);

	if (e->obj->GetState() == KOOPAS_STATE_WALKING || e->obj->GetState() == KOOPAS_STATE_FLYING)
		CEffect::GetInstance()->pushEffectIntoQueue(kx, ky, ID_SPRITE_POINTS_100, true, true);

	e->obj->SetState(KOOPAS_STATE_SHELL); // KOOPAS_STATE_SHELL 200

	
	if (kx <= x)
		e->obj->Deflected(DEFLECT_DIRECTION_LEFT);
	else
		e->obj->Deflected(DEFLECT_DIRECTION_RIGHT);

	isAttackedFront = TAIL_COLLIDED_KOOPAS;

	float ox, oy;
	e->obj->GetPosition(ox, oy);
	CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
}

void CTail::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	isAttackedFront = TAIL_COLLIDED_PLANT;
	CHud::GetInstance()->CollectScore(SCORE_TAIL_ATTACKED_ENEMIES);
	
	float ox, oy;
	e->obj->GetPosition(ox, oy);
	CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
	CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_SPRITE_POINTS_100, true, true);
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}


void CTail::OnCollisionWith(LPGAMEOBJECT obj)
{
	isAttackedBehind = true;

	float ox, oy;
	obj->GetPosition(ox, oy);
	if (dynamic_cast<CGoomba*>(obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
		if (goomba->GetState() == GOOMBA_STATE_DIE_1 || goomba->GetState() == GOOMBA_STATE_DIE_2)
			return;
		
		goomba->SetState(GOOMBA_STATE_DIE_2);
		
		if (ox < x)
			goomba->Deflected(DEFLECT_DIRECTION_LEFT);
		else
			goomba->Deflected(DEFLECT_DIRECTION_RIGHT);

		CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
		CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_SPRITE_POINTS_100, true, true);
	}
	else if (dynamic_cast<CPlant*>(obj))
	{
		obj->Delete();
		CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
		CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_SPRITE_POINTS_100, true, true);
	}
	else if (dynamic_cast<CKoopas*>(obj))
	{
		if(obj->GetState() == KOOPAS_STATE_WALKING || obj->GetState() == KOOPAS_STATE_FLYING)
			CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_SPRITE_POINTS_100, true, true);

		obj->SetState(KOOPAS_STATE_SHELL); 
		
		if (ox <= x)
			obj->Deflected(DEFLECT_DIRECTION_LEFT);
		else
			obj->Deflected(DEFLECT_DIRECTION_RIGHT);

		CEffect::GetInstance()->pushEffectIntoQueue(ox, oy, ID_ANI_TAIL_MARIO_ATTACKED_ENEMIES, 0);
	}
	else
		isAttackedBehind = false;
}

void CTail::Render()
{
	//RenderBoundingBox();

	CAnimations* animations = CAnimations::GetInstance();
}