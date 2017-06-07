#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"


cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	m_unitLeader = m_CharacterEntity;
	m_fRotY = 0.0f;
	m_frustum = new cFrustum();
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	cCharacter::Init();
	m_frustum->Setup();

	for (float z = -2.0f; z <= 1.0f; z++)
	{
		for (float x = 2.0f; x >= -2.0f; x--)
		{
			AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(x, 0, z) * 3));
			m_RectOffest.push_back(D3DXVECTOR3(x, 0, z) * 3);
		}
	}
	//AddUnit(new cUnit(m_CharacterEntity, D3DXVECTOR3(2, 0, 2) * 3));
	m_RectOffest.push_back(D3DXVECTOR3(2, 0, 2) * 3);
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
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 1.0f) * 3);

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
	m_dirSphere.m_vCenter = m_CharacterEntity->Pos() + m_CharacterEntity->Forward()*2.0f;
	D3DXVECTOR3 prevPos = m_CharacterEntity->Pos();
	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();

	if (INPUT->IsKeyPress('W'))
	{
		movePos += m_CharacterEntity->Forward()*0.05f;
		if (INPUT->IsKeyPress(VK_SHIFT))
		{
			movePos += m_CharacterEntity->Forward()*0.15f;
		}
		
	}
	if (INPUT->IsKeyPress('S'))
	{
		movePos -= m_CharacterEntity->Forward()*0.05f;
	}
	if (INPUT->IsKeyPress('A'))
	{
		m_fRotY -= 0.03f;
	}
	if (INPUT->IsKeyPress('D'))
	{
		m_fRotY += 0.03f;
	}

	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&forward, &forward, &matR);
	m_CharacterEntity->SetPos(movePos);
	m_CharacterEntity->SetForward(forward);
	CAMERA->SetLookAt(movePos, m_fRotY);
	//m_CharacterEntity->Steering()->UpdateVelocity(deltaTime);
	//	m_CharacterEntity->AddPos(m_CharacterEntity->Velocity()*deltaTime);


	if (m_vectorUnit.size() > 0)
	{
		for (int i = 0; i < m_vectorUnit.size(); i++)
		{
			m_vectorUnit[i]->Update(deltaTime);
		}
		m_frustum->Update();
	}

	if (INPUT->IsKeyPress('1'))SetRectOffset();
	if (INPUT->IsKeyPress('2'))SetTriOffset();
}

void cPlayer::Render()
{
	cCharacter::Render();
	//int count = 0;

	if (m_vectorUnit.size() > 0)
	{
		for (int i = 0; i < m_vectorUnit.size(); i++)
		{
			if (m_frustum->IsIn(m_vectorUnit[i]->GetMeshSphere()))
			{
				m_vectorUnit[i]->Render();
				//count++;
			}
		}
	}
	//cout << "RenderCount : " << count << endl;
}

void cPlayer::AddUnit(cUnit * pUnit)
{
	pUnit->Init();
	m_vectorUnit.push_back(pUnit);
	OBJECT->AddEntity(pUnit->GetCharacterEntity());
}

void cPlayer::DeleteUnit(int key)
{

}

void cPlayer::SetRectOffset()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		m_vectorUnit[i]->SetOffset(m_RectOffest[i]);
	}
}

void cPlayer::SetTriOffset()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		m_vectorUnit[i]->SetOffset(m_TriOffest[i]);
	}
}
