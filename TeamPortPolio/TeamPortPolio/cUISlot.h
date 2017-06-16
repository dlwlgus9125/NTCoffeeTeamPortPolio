#pragma once
#include "cUIObject.h"
class cUISlot :
	public cUIObject
{
	vector<ST_SLOT>				m_vecSlotInfo;
	vector<ST_SLOTDATA*>		m_vecSlotData;
	vector<ST_SLOTDATA*>		m_vecShownData;
	FONT_TAG m_eFont;

public:
	cUISlot();
	~cUISlot();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Slot(int col, int slotCount, D3DXVECTOR3 imagePos_first, ST_SIZEN imageSize, D3DXVECTOR3 textPos_first, ST_SIZEN textSize, FONT_TAG eFont = FONT_DEF);
	void AddSlotData(string name, LPDIRECT3DTEXTURE9 texture, string info);
	void SetShownData(int startIndex);
};

