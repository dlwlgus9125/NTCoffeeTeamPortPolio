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
	if (x < 0.0f || z < 0.0f || x >= m_nCellPerRow || z >= m_nCellPerRow)
	{
		y = 0;
		return false;
	}

	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	int _0 = (nZ + 0) * (m_nCellPerRow + 1) + nX + 0;
	int _1 = (nZ + 1) * (m_nCellPerRow + 1) + nX + 0;
	int _2 = (nZ + 1) * (m_nCellPerRow + 1) + nX + 1;
	int _3 = (nZ + 0) * (m_nCellPerRow + 1) + nX + 1;

	if (fDeltaX + fDeltaZ < 1.0f)
	{
		D3DXVECTOR3   v10 = m_vecVertex[_0].p - m_vecVertex[_1].p;
		D3DXVECTOR3   v21 = m_vecVertex[_2].p - m_vecVertex[_1].p;
		y = m_vecVertex[_1].p.y + (v10 * fDeltaZ + v21 * fDeltaX).y;         // 좌 하단
	}
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3   v23 = m_vecVertex[_3].p - m_vecVertex[_2].p;
		D3DXVECTOR3   v03 = m_vecVertex[_3].p - m_vecVertex[_0].p;

		y = m_vecVertex[_3].p.y + (v23 * fDeltaZ + v03 * fDeltaX).y;
		return true;
	}

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