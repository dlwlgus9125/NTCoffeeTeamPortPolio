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
}


cTitleScene::~cTitleScene()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}

void cTitleScene::OnEnter()
{
	MAP->Init("TESTMAP3.txt");
	cPlayer* pPlayer = new cPlayer(ASTAR->GetGraph()->GetNode(16001)->Pos(), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->Init();
	OBJECT->AddCharacter(pPlayer);



	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);


	cLeader* pLeader = new cLeader(ASTAR->GetGraph()->GetNode(11581)->Pos(), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pLeader->Init();
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(11581)->Id());
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);
	Setup_DirLight();
}

void cTitleScene::OnUpdate()
{
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
	
}

void cTitleScene::OnExit()
{
}

void cTitleScene::OnRender()
{
	MAP->Render();
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
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // 주변에 영향을 받는 것들은 색을 띄게 만듬
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}