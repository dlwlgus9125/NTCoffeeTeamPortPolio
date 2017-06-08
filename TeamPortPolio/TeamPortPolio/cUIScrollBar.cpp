#include "stdafx.h"
#include "cUIScrollBar.h"
#include "cUIImageView.h"
cUIScrollBar::cUIScrollBar()
	:m_isSellected(false)
	,m_pUIScrollLane(false)
	,m_isInRange(false)
{
}


cUIScrollBar::~cUIScrollBar()
{
}

void cUIScrollBar::SetUIScrollLane(cUIImageView * pimageview)
{
	m_pUIScrollLane = pimageview;
}

void cUIScrollBar::SetTexture(char* szfullpath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture= TEXTURE->GetTexture(szfullpath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIScrollBar::Update()
{
	POINT pt = INPUT->GetMousePos();

	D3DXVECTOR3 HeadPos = m_pParent->GetPosition() + m_vPosition;
	D3DXVECTOR3 LanePos = m_pParent->GetPosition() + m_pUIScrollLane->GetPosition();

	ST_SIZEN LaneSize(m_pUIScrollLane->GetSize());

	RECT HeadRect,LaneRect;
	SetRect(&HeadRect, (int)HeadPos.x, (int)HeadPos.y, (int)HeadPos.x + (int)m_stSize.nWidth, (int)HeadPos.y + (int)m_stSize.nHeight);
	SetRect(&LaneRect, (int)LanePos.x, (int)LanePos.y, (int)LanePos.x+ (int)LaneSize.nWidth, (int)LanePos.y+ (int)LaneSize.nHeight);
	
	if (PtInRect(&HeadRect, pt) && INPUT->IsMousePress(MOUSE_LEFT)) 
	{
		m_isSellected = true;
	}
	if (PtInRect(&LaneRect, pt) && INPUT->IsMouseDown(MOUSE_LEFT))
	{
		m_isInRange = true; m_vPosition.y = (pt.y - m_pParent->GetPosition().y);
	}
	if (INPUT->IsMouseUp(MOUSE_LEFT)) { m_isSellected = false; m_isInRange = false; }

	if (m_isSellected)
	{	
		if(!m_pParent->GetIsMove())			m_vPosition.y = (pt.y - m_pParent->GetPosition().y);
		if (m_vPosition.y < LaneRect.top)	m_vPosition.y = LaneRect.top;
		if (m_vPosition.y > LaneRect.bottom)m_vPosition.y = LaneRect.bottom;
	}
}

void cUIScrollBar::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16 matT;
	D3DXVECTOR3 pos = m_pParent->GetPosition() + m_vPosition;

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	pSprite->SetTransform(&matT);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

}

float cUIScrollBar::GetRate()
{
	D3DXVECTOR3 HeadPos = m_pParent->GetPosition() + m_vPosition;
	D3DXVECTOR3 LanePos = m_pParent->GetPosition() + m_pUIScrollLane->GetPosition();
	
	ST_SIZEN LaneSize(m_pUIScrollLane->GetSize());

	float FullSize = LanePos.y + LaneSize.nHeight;

	return HeadPos.y / FullSize;
}
