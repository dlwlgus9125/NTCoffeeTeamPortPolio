#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "cFrustum.h"
class cPlayer :
	public cCharacter
{
private:
	ISteeringEntity*  m_unitLeader;//부대이동을 담당할 멤버변수
	vector<cUnit*> m_vectorUnit;
	vector<D3DXVECTOR3> m_RectOffest;
	vector<D3DXVECTOR3> m_TriOffest;
	cFrustum*      m_frustum;
	float          m_fRotY;


public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	void AddUnit(cUnit* pUnit);//부대 추가
	void DeleteUnit(int key);

	void SetRectOffset();
	void SetTriOffset();


	//Scene에서 부대 이동을 관리할 겟함수
	IEntity*       GetUnitLeader() { return m_unitLeader; }
	vector<cUnit*> GetUnits() { return m_vectorUnit; }

	
};

