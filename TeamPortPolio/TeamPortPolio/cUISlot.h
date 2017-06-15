#pragma once
#include "cUIObject.h"
class cUISlot :
	public cUIObject
{
	vector<ST_SLOT>			m_vecSlotInfo;
	vector<ST_IMAGE_TEXT>	m_vecData;

public:
	cUISlot();
	~cUISlot();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
};

