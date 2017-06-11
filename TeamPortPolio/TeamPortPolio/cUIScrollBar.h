#pragma once
#include "cUIObject.h"

class cUIScrollBar :public cUIObject
{
	bool m_isSelected;
	bool m_isInRange;
	LPDIRECT3DTEXTURE9	m_pTexture[2];
	SYNTHESIZE(D3DXVECTOR3, m_vLanePos, LanePos);
	SYNTHESIZE(ST_SIZEN, m_stLaneSize, LaneSize);
public:
	cUIScrollBar();
	~cUIScrollBar();
	
	virtual void SetTexture(char * szLanePath,char* szHeadPath);

	virtual void Update()override;

	virtual void Render(LPD3DXSPRITE pSprite)override;
	
	float GetRate();


};