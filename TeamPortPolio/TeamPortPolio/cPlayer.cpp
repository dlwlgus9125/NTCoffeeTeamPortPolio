#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"
#include "cLeader.h"

cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	/*m_unitLeader = new cLeader(pos, radius, forward, mass, maxSpeed);
	m_unitLeader->Init();
	m_unitLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(16001)->Id());
	OBJECT->AddObject(m_unitLeader);
	OBJECT->AddLeader(m_unitLeader);*/
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
		
	m_pFsm = new cStateMachine<cPlayer*>(this);
	m_pFsm->Register(PLAYER_STATE_IDLE, new Player_Idle());
	m_pFsm->Register(PLAYER_STATE_WALK, new Player_Walk());
	m_pFsm->Register(PLAYER_STATE_ATTACK, new Player_Attack());
	//m_pFsm->Register(PLAYER_STATE_DEFENCE, new Player_Idle());
	m_pFsm->Play(PLAYER_STATE_IDLE);
}

void cPlayer::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);

	m_pFsm->Update(deltaTime);

	/*m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	D3DXVECTOR3 prevPos = m_CharacterEntity->Pos();
	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();

	
	if (INPUT->IsKeyPress(VK_W))
	{
		movePos += m_CharacterEntity->Forward()*0.02f;
		if (INPUT->IsKeyPress(VK_SHIFT))
		{
			movePos += m_CharacterEntity->Forward()*0.03f;
		}
	}
	if (INPUT->IsKeyPress(VK_S))
	{
		movePos -= m_CharacterEntity->Forward()*0.02f;
	}
	if (INPUT->IsKeyPress(VK_A))
	{
		m_fRotY -= 0.03f;
	}
	if (INPUT->IsKeyPress(VK_D))
	{
		m_fRotY += 0.03f;
	}*/

	/*
	if (INPUT->IsKeyDown(VK_TAB))
	{
		switch (m_currentMode)
		{
		case FIGHTING_MODE: m_currentMode = DEFENDING_MODE; break;
		case DEFENDING_MODE: m_currentMode = FIGHTING_MODE; break;
		}

		for (int i = 0; i < m_unitLeader->GetUnits().size(); i++)
		{
			m_unitLeader->GetUnits()[i]->SetMode(m_currentMode);
		}
	}*/

	/*D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&forward, &forward, &matR);

	MAP->GetHeight(movePos.x, movePos.y, movePos.z);
	m_CharacterEntity->SetPos(movePos);
	int index = 0;
	MAP->GetMap()->GetIndex(movePos.x, movePos.z, index);*/
	/*if (INPUT->IsKeyDown(VK_SPACE))
	{
		cout << "move.x : " << movePos.x << ", move.z : " << movePos.z << ", index : " << index << endl;
		cout << "id : " << ASTAR->GetGraph()->GetNode(index)->Id() << ", move.x : " << ASTAR->GetGraph()->GetNode(index)->Pos().x << ", move.z : " << ASTAR->GetGraph()->GetNode(index)->Pos().z << endl;
	}*///m_CharacterEntity->SetPos(m_unitLeader->GetCharacterEntity()->Pos());
	//m_CharacterEntity->SetForward(forward);
	//m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

	//if (0.01f<MATH->Distance(prevPos, movePos) && MATH-//>Distance(prevPos, movePos)<=0.03f)
	//{
	//	m_pSkinnedMesh->SetAnimationIndex(P_WALK);
	//}
	//else if (0.03f<MATH->Distance(prevPos, movePos) )
	//{
	//	m_pSkinnedMesh->SetAnimationIndex(P_RUN);
	//}
	//else
	//{
	//	m_pSkinnedMesh->SetAnimationIndex(P_STAND);
	//}

	//CAMERA->SetLookAt(movePos, m_fRotY);
	//if (INPUT->IsKeyPress('1'))m_unitLeader->SetRectOffset();
	//if (INPUT->IsKeyPress('2'))m_unitLeader->SetTriOffset();
}

void cPlayer::Render()
{
	cCharacter::Render();
	//m_unitLeader->Render();
	if (m_pSkinnedMesh)
	{
		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRender();
		}
	}
}
