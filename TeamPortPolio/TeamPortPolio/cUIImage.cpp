#include "stdafx.h"
#include "cUIImage.h"


cUIImage::cUIImage() : m_pTexture(NULL), m_nAlpha(255)
{
	SetSizeUV(ST_SIZE_UV(200, 200));
}


cUIImage::~cUIImage()
{
	SAFE_RELEASE(m_pTexture);
}

void cUIImage::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	SetRect(&rc, 0, 0, m_stSize_UV.fU, m_stSize_UV.fV);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	pSprite->End();
}

void cUIImage::Setup_Image(LPDIRECT3DTEXTURE9 texture, int a)
{
	m_pTexture = texture;
	m_nAlpha = a;
}