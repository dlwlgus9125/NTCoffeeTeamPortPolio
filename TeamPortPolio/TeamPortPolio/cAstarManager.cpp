#include "stdafx.h"
#include "cAstarManager.h"




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

void cAstarManager::Release()
{
	SAFE_DELETE(m_graph);
}

void cAstarManager::Render()
{
	m_graph->Render();
}
