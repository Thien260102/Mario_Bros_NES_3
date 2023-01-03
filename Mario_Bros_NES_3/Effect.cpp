#include "Effect.h"
#include "debug.h"
#include "AssetIDs.h"

CEffect* CEffect::_instance = NULL;

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 0;
	t = y - 0;
	r = l + 0;
	b = t + 0;
}

void CEffect::Render()
{
	for (LPGAMEOBJECT e : effects)
	{
		CEffect* effect = dynamic_cast<CEffect*>(e);
		effect->SpecificRender();
	}
}

void CEffect::SpecificRender()
{
	if (this->renderTime_start != 0)
	{
		// render effect
		if (isSprite)
		{
			CSprites::GetInstance()->Get(idSpriteorAni)->Draw(this->x, this->y);
		}
		else
		{
			CAnimations::GetInstance()->Get(idSpriteorAni)->Render(this->x, this->y);
		}

		if (GetTickCount64() - this->renderTime_start > EFFECT_TIME)
		{
			this->renderTime_start = 0;
			this->vy = 0;
			this->isDeleted = true;
		}
	}
}

void CEffect::SetPosition(float px, float py)
{
	x = px;
	y = py;
	renderTime_start = GetTickCount64();
}

void CEffect::Deflected(int Direction)
{
	vy = -EFFECT_SPEED;
}

void CEffect::PurgeDeletedEffects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = effects.begin(); it != effects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	effects.erase(
		std::remove_if(effects.begin(), effects.end(), CEffect::IsEffectDeleted),
		effects.end());
}

bool CEffect::IsEffectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }