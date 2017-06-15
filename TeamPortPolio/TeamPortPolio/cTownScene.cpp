#include "stdafx.h"
#include "cTownScene.h"
#include "cPlayer.h"


cTownScene::cTownScene()
{
}


cTownScene::~cTownScene()
{
}

void cTownScene::OnEnter()
{
	MAP->Init("TESTTOWN.txt");
	UI->Change(SCENE_TOWN);
	Setup_DirLight();

	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8, 0, 30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->Init();
	OBJECT->AddCharacter(pPlayer);
	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);
}

void cTownScene::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());
	OBJECT->Update(TIME->DeltaTime());
}

void cTownScene::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	UI->Release();
}

void cTownScene::OnRender()
{
	MAP->Render();
	UI->Render(m_pSprite);
	OBJECT->Render();
}

void cTownScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cTownScene::Setup_DirLight()
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
