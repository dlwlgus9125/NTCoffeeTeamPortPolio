#include "stdafx.h"
#include "cImageView.h"


cImageView::cImageView() :
	m_pTexture(NULL)
{
}


cImageView::~cImageView()
{
	SAFE_RELEASE(m_pTexture);
}

void cImageView::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO Info;

	D3DXCreateTextureFromFileEx(D3DDevice,
		szFullPath,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&Info,
		NULL,
		&m_pTexture);

	m_stSize.nWidth = Info.Width;
	m_stSize.nHeight = Info.Height;
}

void cImageView::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16 matT;
	D3DXVECTOR3 p = m_pParent->GetPosition() + m_vPosition;
	D3DXMatrixTranslation(&matT, p.x, p.y, p.z);

	pSprite->SetTransform(&matT);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();
}
