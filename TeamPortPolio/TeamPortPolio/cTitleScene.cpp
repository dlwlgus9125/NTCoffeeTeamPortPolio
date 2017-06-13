#include "stdafx.h"
#include "cTitleScene.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"


cTitleScene::cTitleScene() :
	m_pSprite(NULL)
{	
}


cTitleScene::~cTitleScene()
{
	SAFE_RELEASE(m_pSprite);
}

void cTitleScene::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init("TESTMAP.txt");
	UI->Change(SCENE_TITLE);
	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8,0,30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->Init();
	
	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);
	Setup_DirLight();
}

void cTitleScene::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());

	// >> UI�� �̺�Ʈ ���� 
	int indexInMiniMap;
	UI->GetEvent(indexInMiniMap);
	if (indexInMiniMap > 0)
	{
		int a = 0;

	}
	// <<

	OBJECT->Update(TIME->DeltaTime());	
}

void cTitleScene::OnExit()
{
	SAFE_RELEASE(m_pSprite);
}

void cTitleScene::OnRender()
{
	MAP->Render();
	UI->Render(m_pSprite);
	OBJECT->Render();
	
}

void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}


void cTitleScene::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // �ֺ��� ������ �޴� �͵��� ���� ��� ����
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}