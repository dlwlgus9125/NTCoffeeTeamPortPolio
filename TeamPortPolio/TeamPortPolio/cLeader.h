#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "Leader_State.h"

enum LEADER_STATE
{
	LEADER_STATE_STATE_IDLE,
	LEADER_STATE_STATE_WALK,
	LEADER_STATE_STATE_ATTACK,
	LEADER_STATE_STATE_DEFENCE,
};

class cLeader :
	public cCharacter
{
	cStateMachine<cLeader*>* m_pFsm;
	ISteeringEntity*  m_unitLeader;//부대이동을 담당할 멤버변수
	vector<cUnit*> m_vectorUnit;
	vector<D3DXVECTOR3> m_RectOffest;
	vector<D3DXVECTOR3> m_TriOffest;
	float          m_fRotY;
	int            m_targetIndex;
	vector<int>    m_path;
	MeshSpere      m_meshSphere;
public:
	cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cLeader();

	void Init();
	void Update(float deltaTime);
	void Render();
	void AddUnit(cUnit* pUnit);//부대 추가
	void DeleteUnit(int key);

	void SetRectOffset();
	void SetTriOffset();


	//Scene에서 부대 이동을 관리할 겟함수
	cStateMachine<cLeader*>* FSM() { return m_pFsm; }
	IEntity*       GetUnitLeader() { return m_unitLeader; }
	vector<cUnit*> GetUnits() { return m_vectorUnit; }

	int              GetIndex() { return m_currentIndex; }
	void             SetIndex(int i) { m_currentIndex = i; }
	void             SetPath(vector<int> path) { m_path = path; }
	void             PathClear() { m_path.clear(); }
	vector<int>      GetPath() { return m_path; }
	void             SetTargetIndex(int i) { m_targetIndex = i; }
	int              GetTargetIndex() { return m_targetIndex; }
};

