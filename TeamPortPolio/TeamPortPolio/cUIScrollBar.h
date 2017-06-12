#pragma once
#include "cUIObject.h"

class cUIScrollBar :public cUIObject
{
	bool m_isSelected;
	bool m_isInRange;
	LPDIRECT3DTEXTURE9	m_pTexture;
	RECT m_rcLane;
public:
	cUIScrollBar();
	~cUIScrollBar();
	void SetLaneRect(RECT rc) { m_rcLane = rc; }
	RECT GetLaneRect() { return m_rcLane; }
	void SetTexture(char * szHeadPath);
	
	virtual void Update()override;

	virtual void Render(LPD3DXSPRITE pSprite)override;
	
	float GetRate();
};