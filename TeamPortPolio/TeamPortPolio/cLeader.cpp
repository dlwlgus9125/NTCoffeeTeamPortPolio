#include "stdafx.h"
#include "cLeader.h"

cLeader::cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, 0.5f, forward, mass, maxSpeed);
	m_unitLeader = m_CharacterEntity;
	m_fRotY = 0.0f;
	m_CharacterEntity->SetForward(-m_CharacterEntity->Forward());
}


cLeader::~cLeader()
{
}

void cLeader::Init()
{
	m_targetIndex = m_currentIndex;

	m_CollideSphere.m_radius = 1.0f;
	m_CollideSphere.m_vCenter = m_CharacterEntity->Pos();
	


	m_arrangeCollideSphere.m_radius = 20.0f;
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();

	for (float z = -2.0f; z <= 1.0f; z++)
	{
		for (float x = 2.0f; x >= -2.0f; x--)
		{
			AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(x, 0, z) * 1.5f));
			m_RectOffest.push_back(D3DXVECTOR3(x, 0, z) * 1.5f);
		}
	}
	//AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(2, 0, 2) *1.5f));
	m_RectOffest.push_back(D3DXVECTOR3(2, 0, 2) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(0, 0, -4.0f) *1.5f);

	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -3.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -3.0f) *1.5f);

	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, -2.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, -2.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, -2.0f) *1.5f);


	m_TriOffest.push_back(D3DXVECTOR3(1.5f, 0, -1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.5f, 0, -1.0f) *1.5f);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 0.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 0.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 0.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 0.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 0.0f) *1.5f);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 1.0f) *1.5f);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 1.0f) *1.5f);

	m_pFsm = new cStateMachine<cLeader*>(this);
	m_pFsm->Register(LEADER_STATE_STATE_IDLE, new Leader_State_Idle());
	m_pFsm->Register(LEADER_STATE_STATE_WALK, new Leader_State_Walk());
	m_pFsm->Play(LEADER_STATE_STATE_IDLE);
}

void cLeader::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);
	m_pFsm->Update(deltaTime);

	D3DXVECTOR3 pos = m_CharacterEntity->Pos();
	
	MAP->GetHeight(pos.x, pos.y, pos.z);
	m_CharacterEntity->SetPos(pos);
	
	//if (INPUT->IsKeyPress('1'))SetRectOffset();
	//if (INPUT->IsKeyPress('2'))SetTriOffset();
}

void cLeader::Render()
{
	//cCharacter::Render();
}

void cLeader::AddUnit(cUnit * pUnit)
{
	pUnit->Init();
	m_vectorUnit.push_back(pUnit);
	OBJECT->AddObject(pUnit);
	OBJECT->AddEntity(pUnit->GetCharacterEntity());
}

void cLeader::DeleteUnit(int key)
{

}

void cLeader::SetRectOffset()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		m_vectorUnit[i]->SetOffset(m_RectOffest[i]);
	}
}

void cLeader::SetTriOffset()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		m_vectorUnit[i]->SetOffset(m_TriOffest[i]);
	}
}
