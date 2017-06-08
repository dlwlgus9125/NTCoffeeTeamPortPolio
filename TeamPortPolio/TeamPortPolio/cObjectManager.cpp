#include "stdafx.h"
#include "cObjectManager.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
//#include "IEntity.h"



void cObjectManager::Init()
{
	m_player = new cPlayer(D3DXVECTOR3(0, 0, 0), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	m_player->Init();
	m_vecObject.push_back(m_player);

	/*cLeader* pEnemy = new cLeader(D3DXVECTOR3(0, 0, 50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pEnemy->Init();
	m_vecObject.push_back(pEnemy);
	m_vecEnemyLeader.push_back(pEnemy);*/
}

void cObjectManager::Update(float deltaTime)
{
	//m_player->Update(deltaTime);
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(deltaTime);
	}
}

void cObjectManager::Render()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Render();
	}
}

void cObjectManager::Release()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		delete m_vecObject[i];
	}
	m_vecObject.clear();
}

void cObjectManager::AddEntity(IEntity * entity)
{
	m_vecEntity.push_back(entity);
}

void cObjectManager::AddObject(cObject * object)
{
	m_vecObject.push_back(object);
}
