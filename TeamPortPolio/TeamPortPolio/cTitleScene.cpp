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
