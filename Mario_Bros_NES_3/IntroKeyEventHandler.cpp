#include "IntroKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "IntroScene.h"
#include "Control.h"
#include "Portal.h"

void CIntroKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	LPINTROSCENE intro = ((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene());
	CControl* control = CControl::GetInstance();

	switch (KeyCode)
	{
	case DIK_S:
		if (control->IsActivatingMode()) // switch to WorldMap
		{
			control->InActiveControl(CONTROL_TYPE_MODE);

			DebugOut(L"Switch scene\n");
			intro->GetPortal()->SwitchScene();
		}
		else
		{
			control->ActiveControl(CONTROL_TYPE_MODE);

			intro->MainScreen();

			CPlatformAnimate* Number3 = intro->GetNumber3();
			vector<CPlatform*> platformObjects = intro->GetPlatformObjects();
			float Number3original_y = intro->GetNumber3original_y();

			float x, y;
			Number3->GetPosition(x, y);
			float adjust = Number3original_y - y;
			Number3->SetPosition(x, y + adjust);

			
			platformObjects[0]->GetPosition(x, y); // get position of stage
			platformObjects[2]->SetPosition(x, y + 77); // set position of black screen
			
			for (int i = 3; i < platformObjects.size(); i++)
			{
				if (platformObjects[i]->GetSpriteIDBegin() == ID_SPRITE_CURTAIN_1
					|| platformObjects[i]->GetSpriteIDBegin() == ID_SPRITE_CURTAIN_2)
				{
					//curtain flying
					platformObjects[i]->GetPosition(x, y);
					platformObjects[i]->SetPosition(x, y - 500);

					continue;
				}
				platformObjects[i]->GetPosition(x, y);
				platformObjects[i]->SetPosition(x, y + adjust);
			}
		}
		break;
	
	case DIK_ESCAPE:
		if (control->IsPausing())
			control->InActiveControl(CONTROL_TYPE_PAUSE);
		else
			control->ActiveControl(CONTROL_TYPE_PAUSE);

		break;
	}
}

void CIntroKeyEventHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	/*switch (KeyCode)
	{
	case DIK_S:
		break;
	}*/
}

void CIntroKeyEventHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);
	if (game->IsKeyDown(DIK_RIGHT))
	{
		game->SetCamPos(cx + 1, cy);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		game->SetCamPos(cx - 1, cy);
	}
}