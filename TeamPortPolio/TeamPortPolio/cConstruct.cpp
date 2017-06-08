#include "stdafx.h"
#include "cConstruct.h"
#include "cObject.h"
#include "cMtlTex.h"
#include "cObjLoader.h"

cConstruct::cConstruct()
	: m_pObjMesh(NULL)
	, m_vScale(0.5f, 0.5f, 0.5f)
	, m_fRotX(0.0f), m_fRotY(0.0f), m_fRotZ(0.0f)
	, m_vPosition(0.0f, 0.0f, 0.0f)
{
}


cConstruct::~cConstruct()
{
}

void cConstruct::Setup(char* szFolder, char* szFile)
{
	cObjLoader	l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, szFolder, szFile, true);
}

void cConstruct::Update()
{
	D3DXMATRIXA16	matS, matRX, matRY, matRZ, matT;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matRX);
	D3DXMatrixIdentity(&matRY);
	D3DXMatrixIdentity(&matRZ);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationX(&matRX,  m_fRotX);
	D3DXMatrixRotationY(&matRY,  m_fRotY);
	D3DXMatrixRotationZ(&matRZ, m_fRotZ);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matRX * matRY * matRZ* matT;

	D3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void cConstruct::Render()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
	{
		D3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		D3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		D3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		m_pObjMesh->DrawSubset(i);
	}	
}

void cConstruct::Create(int sIndex)
{
	char* folder = OBJECTDB->GetMapObject(sIndex)->szFolder;
	char* file = OBJECTDB->GetMapObject(sIndex)->szFile;

	m_nSObjID = sIndex;

	Setup(folder, file);
	Update();
}

void cConstruct::Destroy()
{
	SAFE_RELEASE(m_pObjMesh);
	for each(auto p in m_vecObjMtlTex)
	{
		SAFE_RELEASE(p);
	}

	// delete this;
}