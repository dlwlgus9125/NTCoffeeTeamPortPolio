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

	SYNTHESIZE(float, m_fCellSpace, CellSpace);
	SYNTHESIZE(int	, m_nCellPerRow, CellPerRow);
	int m_nVertPerRow;

	float m_fMinX;
	float m_fMaxX;
	float m_fMaxZ;
	float m_fMinZ;
	
public:
	cHeightMap();
	~cHeightMap();

	void Setup(int cellPerRow, float cellSpace, vector<ST_PNT_VERTEX> vecVertex, vector<DWORD> vecIndex);
	virtual void Update();
	virtual bool GetHeight(IN float x, OUT float&y, IN float z) override;
	bool GetIndex(IN float x, IN float z, OUT int& index);
	virtual void Render() override;
};

