#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
#define PLATFORM_TYPE_BLOCK 10
#define PLATFORM_TYPE_NORMAL 20
#define PLATFORM_TYPE_NOCOLLISION 30

class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

	int _type;
	virtual int IsBlocking() 
	{ 
		if (_type == PLATFORM_TYPE_BLOCK)
			return 1;
		else if (_type == PLATFORM_TYPE_NORMAL)
			return 2;
		return 0;
	}

public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int type) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		_type = type;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	
	int GetType() { return _type; }
};

typedef CPlatform* LPPLATFORM;