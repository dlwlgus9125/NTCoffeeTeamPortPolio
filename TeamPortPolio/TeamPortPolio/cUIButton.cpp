#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_eButtonState(E_NORMAL)
{
}


cUIButton::~cUIButton()
{
}

void cUIButton::SetTexture(char* szNor, char* szOver, char* szSel)
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture[E_NORMAL] = TEXTURE->GetTexture(szNor, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	m_aTexture[E_MOUSEOVER] = TEXTURE->GetTexture(szOver, &stImageInfo);
	assert(m_stSize.nWidth == stImageInfo.Width && m_stSize.nHeight == stImageInfo.Height);	// 임시로 이미지 파일이 다른가를 검사

	m_aTexture[E_SELECTED] = TEXTURE->GetTexture(szSel, &stImageInfo);
}

void cUIButton::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;

	if (m_Funtion == FUNTION_OPEN)	{	SetRect(&rc,m_vPosition.x,m_vPosition.y,m_vPosition.x + m_stSize.nWidth,m_vPosition.y + m_stSize.nHeight);	}
	else							{	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWidth, (int)m_matWorld._42 + (int)m_stSize.nHeight);	}

	if (PtInRect(&rc, pt))
	{
		if (GetKeyState(VK_LBUTTON)&0x8000)
		{
			if (m_eButtonState == E_MOUSEOVER)
			{
				m_eButtonState = E_SELECTED;
			}
		}
		else
		{
			if (m_eButtonState == E_SELECTED)
			{
				switch (m_Funtion)
				{
				case FUNTION_OPEN:	m_pParent->m_isHidden	=false;	break;
				case FUNTION_CLOSE:	m_pParent->m_isHidden	=true;	break;
				case FUNTION_NEXT:	m_pParent->m_isNextPage	=true;	break;
				case FUNTION_PREV:	m_pParent->m_isNextPage	=false;	break;
				}
			}
			m_eButtonState = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonState = E_NORMAL;
	}

	cUIObject::Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	
	
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	pSprite->Draw(m_aTexture[m_eButtonState], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));


	cUIObject::Render(pSprite);
}