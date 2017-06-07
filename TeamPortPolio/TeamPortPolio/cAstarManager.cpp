#include "stdafx.h"
#include "cAstarManager.h"




void cAstarManager::Setup(int col, int row)
{
	m_graph = new cGraph(col*row);

	for (int i = 0; i < col*row; i++)
	{
		m_graph->GetNode(i)->SetActive(true);
		
		D3DXVECTOR3 pos;//<-여기에 heightmap연산해서 좌표넣기
		//그렇게하면 높이값까지 코스트로 적용이 가능하기때문에 오히려 자연스러움

		m_graph->GetNode(i)->SetPos(pos);
		m_graph->GetNode(i)->SetID(i);

		int x = i % col;	// 열 번호
		int z = i / col;	// 줄 번호		

		AddEdge(i, x - 1, z + 0);//해당 엣지를 만들때 높이에따라서 엣지추가여부 연산
		AddEdge(i, x + 1, z + 0);
		AddEdge(i, x + 0, z - 1);//엣지는 일단 노드 포지션을 전부 맞춘후
		AddEdge(i, x + 0, z + 1);
		AddEdge(i, x - 1, z - 1);
		AddEdge(i, x - 1, z + 1);
		AddEdge(i, x + 1, z - 1);
		AddEdge(i, x + 1, z + 1);
	}
}

void cAstarManager::AddEdge(int from, int col, int row)
{
	/*if (col >= 0 && col < m_col && row >= 0 && row < m_row)
	{
		int to = col + row * m_col;
		D3DXVECTOR3 fromPos = m_vecGrid[from]->m_pos;//get노드로 처리해서 엣지추가여부 결정하기
		D3DXVECTOR3 toPos = m_vecGrid[to]->m_pos;

		D3DXVECTOR3 length = toPos - fromPos;

		if (m_vecGrid[to])m_graph->AddEdge(from, to, sqrt(pow(length.x, 2) + pow(length.z, 2)));
	}*/
}

vector<int> cAstarManager::GetPath(int chrindex, int targetIndex)
{
	return vector<int>();
}

void cAstarManager::Release()
{
	SAFE_DELETE(m_graph);
}
