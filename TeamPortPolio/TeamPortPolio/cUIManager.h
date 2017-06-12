#pragma once

#include "Singleton.h"

#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{
public:
	void Setup();
	void Release();
	void Update();
	void Render();
	void Changer(int sceneID);
};

