#pragma once
#include "cCharacter.h"
#include "Human_Melee_State.h"

enum UNIT_STATE
{
	UNIT_STATE_STATE_IDLE,
	UNIT_STATE_STATE_WALK,
	UNIT_STATE_STATE_ATTACK,
	UNIT_STATE_STATE_DEFENCE,
};

class cUnit :
	public cCharacter
{
	cStateMachine<cUnit*>* m_pFsm;
	IEntity* m_pLeader;
	D3DXVECTOR3 m_offset;
	cUnit*   m_TargetEnemy;
	bool m_isDeath;
public:
	cUnit(IEntity* pLeader, D3DXVECTOR3 offset);
	~cUnit();
	cStateMachine<cUnit*>* FSM() { return m_pFsm; }
	void Init();
	void Update(float deltaTime);
	void UpdateState();
	void Render();
	void SetOffset(D3DXVECTOR3 offset) { m_offset = offset; }
	D3DXVECTOR3 GetOffset() { return D3DXVECTOR3(m_offset.x, 0 , m_offset.z); }
	IEntity*    GetLeader() { return m_pLeader; }

	void SetEnemy(cUnit* enemy) { m_TargetEnemy = enemy; }
	cUnit* GetEnemy() { return m_TargetEnemy; }
	void SetDeath() { m_isDeath = true; }
	bool GetDeath() { return m_isDeath; }
};

