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
		m_graph->GetNode(i)->SetActive(false);

		D3DXVECTOR3 pos;//<-���⿡ heightmap�����ؼ� ��ǥ�ֱ�
		//�׷����ϸ� ���̰����� �ڽ�Ʈ�� ������ �����ϱ⶧���� ������ �ڿ�������

		m_graph->GetNode(i)->SetPos(vecPosOfNode[i]);
		int index = 0;
		MAP->GetMap()->GetIndex(vecPosOfNode[i].x, vecPosOfNode[i].z, index);
		m_graph->GetNode(i)->SetID(index);
	}
	for (int i = 0; i < vecPosOfNode.size(); i++)
	{
		if (vecPosOfNode[i].y == 0.0f || vecPosOfNode[i].y == 1.0f || vecPosOfNode[i].y == 2.0f || vecPosOfNode[i].y == 3.0f || vecPosOfNode[i].y == 4.0f)
		{
			m_graph->GetNode(i)->SetActive(true);
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

	m_isMapLoadingComplete = true;
}

void cAstarManager::AddEdge(int from, int col, int row)
{
	if (col >= 0 && col < 150 && row >= 0 && row < 150)
		//if (col >= 0 && col < 15 && row >= 0 && row < 15)
	{
		int to = col + row * 150;
		D3DXVECTOR3 fromPos = m_graph->GetNode(from)->Pos();//get���� ó���ؼ� �����߰����� �����ϱ�
		D3DXVECTOR3 toPos = m_graph->GetNode(to)->Pos();

		if (abs(fromPos.y - toPos.y) <= 1.0f&&m_graph->GetNode(from)->Active() == true && m_graph->GetNode(to)->Active() == true)
		{
			D3DXVECTOR3 length = toPos - fromPos;

			m_graph->AddEdge(from, to, sqrt(pow(length.x, 2) + pow(length.z, 2)));
		}
	}
}

vector<int> cAstarManager::GetPath(int chrindex, int targetIndex)
{
	if (chrindex != targetIndex)
	{
		cAstar as(m_graph, chrindex, targetIndex);
		if (as.Search())
		{
			return as.GetPath();
			//m_path = as.GetRoute();
		}
	}
	return vector<int>();
}

void cAstarManager::Update()
{
	if (m_isMapLoadingComplete == true)
	{
		SetObjectIndex();
		SetLeaderPath();
		SetTargetOfLeader();
	}
}

void cAstarManager::Release()
{
	m_isMapLoadingComplete = false;
	if (m_graph)SAFE_DELETE(m_graph);

}

void cAstarManager::Render()
{
	m_graph->Render();
}

bool cAstarManager::GetCursorIndex(int & TargetIndex)
{
	if (m_graph)
	{
		int cellIndex = -1;	// �޽� �浹 ������ �ε����� -1. �ƴ϶�� �ش� �ε��� ���� ����.

		D3DXVECTOR3 posOnMap = D3DXVECTOR3(-1000, -1000, -1000);	//	�����Ⱚ �־�α�. �� ���� �� ���� �ʾ����� �� �����Ⱚ �״�� ����.

		float minX = MAP->GetMinX();	// IsCollidedWithMesh�� ����ó���� ���� ����
		float maxX = MAP->GetMaxX();	// IsCollidedWithMesh�� ����ó���� ���� ����

		cRay::IsCollidedWithMesh(INPUT->GetMousePosVector2(), MAP->GetMesh(), cellIndex, posOnMap, minX, maxX);
		//cout << "posOnMap.x : " << posOnMap.x << "posOnMap.z : " << posOnMap.z<< endl;
		if (cellIndex != -1 && m_graph->GetNode(cellIndex)->Active() != false) { cout << "Active !! cellindex : " << cellIndex << endl; TargetIndex = cellIndex; return true; }
		else { cout << "Non-Active !!" << endl; return false; }

	}
	return false;
}

void cAstarManager::SetObjectIndex()
{
	for (int i = 0; i < OBJECT->GetCharacter().size(); i++)
	{
		D3DXVECTOR3 pos = OBJECT->GetCharacter()[i]->GetCharacterEntity()->Pos();
		int index = 0;
		MAP->GetMap()->GetIndex(pos.x, pos.z, index);
		if (OBJECT->GetCharacter()[i]->GetIndex() != index)OBJECT->GetCharacter()[i]->SetIndex(index);
	}
	for (int i = 0; i < OBJECT->GetLeader().size(); i++)
	{
		D3DXVECTOR3 pos = OBJECT->GetLeader()[i]->GetCharacterEntity()->Pos();
		int index = 0;
		MAP->GetMap()->GetIndex(pos.x, pos.z, index);
		if (OBJECT->GetLeader()[i]->GetIndex() != index)OBJECT->GetLeader()[i]->SetIndex(index);
	}
}

void cAstarManager::SetLeaderPath()
{
	for (int i = 0; i < OBJECT->GetLeader().size(); i++)
	{
		if (OBJECT->GetLeader()[i]->GetPath().size()<=0&&OBJECT->GetLeader()[i]->GetIndex() != OBJECT->GetLeader()[i]->GetTargetIndex())
		{

		//	cout << "current : " << OBJECT->GetLeader()[i]->GetIndex() << "target : " << OBJECT->GetLeader()[i]->GetTargetIndex() << endl;
			OBJECT->GetLeader()[i]->SetPath(this->GetPath(OBJECT->GetLeader()[i]->GetIndex(), OBJECT->GetLeader()[i]->GetTargetIndex()));
			//m_path = as.GetRoute();
			//cout << "size : " << OBJECT->GetLeader()[i]->GetPath().size() << endl;
		}
	}
}


void cAstarManager::SetTargetOfLeader()
{
	for (int thisLeader = 0; thisLeader < OBJECT->GetLeader().size(); thisLeader++)
	{
		for (int anotherLeader = 0; anotherLeader < OBJECT->GetLeader().size(); anotherLeader++)
		{
			if (OBJECT->GetLeader()[thisLeader]->GetCamp() != OBJECT->GetLeader()[anotherLeader]->GetCamp())
			{
				if (MATH->IsCollided(OBJECT->GetLeader()[thisLeader]->GetArrangeSphere(), OBJECT->GetLeader()[anotherLeader]->GetArrangeSphere()))
				{
					if (OBJECT->GetLeader()[thisLeader]->GetTargetObject() != OBJECT->GetLeader()[anotherLeader])
						OBJECT->GetLeader()[thisLeader]->SetTargetObject(OBJECT->GetLeader()[anotherLeader]);
				}
			}
		}
	}
}
