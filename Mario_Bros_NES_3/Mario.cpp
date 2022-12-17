#include <algorithm>
#include <math.h>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "Brick.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (flag == MARIO_ATTACK_TIME && (GetTickCount64() - time_start > flag))
	{
		flag = 0;
		time_start = 0;
	}

	if (flag == MARIO_KICK_TIME && (GetTickCount64() - time_start > flag))
	{
		flag = 0;
		time_start = 0;
	}

	isOnPlatform = false;
	if (_koopas != NULL)
	{
		if (_koopas->IsHeld() == false)
			_koopas = NULL;
		else
		{
			float temp = -1;
			if (nx >= 0) temp = 1;
			switch (level)
			{
			case MARIO_LEVEL_SMALL:
				_koopas->SetPosition(x + temp * MARIO_SMALL_BBOX_WIDTH / 2 + temp * KOOPAS_BBOX_WIDTH / 2,
					y - MARIO_SMALL_BBOX_HEIGHT / 2);
				break;

			case MARIO_LEVEL_BIG:
				_koopas->SetPosition(x + temp * MARIO_BIG_BBOX_WIDTH / 2 + temp * KOOPAS_BBOX_WIDTH / 2, y);
				break;

			case MARIO_LEVEL_RACCOON:
				_koopas->SetPosition(x + temp * MARIO_RACCOON_BBOX_WIDTH / 2 + temp * KOOPAS_BBOX_WIDTH / 2, 
					y + 1);
				break;
			}
			_koopas->SetSpeed(vx, vy);
		}
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);	
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (koopas->GetState() == KOOPAS_STATE_DIE)
		return;
	//MARIO kick KOOPAS shell
	if (koopas->GetState() == KOOPAS_STATE_SHELL)
	{
		//Mario animation kick
		if (e->ny != 0 || (holdable == 0 && e->nx != 0))
		{
			this->SetState(MARIO_STATE_KICK);
			koopas->SetNx(-this->nx);
			koopas->SetState(KOOPAS_STATE_ATTACKING);
		}
		else if (holdable && _koopas == NULL)
		{
			koopas->isHold();
			_koopas = koopas;
			if(nx >= 0)
				_koopas->SetPosition(x + MARIO_BIG_BBOX_WIDTH / 2 + KOOPAS_BBOX_WIDTH / 2, y);
			else
				_koopas->SetPosition(x - MARIO_BIG_BBOX_WIDTH / 2 - KOOPAS_BBOX_WIDTH / 2, y);
		}
	}
	// jump on top >> Koopas and deflect a bit 
	else if (e->ny < 0)
	{
		if (koopas->GetState() >= KOOPAS_STATE_WALKING && koopas->GetState() < KOOPAS_STATE_SHELL)
		{
			koopas->SetState(KOOPAS_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Koopas
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() < KOOPAS_STATE_SHELL)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = (CMushroom*)e->obj;

	if (mushroom->getType() == MUSHROOM_1UP)
	{
		// + 1 up
	}
	else
	{
		switch (level)
		{
			case MARIO_LEVEL_SMALL:
				SetLevel(MARIO_LEVEL_BIG);
				break;
			case MARIO_LEVEL_BIG:
				SetLevel(MARIO_LEVEL_RACCOON);
				break;
		}

	}
	

	e->obj->Delete();
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_WALKING)
		return;
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE_1)
		{
			goomba->SetState(GOOMBA_STATE_DIE_1);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE_1)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	switch (brick->GetType())
	{
	case BRICK_TYPE_GOLD:
		// Mario jumping into brick from below
		if (e->ny > 0)
		{
			if (level == MARIO_LEVEL_SMALL && brick->GetState() != BRICK_STATE_DEFLECT)
				brick->SetState(BRICK_STATE_DEFLECT);
			else if (level != MARIO_LEVEL_SMALL)
				brick->SetType(BRICK_TYPE_BREAK);
		}
		else if (flag == MARIO_ATTACK_TIME && e->nx != 0) // MARIO Raccoon attack
		{
			brick->SetType(BRICK_TYPE_BREAK);
		}
		
		break;

	case BRICK_TYPE_QUESTION:
		if ((e->ny > 0) || (flag == MARIO_ATTACK_TIME && e->nx != 0))
			brick->SetType(BRICK_TYPE_EMPTY);
		break;
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int flag = 0;
	if (_koopas)	flag = _koopas->IsHeld();

	int aniId = -1;
	if (!isOnPlatform)
	{
		bool isRun = (abs(ax) == MARIO_ACCEL_RUN_X);
		switch (flag)
		{
		case 1:
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
			break;
		case 0:
			switch (isRun)
			{
			case true:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
				break;

			case false:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
				break;
			}
			break;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			switch (flag)
			{
			case 1:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_STAND_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_STAND_LEFT;
				}
				else
					if (ax > 0)
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_RUN_RIGHT;
					}
					else // vx < 0
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_RUN_LEFT;
					}
				break;

			case 0:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
				break;
			}

		}


	if (flag == MARIO_KICK_TIME)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int flag = 0; // to determine Mario is holding Koopas 
	if (_koopas)	flag = _koopas->IsHeld();

	int aniId = -1;
	if (!isOnPlatform)
	{
		bool isRun = (abs(ax) == MARIO_ACCEL_RUN_X);
		switch (flag)
		{
		case 1:
			if (nx >= 0)
				aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
			break;
		case 0:
			switch (isRun)
			{
			case true:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
				break;

			case false:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				break;
			}
			break;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			switch (flag)
			{
			case 1:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_STAND_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_STAND_LEFT;
				}
				else
					if (ax > 0)
					{
						aniId = ID_ANI_MARIO_HOLD_RUN_RIGHT;
					}
					else // vx < 0
					{
						aniId = ID_ANI_MARIO_HOLD_RUN_LEFT;
					}
				break;

			case 0:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
				break;
			}
			
		}


	if (flag == MARIO_KICK_TIME)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_KICK_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animation ID for raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int flag = 0; // to determine Mario is holding Koopas 
	if (_koopas)	flag = _koopas->IsHeld();

	int aniId = -1;
	if (!isOnPlatform)
	{
		bool isRun = (abs(ax) == MARIO_ACCEL_RUN_X);
		switch (flag)
		{
		case 1:
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT;
			break;
		case 0:
			switch (isRun)
			{
			case true:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
				break;

			case false:
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
				break;
			}
			break;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
		{
			switch (flag)
			{
			case 1:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_STAND_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_HOLD_STAND_LEFT;
				}
				else
					if (ax > 0)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_RUN_RIGHT;
					}
					else // vx < 0
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_RUN_LEFT;
					}
				break;

			case 0:
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
				}
				break;
			}

		}


	if (flag == MARIO_KICK_TIME)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d \t level: %d", coin, level);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_ATTACK:
		if (time_start == 0)
			time_start = GetTickCount64();
		
		flag = MARIO_ATTACK_TIME;
		break;

	case MARIO_STATE_KICK:
		if (time_start == 0)
			time_start = GetTickCount64();
		flag = MARIO_KICK_TIME;
		break;

	case MARIO_STATE_READY_HOLD:
		holdable = 1;
		break;

	case MARIO_STATE_HOLD_RELEASE:
		holdable = 0;
		if (_koopas != NULL)
		{
			this->SetState(MARIO_STATE_KICK);
			_koopas->SetNx(-this->nx);
			_koopas->SetState(KOOPAS_STATE_ATTACKING);
			_koopas = NULL;
		}
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else
	{
		if (isSitting)
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			if (state == MARIO_STATE_ATTACK)
			{
				left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
				top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
				right = left + MARIO_RACCOON_BBOX_WIDTH + MARIO_RACCOON_ATTACK_WIDTH;
				bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
			}
			else
			{
				left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
				top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
				right = left + MARIO_RACCOON_BBOX_WIDTH;
				bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
			}
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else 
		y -= (MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT);

	level = l;
}

