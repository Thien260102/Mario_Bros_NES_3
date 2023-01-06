#pragma once
#include "Scene.h"
#include "Game.h"
#include "Textures.h"
#include "GameObject.h"
#include "Portal.h"
#include "Platform.h"
#include "PlatformAnimate.h"

#define CURTAIN_FLYING_TIME	2000

#define CURTAIN_FLYING	100
#define GAMENAME_DOWING  200

class CIntroScene :public CScene
{
protected:
	ULONGLONG curtainFlying_start;
	int flag; // determine curtain flying or something else (example: Game name downing)
	float Number3original_y = 0;

	LPGAMEOBJECT player[2];
	
	CPortal* portal;

	vector<LPGAMEOBJECT> objects;
			
	vector<CPlatform*> platform_objects;
	CPlatformAnimate* Number3;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:

	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer(int i) { if (i < 2 && i >= 0) return player[i];  return NULL; }

	CPortal* GetPortal() { return portal; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;