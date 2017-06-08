#include "stdafx.h"
#include "cTitleScene.h"

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
	// >> 맵 로드
	char* folderPath = "map";
	string temp = "TESTMAP.txt";
	char* filePath = strdup(temp.c_str());

	m_pMap = new cHeightMap();
	cObjLoader loader;
	vector<cMtlTex*> vecMtlTex;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD> vecIndex;
	int nCellPerRow = 0;
	float fCellSpace = 0.0f;
	LPD3DXMESH pMesh = loader.LoadMesh_Map(vecMtlTex, vecVertex, vecIndex, nCellPerRow, fCellSpace, m_vecConstruct, folderPath, filePath, false);
	m_pMap->Setup(nCellPerRow, fCellSpace, vecVertex, vecIndex);
	m_pMap->SetMesh(pMesh);
	m_pMap->SetVecMtlTex(vecMtlTex);
	// << 

	// >> 노드에 쓸 노드 중점의 위치 만드는 부분
	vector<D3DXVECTOR3> vecPosOfNode;
	for (int i = 0; i < vecIndex.size(); i += 6)
	{
		D3DXVECTOR3 v0 = vecVertex[vecIndex[i + 0]].p;
		D3DXVECTOR3 v1 = vecVertex[vecIndex[i + 1]].p;
		D3DXVECTOR3 v2 = vecVertex[vecIndex[i + 2]].p;
		D3DXVECTOR3 v5 = vecVertex[vecIndex[i + 5]].p;

		D3DXVECTOR3 pos;
		pos.x = (v0.x + v1.x + v2.x + v5.x) / 4;
		pos.y = (v0.y + v1.y + v2.y + v5.y) / 4;
		pos.z = (v0.z + v1.z + v2.z + v5.z) / 4;

		vecPosOfNode.push_back(pos);
	}
	// << 

	// >> 스카이박스 생성
	m_pSkyBox = new cSkyBox();
	m_pSkyBox->Setup(nCellPerRow / 2, nCellPerRow / 2, nCellPerRow / 2);
	// << 
}

void cTitleScene::OnUpdate()
{
	if (m_pSkyBox) m_pSkyBox->Update(CAMERA->GetCamera());
}

void cTitleScene::OnExit()
{
	SAFE_DELETE(m_pSkyBox);
}

void cTitleScene::OnRender()
{
	D3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	D3DDevice->BeginScene();

	if (m_pSkyBox) m_pSkyBox->Render();

	if (m_pMap) m_pMap->Render();

	for (int i = 0; i < m_vecConstruct.size(); i++)
	{
		m_vecConstruct[i]->Render();
	}

	D3DDevice->EndScene();

	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
