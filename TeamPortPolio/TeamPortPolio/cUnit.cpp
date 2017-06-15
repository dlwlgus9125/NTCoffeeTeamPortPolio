#include "stdafx.h"
#include "cUnit.h"


cUnit::cUnit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), 0.5f,
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
	m_CollideSphere.fRadius = 1.0f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 1.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();

	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh =  new cSkinnedMesh(TEXTURE->GetCharacterResource("Character/BloodeHuman/", "b_footman.x"));
	
	m_pSkinnedMesh->FindAttackBone("Sword_2H_Broadsword_A_03_Bone08");

	m_pFsm = new cStateMachine<cUnit*>(this);
	m_pFsm->Register(UNIT_STATE_MELEE_IDLE,    new Melee_Idle());
	m_pFsm->Register(UNIT_STATE_MELEE_WALK,    new Melee_Walk());
	m_pFsm->Register(UNIT_STATE_MELEE_BATTLE,  new Melee_Battle());
	m_pFsm->Register(UNIT_STATE_MELEE_DEFENCE, new Melee_Defence());
	m_pFsm->Register(UNIT_STATE_MELEE_DEATH, new Melee_Death());
	m_pFsm->Play(UNIT_STATE_MELEE_IDLE);
}

void cUnit::Update(float deltaTime)
{
	if (m_isDeath == false)
	{
		cCharacter::Update(deltaTime);

		m_pFsm->Update(deltaTime);

		D3DXVECTOR3 pos = m_CharacterEntity->Pos();
		MAP->GetHeight(pos.x, pos.y, pos.z);
		m_CharacterEntity->SetPos(pos);
		m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

		if (m_Status.m_HP <= 0.0f)m_pFsm->Play(UNIT_STATE_MELEE_DEATH);
	}
}

void cUnit::Render()
{
	cCharacter::Render();
	
	if (m_pSkinnedMesh)
	{
		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRender(m_isDeath);

			SetAttackColliderPos();
			D3DXMATRIXA16 matT;
			D3DXMatrixIdentity(&matT);

			D3DXMatrixTranslation(&matT, m_AttackCollideSphere.vCenter.x, m_AttackCollideSphere.vCenter.y, m_AttackCollideSphere.vCenter.z);

			D3DDevice->SetTransform(D3DTS_WORLD, &matT);
			D3DDevice->SetMaterial(&m_MeshSphere.m_stMtlSphere);

			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			m_MeshSphere.m_pMeshSphere->DrawSubset(0);
			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

}
