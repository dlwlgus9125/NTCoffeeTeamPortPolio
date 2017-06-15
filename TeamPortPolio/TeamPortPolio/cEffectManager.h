#pragma once
#include "Singleton.h"
#include "cFog.h"
#include "cSnow.h"
#include "cCamera.h"

#define EFFECT cEffectManager::Instance()

class cEffectManager : public Singleton<cEffectManager>
{
	cFog*		m_pFog;
	cSnow*		m_pSnow;

	bool		m_isFogOn;
	int			m_nFogPassIndex;
	bool		m_isSnowOn;

public:
	void Init(bool isFogOn, int fogPassIndex, bool isSnowOn);
	void Update();
	void Render();
	void Render_Fog_Begin();
	void Render_Fog_End();
	void Release();
};

