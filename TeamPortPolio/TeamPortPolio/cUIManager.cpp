#include "stdafx.h"
#include "cUIManager.h"

// 타이틀씬에 대한 UI 설정
void cUIManager::Setup_TitleScene()
{
	/*
	< GetEvent로 반환되는 index 안내 >

	- 버튼 :	0 : pButton1
				1 : pButton2
				2 : pButton3
				3 : pButton4

	*/

	// 미니맵
	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(WND_WIDTH * 0.25f, WND_HEIGHT * 0.10f, 0), UI_MINIMAP);
	m_pMiniMap->SetSize(ST_SIZEN(500,500));
	m_pMiniMap->Setup_Image(TEXTURE->GetTexture("image/UI/titlescene/minimap/testmap.png"), 150);
	m_pMiniMap->SetAlpha(150);

	// 미니맵버튼 1
	cUIButton* pButton1 = new cUIButton;
	pButton1->Setup(D3DXVECTOR3(50, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pButton1->Setup_Button("Image/UI/titlescene/button/formation_rect/idle.png", 
		"Image/UI/titlescene/button/formation_rect/mouseover.png", 
		"Image/UI/titlescene/button/formation_rect/selected.png", TITLE_BTN_FMT_RECT);
	pButton1->SetSize(ST_SIZEN(50, 50));
	m_vecBtn.push_back(pButton1);
	m_pMiniMap->AddChild(pButton1);

	// 미니맵버튼 2
	cUIButton* pButton2 = new cUIButton;
	pButton2->Setup(D3DXVECTOR3(150, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pButton2->Setup_Button("Image/UI/titlescene/button/formation_tri/idle.png",
		"Image/UI/titlescene/button/formation_tri/mouseover.png",
		"Image/UI/titlescene/button/formation_tri/selected.png", TITLE_BTN_FMT_TRI);
	pButton2->SetSize(ST_SIZEN(50, 50));
	m_vecBtn.push_back(pButton2);
	m_pMiniMap->AddChild(pButton2);

	// 미니맵버튼 3
	cUIButton* pButton3 = new cUIButton;
	pButton3->Setup(D3DXVECTOR3(300, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pButton3->Setup_Button("Image/UI/titlescene/button/state_att/idle.png",
		"Image/UI/titlescene/button/state_att/mouseover.png",
		"Image/UI/titlescene/button/state_att/selected.png", TITLE_BTN_ATTSTATE);
	pButton3->SetSize(ST_SIZEN(50, 50));
	m_vecBtn.push_back(pButton3);
	m_pMiniMap->AddChild(pButton3);

	// 미니맵버튼 4
	cUIButton* pButton4 = new cUIButton;
	pButton4->Setup(D3DXVECTOR3(400, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pButton4->Setup_Button("Image/UI/titlescene/button/state_def/idle.png",
		"Image/UI/titlescene/button/state_def/mouseover.png",
		"Image/UI/titlescene/button/state_def/selected.png", TITLE_BTN_DEFSTATE);
	pButton4->SetSize(ST_SIZEN(50, 50));
	m_vecBtn.push_back(pButton4);
	m_pMiniMap->AddChild(pButton4);
}

void cUIManager::Setup_TownScene()
{
	cUITab* pTab_Weapon = new cUITab();
	pTab_Weapon->Setup(D3DXVECTOR3(0, 0, 0), UI_TAB);
	pTab_Weapon->Setup_Tap("image/rect/darkgray.png", "image/rect/gray.png", ST_SIZEN(150, 50), "image/rect/gray.png", D3DXVECTOR3(0, 0, 0), ST_SIZEN(400, 600));
	pTab_Weapon->AddTitle("검", D3DXVECTOR3(0, 600, 0));
	pTab_Weapon->AddTitle("도끼", D3DXVECTOR3(170, 600, 0));
	m_vecTab.push_back(pTab_Weapon);
}

void cUIManager::Setup()
{
	m_pMiniMap = NULL;
}

void cUIManager::Release()
{
	for each(auto p in m_vecImage)
	{
		p->Destroy();
	}
	for each(auto p in m_vecText)
	{
		p->Destroy();
	}
	for each(auto p in m_vecBtn)
	{
		p->Destroy();
	}	
	for each(auto p in m_vecTab)
	{
		p->Destroy();
	}
	
	SAFE_DELETE(m_pMiniMap);
}

void cUIManager::Update(float deltaTime)
{
	PressKey();

	if(m_pMiniMap) m_pMiniMap->Update(deltaTime);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Update(deltaTime);
	}
}

void cUIManager::Render(LPD3DXSPRITE pSprite)
{
	if (m_pMiniMap) m_pMiniMap->Render(pSprite);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Render(pSprite);
	}
}

// 씬 변경에 따른 UI 전체 변경시키는 함수
void cUIManager::Change(int sceneID)
{
	Release();

	switch (sceneID)
	{
	case SCENE_TITLE:
		Setup_TitleScene();
		break;
	case SCENE_TOWN:
		Setup_TownScene();
		break;
	}
}

void cUIManager::PressKey()
{
	if (INPUT->IsKeyDown(VK_CONTROL) && m_pMiniMap) m_pMiniMap->SetHiddenAll(!(m_pMiniMap->GetHidden()));
}

void cUIManager::SetEvent(int order)
{
	switch (order)
	{
	case 0:
		m_vecTab[0]->SetHidden(false);
		break;
	}

}

void cUIManager::GetEvent(OUT int& minimapIndex, OUT int& buttonIndex)
{
	// 미니맵 우클릭 시 노드의 인덱스 반환해주는 부분
	minimapIndex = m_pMiniMap->GetIndex();

	// 버튼 중 클릭된 녀석의 인덱스 반환해주는 함수
	buttonIndex = -1;
	for (int i = 0; i < m_vecBtn.size(); i++)
	{
		if (m_vecBtn[i]->GetCurrentState() == UI_CLICKED)
		{
			buttonIndex = m_vecBtn[i]->GetEventID();
			break;
		}		
	}
}