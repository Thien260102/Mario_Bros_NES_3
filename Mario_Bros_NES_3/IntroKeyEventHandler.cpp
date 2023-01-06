#include "IntroKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "IntroScene.h"
#include "Control.h"
#include "Portal.h"

void CIntroKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CControl* control = CControl::GetInstance();

	switch (KeyCode)
	{
	case DIK_S:
		if (control->IsActivatingMode()) // switch to WorldMap
		{
			control->InActiveControl(CONTROL_TYPE_MODE);

			DebugOut(L"Switch scene\n");
			((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetPortal()->SwitchScene();
		}
		else
			control->ActiveControl(CONTROL_TYPE_MODE);
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
	/*LPGAME game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT))
	{
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
	}*/
}