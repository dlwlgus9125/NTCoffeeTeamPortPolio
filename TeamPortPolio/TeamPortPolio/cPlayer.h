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
	cLeader*       m_unitLeader;//�δ��̵��� ����� �������
	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;


public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	

	//Scene���� �δ� �̵��� ������ ���Լ�
	cLeader*       GetUnitLeader() { return m_unitLeader; }
	void           SetUnitLeaderTargetIndex(int index);
	
};

