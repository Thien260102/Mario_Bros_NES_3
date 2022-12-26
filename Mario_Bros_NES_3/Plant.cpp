#include "Plant.h"
#include "debug.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (_type == PLANT_TYPE_GREEN || _type == PLANT_TYPE_GREEN_FIRE)
	{
		left = x - PLANT_GREEN_BBOX_WIDTH / 2;
		top = y - PLANT_GREEN_BBOX_HEIGHT / 2;
		right = left + PLANT_GREEN_BBOX_WIDTH;
		bottom = top + PLANT_GREEN_BBOX_HEIGHT;
	}
	else
	{
		left = x - PLANT_RED_BBOX_WIDTH / 2;
		top = y - PLANT_RED_BBOX_HEIGHT / 2;
		right = left + PLANT_RED_BBOX_WIDTH;
		bottom = top + PLANT_RED_BBOX_HEIGHT;
	}
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	y += vy * dt;


	switch (state)
	{
	case PLANT_STATE_RISE:

		switch (_type)
		{
		case PLANT_TYPE_GREEN:
		case PLANT_TYPE_GREEN_FIRE:
			if (old_y - y > PLANT_GREEN_BBOX_HEIGHT)
			{
				y = old_y - PLANT_GREEN_BBOX_HEIGHT;
				SetState(PLANT_STATE_ATTACK);
			}
			break;

		case PLANT_TYPE_RED_FIRE:
			if (old_y - y > PLANT_RED_BBOX_HEIGHT)
			{
				y = old_y - PLANT_RED_BBOX_HEIGHT;
				SetState(PLANT_STATE_ATTACK);
			}
			break;
		}

		break;
	case PLANT_STATE_DOWN:
		if (y - old_y >= 0) // state DOWN
		{
			y = old_y;
			SetState(PLANT_STATE_IDLE);
		}
		break;
	case PLANT_STATE_ATTACK:
	case PLANT_STATE_IDLE:
		if ((GetTickCount64() - time_start) > PLANT_ATTACK_IDLE_TIME)
		{
			time_start = 0;
			if (state == PLANT_STATE_IDLE
				&& ((abs(Mario_x - x) > DISTANCE_BETWEEN_MARIO_AND_PLANT)))
				SetState(PLANT_STATE_RISE);
			else if (state == PLANT_STATE_ATTACK)
				SetState(PLANT_STATE_DOWN);
		}
		break;
	}

	//Get position of Mario
	CPlayScene* playScene = NULL;

	if (playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene()))
	{
		playScene->GetPlayer()->GetPosition(Mario_x, Mario_y);
	}

	
	if (_bullet != NULL)
	{
		vector<LPGAMEOBJECT> objects;
		_bullet->Update(dt, &objects);

		objects.push_back(playScene->GetPlayer());
		CCollision::GetInstance()->Process(_bullet, dt, &objects);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::SetState(int State)
{
	CGameObject::SetState(State);
	switch (state)
	{
	case PLANT_STATE_RISE:
		vy = -PLANT_RISING_DOWNING_SPEED;
		break;
	case PLANT_STATE_DOWN:
		vy = PLANT_RISING_DOWNING_SPEED;
		break;
	case PLANT_STATE_ATTACK:
		time_start = GetTickCount64();
		vy = 0;

		if (_type == PLANT_TYPE_GREEN)
			return;

		_bullet = new CBullet(x, y, BULLET_BY_PLANT);

		float direction_x, direction_y;
		direction_x = (Mario_x >= x) ? BULLET_DIRECTION_RIGHT : BULLET_DIRECTION_LEFT;
		direction_y = (Mario_y >= y) ? BULLET_DIRECTION_BOT : BULLET_DIRECTION_TOP;
		dynamic_cast<CBullet*>(_bullet)->SetDirection(direction_x, direction_y);

		break;
	case PLANT_STATE_IDLE:
		time_start = GetTickCount64();
		vy = 0;
		break;
	}
}

int CPlant::GetAniId()
{
	int aniId = -1;
	
	switch (_type)
	{
	case PLANT_TYPE_GREEN:
		aniId = ID_ANI_PLANT_GREEN;
		break;

	case PLANT_TYPE_GREEN_FIRE:
		aniId = ID_ANI_PLANT_GREEN_FIRE;
		if (Mario_x < x)
		{
			if (Mario_y >= y) // y Mario < y Plant
				aniId = ID_ANI_PLANT_GREEN_TARGET_BOT_LEFT;
			else
				aniId = ID_ANI_PLANT_GREEN_TARGET_TOP_LEFT;
		}
		else
		{
			if (Mario_y >= y) // y Mario < y Plant
				aniId = ID_ANI_PLANT_GREEN_TARGET_BOT_RIGHT;
			else
				aniId = ID_ANI_PLANT_GREEN_TARGET_TOP_RIGHT;
		}
		
		break;

	case PLANT_TYPE_RED_FIRE:
		aniId = ID_ANI_PLANT_RED_FIRE;
		if (Mario_x <= x)
		{
			if (Mario_y >= y) // y Mario < y Plant
				aniId = ID_ANI_PLANT_RED_TARGET_BOT_LEFT;
			else
				aniId = ID_ANI_PLANT_RED_TARGET_TOP_LEFT;
		}
		else
		{
			if (Mario_y >= y) // y Mario < y Plant
				aniId = ID_ANI_PLANT_RED_TARGET_BOT_RIGHT;
			else
				aniId = ID_ANI_PLANT_RED_TARGET_TOP_RIGHT;
		}
		break;
	}

	return aniId;
}

void CPlant::Render()
{
	int aniId = GetAniId();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	if (_bullet != NULL)
		_bullet->Render();
}

void CPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

		if (koopas->GetState() == KOOPAS_STATE_SHELL && koopas->IsHeld())
		{
			this->Delete();
			koopas->SetState(KOOPAS_STATE_DIE);
		}
	}
	else if (dynamic_cast<CPhaseChecker*>(e->obj))
	{
		CPhaseChecker* phaseChecker = dynamic_cast<CPhaseChecker*>(e->obj);
		if (phaseChecker->GetType() == PHASECHECK_BY_MARIO)
			this->Delete();
	}
}