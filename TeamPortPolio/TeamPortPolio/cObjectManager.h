#pragma once

class cObject;
class cUnit;
class cPlayer;
class cLeader;
class cSkinnedMesh;


class IEntity;
#define OBJECT  cObjectManager::Instance()



class cObjectManager : public Singleton<cObjectManager>
{
	vector<cObject*> m_vecObject;
	vector<IEntity*> m_vecEntity;
	vector<cLeader*> m_vecEnemyLeader;
	cPlayer*         m_player;
	
	queue<cSkinnedMesh*> m_queFootman;


public:


	void Init();
	void Update(float deltaTime);
	void Render();
	void Release();

	void AddEntity(IEntity* entity);
	void AddObject(cObject* object);
	void SetPlayer(cPlayer* player) { m_player = player; }

	vector<IEntity*> GetEntities() { return m_vecEntity; }

	cPlayer* GetPlayer() { return m_player; }

	cSkinnedMesh* GetFootman();

	void AddArmy();
};

