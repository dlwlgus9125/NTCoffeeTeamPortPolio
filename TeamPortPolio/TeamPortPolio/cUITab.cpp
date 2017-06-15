#include "stdafx.h"
#include "cUITab.h"


cUITab::cUITab() : m_pTexture_Body(NULL)
{
}


cUITab::~cUITab()
{
}

void cUITab::Setup_Tap(string sPath_idle_title, string sPath_selected_title, ST_SIZEN titleSize, string sPath_body, D3DXVECTOR3 pos_body, ST_SIZEN bodySize, FONT_TAG eFont)
{
	m_mapTexture_Title[UI_IDLE] = TEXTURE->GetTexture(sPath_idle_title);
	m_mapTexture_Title[UI_SELECTED] = TEXTURE->GetTexture(sPath_selected_title);
	m_stTitleSize = titleSize;

	m_pTexture_Body = TEXTURE->GetTexture(sPath_body);
	m_vPos_Body = pos_body;
	m_stBodySize = bodySize;

	m_eFont = eFont;
}

void cUITab::AddTitle(string title, D3DXVECTOR3 pos_title)
{
	D3DXVECTOR3 translated_pos_title = m_vPosition + pos_title;
	ST_TAB tab = ST_TAB(title, translated_pos_title, UI_IDLE);
	m_vecTabInfo.push_back(tab);
}

void cUITab::Update(float deltaTime)
{
	if (m_isHidden) return;

	// >> �� ���� ��, ù��° �޴��� ���̵���
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		if (m_vecTabInfo[i].state == UI_SELECTED) break;
		if (i == m_vecTabInfo.size() - 1) m_vecTabInfo[0].state = UI_SELECTED;
	}
	// << 
	// >> ���� Ÿ��Ʋ Ŭ�� �� ��� �� Ÿ��Ʋ�� ���� �ٲ��ִ� �κ�
	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		for (int i = 0; i < m_vecTabInfo.size(); i++)
		{
			D3DXVECTOR2 lt = D3DXVECTOR2(m_vecTabInfo[i].pos.x, m_vecTabInfo[i].pos.y);
			D3DXVECTOR2 rb = D3DXVECTOR2(m_vecTabInfo[i].pos.x + m_stTitleSize.nWidth, m_vecTabInfo[i].pos.y + m_stTitleSize.nHeight);
			if (MATH->IsCollided(INPUT->GetMousePosVector2(), lt, rb))
			{
				for (int k = 0; k < m_vecTabInfo.size(); k++)
				{
					if (k == i) m_vecTabInfo[i].state = UI_SELECTED;
					else m_vecTabInfo[k].state = UI_IDLE;
				}
				break;
			}
		}
	}	
	// <<

	cUIObject::Update(deltaTime);
}

void cUITab::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	// >> Ÿ��Ʋ ����
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		SetRect(&rc, 0, 0, m_stTitleSize.nWidth, m_stTitleSize.nHeight);
		pSprite->Draw(m_mapTexture_Title[m_vecTabInfo[i].state], &rc, &D3DXVECTOR3(0, 0, 0), &m_vecTabInfo[i].pos, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	}
	// << 

	// >> �ٵ� ����
	pSprite->SetTransform(&m_matWorld);
	SetRect(&rc, 0, 0, m_stBodySize.nWidth, m_stBodySize.nHeight);
	pSprite->Draw(m_pTexture_Body, &rc, &D3DXVECTOR3(0, 0, 0), &m_vPos_Body, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	// << 

	pSprite->End();

	// >> Ÿ��Ʋ �۾� �μ�
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		LPD3DXFONT pFont = FONT->GetFont(m_eFont);
		SetRect(&rc, m_vecTabInfo[i].pos.x, m_vecTabInfo[i].pos.y, m_vecTabInfo[i].pos.x + m_stTitleSize.nWidth, m_vecTabInfo[i].pos.y + m_stTitleSize.nHeight);
		pFont->DrawText(NULL, m_vecTabInfo[i].text.c_str(), m_vecTabInfo[i].text.length(), &rc, DT_CENTER | DT_VCENTER, 
			m_vecTabInfo[i].state == UI_IDLE ? D3DCOLOR_XRGB(255, 255, 255) : D3DCOLOR_XRGB(255, 255, 0));
	}
	// << 

	cUIObject::Render(pSprite);
}

void cUITab::Destroy()
{
	SAFE_RELEASE(m_pTexture_Body);
	for each(auto p in m_mapTexture_Title)
	{
		SAFE_RELEASE(p.second);
	}

	delete this;
}
