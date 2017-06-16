#include "stdafx.h"
#include "cUISlot.h"


cUISlot::cUISlot()
{
}


cUISlot::~cUISlot()
{
}

void cUISlot::Update(float deltaTime)
{
	if (m_isHidden) return;

	cUIObject::Update(deltaTime);
}

void cUISlot::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	cUIObject::Render(pSprite);
}

void cUISlot::Destroy()
{

	cUIObject::Destroy();
}
