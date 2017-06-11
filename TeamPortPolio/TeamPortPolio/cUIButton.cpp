#include "stdafx.h"
#include "cUIButton.h"
#include "cUITextView.h"

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

	m_aTexture[E_MOUSEOVER] = TEXTURE->GetTexture(szOver, &stImageInfo);
	//assert(m_stSize.nWidth == stImageInfo.Width && m_stSize.nHeight == stImageInfo.Height);	// 임시로 이미지 파일이 다른가를 검사
	m_aTexture[E_SELECTED] = TEXTURE->GetTexture(szSel, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

}

void cUIButton::Update()
{
	POINT pt = INPUT->GetMousePos();

	D3DXVECTOR3 Pos = m_pParent->GetPosition() + m_vPosition;

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, m_fScaleX,m_fScaleY, 1);
	
	RECT rc;
	if (m_Funtion != FUNTION_OPEN)  {	
		SetRect(&rc, (int)Pos.x, (int)Pos.y, (int)Pos.x + ((int)m_stSize.nWidth*m_fScaleX), (int)Pos.y + ((int)m_stSize.nHeight*m_fScaleY));
		D3DXMatrixTranslation(&matT, Pos.x, Pos.y, Pos.z);
	}
	else if(m_Funtion==FUNTION_OPEN){	
		SetRect(&rc,m_vPosition.x,m_vPosition.y,m_vPosition.x + (m_stSize.nWidth*m_fScaleX),m_vPosition.y + (m_stSize.nHeight*m_fScaleY));
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	}
	m_Matrix = matS*matT;

	if (PtInRect(&rc, pt))
	{
		if (INPUT->IsMouseDown(MOUSE_LEFT))
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
				case FUNTION_OPEN:	m_pParent->SetIsHidden(false);	break;
				case FUNTION_CLOSE:	m_pParent->SetIsHidden(true);	break;
				case FUNTION_OK: 
				{
					if (m_pParent->GetOnClick()) SetOnClick(false);
					else m_pParent->SetOnClick(true);
				}
				break;
				}
			}
			m_eButtonState = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonState = E_NORMAL;
	}
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
	pSprite->SetTransform(&m_Matrix);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_aTexture[m_eButtonState], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();
}