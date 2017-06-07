#include "stdafx.h"
#include "cUnit.h"


cUnit::cUnit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), pLeader->Radius() * 0.6f,
		pLeader->Forward(), pLeader->Mass(), pLeader->MaxSpeed() * 3);
	m_pLeader = pLeader;
	m_offset = offset;
}


cUnit::~cUnit()
{
	SAFE_DELETE(m_CharacterEntity);
	SAFE_DELETE(m_pFsm);
	//delete m_pLeader;
}

void cUnit::Init()
{
	cCharacter::Init();

	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("Character/Human", "HumanInfantry.x");
	m_pSkinnedMesh->SetIEntity(m_CharacterEntity);

	m_pFsm = new cStateMachine<cUnit*>(this);
	m_pFsm->Register(UNIT_STATE_STATE_IDLE,    new Human_State_Idle());
	m_pFsm->Register(UNIT_STATE_STATE_WALK,    new Human_State_Walk());
	m_pFsm->Register(UNIT_STATE_STATE_ATTACK,  new Human_State_Attack());
	m_pFsm->Register(UNIT_STATE_STATE_DEFENCE, new Human_State_Defence());
	m_pFsm->Play(UNIT_STATE_STATE_IDLE);
}

void cUnit::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);

	m_pFsm->Update(deltaTime);
	if (m_pSkinnedMesh)m_pSkinnedMesh->Update();
	
	
}

void cUnit::UpdateState()
{
	/*if (m_pSkinnedMesh->Getindex() == F_ATTACK1 || m_pSkinnedMesh->Getindex() == F_ATTACK2 || m_pSkinnedMesh->Getindex() == F_ATTACK3)
	{
		if (m_pSkinnedMesh->GetPassedTime()  > m_pSkinnedMesh->GetCurrentAnim()->GetPeriod() - 0.3f)
		{
			m_pSkinnedMesh->SetAnimationIndexBlend(F_READYATTACK);
		}
	}
	
	if (m_pSkinnedMesh->Getindex() != F_BATTLEWALK&&0.005f <= m_CharacterEntity->Speed() && m_CharacterEntity->Speed() <= 0.5f)
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(F_BATTLEWALK);
	}
	else if (m_pSkinnedMesh->Getindex() != F_BATTLERUN&&0.5f < m_CharacterEntity->Speed())
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(F_BATTLERUN);
	}
	else if (m_pSkinnedMesh->Getindex() != F_READYATTACK&&m_CharacterEntity->Speed() < 0.005f)
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(F_READYATTACK);
	}*/

	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		FOOTMAN_STATE state = F_SHEILDBLOCK;
		//m_pSkinnedMesh->

		m_pSkinnedMesh->SetAnimationIndexBlend(state);
	}
}

void cUnit::Render()
{
	cCharacter::Render();
	
	if (m_pSkinnedMesh) m_pSkinnedMesh->Render(NULL);

}
