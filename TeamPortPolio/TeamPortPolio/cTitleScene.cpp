#include "stdafx.h"
#include "cTitleScene.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"


cTitleScene::cTitleScene() :
	m_pSprite(NULL),
	m_pTexture(NULL)
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	m_pBackgroundImage.SetPosition(0, 0, 0);
	m_pBackgroundImage.SetTexture("Image/TitleScene.png");
}


cTitleScene::~cTitleScene()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pSkyBox);
	for each(auto p in m_vecConstruct)
	{
		SAFE_DELETE(p);
	}
}

void cTitleScene::OnEnter()
{
	MAP->Init("TESTMAP.txt");
	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8,0,30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->Init();
	
	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);
	Setup_DirLight();
}

void cTitleScene::OnUpdate()
{
	
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
	
}

void cTitleScene::OnExit()
{
	SAFE_DELETE(m_pSkyBox);
}

void cTitleScene::OnRender()
{
	MAP->Render();
	OBJECT->Render();
	
}

void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MAP->Render();
}


void cTitleScene::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // 주변에 영향을 받는 것들은 색을 띄게 만듬
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}