#include "stdafx.h"
#include "cUIItemSlot.h"
#include "cItem.h"
#include "cUIScrollBar.h"
cUIItemSlot::cUIItemSlot()
	:m_pbar(NULL)
{
	for (int i = 0; i < sizeof(ItemSlot); i++)
	{
		m_stItemSlot[i].pItem = new cItem;
		m_stItemSlot[i].pItem->SetItemTag(ITEM_NONE);
	}
}

cUIItemSlot::~cUIItemSlot()
{
	for (int i = 0; i < sizeof(ItemSlot); i++)
	{
		m_stItemSlot[i].pItem->SetItemTag(ITEM_NONE);
		SAFE_DELETE(m_stItemSlot[i].pItem);
	}
}

void cUIItemSlot::SetTexture()
{
	D3DXIMAGE_INFO stImageInfo;
	for (int i = 0; i < 10; i++)
	{
		m_stItemSlot[i].pBackTex= TEXTURE->GetTexture("UI/black.png", &stImageInfo);
		m_stItemSlot[i].pItemTex= TEXTURE->GetTexture("UI/yellow.png", &stImageInfo);
	}
	m_aTexture[0] = TEXTURE->GetTexture("UI/sky.png", &stImageInfo);
	m_aTexture[1] = TEXTURE->GetTexture("UI/darkgray.png", &stImageInfo);
	m_aTexture[2] = TEXTURE->GetTexture("UI/gray.png", &stImageInfo);


	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}


void cUIItemSlot::Update()
{
	m_nScrolledIndex = (m_pbar->GetRate() * 10)-3;
	if (m_nScrolledIndex < 0)m_nScrolledIndex = 0;
	if (m_nScrolledIndex > 7)m_nScrolledIndex = 7;
	
	for (int i = 0; i < sizeof(m_stItemSlot); i++)
	{
		switch (m_stItemSlot[i].pItem->GetItemTag())
		{
		case ITEM_NONE:	m_stItemSlot[i].pItemTex = m_aTexture[0]; break;
		case ITEM_MELEE:m_stItemSlot[i].pItemTex = m_aTexture[1]; break;
		case ITEM_RANGE:m_stItemSlot[i].pItemTex = m_aTexture[2]; break;
		}
	}

	D3DXMATRIXA16 matS, matT;
	D3DXVECTOR3 pos = m_pParent->GetPosition() + m_vPosition;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, m_fScaleX, m_fScaleY, 1);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	m_Matrix = matS*matT;

}

void cUIItemSlot::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_Matrix);
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, 3*m_stSize.nHeight);
	
	pSprite->Draw(m_stItemSlot[m_nScrolledIndex].pBackTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	pSprite->Draw(m_stItemSlot[m_nScrolledIndex +1].pBackTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, m_stSize.nHeight, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	pSprite->Draw(m_stItemSlot[m_nScrolledIndex +2].pBackTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, m_stSize.nHeight+ m_stSize.nHeight, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->Draw(m_stItemSlot[m_nScrolledIndex].pItemTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	pSprite->Draw(m_stItemSlot[m_nScrolledIndex + 1].pItemTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, m_stSize.nHeight, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	pSprite->Draw(m_stItemSlot[m_nScrolledIndex + 2].pItemTex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, m_stSize.nHeight + m_stSize.nHeight, 0), D3DCOLOR_ARGB(255, 255, 255, 255));


	pSprite->End();
}

