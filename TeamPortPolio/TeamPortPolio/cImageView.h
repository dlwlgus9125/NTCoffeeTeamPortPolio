#pragma once
#include "cUIObject.h"

class cImageView : public cUIObject
{
public:
	cImageView();
	virtual ~cImageView();

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	virtual void SetTexture(char* szFullPath);

	virtual void Render(LPD3DXSPRITE pSprite);
};

