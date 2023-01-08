#include "Mario_WorldMap.h"
#include "Collision.h"
#include "PlatformAnimate.h"
#include "Portal.h"
#include "Platform.h"
 
void CMario_WorldMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_BBOX_WIDTH / 2;
	t = y - MARIO_BBOX_HEIGHT / 2;
	r = l + MARIO_BBOX_WIDTH;
	b = t + MARIO_BBOX_HEIGHT;
}

void CMario_WorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, coObjects);
		
	if (absolutely_touching == 1)
	{
		if (nx > 0)
		{
			old_pos = x;
			vx = MARIO_WORLDMAP_WALKING_SPEED;
		}
		else if(nx < 0)
		{
			old_pos = x;
			vx = -MARIO_WORLDMAP_WALKING_SPEED;
		}
		else if(ny > 0)
		{
			old_pos = y;
			vy = MARIO_WORLDMAP_WALKING_SPEED;
		}
		else if(ny < 0)
		{
			old_pos = y;
			vy = -MARIO_WORLDMAP_WALKING_SPEED;
		}

		crossing_start = GetTickCount64();
		absolutely_touching = 0;
	}
	if (crossing_start != 0)
	{
		bool adjusted = false;

		if (vx > 0 && (x + vx * dt - old_pos) > MARIO_CROSSING_RANGE)
		{
			vx = (MARIO_CROSSING_RANGE + old_pos - x) / dt;
			adjusted = true;
		}
		else if (vx < 0 && (old_pos - (x + vx * dt)) > MARIO_BBOX_WIDTH)
		{
			vx = -(MARIO_BBOX_WIDTH - old_pos + x) / (dt);
			adjusted = true;
		}
		else if (vy > 0 && (y + vy * dt - old_pos) > MARIO_BBOX_HEIGHT)
		{
			vy = (MARIO_BBOX_HEIGHT + old_pos - y) / dt;
			adjusted = true;
		}
		else if (vy < 0 && (old_pos - (y + vy * dt)) > MARIO_BBOX_HEIGHT)
		{
			vy = -(MARIO_BBOX_HEIGHT - old_pos + y) / (dt);
			adjusted = true;
		}

		x += vx * dt;
		y += vy * dt;

		if (adjusted)
		{
			vx = 0;
			vy = 0;
			crossing_start = 0;
		}
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario_WorldMap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())
	{
		if (dynamic_cast<CPlatformAnimate*>(e->obj))
		{
			CPlatformAnimate* platform = dynamic_cast<CPlatformAnimate*>(e->obj);

			if (platform->GetType() == PLATFORM_ANIMATE_TYPE_GATE)
			{
				absolutely_touching = 1;
			}
		}
		vx = 0;
		vy = 0;
	}

	if (dynamic_cast<CPortal*>(e->obj))
	{
		if (canGoIntoPortal)
		{
			DebugOut(L"Collide with portal\n");
			dynamic_cast<CPortal*>(e->obj)->SwitchScene();
		}
	}
}

void CMario_WorldMap::OnCollisionWith(LPGAMEOBJECT o)
{
	if(canGoIntoPortal && dynamic_cast<CPortal*>(o))
		dynamic_cast<CPortal*>(o)->SwitchScene();
}

void CMario_WorldMap::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario_WorldMap::Render()
{
	int aniId = ID_ANI_MARIO_SMALL_WORLDMAP;

	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		aniId = ID_ANI_MARIO_SMALL_WORLDMAP;
		break;

	case MARIO_LEVEL_BIG:
		aniId = ID_ANI_MARIO_BIG_WORLDMAP;
		break;

	case MARIO_LEVEL_RACCOON:
		aniId = ID_ANI_MARIO_RACCOON_WORLDMAP;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMario_WorldMap::SetState(int State)
{
	state = State;
	switch (state)
	{
	case MARIO_WM_STATE_WALKING_RIGHT:
		vx = MARIO_WORLDMAP_WALKING_SPEED;
		vy = 0;

		nx = 1;
		ny = 0;
		break;
	case MARIO_WM_STATE_WALKING_LEFT:
		vx = -MARIO_WORLDMAP_WALKING_SPEED;
		vy = 0;

		nx = -1;
		ny = 0;
		break;
	case MARIO_WM_STATE_WALKING_UP:
		vy = -MARIO_WORLDMAP_WALKING_SPEED;
		vx = 0;

		ny = -1;
		nx = 0;
		break;
	case MARIO_WM_STATE_WALKING_DOWN:
		vy = MARIO_WORLDMAP_WALKING_SPEED;
		vx = 0;

		ny = 1;
		nx = 0;
		break;
	}
}