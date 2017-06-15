#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
{
	m_targetObject = NULL;
}


cCharacter::~cCharacter()
{
	//SAFE_DELETE( m_pSkinnedMesh);
}

void cCharacter::Init()
{
	m_currentMode = DEFENDING_MODE;
	m_AttackCollideSphere.fRadius = 0.1f;
	D3DXCreateSphere(D3DDevice, m_AttackCollideSphere.fRadius, 10, 10, &m_MeshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_MeshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_MeshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//D3DXCreateSphere(D3DDevice, m_arrangeCollideSphere.m_radius, 10, 10, &m_arrangeCollideSphere.m_pMeshSphere, NULL);
	//ZeroMemory(&m_arrangeCollideSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	//m_arrangeCollideSphere.m_stMtlSphere.Ambient = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	//m_arrangeCollideSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	//m_arrangeCollideSphere.m_stMtlSphere.Specular = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	m_currentIndex = 0;
	m_AttackCollideSphere.fRadius = 0.2f;
	m_isDeath = false;
}

void cCharacter::Update(float deltaTime)
{
	
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();

	
}

void cCharacter::Render()
{

	
	RenderSphere();	


	
}

void cCharacter::RenderSphere()
{
	
}

void cCharacter::SetAttackColliderPos()
{
	m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);
	
	D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_pSkinnedMesh->GetAttackBoneMat());
}

FIGHT_STATE cCharacter::Fight(cCharacter * attacker, cCharacter * defender)
{
	
	int randCount = rand() % 10+1;

	if (randCount <= defender->m_Status.m_avoid)
	{
		return FIGHT_AVOID;
	}
	else if (randCount <= defender->m_Status.m_defence)
	{
		return FIGHT_BLOCK;
	}

	defender->m_Status.SetHP(-attacker->m_Status.m_Damage);
	return FIGHT_HIT;
}
