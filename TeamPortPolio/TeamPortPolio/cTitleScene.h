#pragma once
#include "cSceneManager.h"
#include "cImageView.h"

// >> 
#include "cSkyBox.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cConstruct.h"
// << 

class cTitleScene : public cIScene
{
private:
	LPD3DXSPRITE       m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO     m_stImageInfo;
	cImageView         m_pBackgroundImage;

	// >> 
	cSkyBox*				m_pSkyBox;
	cHeightMap*					m_pMap;
	vector<cConstruct*>		m_vecConstruct;
	// << 

public:
	cTitleScene();
	~cTitleScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

