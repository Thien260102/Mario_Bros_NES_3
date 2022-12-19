#include "Plant.h"


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

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::SetState(int State)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_RISE:
		ay = 0;
		break;
	case PLANT_STATE_DOWN:
		ay = 0;
		break;
	case PLANT_STATE_ATTACK:
		ay = 0;
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
		break;

	case PLANT_TYPE_RED_FIRE:
		aniId = ID_ANI_PLANT_RED_FIRE;
		break;
	}

	return aniId;
}

void CPlant::Render()
{
	int aniId = GetAniId();

	CAnimations::GetInstance()->Get(7000)->Render(x, y);
	RenderBoundingBox();
}