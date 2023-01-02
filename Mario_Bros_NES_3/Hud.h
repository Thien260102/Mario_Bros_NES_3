#pragma once
#include "GameObject.h"

#define ID_ANI_P_CHANGING_COLOR	8888
#define EFFECTS_SPEED 0.02f

#define HUD_BBOX_WIDTH	153
#define HUD_BBOX_HEIGHT	29

#define GIFTBOX_BBOX_WIDTH	24
#define GIFTBOX_BBOX_HEIGHT	29


#define NUMBER_WIDTH	7
#define NUMBER_HEIGHT	6
#define MARIO_SYMBOL_WIDTH	15
#define MARIO_SYMBOL_HEIGHT	7

////	relative location to HUD	////
#define ROW_ABOVE_Y 8	// contain something example: World 1.1 , >>>>> P and $ 12
#define ROW_BELOW_Y 16	//example: M (or L), 1(Life), 300(Time)

//LEFT TO RIGHT
#define COLUMN_ML_X		5	// M or L (Mario or Lugi) 
#define COLUMN_SPEED_X	53	
//RIGHT TO LEFT
#define COLUMN_WL_X		45	//current world, life
#define COLUMN_SCORE_X	108 //Score
#define COLUMN_MT_X		148	//money and time


////	relative location to HUD	////

#define LENGTH_SCORE	8
#define LENGTH_TIME		3

#define ADJUST 3

class CHud : public CGameObject
{
protected:

	int coin;
	int life;

	int score;
	vector<int> gifts;

	void RenderNumber(float p_x, float p_y, int number, 
		int length = 0,  //use in case option = 1
		int option = 0); //0: Normal draw( example: 100 -> draw 100), 1: Special draw (example: 100 -> draw 0000100)
public:
	CHud(float x, float y) : CGameObject(x, y)
	{
		gifts.clear();
		coin = 0;
		life = 39;
		score = 30000;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		this->Update();
	}
	void Update();
	void Render();


	virtual int IsBlocking() { return 0; }

	void CollectCoin() { coin++; }
	void Collect_1upMushroom() { life++; }
	void MarioDeath() { life--; }
	int AddScore(int Score) { score = Score; }

	int CanRevive() { return life > 0; }
};
