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
	MAP->Init("TESTMAP3.txt");
	UI->Change(SCENE_TITLE);
	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8,0,30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
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
	UI->Update(TIME->DeltaTime());

	// >> UI�� �̺�Ʈ ���� 
	int indexInMiniMap;
	int buttonIndex;

	UI->GetEvent(indexInMiniMap, buttonIndex);
	if (indexInMiniMap > 0)
	{
		OBJECT->GetPlayer()->SetUnitLeaderTargetIndex(indexInMiniMap);
		cout << "UI Index : " << indexInMiniMap << endl;
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