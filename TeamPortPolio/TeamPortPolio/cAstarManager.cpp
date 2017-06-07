#include "stdafx.h"
#include "cAstarManager.h"




void cAstarManager::Setup(int col, int row)
{
	m_graph = new cGraph(col*row);

	for (int i = 0; i < col*row; i++)
	{
		m_graph->GetNode(i)->SetActive(true);
		
		D3DXVECTOR3 pos;//<-���⿡ heightmap�����ؼ� ��ǥ�ֱ�
		//�׷����ϸ� ���̰����� �ڽ�Ʈ�� ������ �����ϱ⶧���� ������ �ڿ�������

		m_graph->GetNode(i)->SetPos(pos);
		m_graph->GetNode(i)->SetID(i);

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
	/*if (col >= 0 && col < m_col && row >= 0 && row < m_row)
	{
		int to = col + row * m_col;
		D3DXVECTOR3 fromPos = m_vecGrid[from]->m_pos;//get���� ó���ؼ� �����߰����� �����ϱ�
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
