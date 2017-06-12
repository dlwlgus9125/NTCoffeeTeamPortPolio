#include "stdafx.h"
#include "cHeightMap.h"
#include "cMtlTex.h"
#include "cSkyBox.h"


cHeightMap::cHeightMap() : m_pMesh(NULL)
{
}


cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(m_pMesh);
	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
}

// Load 후에 초기화 해주는 함수
void cHeightMap::Setup(int cellPerRow, float cellSpace, vector<ST_PNT_VERTEX> vecVertex, vector<DWORD> vecIndex)
{
	SetWire(false);

	m_nCellSpace = cellSpace;

	D3DXVECTOR3 startPos = D3DXVECTOR3(cellPerRow * 0.5f * -1, 0.0f, cellPerRow * 0.5f * -1);

	int nNumVertex = pow(cellPerRow + 1, 2);

	int nRow = cellPerRow + 1;
	int nCol = nRow;
	int nTileN = nRow - 1;
	m_nCellPerRow = cellPerRow;

	m_vecVertex = vecVertex;
	m_vecIndex = vecIndex;
}

void cHeightMap::Update()
{

}

bool cHeightMap::GetHeight(IN float x, OUT float&y, IN float z)
{

	return true;
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if(m_drawWired) D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DDevice->SetMaterial(&(m_vecMtlTex[0]->GetMaterial()));
	D3DDevice->SetTexture(0, m_vecMtlTex[0]->GetTexture());
	m_pMesh->DrawSubset(0);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}