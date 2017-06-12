#pragma once
#include "stdafx.h"
#include "cUILifeBar.h"

cUILifeBar::cUILifeBar()
	:m_pTexture(NULL)
	, m_pLine(NULL)
{
	SetFuntion(FUNTION_LIFE_BAR);
}

cUILifeBar::~cUILifeBar()
{
	SAFE_RELEASE(m_pLine);
	SAFE_RELEASE(m_pTexture);
}

void cUILifeBar::SetTexture(char * szfullpath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = TEXTURE->GetTexture(szfullpath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	D3DXCreateLine(D3DDevice, &m_pLine);
}

void cUILifeBar::Update()
{
	D3DXMATRIXA16 matS, matT;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS,m_fScaleX, m_fScaleY, 1);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_Matrix = matS*matT;

	float value = 0;// CurrentHp / maxHp;
	float WidthOfLifeBar = GetSize().nWidth*m_fScaleX;
	float HeightOfLifeBar = GetSize().nHeight*m_fScaleY*0.5;
	//>>test
	static float a = 0;
	if (INPUT->IsKeyPress(VK_LEFT))a -= 20;
	if (a > WidthOfLifeBar*18/20) a = WidthOfLifeBar * 18 / 20;
	if (a < 0) a = 0;
	//<<
	m_pLine->SetWidth(HeightOfLifeBar);
	m_vLifeBar[0] = D3DXVECTOR3(m_vPosition.x+ WidthOfLifeBar * 1 / 20, HeightOfLifeBar, 0);/*시작지점*/
	m_vLifeBar[1] = D3DXVECTOR3(m_vLifeBar[0].x+(a+=10), HeightOfLifeBar, 0);/*끝지점*/
	
	m_color = D3DXCOLOR(WidthOfLifeBar / (4*a), (4*a) / WidthOfLifeBar, 0, 1);
}


void cUILifeBar::Render(LPD3DXSPRITE pSprite)
{
	//체력바
	m_pLine->Begin();
	
	D3DXMATRIX out, view, proj;
	D3DDevice->GetTransform(D3DTS_VIEW, &view);
	D3DDevice->GetTransform(D3DTS_PROJECTION, &proj);

	out = view * proj;
	m_pLine->DrawTransform(m_vLifeBar, 2, &out, m_color);
	m_pLine->End();
	//<<
	//>>뒷판
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_Matrix);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();
	//<<
}

