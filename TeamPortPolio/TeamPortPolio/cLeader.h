#pragma once
#include "cCharacter.h"
#include "cUnit.h"

class cLeader :
	public cCharacter
{
	cStateMachine<cLeader*>* m_pFsm;
	ISteeringEntity*  m_unitLeader;//�δ��̵��� ����� �������
	vector<cUnit*> m_vectorUnit;
	vector<D3DXVECTOR3> m_RectOffest;
	vector<D3DXVECTOR3> m_TriOffest;
	float          m_fRotY;
	

public:
	cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cLeader();

	void Init();
	void Update(float deltaTime);
	void Render();
	void AddUnit(cUnit* pUnit);//�δ� �߰�
	void DeleteUnit(int key);

	void SetRectOffset();
	void SetTriOffset();


	//Scene���� �δ� �̵��� ������ ���Լ�
	IEntity*       GetUnitLeader() { return m_unitLeader; }
	vector<cUnit*> GetUnits() { return m_vectorUnit; }

	int              GetIndex() { return m_currentIndex; }
	void             SetIndex(int i) { m_currentIndex = i; }
};

