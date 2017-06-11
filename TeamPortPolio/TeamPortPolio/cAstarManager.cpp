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

		D3DXVECTOR3 pos;//<-���⿡ heightmap�����ؼ� ��ǥ�ֱ�
		//�׷����ϸ� ���̰����� �ڽ�Ʈ�� ������ �����ϱ⶧���� ������ �ڿ�������

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
		int x = i % col;	// �� ��ȣ
		int z = i / col;	// �� ��ȣ	

		AddEdge(i, x - 1, z + 0);//�ش� ������ ���鶧 ���̿����� �����߰����� ����
		AddEdge(i, x + 1, z + 0);
		AddEdge(i, x + 0, z - 1);//������ �ϴ� ��� �������� ���� ������
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
		D3DXVECTOR3 fromPos = m_graph->GetNode(from)->Pos();//get���� ó���ؼ� �����߰����� �����ϱ�
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
