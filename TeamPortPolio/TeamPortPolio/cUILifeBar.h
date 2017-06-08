#pragma once
#include "cUIObject.h"
class cUILifeBar :public cUIObject
{
public:
	cUILifeBar();
	~cUILifeBar();
	virtual void SetTexture(char * szfullpath);

	virtual void Update()override;

	virtual void Render(LPD3DXSPRITE pSprite)override;

private:

	LPDIRECT3DTEXTURE9  m_pTexture;
	LPD3DXLINE m_pLine;
	D3DXVECTOR3 m_vLifeBar[2];
	D3DXCOLOR m_color;
};
