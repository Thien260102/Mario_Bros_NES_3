#include "Hud.h"
#include "Game.h"
#include "PlayScene.h"
#include "Sprites.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"
#include "Timer.h"

CHud* CHud::_instance = NULL;

void CHud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_BBOX_WIDTH / 2;
	t = y - HUD_BBOX_HEIGHT / 2;
	r = l + HUD_BBOX_WIDTH;
	b = t + HUD_BBOX_HEIGHT;
}

void CHud::Update()
{
	// Get camera position
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	x = cam_x + HUD_BBOX_WIDTH * 2 / 3;
	y = (cam_y + CGame::GetInstance()->GetBackBufferHeight() * 4 / 5 + HUD_BBOX_HEIGHT - ADJUST);
}

void CHud::Render()
{
	Update();
	CSprites* sprites = CSprites::GetInstance();

	//draw main hud
	sprites->Get(ID_SPRITE_HUD)->Draw(x, y);

	//draw giftbox and gift
	float giftBox_x, giftBox_y;
	giftBox_x = x + HUD_BBOX_WIDTH / 2 + GIFTBOX_BBOX_WIDTH;
	giftBox_y = y;
	for (int i = 0; i < 3; i++)
	{
		sprites->Get(ID_SPRITE_GIFT_BOX_BLU)->Draw(giftBox_x, giftBox_y);
		
		if(gifts.size() > i)
			sprites->Get(gifts[i])->Draw(giftBox_x, giftBox_y);
		
		giftBox_x += GIFTBOX_BBOX_WIDTH;
	}

	// get left edge of HUD
	float hx, hy;
	hx = x - HUD_BBOX_WIDTH / 2;
	hy = y - HUD_BBOX_HEIGHT / 2;

	//draw name of charactor M or L(Mario or Lugi)
	sprites->Get(ID_SPRITE_SYMBOL_M)->Draw(hx + MARIO_SYMBOL_WIDTH / 2 + COLUMN_ML_X, hy + MARIO_SYMBOL_HEIGHT / 2 + ROW_BELOW_Y);

	//draw current world
	sprites->Get(ID_SPRITE_NUMBER_1)->Draw(hx - NUMBER_WIDTH / 2 + COLUMN_WL_X, hy + ROW_ABOVE_Y + NUMBER_HEIGHT / 2);


	//draw Life
	float p_x = hx - NUMBER_WIDTH / 2 + COLUMN_WL_X;
	float p_y = hy + ROW_BELOW_Y + NUMBER_HEIGHT / 2;
	RenderNumber(p_x, p_y, life);
	
	//draw Score
	p_x = hx - NUMBER_WIDTH / 2 + COLUMN_SCORE_X;
	p_y = hy + ROW_BELOW_Y + NUMBER_HEIGHT / 2;
	RenderNumber(p_x, p_y, score, LENGTH_SCORE, 1);

	//draw Coin
	p_x = hx - NUMBER_WIDTH / 2 + COLUMN_MT_X;
	p_y = hy + ROW_ABOVE_Y + NUMBER_HEIGHT / 2;
	RenderNumber(p_x, p_y, coin);

	//draw time
	p_x = hx - NUMBER_WIDTH / 2 + COLUMN_MT_X;
	p_y = hy + ROW_BELOW_Y + NUMBER_HEIGHT / 2;
	RenderNumber(p_x, p_y, CTimer::GetInstance()->Get_CurrentTime() / 1000, LENGTH_TIME, 1);

	//draw symbol of Mario's speed state
	p_x = hx - NUMBER_WIDTH / 2 + COLUMN_SPEED_X;
	p_y = hy + ROW_ABOVE_Y + NUMBER_HEIGHT / 2;

	//Get speed of Mario
	float Mvx = 0;
	float Mvy = 0;
	bool isFlying = false;
	if (dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene()))
	{
		CMario* mario = dynamic_cast<CMario*>(((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
		mario->GetSpeed(Mvx, Mvy);
		isFlying = mario->IsFlying();
	}

	for (int i = 0; i < 6; i++)
	{
		if ((abs(Mvx) - MARIO_WALKING_SPEED) >= (SPEED_LEVEL * (i + 1)) || isFlying)
			sprites->Get(ID_SPRITE_ARROW_WHITE)->Draw(p_x + ARROW_SYMBOL_WIDTH, p_y);
		else
			sprites->Get(ID_SPRITE_ARROW_BLACK)->Draw(p_x + ARROW_SYMBOL_WIDTH, p_y);
		p_x += ARROW_SYMBOL_WIDTH + 1;
	}
	if (abs(Mvx) == MARIO_RUNNING_SPEED || isFlying)
		CAnimations::GetInstance()->Get(ID_ANI_P_CHANGING_COLOR)->Render(p_x + POWER_SYMBOL_WIDTH, p_y);
	else
		sprites->Get(ID_SPRITE_P_BLACK)->Draw(p_x + POWER_SYMBOL_WIDTH, p_y);
}

void CHud::RenderNumber(float p_x, float p_y, int number, int length, int option)
{
	CSprites* sprites = CSprites::GetInstance();

	switch (option)
	{
	case 1:
		for (int i = 0; i < length; i++)
		{
			int digit = number % 10;
			sprites->Get(ID_SPRITE_NUMBER_0 + digit)->Draw(p_x, p_y);
			p_x -= NUMBER_WIDTH;

			number /= 10;
		}
		break;

	case 0:
		if (number == 0)
			sprites->Get(ID_SPRITE_NUMBER_0)->Draw(p_x, p_y);

		while ((number / 1) > 0)
		{
			int digit = number % 10;
			sprites->Get(ID_SPRITE_NUMBER_0 + digit)->Draw(p_x, p_y);
			p_x -= NUMBER_WIDTH;

			number /= 10;
		}
		break;
	}




}