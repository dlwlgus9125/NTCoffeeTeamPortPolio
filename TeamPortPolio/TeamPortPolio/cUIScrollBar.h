#pragma once
#include "cUIObject.h"

class cUIImageView;
class cUIScrollBar :public cUIObject
{
	bool m_isSellected;
	bool m_isInRange;
	LPDIRECT3DTEXTURE9	m_pTexture;
	cUIImageView* m_pUIScrollLane;
public:
	cUIScrollBar();
	~cUIScrollBar();
	
	virtual void SetTexture(char * szfullpath);

	virtual void Update()override;

	virtual void Render(LPD3DXSPRITE pSprite)override;
	
	void SetUIScrollLane(cUIImageView* pimageview);
	float GetRate();


};