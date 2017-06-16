#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"
#include "cLeader.h"

cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	m_unitLeader = NULL;
	m_unitLeader = new cLeader(pos, radius, forward, mass, maxSpeed);
	m_unitLeader->Init();
	m_unitLeader->SetCamp(CAMP_PLAYER);
	m_unitLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(16001)->Id());
	OBJECT->AddObject(m_unitLeader);
	OBJECT->AddLeader(m_unitLeader);
	m_fRotY = 0.0f;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pFsm);

}

void cPlayer::Init()
{
	m_CollideSphere.fRadius = m_CharacterEntity->Radius();
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();
	m_CollideSphere.vCenter.y += 0.5f;
	
	m_arrangeCollideSphere.fRadius = 20.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();
	
	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh = new cSkinnedMesh(TEXTURE->GetCharacterResource("Character/BloodeHuman/", "b_footman.x"));

	m_pSkinnedMesh->FindAttackBone("Sword_2H_Broadsword_A_03_Bone08");
		
	m_pFsm = new cStateMachine<cPlayer*>(this);
	m_pFsm->Register(PLAYER_STATE_IDLE, new Player_Idle());
	m_pFsm->Register(PLAYER_STATE_WALK, new Player_Walk());
	m_pFsm->Register(PLAYER_STATE_ATTACK, new Player_Attack());
	m_pFsm->Register(PLAYER_STATE_DEFENCE, new Player_Defence());
	m_pFsm->Play(PLAYER_STATE_IDLE);
}

void cPlayer::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);

	m_pFsm->Update(deltaTime);

	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();
	MAP->GetHeight(movePos.x, movePos.y, movePos.z);
	m_CharacterEntity->SetPos(movePos);

	if (INPUT->IsKeyPress(VK_A))
	{
		m_fRotY -= 0.03;
	}
	if (INPUT->IsKeyPress(VK_D))
	{
		m_fRotY += 0.03;
	}



	D3DXMATRIXA16 matR;
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);

	D3DXVec3TransformCoord(&forward, &forward, &matR);
	m_CharacterEntity->SetForward(forward);

	m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

	CAMERA->SetLookAt(m_CharacterEntity->Pos(), m_fRotY);


}

void cPlayer::Render()
{
	cCharacter::Render();
	//m_unitLeader->Render();
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

void cPlayer::SetUnitLeaderTargetIndex(int index)
{
	if (m_unitLeader)
	{
		m_unitLeader->PathClear();
		if (ASTAR->GetGraph()->GetNode(index)->Active())
		{
			m_unitLeader->SetTargetIndex(index);
			/*cout << "targetInd : " << index << endl;
			cout << "size : " << m_unitLeader->GetPath().size() << endl;*/
		}
	}
}
