#include "stdafx.h"
#include "cEffectManager.h"


void cEffectManager::Init(bool isFogOn, int fogPassIndex, bool isSnowOn)
{
	m_isFogOn = isFogOn;
	m_nFogPassIndex = fogPassIndex;
	m_isSnowOn = isSnowOn;

	if (m_isFogOn)
	{
		m_pFog = new cFog();
		m_pFog->Setup("obj/Effect/Fog/fog.txt");
	}

	if (m_isSnowOn)
	{
		m_pSnow = new cSnow();
		m_pSnow->Setup();
	}
}

void cEffectManager::Update()
{
	if (m_pFog) m_pFog->Update(CAMERA->GetCamera());
	if (m_pSnow) m_pSnow->Update();
}

void cEffectManager::Render()
{
	if (m_pSnow) m_pSnow->Render();
}

void cEffectManager::Release()
{
	if (m_pFog) SAFE_DELETE(m_pFog);
	if (m_pSnow) SAFE_DELETE(m_pSnow);
}

void cEffectManager::Render_Fog_Begin()
{
	if (m_pFog) m_pFog->Render_Begin(m_nFogPassIndex);
}

void cEffectManager::Render_Fog_End()
{
	if (m_pFog) m_pFog->Render_End();
}