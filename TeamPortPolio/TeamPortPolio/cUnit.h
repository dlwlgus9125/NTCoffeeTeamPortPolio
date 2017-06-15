#pragma once
#include "cCharacter.h"
#include "Human_Melee_State.h"

enum UNIT_STATE
{
	UNIT_STATE_MELEE_IDLE,
	UNIT_STATE_MELEE_WALK,
	UNIT_STATE_MELEE_BATTLE,
	UNIT_STATE_MELEE_DEFENCE,
};

class cUnit :
	public cCharacter
{
	cStateMachine<cUnit*>* m_pFsm;
	IEntity* m_pLeader;
	D3DXVECTOR3 m_offset;
	cUnit*   m_TargetEnemy;
	bool m_isDeath;

	//자신을 겨누고있는 최대 적의 수를 파악
	vector<cUnit*> m_targetedEnemy;
public:
	cUnit(IEntity* pLeader, D3DXVECTOR3 offset);
	~cUnit();
	cStateMachine<cUnit*>* FSM() { return m_pFsm; }
	void Init();
	void Update(float deltaTime);
	void UpdateState();
	void Render();
	void SetOffset(D3DXVECTOR3 offset) { m_offset = offset; }
	D3DXVECTOR3 GetOffset() { return D3DXVECTOR3(m_offset.x, 0, m_offset.z); }
	IEntity*    GetLeader() { return m_pLeader; }

	void SetEnemy(cUnit* enemy) { m_TargetEnemy = enemy; }
	cUnit* GetEnemy() { return m_TargetEnemy; }
	void SetDeath() { m_isDeath = true; }
	bool GetDeath() { return m_isDeath; }
	int GetTargetedSize() { return m_targetedEnemy.size(); }
	bool AddTargetedEnemy(cUnit* pUnit)
	{
		if (m_targetedEnemy.size() <= 1)
		{
			m_targetedEnemy.push_back(pUnit);
			return true;
		}
		return false;
	}
	void ClearTargetedEnemy() { m_targetedEnemy.clear(); }
};

