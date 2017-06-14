#include "stdafx.h"
#include "cUITap.h"


cUITap::cUITap() : m_pTexture_Body(NULL)
{
}


cUITap::~cUITap()
{
}

void cUITap::Setup_Tap(string sPath_idle_title, string sPath_selected_title, ST_SIZEN titleSize, string sPath_body, D3DXVECTOR3 pos_body, FONT_TAG eFont)
{
	m_mapTexture_Title[UI_IDLE] = TEXTURE->GetTexture(sPath_idle_title);
	m_mapTexture_Title[UI_SELECTED] = TEXTURE->GetTexture(sPath_selected_title);
	m_stTitleSize = titleSize;

	m_pTexture_Body = TEXTURE->GetTexture(sPath_body);
	m_vPos_Body = pos_body;

	m_eFont = eFont;
}

void cUITap::AddTitle(string title, D3DXVECTOR3 pos_title)
{
	D3DXVECTOR3 translated_pos_title = m_vPosition + pos_title;
	ST_TAB tab = ST_TAB(title, translated_pos_title, UI_IDLE);
}

void cUITap::Update(float deltaTime)
{
	if (m_isHidden) return;

	// >> 탭의 타이틀 클릭 시 모든 탭 타이틀의 상태 바꿔주는 부분ㄴ
	for (int i = 0; i < vecTabInfo.size(); i++)
	{
		D3DXVECTOR2 lt = D3DXVECTOR2(vecTabInfo[i].pos.x, vecTabInfo[i].pos.y);
		D3DXVECTOR2 rb = D3DXVECTOR2(vecTabInfo[i].pos.x + m_stTitleSize.nWidth, vecTabInfo[i].pos.y + m_stTitleSize.nHeight);
		if (MATH->IsCollided(INPUT->GetMousePosVector2(), lt, rb))
		{
			for (int k = 0; k < vecTabInfo.size(); k++)
			{
				if (k == i) vecTabInfo[i].state = UI_SELECTED;
				else vecTabInfo[k].state = UI_IDLE;
			}
			break;
		}
	}
	// <<

	cUIObject::Update(deltaTime);
}

void cUITap::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	for (int i = 0; i < vecTabInfo.size(); i++)
	{
		// >> 타이틀 렌더
		SetRect(&rc, 0, 0, m_stTitleSize.nWidth, m_stTitleSize.nHeight);
		pSprite->Draw(m_mapTexture_Title[vecTabInfo[i].state], &rc, &D3DXVECTOR3(0, 0, 0), &vecTabInfo[i].pos, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		// << 

		// >> 타이틀 글씨 인쇄
		LPD3DXFONT pFont = FONT->GetFont(m_eFont);
		pFont->DrawText(NULL, vecTabInfo[i].text.c_str(), vecTabInfo[i].text.length(), &rc, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
		// << 
	}

	// >> 바디 렌더
	SetRect(&rc, 0, 0, m_stSize.nWidth - m_stTitleSize.nWidth, m_stSize.nHeight - m_stTitleSize.nHeight);
	pSprite->Draw(m_pTexture_Body, &rc, &D3DXVECTOR3(0, 0, 0), &m_vPos_Body, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	// << 

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUITap::Destroy()
{
	SAFE_RELEASE(m_pTexture_Body);
	for each(auto p in m_mapTexture_Title)
	{
		SAFE_RELEASE(p.second);
	}

	delete this;
}
