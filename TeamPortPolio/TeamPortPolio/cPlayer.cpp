#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"
#include "cLeader.h"

cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	m_unitLeader = new cLeader(pos, radius, forward, mass, maxSpeed);
	m_unitLeader->Init();
	OBJECT->AddObject(m_unitLeader);

	m_fRotY = 0.0f;
	m_frustum = new cFrustum();
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	m_CollideSphere.m_radius = m_CharacterEntity->Radius();
	m_CollideSphere.m_vCenter = m_CharacterEntity->Pos();
	m_CollideSphere.m_vCenter.y += 0.5f;
	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh = new cSkinnedMesh(TEXTURE->GetCharacterResource("Character/Human/", "newfootman.x"));

	m_arrangeCollideSphere.m_radius = 20.0f;
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();
	m_frustum->Setup();

	/*for (float z = -2.0f; z <= 1.0f; z++)
	{
		for (float x = 2.0f; x >= -2.0f; x--)
		{
			AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(x, 0, z) * 3));
			m_RectOffest.push_back(D3DXVECTOR3(x, 0, z) * 3);
		}
	}*/
	//AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(2, 0, 2) * 3));
	/*m_RectOffest.push_back(D3DXVECTOR3(2, 0, 2) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(0, 0, -4.0f) * 3);

	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -3.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -3.0f) * 3);

	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, -2.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, -2.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, -2.0f) * 3);


	m_TriOffest.push_back(D3DXVECTOR3(1.5f, 0, -1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-1.5f, 0, -1.0f) * 3);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 0.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 0.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 0.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 0.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 0.0f) * 3);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 1.0f) * 3);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 1.0f) * 3);*/

	/*for (int x = -2; x <= 0; x++)
	{
	for (int z = -2; z <= 2; z++)
	{
	if (x == 0 && z == 0) continue;

	AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(x, 0, z) * 5));
	}
	}*/

}

void cPlayer::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
	D3DXVECTOR3 prevPos = m_CharacterEntity->Pos();
	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();

	if (INPUT->IsKeyPress('W'))
	{
		movePos += m_CharacterEntity->Forward()*0.02f;
		if (INPUT->IsKeyPress(VK_SHIFT))
		{
			movePos += m_CharacterEntity->Forward()*0.03f;
		}

	}
	if (INPUT->IsKeyPress('S'))
	{
		movePos -= m_CharacterEntity->Forward()*0.02f;
	}
	if (INPUT->IsKeyPress('A'))
	{
		m_fRotY -= 0.03f;
	}
	if (INPUT->IsKeyPress('D'))
	{
		m_fRotY += 0.03f;
	}

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
	}

	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&forward, &forward, &matR);
	m_CharacterEntity->SetPos(movePos);
	m_CharacterEntity->SetForward(forward);


	m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

	if (0.01f<MATH->Distance(prevPos, movePos) && MATH->Distance(prevPos, movePos)<=0.03f)
	{
		m_pSkinnedMesh->SetAnimationIndex(F_WALK);
	}
	else if (0.03f<MATH->Distance(prevPos, movePos) )
	{
		m_pSkinnedMesh->SetAnimationIndex(F_RUN);
	}
	else
	{
		m_pSkinnedMesh->SetAnimationIndex(F_STAND);
	}


	CAMERA->SetLookAt(movePos, m_fRotY);
	

	if (INPUT->IsKeyPress('1'))m_unitLeader->SetRectOffset();
	if (INPUT->IsKeyPress('2'))m_unitLeader->SetTriOffset();
}

void cPlayer::Render()
{
	cCharacter::Render();
	
	if (m_pSkinnedMesh)
	{
		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRender();
		}
	}
}
