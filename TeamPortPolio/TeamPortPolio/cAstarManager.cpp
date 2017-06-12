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
	D3DXVECTOR3 colliedPos;
	if (m_graph)
	{
		if (INPUT->IsMouseDown(MOUSE_RIGHT))
		{
			int cellIndex = -1;	// �޽� �浹 ������ �ε����� -1. �ƴ϶�� �ش� �ε��� ���� ����.

			D3DXVECTOR3 posOnMap = D3DXVECTOR3(-1000, -1000, -1000);	//	�����Ⱚ �־�α�. �� ���� �� ���� �ʾ����� �� �����Ⱚ �״�� ����.

			float minX = MAP->GetMinX();	// IsCollidedWithMesh�� ����ó���� ���� ����
			float maxX = MAP->GetMaxX();	// IsCollidedWithMesh�� ����ó���� ���� ����

			cRay::IsCollidedWithMesh(INPUT->GetMousePosVector2(), MAP->GetMesh(), cellIndex, posOnMap, minX, maxX);
			
			cout << cellIndex << endl;
			
			int nodeIndex = (float)cellIndex * 0.5f;

			if (m_graph->GetNode(nodeIndex)->Active() != false) cout << "Active !!" << endl;
			else cout << "Non-Active !!" << endl;
		}
		
	}
}

void cAstarManager::Release()
{
	if(m_graph)SAFE_DELETE(m_graph);
}

void cAstarManager::Render()
{
	m_graph->Render();
}
