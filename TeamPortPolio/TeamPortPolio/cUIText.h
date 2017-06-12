#pragma once
#include "cUIObject.h"
class cUIText :
	public cUIObject
{
	SYNTHESIZE(string, m_sText, Text);
	FONT_TAG m_eFont;
public:
	cUIText();
	~cUIText();

	virtual void Render(LPD3DXSPRITE pSprite);

	void Setup_Text(string text, FONT_TAG tag = FONT_DEF);
};

