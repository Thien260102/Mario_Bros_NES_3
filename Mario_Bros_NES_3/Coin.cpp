#include "Coin.h"
#include "Brick.h"
#include "Game.h"
#include "PlayScene.h"
#include "Effect.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (remainTime_start != 0)
		CoinTransformBrick();

	if (vy == 0 && ay == 0)
		return;

	if (ay != 0 && vy >= 0 && y >= (old_y - 2 * COIN_BBOX_HEIGHT))
	{
		this->Delete();
		CEffect::GetInstance()->pushEffectIntoQueue(x, y, ID_SPRITE_POINTS_100, true, true);
	}

	if (ay != 0)
	{
		vy += ay * dt;
		y += vy * dt;
	}
}

void CCoin::CoinTransformBrick()
{
	if (GetTickCount64() - remainTime_start > COIN_TIMEOUT)
	{
		if ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())
		{
			this->Delete();

			CGameObject* brick = new CBrick(x, y);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetObjects().push_back(brick);
		}
	}
}

void CCoin::Render()
{
	int aniId = ID_ANI_COIN;
	if (ay != 0)
		aniId = ID_ANI_COIN_DEFLECT;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Deflected(int direction)
{
	ay = COIN_GRAVITY;
	vy = -COIN_DEFLECT;
	old_y = y;
}