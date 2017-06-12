#pragma once
#include "cSceneManager.h"

class cMainTitleScene :
	public cIScene
{
public:
	cMainTitleScene();
	~cMainTitleScene();

public:
	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

