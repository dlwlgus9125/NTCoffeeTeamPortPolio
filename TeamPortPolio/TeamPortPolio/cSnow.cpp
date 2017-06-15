#include "stdafx.h"
#include "cSnow.h"

cSnow::cSnow()
{
}

cSnow::~cSnow()
{
}


DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}


void cSnow::Setup()
{
	srand((unsigned)time(NULL));
	m_vecParticleVertex.clear();
	m_vecParticleVertex.resize(1000);
	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		float fRadius = rand() % 100;
		m_vecParticleVertex[i].p = D3DXVECTOR3(fRadius, 100, fRadius);

		D3DXVECTOR3	vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f));

		D3DXMATRIX	matRX, matRY, matRZ, matWorld;
		D3DXMatrixIsIdentity(&matWorld);
		D3DXMatrixRotationX(&matRX, vAngle.x);
		D3DXMatrixRotationY(&matRY, vAngle.y);
		D3DXMatrixRotationZ(&matRZ, vAngle.z);
		matWorld = matRX * matRY * matRZ;

		D3DXVec3TransformCoord(&m_vecParticleVertex[i].p, &m_vecParticleVertex[i].p, &matWorld);

		m_vecParticleVertex[i].c = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
}

void cSnow::Update()
{
	int nAlpha = 0;
	int nDelta = 4;

	nAlpha += nDelta;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}

	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		if (i % 2) continue;
		m_vecParticleVertex[i].c = D3DCOLOR_ARGB(255, 255, 255, 255);	// alpha 값만 변경

		if (m_vecParticleVertex[i].p.y < -100) m_vecParticleVertex[i].p.y = 50 + rand() % 50;
		else m_vecParticleVertex[i].p.y -= 0.5f;

		if (m_vecParticleVertex[i].p.x < -100) m_vecParticleVertex[i].p.x = 100;
		else m_vecParticleVertex[i].p.x -= 0.1f;
	}
}

void cSnow::Render()
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);			// 점을 확대할지 말지 정하는것
	D3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(5.0f));			// 포인트 사이즈
	D3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	D3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	D3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(10.0f));		// 10.0f로 바꿔서 실험해보기

	D3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	D3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	D3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(100.0f));

	D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 텍스쳐의 알파블렌딩 방식 결정
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	D3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	D3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	D3DDevice->SetTexture(0, TEXTURE->GetTexture("obj/Effect/Snow/alpha_tex.tga"));
	D3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, m_vecParticleVertex.size(), &m_vecParticleVertex[0], sizeof(ST_PC_VERTEX));

	D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	D3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}