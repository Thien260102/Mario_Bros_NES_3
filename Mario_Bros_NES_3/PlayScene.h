#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopas.h"
#include "Plant.h"
#include "InvisibleObject.h"

////use only for map 1.1////
#define CAMERA_POSITION_MIN_Y 0
#define DEFAULT_CAMERA_POSITION_Y 230//252
#define CAMERA_POSITION_MAX_X 2499
#define POSITION_SECRET_ROOM 2700
#define POSITION_SECRET_ROOM_Y 220
////////////////////////////

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	
	// InvisibleObject
	CInvisibleObject* invisible;

	vector<LPGAMEOBJECT> objects;
	
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	CInvisibleObject* GetInvisibleObject() { return invisible; }

	vector<LPGAMEOBJECT>& GetObjects() { return objects; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

