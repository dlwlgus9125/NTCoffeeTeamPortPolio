#pragma once
#include "Singleton.h"
#include "cGraph.h"
#include "cAstar.h"

#define ASTAR cAstarManager::Instance()


class cAstarManager :
	public Singleton<cAstarManager>
{
	cGraph*            m_graph;
	vector<int> m_path;
	vector<int> vecRoad;
public:
	void Setup(vector<D3DXVECTOR3> vecPosOfNode);
	void AddEdge(int from, int col, int row);
	vector<int> GetPath(int chrindex, int targetIndex);
	void Release();

	void Render();
};

