#pragma once
#include "Scene.h"
#include "Game.h"
#include "Textures.h"
#include "GameObject.h"
#include "Portal.h"
#include "Platform.h"
#include "PlatformAnimate.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Mario.h"

#define WAITING_KOOPAS_ATTACK_TIME 2000
#define CURTAIN_FLYING_TIME	3000

#define CURTAIN_FLYING	100
#define GAMENAME_DOWING  200

#define MARIO_WALKING_TIME 1350
#define MARIO_JUMPING_TIME (MARIO_WALKING_TIME + 1100)

#define LUIGI_HOLDING_KOOPAS 1

#define MARIO_JUMP_ON_GOOMBA 11

#define LUIGI_KICKING_KOOPAS 111

#define MARIO_JUMP_ON_KOOPAS 1111
#define MARIO_HOLDING_KOOPAS 2222

#define KOOPAS_ATTACKING 4444

#define KOOPAS_WALKING	555

class CIntroScene :public CScene
{
protected:
	ULONGLONG time_start;
	int flag; // determine curtain flying or something else (example: Game name downing)
	float Number3original_y = 0;

	LPGAMEOBJECT player[2];
	ULONGLONG MarioWalking_start;
	int stateOfMario;
	
	CPortal* portal;

	vector<LPGAMEOBJECT> objects;
			
	vector<CPlatform*> platform_objects;
	CPlatformAnimate* Number3;

