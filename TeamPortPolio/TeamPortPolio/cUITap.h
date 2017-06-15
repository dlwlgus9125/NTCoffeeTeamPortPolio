#pragma once
#include "cUIObject.h"
class cUITap :
	public cUIObject
{
	vector<ST_TAB>	vecTabInfo;
	ST_SIZEN m_stTitleSize;
	D3DXVECTOR3 m_vPos_Body;
	map<int, LPDIRECT3DTEXTURE9> m_mapTexture_Title;
	LPDIRECT3DTEXTURE9 m_pTexture_Body;
	FONT_TAG m_eFont;
public:
	cUITap();
	~cUITap();

	void Setup_Tap(string sPath_idle_title, string sPath_selected_title, ST_SIZEN titleSize, string sPath_body, D3DXVECTOR3 pos_body, FONT_TAG eFont = FONT_DEF);
	void AddTitle(string title, D3DXVECTOR3 pos_title);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
};

