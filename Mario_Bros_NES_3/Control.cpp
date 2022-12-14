#include "Control.h"
#include "Game.h"
#include "PlayScene.h"

CControl* CControl::_instance = NULL;

void CControl::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CONTROL_PAUSE_BBOX_WIDTH / 2;
	t = y - CONTROL_PAUSE_BBOX_HEIGHT / 2;
	r = l + CONTROL_PAUSE_BBOX_WIDTH;
	b = t + CONTROL_PAUSE_BBOX_HEIGHT;
}

void CControl::CalculatePosition(int type)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	switch (type)
	{
	case CONTROL_TYPE_PAUSE:
		x = cam_x + CGame::GetInstance()->GetBackBufferWidth() / 2;
		y = (cam_y + CGame::GetInstance()->GetBackBufferHeight() / 2 + CONTROL_PAUSE_BBOX_HEIGHT / 2);
		break;

	case CONTROL_TYPE_MODE:
		x = cam_x + CGame::GetInstance()->GetBackBufferWidth() / 2;
		y = (cam_y + CGame::GetInstance()->GetBackBufferHeight() * 2 / 3 + CONTROL_MODE_BBOX_HEIGHT);
		break;
	}

}

void CControl::Render()
{
	CSprites* sprites = CSprites::GetInstance();

	for (int i = 0; i < n; i++)
	{
		if (active[i] == 0)
			continue;

		this->CalculatePosition(i + 1);

		int spriteId = -1;
		switch (i + 1) // type
		{
		case CONTROL_TYPE_PAUSE:
			spriteId = ID_SPRITE_PAUSE;
			break;

		case CONTROL_TYPE_MODE:
			spriteId = ID_SPRITE_1PLAYERGAME;
			break;
		}

		sprites->Get(spriteId)->Draw(x, y);
	}
}