#pragma once
#include "cIMap.h"

class cMtlTex;

class cHeightMap :
	public cIMap
{
	SYNTHESIZE(LPD3DXMESH,	m_pMesh, Mesh);
	SYNTHESIZE(vector<ST_PNT_VERTEX>, m_vecVertex, VecVertex);
	SYNTHESIZE(vector<cMtlTex*>	,	m_vecMtlTex, VecMtlTex);
	SYNTHESIZE(vector<DWORD>, m_vecIndex, VecIndex);

	SYNTHESIZE(float, m_nCellSpace, CellSpace);
	SYNTHESIZE(int	, m_nCellPerRow, CellPerRow);
	
public:
	cHeightMap();
	~cHeightMap();

	void Setup(int cellPerRow, float cellSpace, vector<ST_PNT_VERTEX> vecVertex, vector<DWORD> vecIndex);
	virtual void Update();
	virtual bool GetHeight(IN float x, OUT float&y, IN float z) override;
	virtual void Render() override;
};

