#include "WorldMapKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario_WorldMap.h"
#include "WorldMapScene.h"
#include "Control.h"

void CWorldMapKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario_WorldMap* mario = (CMario_WorldMap*)((LPWORLDMAPSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	LPGAME game = CGame::GetInstance();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetCanGoIntoPortal(1);
		break;

	case DIK_ESCAPE:
		if (CControl::GetInstance()->IsPausing())
			CControl::GetInstance()->InActiveControl(CONTROL_TYPE_PAUSE);
		else
			CControl::GetInstance()->ActiveControl(CONTROL_TYPE_PAUSE);
		//DebugOut(L"ESC pressed\n");

		break;
	}

}

void CWorldMapKeyEventHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario_WorldMap* mario = (CMario_WorldMap*)((LPWORLDMAPSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetCanGoIntoPortal(0);
		break;
	}
}

void CWorldMapKeyEventHandler::KeyState(BYTE* states)
{
	CMario_WorldMap* mario = (CMario_WorldMap*)((LPWORLDMAPSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	LPGAME game = CGame::GetInstance();

	if (mario->IsMoving())
		return;

	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetState(MARIO_WM_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		mario->SetState(MARIO_WM_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		mario->SetState(MARIO_WM_STATE_WALKING_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		mario->SetState(MARIO_WM_STATE_WALKING_DOWN);
	}

}
