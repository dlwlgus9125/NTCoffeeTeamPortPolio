#include "stdafx.h"
#include "cMainTitleScene.h"
#include "cObjectManager.h"
#include "cPlayer.h"

cMainTitleScene::cMainTitleScene()
{
}


cMainTitleScene::~cMainTitleScene()
{
}

void cMainTitleScene::OnEnter()
{
	MAP->Init("TESTMAP.txt");
	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8, 0, 30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->Init();

	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);
}

void cMainTitleScene::OnUpdate()
{
	OBJECT->GetPlayer()->Update(TIME->DeltaTime());
	MAP->Update();
}

void cMainTitleScene::OnExit()
{
	MAP->Destroy();
}

void cMainTitleScene::OnRender()
{
	MAP->Render();
	OBJECT->GetPlayer()->Render();
}

void cMainTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
