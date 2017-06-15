#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "Leader_State.h"

enum LEADER_STATE
{
	LEADER_STATE_IDLE,
	LEADER_STATE_WALK,
	LEADER_STATE_PURSUIT,
	LEADER_STATE_DEFENCE,
	LEADER_STATE_DEFEAT,
};
enum CAMP_STATE
{
	CAMP_PLAYER,
	CAMP_ENEMY1,
	CAMP_NONE,
};

class cLeader :
	public cCharacter
{
	cStateMachine<cLeader*>* m_pFsm;
	ISteeringEntity*  m_unitLeader;//�δ��̵��� ����� �������
	vector<cUnit*> m_vectorUnit;
	vector<D3DXVECTOR3> m_RectOffest;
	vector<D3DXVECTOR3> m_TriOffest;
	float          m_fRotY;
	int            m_targetIndex;
	vector<int>    m_path;
	MeshSpere      m_meshSphere;
	CAMP_STATE     m_camp;


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
	cStateMachine<cLeader*>* FSM() { return m_pFsm; }
	IEntity*       GetUnitLeader() { return m_unitLeader; }
	vector<cUnit*> GetUnits() { return m_vectorUnit; }

	void             SetCamp(int camp) { m_camp = (CAMP_STATE)camp; }
	CAMP_STATE       GetCamp() { return m_camp; }
	void             SetPath(vector<int> path) { m_path = path; }
	void             PathClear() { m_path.clear(); }
	vector<int>      GetPath() { return m_path; }
	void             SetTargetIndex(int i) { m_targetIndex = i; }
	int              GetTargetIndex() { return m_targetIndex; }
};

