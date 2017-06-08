#include "stdafx.h"
#include "cLeader.h"

cLeader::cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	m_unitLeader = m_CharacterEntity;
	m_fRotY = 0.0f;
	m_CharacterEntity->SetForward(-m_CharacterEntity->Forward());
}


cLeader::~cLeader()
{
}

void cLeader::Init()
{
	m_CollideSphere.m_radius = m_CharacterEntity->Radius();
	m_CollideSphere.m_vCenter = m_CharacterEntity->Pos();
	m_CollideSphere.m_vCenter.y += 0.5f;


	m_arrangeCollideSphere.m_radius = 20.0f;
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();

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

}

void cLeader::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
	D3DXVECTOR3 prevPos = m_CharacterEntity->Pos();
	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();

	/*if (INPUT->IsKeyPress('W'))
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

	if (INPUT->IsKeyDown(VK_TAB))
	{
		switch (m_currentMode)
		{
		case FIGHTING_MODE: m_currentMode = DEFENDING_MODE; break;
		case DEFENDING_MODE: m_currentMode = FIGHTING_MODE; break;
		}

		for (int i = 0; i < m_vectorUnit.size(); i++)
		{
			m_vectorUnit[i]->SetMode(m_currentMode);
		}
	}*/

	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&forward, &forward, &matR);
	m_CharacterEntity->SetPos(movePos);
	m_CharacterEntity->SetForward(forward);

	//if (INPUT->IsKeyPress('1'))SetRectOffset();
	//if (INPUT->IsKeyPress('2'))SetTriOffset();
}

void cLeader::Render()
{
	cCharacter::Render();
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
