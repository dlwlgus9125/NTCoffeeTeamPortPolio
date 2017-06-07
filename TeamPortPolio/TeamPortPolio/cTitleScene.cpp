#include "stdafx.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene() :
	m_pSprite(NULL),
	m_pTexture(NULL)
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	m_pBackgroundImage.SetPosition(0, 0, 0);
	m_pBackgroundImage.SetTexture("Image/TitleScene.png");
}


cTitleScene::~cTitleScene()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}

void cTitleScene::OnEnter()
{
}

void cTitleScene::OnUpdate()
{
}

void cTitleScene::OnExit()
{
}

void cTitleScene::OnRender()
{
	D3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	D3DDevice->BeginScene();
	
	m_pBackgroundImage.Render(m_pSprite);

	D3DDevice->EndScene();

	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
