#pragma once
class cObject;
class IEntity;
class cLeader;
#define OBJECT  cObjectManager::Instance()



class cObjectManager : public Singleton<cObjectManager>
{
	vector<cObject*> m_vecObject;
	vector<IEntity*> m_vecEntity;
	vector<cLeader*> m_vecEnemyLeader;
	cObject*         m_player;
	
public:


	void Init();
	void Update(float deltaTime);
	void Render();
	void Release();

	void AddEntity(IEntity* entity);
	void AddObject(cObject* object);
	void SetPlayer(cObject* player) { m_player = player; }

	vector<IEntity*> GetEntities() { return m_vecEntity; }

	cObject* GetPlayer() { return m_player; }
};

