#pragma once
#include "cUIObject.h"

class cUITextView :	public cUIObject
{
public:
	cUITextView();
	virtual ~cUITextView();

protected:
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);
	
	LPD3DXFONT m_pFont;
	vector<string> m_vecText;
	void SetText(string Text);
	string GetText(bool PageofText);
	void SetUpFont();
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
	
	
};

