#include "IntroScene.h"

#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "TeleportGate.h"
#include "Hud.h"
#include "PlatformAnimate.h"
#include "Mario.h"
#include "Control.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Koopas.h"

#include "IntroKeyEventHandler.h"

using namespace std;

CIntroScene::CIntroScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player[0] = NULL;
	player[1] = NULL;
	flag = 0;
	key_handler = new CIntroKeyEventHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CIntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CIntroScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CIntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CIntroScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player[0] != NULL && player[1] != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		if (player[0] == NULL)
		{
			player[0] = (CMario*)obj;
			((CMario*)player[0])->SetLevel(MARIO_LEVEL_BIG);
		}

		else
		{
			player[1] = (CMario*)obj;
			((CMario*)player[1])->SetLevel(MARIO_LEVEL_BIG);
		}

		DebugOut(L"[INFO] Player object has been created!\n");
		
		break;

	case OBJECT_TYPE_PLATFORM_ANIMATE:
	{
		int aniOrsprite = atoi(tokens[3].c_str());
		int type = atoi(tokens[4].c_str());
		int isAni = atoi(tokens[5].c_str());

		obj = new CPlatformAnimate(x, y, aniOrsprite, type, isAni);
		Number3 = (CPlatformAnimate*)(obj);

		Number3original_y = y;
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int type = atoi(tokens[9].c_str());
		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			type
		);

		platform_objects.push_back((CPlatform*)obj);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		int type = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id, type);

		portal = (CPortal*)obj;

		
		break;
	}
	

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CIntroScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CIntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	flag = CURTAIN_FLYING;
	curtainFlying_start = GetTickCount64();
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CIntroScene::Update(DWORD dt)
{
	//PAUSING
	if (CControl::GetInstance()->IsPausing())
		return;
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 2; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	//objects[0]->Update(dt, &coObjects);
	//player[0]->Update(dt, &coObjects);
	//player[1]->Update(dt, &coObjects);
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//Curtain flying
	if (flag == CURTAIN_FLYING)
	{
		float number3_x, number3_y;
		Number3->GetPosition(number3_x, number3_y);
		Number3->SetPosition(number3_x, number3_y - 0.1f * dt);

		for (int i = 1; i < platform_objects.size(); i++)
		{
			int id = platform_objects[i]->GetSpriteIDBegin();
			float x, y;
			platform_objects[i]->GetPosition(x, y);
			if (1)//(id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2))
			{
				if (GetTickCount64() - curtainFlying_start > CURTAIN_FLYING_TIME)
				{
					flag = GAMENAME_DOWING;
					curtainFlying_start = 0;
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

		for (int i = 1; i < platform_objects.size(); i++)
		{
			int id = platform_objects[i]->GetSpriteIDBegin();
			float x, y;
			platform_objects[i]->GetPosition(x, y);
			if (!(id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2))
			{
				if (Number3original_y <= number3_y)
				{
					flag = 0;
					float adjust = (Number3original_y - number3_y);
					platform_objects[i]->SetPosition(x, y - adjust);
					Number3->SetPosition(number3_x, Number3original_y);

					CControl::GetInstance()->ActiveControl(CONTROL_TYPE_MODE);

					CGameObject* obj = new CGoomba(number3_x - 10, number3_y, GOOMBA_TYPE_NORMAL);
					objects.push_back(obj);

					obj = new CKoopas(number3_x, number3_y, KOOPAS_TYPE_GREEN, 1);
					obj->SetState(KOOPAS_STATE_SHELL);
					objects.push_back(obj);

					obj = new CMushroom(number3_x, number3_y, MUSHROOM_TYPE_SUPER);
					objects.push_back(obj);

					obj = new CMushroom(number3_x, number3_y, MUSHROOM_TYPE_SUPER_LEAF);
					objects.push_back(obj);
				}
				else
				{
					platform_objects[i]->SetPosition(x, y + 0.1f * dt);
				}
			}
		}
	}

	// Lugi jump on Mario and touch sky
	//float mx, my;
	//player[0]->GetPosition(mx, my);
	//if (my < 0)
	//{
		//flag = GAMENAME_DOWING;
	//}
	

	float cx, cy;
	cx = 0;
	cy = 0;

	CGame::GetInstance()->SetCamPos(cx, cy);
	//DebugOutTitle(L"cx: %f\n", cx);
	PurgeDeletedObjects();
}

void CIntroScene::Render()
{
	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->Render();

	player[0]->Render();
	player[1]->Render();
	//render stage
	platform_objects[0]->Render();

	
	for (int i = platform_objects.size() - 1; i > 0; i--)
	{
		int id = platform_objects[i]->GetSpriteIDBegin();
		if((id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2))
			platform_objects[i]->Render();
	}

	//CControl::GetInstance()->ActiveControl(CONTROL_TYPE_MODE);
	CControl::GetInstance()->Render();
}

/*
*	Clear all objects from this scene
*/
void CIntroScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CIntroScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player[0] = NULL;
	player[1] = NULL;
	platform_objects.clear();

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CIntroScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CIntroScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CIntroScene::IsGameObjectDeleted),
		objects.end());
}