#include "stdafx.h"
#include "cTownScene.h"


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

	//cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8, 0, 30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	//pPlayer->Init();
	//OBJECT->AddCharacter(pPlayer);
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
}

void cTownScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
