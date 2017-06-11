#pragma once
#include "cUIObject.h"

class cUITextView;
class cUIButton : public cUIObject
{
public:
	cUIButton();
	virtual ~cUIButton();

protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_CNT,	// ī��Ʈ��
	};
	SYNTHESIZE(eButtonState, m_eButtonState, ButtonState);
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];

public:
	virtual void SetTexture(char* szNor, char* szOver, char* szSel);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};