#include "stdafx.h"
#include "cGameManager.h"
#include "cObjectManager.h"
#include "TestMap.h"
#include "cSceneManager.h"
#include "cTitleScene.h"
#include "cUIManager.h"
void cGameManager::Init()
{
	DEVICE->Init();
	pGraph	  = NULL;
	pControl = NULL;
	pEvent	  = NULL;
	pPosition= NULL;
	pWindow  = NULL;
	HRESULT hr = 0;
	hr = CoInitialize(NULL);

	if (FAILED(hr))
		::MessageBox(0, "CoInitialize error", 0, 0);
	
	hr = CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(LPVOID*)&pGraph);

	if (FAILED(hr))
		::MessageBox(0, "CoCreateInstance error", 0, 0);

	hr = pGraph->QueryInterface(IID_IMediaControl, (LPVOID*)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (LPVOID*)&pEvent);
	hr = pGraph->QueryInterface(IID_IMediaPosition, (LPVOID*)&pPosition);
	//pGraph->RenderFile(L"swf/013_defeating_isaac_in_the_cathedral.avi", NULL);;

	pGraph->RenderFile(L"swf/blizzard_logos_black.avi", NULL);

	hr = pGraph->QueryInterface(IID_IVideoWindow, (LPVOID*)&pWindow);

	if (SUCCEEDED(hr))
	{
		pWindow->put_Owner((OAHWND)g_hWnd);
		hr = pWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
		if (FAILED(hr))
		{
			::MessageBox(0, "WindowStyle error", 0, 0);
		}
		RECT rc;
		GetClientRect(g_hWnd, &rc);

		pWindow->SetWindowPosition(0, 0, rc.right, rc.bottom);
		pWindow->put_Visible(true);
	}

	else
		::MessageBox(0, "pWindow QueryInterface error", 0, 0);


	TIME->Init(60);
	TESTMAP->Setup();
	
	OBJECT->Init();
	OBJECTDB->Setup();
	SCENE->Register(0, new cTitleScene());
	SCENE->StartScene(0);
	CAMERA->Setup();
	
	INPUT->Init();
	//UI->OnEnter(Scenetag(0));
	//<<
}

void cGameManager::Update()
{
	//m_pUIManager->OnUpdate();
	if (!isOkView)
	{
		if (pEvent->GetEvent(&EventCode, &Param1, &Param2, 0) != E_ABORT)
		{
			if (EventCode == EC_COMPLETE)
			{
				//pPosition->put_CurrentPosition(0);
				isOkView = true;

				pControl->Release();
				pEvent->Release();
				pPosition->Release();
				pWindow->put_Visible(OAFALSE);
				// 윈도우 부모 윈도우 설정 해제.
				pWindow->put_Owner(NULL);
				pGraph->Release();
				CoUninitialize();
			}
		}

	}

	if (isOkView)
	{

		if (TIME->Update())
		{
			//cout << m_player->GetCharacterEntity()->Pos().x << ", " << m_player->GetCharacterEntity()->Pos().y << ", " << m_player->GetCharacterEntity()->Pos().z << endl;

			m_prevTime = m_currentTime;
			INPUT->Update();
			OBJECT->Update(TIME->DeltaTime());
			CAMERA->Update();
			SCENE->Update();
			//UI->OnUpdate(TIME->DeltaTime());

		}

	}

}

void cGameManager::Render()
{
	
	if(!isOkView)
		pControl->Run();

	else if (isOkView)
	{
		D3DDevice->Clear(NULL,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(47, 121, 112),
			1.0f, 0);
		D3DDevice->BeginScene();
		TESTMAP->Render();
		OBJECT->Render();
		//UI->Render();
		SCENE->Render();
		D3DDevice->EndScene();
		D3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void cGameManager::Release()
{
	//m_pUIManager->OnExit();
}

void cGameManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(!UI->GetIsUIOpen())CAMERA->WndProc(hwnd, message, wParam, lParam);


	//switch (message)
	//{
	//case WM_LBUTTONDOWN:
	//{

	//}
	//break;

	//case WM_RBUTTONDOWN:
	//{

	//}
	//break;
	//}
}




