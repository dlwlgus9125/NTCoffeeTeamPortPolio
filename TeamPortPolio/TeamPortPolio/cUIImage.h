#pragma once

#include "cUIObject.h"

class cUIImage : cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	SYNTHESIZE(int, m_nAlpha, Alpha);
public:
	cUIImage();
	~cUIImage();

	virtual void Render(LPD3DXSPRITE pSprite);

	void Setup_Image(LPDIRECT3DTEXTURE9 texture, int a = 255);
};

