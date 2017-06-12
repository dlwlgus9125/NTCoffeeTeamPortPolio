#include "stdafx.h"
#include "cLeader.h"

cLeader::cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, 0.5f, forward, mass, maxSpeed);
	m_unitLeader = m_CharacterEntity;
	m_fRotY = 0.0f;
	m_CharacterEntity->SetForward(-m_CharacterEntity->Forward());
	m_targetIndex = m_currentIndex;
}


cLeader::~cLeader()
{
}

void cLeader::Init()
{
	

	m_CollideSphere.fRadius = 0.1f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();
	


	m_arrangeCollideSphere.fRadius = 20.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
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
	m_meshSphere.m_vCenter = m_CollideSphere.vCenter;
	D3DXCreateSphere(D3DDevice, m_CollideSphere.fRadius, 10, 10, &m_meshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_meshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_meshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void cLeader::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);
	m_pFsm->Update(deltaTime);

	D3DXVECTOR3 pos = m_CharacterEntity->Pos();
	
	MAP->GetHeight(pos.x, pos.y, pos.z);
	m_CharacterEntity->SetPos(pos);
	int i = GetTargetIndex();
	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		PathClear();
		if (ASTAR->GetCursorIndex(i))
		{
			SetTargetIndex(i);
			cout << "targetInd : " << i << endl;
		}
	}
	CAMERA->SetLookAt(pos, 0);
	m_pFsm->Update(deltaTime);
	//if (INPUT->IsKeyPress('1'))SetRectOffset();
	//if (INPUT->IsKeyPress('2'))SetTriOffset();
	m_meshSphere.m_vCenter = m_CollideSphere.vCenter;
}

void cLeader::Render()
{
	//cCharacter::Render();
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_CollideSphere.vCenter.x, m_CollideSphere.vCenter.y, m_CollideSphere.vCenter.z);
	matWorld = matR*matT;

	
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DDevice->SetMaterial(&m_meshSphere.m_stMtlSphere);
	//g_pD3DDevice->SetTexture(0, m_pSphere.m_pTexture);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, D3DFILL_SOLID);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_meshSphere.m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
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
