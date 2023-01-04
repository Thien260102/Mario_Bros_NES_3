#include "PlatformAnimate.h"

void CPlatformAnimate::Render()
{
	CAnimations::GetInstance()->Get(animation)->Render(x, y);
}

void CPlatformAnimate::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLATFORM_ANIMATE_BBOX_WIDTH / 2;
	t = y - PLATFORM_ANIMATE_BBOX_HEIGHT / 2;
	r = l + PLATFORM_ANIMATE_BBOX_WIDTH;
	b = t + PLATFORM_ANIMATE_BBOX_HEIGHT;
}