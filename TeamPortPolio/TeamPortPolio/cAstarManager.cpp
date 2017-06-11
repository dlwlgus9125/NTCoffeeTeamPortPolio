#include "stdafx.h"
#include "cAstarManager.h"
#include "cRay.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"


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

void cAstarManager::Update()
{
	D3DXVECTOR3 colliedPos;

	/*if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		for (int i = 0; i < m_graph->NodeCount(); i++)
		{
			if (m_graph->GetNode(i)->Active() != false)
			{
				if (cRay::RaySphereIntersect(INPUT->GetMousePosVector2(), m_graph->GetNode(i)->GetMesh(), m_graph->GetNode(0)->Pos().x, m_graph->GetNode(149)->Pos().x))
				{
					cout << "index : " << i << endl;
					break;
				}

			}
		}
	}*/
	for (int i = 0; i < ASTAR->GetGraph()->NodeCount(); i++)
	{
		if ((OBJECT->GetPlayer()->GetCharacterEntity()->Pos().x - 2.0f < ASTAR->GetGraph()->GetNode(i)->Pos().x&&ASTAR->GetGraph()->GetNode(i)->Pos().x < OBJECT->GetPlayer()->GetCharacterEntity()->Pos().x + 2.0f)
			&& (OBJECT->GetPlayer()->GetCharacterEntity()->Pos().z - 2.0f < ASTAR->GetGraph()->GetNode(i)->Pos().z&&ASTAR->GetGraph()->GetNode(i)->Pos().z < OBJECT->GetPlayer()->GetCharacterEntity()->Pos().z + 2.0f))
		{
			if (ASTAR->GetGraph()->GetNode(i)->Active() == true && MATH->IsCollided(OBJECT->GetPlayer()->GetMeshSphere(), ASTAR->GetGraph()->GetNode(i)->GetMesh()))
			{
				int prevIndex = OBJECT->GetPlayer()->GetUnitLeader()->GetIndex();
				OBJECT->GetPlayer()->GetUnitLeader()->SetIndex(ASTAR->GetGraph()->GetNode(i)->Id());
				int currentIndex = OBJECT->GetPlayer()->GetUnitLeader()->GetIndex();
				//if (currentIndex != prevIndex)cout << "index : " << OBJECT->GetPlayer()->GetUnitLeader()->GetIndex() << endl;
			}
		}
	}
}

void cAstarManager::Release()
{
	SAFE_DELETE(m_graph);
}

void cAstarManager::Render()
{
	m_graph->Render();
}
