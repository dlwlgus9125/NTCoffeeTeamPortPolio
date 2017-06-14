#include "stdafx.h"
#include "cUnit.h"


cUnit::cUnit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), 0.5f,
		pLeader->Forward(), pLeader->Mass(), pLeader->MaxSpeed() * 3);
	m_pLeader = pLeader;
	m_offset = offset;
	m_isDeath = false;
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
	m_CollideSphere.vCenter.y += 0.5f;

	m_arrangeCollideSphere.fRadius = 1.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();

	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh =  new cSkinnedMesh(TEXTURE->GetCharacterResource("Character/BloodeHuman/", "b_footman.x"));
	
	m_meshSphere.m_radius = 0.1f;
	m_attackCollider.fRadius = 0.1f;

	D3DXCreateSphere(D3DDevice, m_attackCollider.fRadius, 10, 10, &m_meshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_meshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_meshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	m_pFsm = new cStateMachine<cUnit*>(this);
	m_pFsm->Register(UNIT_STATE_MELEE_IDLE,    new Human_Melee_Idle());
	m_pFsm->Register(UNIT_STATE_MELEE_WALK,    new Human_Melee_Walk());
	m_pFsm->Register(UNIT_STATE_MELEE_BATTLE,  new Human_Melee_Battle());
	m_pFsm->Register(UNIT_STATE_MELEE_DEFENCE, new Human_Melee_Defence());
	m_pFsm->Play(UNIT_STATE_MELEE_IDLE);
}

void cUnit::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);

	m_pFsm->Update(deltaTime);
	
	D3DXVECTOR3 pos = m_CharacterEntity->Pos();
	MAP->GetHeight(pos.x, pos.y, pos.z);
	m_CharacterEntity->SetPos(pos);
	m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());
}

void cUnit::Render()
{
	cCharacter::Render();
	
	if (m_pSkinnedMesh)
	{
		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRender();

			D3DDevice->SetTransform(D3DTS_WORLD, &SetAttackCollider());
			D3DDevice->SetMaterial(&m_meshSphere.m_stMtlSphere);

			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			//m_meshSphere.m_pMeshSphere->DrawSubset(0);
			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

}

