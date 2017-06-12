#pragma once

#include "Singleton.h"

#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{
public:
	void Setup();
	void Release();
	void Update();
	void Render(LPD3DXSPRITE pSprite);
	void Changer(int sceneID);
};

