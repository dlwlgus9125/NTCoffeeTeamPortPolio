#pragma once
#include <Windows.h>
#include "Singleton.h"

#define TIME	cTimeManager::Instance()

class cTimeManager : public Singleton<cTimeManager>
{
	LONGLONG m_frequency;		// �ʴ� ���ļ�
	LONGLONG m_startCount;		// ���� ī��Ʈ
	LONGLONG m_currentCount;	// ���� ī��Ʈ
	LONGLONG m_previousCount;	// ���� ī��Ʈ

	float m_frequencyTime;		// ���ļ��� �ð�
	float m_frameTime;			// �����Ӵ� �ð�
	float m_deltaTime;
	float m_oneSecond;

	int m_fps;					// �ʴ� ������ ��

	//>>ĳ���� ������
	DWORD m_dwLastUpdateTime;
	float m_fEllapsedTime;

public:
	void Init(int fps);

	int FPS();
	float StartTime();
	float CurrentTime();
	float DeltaTime();

	bool Update();

	bool UpdateOneSecond();


	//>>ĳ���� ������
	void  ElapsedUpdate();
	float GetElapsedTime();
	float GetLastUpdateTime();
};