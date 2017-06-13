#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "cFrustum.h"

class cLeader;
class cSkinnedMesh;

class cPlayer :
	public cCharacter
{
private:
	cLeader*       m_unitLeader;//부대이동을 담당할 멤버변수
	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;


public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	

	//Scene에서 부대 이동을 관리할 겟함수
	cLeader*       GetUnitLeader() { return m_unitLeader; }
	void           SetUnitLeaderTargetIndex(int index);
	
};

