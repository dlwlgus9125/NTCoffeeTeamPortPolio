#include "stdafx.h"
#include "cUIManager.h"

// 타이틀씬에 대한 UI 설정
void cUIManager::Setup_TitleScene()
{
	/*
	< index 안내 >



	*/

	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(WND_WIDTH * 0.25f, WND_HEIGHT * 0.25f, 0), UI_MINIMAP);
	m_pMiniMap->SetSize(ST_SIZEN(500,500));
	m_pMiniMap->Setup_Image(TEXTURE->GetTexture("image/UI/minimap/testmap.png"), 150);
}

void cUIManager::Setup_TownScene()
{

}

void cUIManager::Setup()
{
	m_pMiniMap = NULL;
}

void cUIManager::Release()
{
	for each(auto p in m_vecImage)
	{
		SAFE_DELETE(p);
	}
	for each(auto p in m_vecText)
	{
		SAFE_DELETE(p);
	}
	
	SAFE_DELETE(m_pMiniMap);
}

void cUIManager::Update(float deltaTime)
{
	PressKey();

	if(m_pMiniMap) m_pMiniMap->Update(deltaTime);
}

void cUIManager::Render(LPD3DXSPRITE pSprite)
{
	if (m_pMiniMap) m_pMiniMap->Render(pSprite);
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
	if (INPUT->IsKeyDown(VK_CONTROL))
	{
		bool isHidden = m_pMiniMap->GetHidden();
		m_pMiniMap->SetHidden(!isHidden);
	}
}

void cUIManager::GetEvent(OUT int& minimapIndex)
{
	minimapIndex = m_pMiniMap->GetIndex();
}