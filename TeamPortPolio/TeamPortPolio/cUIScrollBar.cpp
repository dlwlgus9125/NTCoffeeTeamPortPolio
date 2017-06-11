#include "stdafx.h"
#include "cUIScrollBar.h"

cUIScrollBar::cUIScrollBar()
	:m_isSelected(false)
	,m_isInRange(false)
{
}

cUIScrollBar::~cUIScrollBar()
{
}

void cUIScrollBar::SetTexture(char* szLanePath,char* szHeadPath)
{
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture[0]= TEXTURE->GetTexture(szLanePath, &stImageInfo);

	m_stLaneSize.nWidth = stImageInfo.Width;
	m_stLaneSize.nHeight = stImageInfo.Height;

	m_pTexture[1] = TEXTURE->GetTexture(szHeadPath, &stImageInfo);
	
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIScrollBar::Update()
{
	POINT pt = INPUT->GetMousePos();

	D3DXMATRIXA16 matS, matT;
	D3DXVECTOR3 pos = m_pParent->GetPosition() + m_vPosition;;
	
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, m_fScaleX, m_fScaleY, 1);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);
	
	m_Matrix = matS*matT;

	D3DXVECTOR3 HeadPos = m_pParent->GetPosition() + m_vPosition;
	D3DXVECTOR3 LanePos = m_pParent->GetPosition() + m_vLanePos;

	ST_SIZEN LaneSize(GetLaneSize().nWidth*m_fScaleX, GetLaneSize().nHeight*m_fScaleY);
	ST_SIZEN HeadSize(GetSize().nWidth*m_fScaleX, GetSize().nHeight*m_fScaleY);
	RECT HeadRect,LaneRect;
	SetRect(&LaneRect, (int)LanePos.x, (int)LanePos.y, (int)LanePos.x+ (int)LaneSize.nWidth,  (int)LanePos.y+  (int)LaneSize.nHeight);
	SetRect(&HeadRect, (int)HeadPos.x, (int)HeadPos.y, (int)HeadPos.x + (int)HeadSize.nWidth, (int)HeadPos.y + (int)HeadSize.nHeight);
	
	if (PtInRect(&HeadRect, pt) && INPUT->IsMousePress(MOUSE_LEFT)) 
	{
		m_isSelected = true;
	}
	if (PtInRect(&LaneRect, pt) && INPUT->IsMouseDown(MOUSE_LEFT))
	{
		m_isInRange = true; m_vPosition.y = (pt.y - m_pParent->GetPosition().y);
	}
	if (INPUT->IsMouseUp(MOUSE_LEFT)) { m_isSelected = false; m_isInRange = false; }

	if (m_isSelected)
	{	
		if(!m_pParent->GetIsMove())										 m_vPosition.y = (pt.y - m_pParent->GetPosition().y);
		if (m_vPosition.y <	LaneRect.top - m_pParent->GetPosition().y)	 m_vPosition.y = LaneRect.top-m_pParent->GetPosition().y;
		if (m_vPosition.y > LaneRect.bottom - m_pParent->GetPosition().y)m_vPosition.y = LaneRect.bottom-m_pParent->GetPosition().y;
	}
}

void cUIScrollBar::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rcLane, rcHead;

	pSprite->SetTransform(&m_Matrix);
	SetRect(&rcHead, 0, 0, GetSize().nWidth, GetSize().nHeight);
	pSprite->Draw(m_pTexture[1], &rcHead, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMATRIXA16 matS,matT, matW;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXVECTOR3 LanePos = m_pParent->GetPosition() + m_vLanePos;
	D3DXMatrixScaling(&matS, m_fScaleX, m_fScaleY, 1);
	D3DXMatrixTranslation(&matT, LanePos.x, LanePos.y,0);
	
	matW = matS*matT;
	pSprite->SetTransform(&matW);
	SetRect(&rcLane, 0, 0, GetLaneSize().nWidth, GetLaneSize().nHeight);
	pSprite->Draw(m_pTexture[0], &rcLane, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	
	

	pSprite->End();
}

float cUIScrollBar::GetRate()
{
	D3DXVECTOR3 HeadPos = m_pParent->GetPosition() + m_vPosition;
	D3DXVECTOR3 LanePos = m_pParent->GetPosition() + m_vLanePos;

	float FullSize = LanePos.y + GetLaneSize().nHeight;

	return HeadPos.y / FullSize;
}
