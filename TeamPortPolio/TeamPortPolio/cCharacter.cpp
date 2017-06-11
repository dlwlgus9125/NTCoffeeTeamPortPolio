#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
{

}


cCharacter::~cCharacter()
{
	//SAFE_DELETE( m_pSkinnedMesh);
}

void cCharacter::Init()
{
	m_currentMode = DEFENDING_MODE;

	D3DXCreateSphere(D3DDevice, m_CollideSphere.m_radius, 10, 10, &m_CollideSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_CollideSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_CollideSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_CollideSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_CollideSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	D3DXCreateSphere(D3DDevice, m_arrangeCollideSphere.m_radius, 10, 10, &m_arrangeCollideSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_arrangeCollideSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_arrangeCollideSphere.m_stMtlSphere.Ambient = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	m_arrangeCollideSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	m_arrangeCollideSphere.m_stMtlSphere.Specular = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	m_currentIndex = 0;
	
}

void cCharacter::Update(float deltaTime)
{
	
	m_CollideSphere.m_vCenter = m_CharacterEntity->Pos();
	m_arrangeCollideSphere.m_vCenter = m_CharacterEntity->Pos();
}

void cCharacter::Render()
{
	RenderSphere();	


	
}

void cCharacter::RenderSphere()
{
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_CollideSphere.m_vCenter.x, m_CollideSphere.m_vCenter.y, m_CollideSphere.m_vCenter.z);
	matWorld = matR*matT;

	D3DXMATRIXA16 matDir;
	D3DXMatrixIdentity(&matDir);
	D3DXMatrixTranslation(&matDir, m_arrangeCollideSphere.m_vCenter.x, m_arrangeCollideSphere.m_vCenter.y, m_arrangeCollideSphere.m_vCenter.z);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DDevice->SetMaterial(&m_CollideSphere.m_stMtlSphere);
	//g_pD3DDevice->SetTexture(0, m_pSphere.m_pTexture);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, D3DFILL_SOLID);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_CollideSphere.m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetTransform(D3DTS_WORLD, &matDir);
	m_arrangeCollideSphere.m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
