#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
{
}


cUIImageView::~cUIImageView()
{
}

void cUIImageView::SetTexture(char* szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = TEXTURE->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	

	//cUIObject::Render(pSprite);
}