#include "stdafx.h"
#include "cSceneManager.h"

void cSceneManager::StartScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		::MessageBox(0, "StartScene error - Can't Found Scene ", 0, 0);
	}
	m_current = tag;
}

void cSceneManager::Register(int tag, cIScene * pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
		m_scenes[tag]->SetTag(tag);
	}
}

void cSceneManager::ChangeScene(int tag)
{
	if (m_current != tag)
	{
		cIScene* prevScene = GetScene(m_current);

		if (prevScene != NULL)
			prevScene->OnExit();
		else
			::MessageBox(0, TEXT("prevScene error - NULL"), 0, 0);

		cIScene* nextScene = GetScene(tag);

		if (nextScene != NULL)
		{
			nextScene->OnEnter();
			m_current = tag;
			Sleep(500);
		}
		else
			::MessageBox(0, TEXT("nextScene error - NULL"), 0, 0);
	}

	else if (m_current == tag)
		::MessageBox(0, TEXT("ChangeScene error - m_current == tag"), 0, 0);
}

void cSceneManager::Update()
{
	cIScene* currentScene = GetScene(m_current);
	if (currentScene != NULL)
		currentScene->OnUpdate();
	else
		::MessageBox(0, TEXT("Update error - currentScene == NULL"), 0, 0);
}

void cSceneManager::Render()
{
	cIScene* currentScene = GetScene(m_current);
	if (currentScene != NULL)
		currentScene->OnRender();
	else
		::MessageBox(0, TEXT("Render error - currentScene == NULL"), 0, 0);
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cIScene* currentScene = GetScene(m_current);
	if (currentScene != NULL)
		currentScene->WndProc(hWnd, message, wParam, lParam);
	else
		::MessageBox(0, TEXT("WndProc error - currentScene == NULL"), 0, 0);
}

int cSceneManager::Current()
{
	return m_current;
}

cIScene * cSceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		::MessageBox(0, TEXT("GetScene error"), 0, 0);
		return NULL;
	}

	return m_scenes[tag];
}