	vector<LPGAMEOBJECT> ItemsAndEnemies;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	void Action(DWORD dt)
	{
		int Screen_Width = CGame::GetInstance()->GetBackBufferWidth();
		int Screen_Height = CGame::GetInstance()->GetBackBufferHeight();

		CMario* Luigi = (CMario*)player[0];
		CMario* Mario = (CMario*)player[1];

		if (flag == CURTAIN_FLYING)
		{
			float number3_x, number3_y;
			Number3->GetPosition(number3_x, number3_y);
			Number3->SetPosition(number3_x, number3_y - 0.1f * dt);

			for (int i = 3; i < platform_objects.size(); i++)
			{
				int id = platform_objects[i]->GetSpriteIDBegin();
				float x, y;
				platform_objects[i]->GetPosition(x, y);
				if (1)//(id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2))
				{
					if (GetTickCount64() - time_start > CURTAIN_FLYING_TIME)
					{
						flag = 0;
						time_start = 0;
						MarioWalking_start = GetTickCount64();
					}
					else
					{
						platform_objects[i]->SetPosition(x, y - 0.1f * dt);
					}
				}
			}
		}
		else if (flag == GAMENAME_DOWING)
		{
			float number3_x, number3_y;
			Number3->GetPosition(number3_x, number3_y);
			Number3->SetPosition(number3_x, number3_y + 0.1f * dt);

			float adjust = (Number3original_y - number3_y);
			if (adjust <= 0) // Number3original_y <= number3_y
			{
				flag = 0;
				Number3->SetPosition(number3_x, Number3original_y);

				CGameObject* obj;

				obj = new CGoomba(number3_x - 50, 0, GOOMBA_TYPE_NORMAL, 1);
				float vx, vy;
				obj->GetSpeed(vx, vy);
				obj->SetSpeed(0, vy);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopas(number3_x - 25, number3_y, KOOPAS_TYPE_GREEN, 1);
				obj->SetState(KOOPAS_STATE_SHELL);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopas(number3_x + 35, number3_y, KOOPAS_TYPE_GREEN, 1);
				obj->SetState(KOOPAS_STATE_SHELL);
				ItemsAndEnemies.push_back(obj);

				obj = new CMushroom(number3_x + 50, 0, MUSHROOM_TYPE_SUPER);
				ItemsAndEnemies.push_back(obj);

				obj = new CMushroom(number3_x - 7.5, number3_y, MUSHROOM_TYPE_SUPER_LEAF);
				ItemsAndEnemies.push_back(obj);

				stateOfMario = MARIO_STATE_JUMP;
				Mario->SetState(stateOfMario);
				DebugOut(L"Mario jump");

				for (auto obj : ItemsAndEnemies)
					if (dynamic_cast<CKoopas*>(obj))
						obj->SetState(KOOPAS_STATE_SHELL);
			}

			for (int i = 3; i < platform_objects.size(); i++)
			{
				int id = platform_objects[i]->GetSpriteIDBegin();
				float x, y;
				platform_objects[i]->GetPosition(x, y);
				if (!(id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2))
				{
					if (adjust <= 0)
					{
						platform_objects[i]->SetPosition(x, y - adjust);
					}
					else
					{
						platform_objects[i]->SetPosition(x, y + 0.1f * dt);
					}
				}
			}

			float x, y;
			platform_objects[0]->GetPosition(x, y); // get position of stage
			platform_objects[2]->SetPosition(x, y + 77); // set position of black screen
		}


		if (MarioWalking_start != 0)
		{
			//Luigi touch top of the screen
			float x, y;
			Luigi->GetPosition(x, y);
			if (y - 20 <= 0)
			{
				Luigi->GetSpeed(x, y);
				Luigi->SetSpeed(x, 0);
				flag = GAMENAME_DOWING;
			}

			ULONGLONG delta = GetTickCount64() - MarioWalking_start;
			if (delta < MARIO_WALKING_TIME && player[0]->GetState() != MARIO_STATE_WALKING_RIGHT)
			{
				Luigi->SetState(MARIO_STATE_WALKING_RIGHT);
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
				Luigi->SetMaxVx(0.0758f);
			}
			else if (delta > MARIO_WALKING_TIME && stateOfMario != MARIO_STATE_JUMP)
			{
				Mario->SetState(MARIO_STATE_IDLE);
				stateOfMario = MARIO_STATE_JUMP;
			}
			else if (delta < MARIO_JUMPING_TIME && stateOfMario == MARIO_STATE_JUMP
				&& player[0]->GetState() != MARIO_STATE_JUMP)
			{
				Luigi->SetState(MARIO_STATE_JUMP);
			}
			else if (delta > MARIO_JUMPING_TIME)
			{
				//Actor(player[0]);
				Mario->SetState(MARIO_STATE_SIT_RELEASE);
				MarioWalking_start = 0;
				DebugOut(L"\nMario sit release");
			}

		}
		
		//excepting Mario falling 
		float x, y;
		player[0]->GetPosition(x, y);
		if (x > CGame::GetInstance()->GetBackBufferWidth() + 50)
		{
			player[0]->SetState(MARIO_STATE_IDLE);
		}

		// Luigi
		if (((CMario*)player[0])->GetLevel() != MARIO_LEVEL_BIG)
			((CMario*)player[0])->SetLevel(MARIO_LEVEL_BIG);


		if (Mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			if (stateOfMario == MARIO_STATE_JUMP)
			{
				switch (Mario->GetState())
				{
				case MARIO_STATE_FLY:
					Mario->SetState(MARIO_STATE_RELEASE_FLY);
					Mario->SetState(MARIO_STATE_RELEASE_JUMP);

					break;

				case MARIO_STATE_JUMP:
				case MARIO_STATE_RELEASE_FLY:
				case MARIO_STATE_RELEASE_JUMP:
					Mario->SetState(MARIO_STATE_WALKING_LEFT);
					Mario->SetState(MARIO_STATE_FLY);
				}
				flag = MARIO_JUMP_ON_GOOMBA;
			}
			
			if (Mario->IsOnPlatform() && flag == MARIO_JUMP_ON_GOOMBA)
			{
				stateOfMario = MARIO_STATE_WALKING_RIGHT;
			}

			if (stateOfMario == MARIO_STATE_WALKING_RIGHT)
			{
				Mario->SetState(stateOfMario);
				
				Mario->GetPosition(x, y);
				if (x >= Screen_Width * 6 / 8)
				{
					Mario->SetState(MARIO_STATE_IDLE);
					stateOfMario = MARIO_STATE_IDLE;

					if (ItemsAndEnemies.size() == 0)
					{
						Luigi->GetPosition(x, y);
						Luigi->SetState(MARIO_STATE_READY_HOLD);

						LPGAMEOBJECT obj = new CKoopas(x - 20, y, KOOPAS_TYPE_GREEN, 1);
						obj->SetState(KOOPAS_STATE_SHELL);
						ItemsAndEnemies.push_back(obj);

						flag = LUIGI_HOLDING_KOOPAS;
						time_start = GetTickCount64();
						stateOfMario = 0;
					}
					
				}
			}
		}
		
		if (flag == LUIGI_HOLDING_KOOPAS)
		{
			Luigi->SetState(MARIO_STATE_WALKING_LEFT);
			Luigi->SetState(MARIO_STATE_READY_HOLD);
			if (GetTickCount64() - time_start > MARIO_WALKING_TIME)
			{
				Luigi->SetState(MARIO_STATE_HOLD_RELEASE);
				Luigi->SetState(MARIO_STATE_IDLE);
				time_start = 0;
				Mario->SetState(MARIO_STATE_JUMP);
				flag = MARIO_JUMP_ON_KOOPAS;
			}
			
			Luigi->GetPosition(x, y);
			if (x <= Screen_Width + 10)
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
		}

		if (flag == MARIO_JUMP_ON_KOOPAS)
		{
			Mario->GetSpeed(x, y);
			if (y >= 0 && Mario->IsOnPlatform())
			{
				Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				Mario->SetState(MARIO_STATE_READY_HOLD);
			}

			if (Mario->IsHolding())
			{
				Mario->GetPosition(x, y);
				if (x > Screen_Width / 2 - 20)
				{
					Mario->SetState(MARIO_STATE_HOLD_RELEASE);
					Mario->SetState(MARIO_STATE_IDLE);
					Luigi->SetState(MARIO_STATE_WALKING_RIGHT);

					flag = KOOPAS_ATTACKING;
					time_start = GetTickCount64();
				}
			}
		}

		if (flag == KOOPAS_ATTACKING)
		{
			if (time_start != 0 && (GetTickCount64() - time_start) > WAITING_KOOPAS_ATTACK_TIME)
			{
				Mario->GetPosition(x, y);
				LPGAMEOBJECT obj = new CKoopas(0, y, KOOPAS_TYPE_GREEN, 1);
				obj->SetNx(-1);
				obj->SetState(KOOPAS_STATE_ATTACKING);
				ItemsAndEnemies.push_back(obj);
				time_start = 0;
			}
			if (Mario->GetLevel() == MARIO_LEVEL_BIG)
			{
				Mario->SetLevel(MARIO_LEVEL_SMALL);
			}
			else if (Mario->GetLevel() == MARIO_LEVEL_SMALL)
			{
				if (ItemsAndEnemies.size() == 0)
				{
					time_start = GetTickCount64();
					flag = MARIO_WALKING_TIME;
					Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				}
			}
		}
		if (flag == MARIO_WALKING_TIME)
		{
			float vx, vy;
			Mario->GetSpeed(vx, vy);
			Mario->GetPosition(x, y);
			DebugOut(L"x: %f, y: %f, vx: %f, vy: %f \n", x, y, vx, vy);
			if (vx > 0 && x >= Screen_Width * 4 / 5)
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
			if (vx < 0 && x <= Screen_Width * 3 / 5)
			{
				Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				flag = KOOPAS_WALKING;
			}

		}
		if (flag == KOOPAS_WALKING)
		{
			Mario->GetPosition(x, y);
			if (x > Screen_Width + 30 && ItemsAndEnemies.size() == 0)
			{
				LPGAMEOBJECT obj = new CKoopas(0, y - 5, KOOPAS_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopas(-20, y - 5, KOOPAS_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopas(-40, y - 5, KOOPAS_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);
			}

			if (ItemsAndEnemies.size() != 0)
			{
				ItemsAndEnemies[0]->GetPosition(x, y);
				if (x >= Screen_Width / 2 + 15)
				{
					LPGAMEOBJECT obj = new CKoopas(-40, y - 5, KOOPAS_TYPE_GREEN, 1);
					obj->SetSpeed(0.08f, 0);
					ItemsAndEnemies.push_back(obj);

					Mario->SetState(MARIO_STATE_IDLE);
					flag = 0;
				}
			}

		}
	}

public:

	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer(int i = 0) { if (i < 2 && i >= 0) return player[i];  return NULL; }

	CPortal* GetPortal() { return portal; }

	vector<CPlatform*>& GetPlatformObjects() { return platform_objects; }
	CPlatformAnimate* GetNumber3() { return Number3; }
	float GetNumber3original_y() { return Number3original_y; }

	void MainScreen() { flag = 0; time_start = 0; MarioWalking_start = 0; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;