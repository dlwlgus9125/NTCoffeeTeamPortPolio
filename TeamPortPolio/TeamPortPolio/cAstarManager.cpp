#include "stdafx.h"
#include "cAstarManager.h"




void cAstarManager::Setup(vector<D3DXVECTOR3> vecPosOfNode)
{
	m_graph = new cGraph(vecPosOfNode.size());
	int col = sqrt(vecPosOfNode.size());
	for (int i = 0; i < vecPosOfNode.size(); i++)
	{
		m_graph->GetNode(i)->SetActive(true);
		
		D3DXVECTOR3 pos;//<-여기에 heightmap연산해서 좌표넣기
		//그렇게하면 높이값까지 코스트로 적용이 가능하기때문에 오히려 자연스러움

		m_graph->GetNode(i)->SetPos(vecPosOfNode[i]);
		m_graph->GetNode(i)->SetID(i);	
	}
	for (int i = 0; i < vecPosOfNode.size(); i++)
	{
		if (vecPosOfNode[i].y > 4.1f)
		{
			m_graph->GetNode(i)->SetActive(false);
		}
	}
	for (int i = 0; i < vecPosOfNode.size(); i++)
	{
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
	if (col >= 0 && col < 150 && row >= 0 && row < 150)
	{
		int to = col + row * 150;
		D3DXVECTOR3 fromPos = m_graph->GetNode(from)->Pos();//get노드로 처리해서 엣지추가여부 결정하기
		D3DXVECTOR3 toPos = m_graph->GetNode(to)->Pos();

		if (abs(fromPos.y - toPos.y) <= 0.5f&&m_graph->GetNode(from)->Active() == true && m_graph->GetNode(to)->Active() == true)
		{
			D3DXVECTOR3 length = toPos - fromPos;

			m_graph->AddEdge(from, to, sqrt(pow(length.x, 2) + pow(length.z, 2)));
		}
	}
}

vector<int> cAstarManager::GetPath(int chrindex, int targetIndex)
{
	return vector<int>();
}

void cAstarManager::Release()
{
	SAFE_DELETE(m_graph);
}

void cAstarManager::Render()
{
	m_graph->Render();
}
