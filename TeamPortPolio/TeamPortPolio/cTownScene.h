#pragma once
#include "cSceneManager.h"
class cTownScene :
	public cIScene
{
	LPD3DXSPRITE       m_pSprite;
public:
	cTownScene();
	~cTownScene();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

