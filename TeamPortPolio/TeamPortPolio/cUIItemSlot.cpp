#include "stdafx.h"
#include "cUIItemSlot.h"
#include "cItem.h"
#include "cUIScrollBar.h"
cUIItemSlot::cUIItemSlot()
	:m_pbar(NULL)
{
}

cUIItemSlot::~cUIItemSlot()
{
}

void cUIItemSlot::SetTexture()
{
	vector<ITEM_TAG> vecTag;
	char* szFullpath;
	D3DXIMAGE_INFO stImageInfo;
	for (int i = 0; i < vecTag.size(); i++)
	{
		switch (vecTag[i])
		{
		case ITEM_NONE:szFullpath = ""; break;
		case ITEM_MELEE:szFullpath = ""; break;
		case ITEM_RANGE:szFullpath = ""; break;
		}
		m_vecSlot[i].pItemTex = TEXTURE->GetTexture(szFullpath, &stImageInfo);
		m_vecSlot[i].pBackTex = TEXTURE->GetTexture("", &stImageInfo);
	}

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}


void cUIItemSlot::Update()
{
	m_fScrolledRate = m_pbar->GetRate()*m_vecSlot.size();

	
}

void cUIItemSlot::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIXA16 matT;
	D3DXVECTOR3 pos = m_pParent->GetPosition() + m_vPosition;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	pSprite->SetTransform(&matT);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	//pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();
}

