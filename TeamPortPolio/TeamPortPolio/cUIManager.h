#pragma once

#include "Singleton.h"
#include "cUIImage.h"
#include "cUIText.h"
#include "cUIMiniMap.h"

#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{
	vector<cUIImage*>			m_vecImage;
	vector<cUIText*>			m_vecText;
	cUIMiniMap*					m_pMiniMap;

	void Setup_TitleScene();
	void Setup_TownScene();

public:
	void Setup();
	void Release();
	void Update(float deltaTime);
	void Render(LPD3DXSPRITE pSprite);
	void Change(int sceneID);
	void PressKey();
	void GetEvent(OUT int& minimapIndex);


};

