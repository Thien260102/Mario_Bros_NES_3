#include "TeleportGate.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"

void CTeleportGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene()))
	{
		CMario* mario = dynamic_cast<CMario*>(((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer());

		vector<LPGAMEOBJECT> objects;
		objects.clear();
		objects.push_back(mario);

		CCollision::GetInstance()->Process(this, &objects);

		if (tele_start != 0)
		{
			mario->SetGravity(0.0f);
			mario->SetSpeed(0.0f, 0.0f);

			float mx, my;
			mario->GetPosition(mx, my);
			if (_direction == TELEPORT_DIRECTION_UP)
				my += (-TELEPORT_SPEED * dt);
			else
				my += (TELEPORT_SPEED * dt);

			mario->SetPosition(mx, my);

			TeleObject(mario);
		}
	}
}

void CTeleportGate::OnCollisionWith(LPGAMEOBJECT obj)
{
	CMario* mario = dynamic_cast<CMario*>(obj);
	switch (_direction)
	{
	case TELEPORT_DIRECTION_DOWN:
		if (mario->IsCanGetIntoPipe() == MARIO_GETINTO_PIPE_DOWN) // Mario get into pipe(sewer)
		{
			//DebugOut(L"[Teleport] teleport Mario\n");
			tele_start = GetTickCount64();
		}
		break;

	case TELEPORT_DIRECTION_UP:
		if (mario->IsCanGetIntoPipe() == MARIO_GETINTO_PIPE_UP) // Mario get into pipe(sewer)
		{
			//DebugOut(L"[Teleport] teleport Mario\n");
			tele_start = GetTickCount64();
		}

		break;
	}
	
}

void CTeleportGate::TeleObject(LPGAMEOBJECT obj)
{
	if (GetTickCount64() - tele_start > TELEPORTING_TIME)
	{
		CMario* mario = dynamic_cast<CMario*>(((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer());
		mario->SetGravity(MARIO_GRAVITY);

		tele_start = 0;
		obj->SetPosition(des_x, des_y);
	}
}

void CTeleportGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TELEPORT_BBOX_WIDTH / 2;
	top = y - TELEPORT_BBOX_HEIGHT / 2;
	right = left + TELEPORT_BBOX_WIDTH;
	bottom = top + TELEPORT_BBOX_HEIGHT;
}

void CTeleportGate::Render()
{
	RenderBoundingBox();
}