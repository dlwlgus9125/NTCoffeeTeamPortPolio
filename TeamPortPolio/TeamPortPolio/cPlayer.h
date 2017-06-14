#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "cFrustum.h"
#include "Player_State.h"

enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_WALK,
	PLAYER_STATE_ATTACK,
	PLAYER_STATE_DEFENCE,
};

class cLeader;
class Player_State;
class cSkinnedMesh;

class cPlayer :
	public cCharacter
{
private:
	cLeader*       m_unitLeader;//부대이동을 담당할 멤버변수
	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;

	// 상태머신에 사용될 변수
	cStateMachine<cPlayer*>* m_pFsm;
	D3DXVECTOR3 m_charPostion;
	D3DXVECTOR3 m_charForward;

public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();


	//Scene에서 부대 이동을 관리할 겟함수
	cLeader*       GetUnitLeader() { return m_unitLeader; }

	// 추가
	cStateMachine<cPlayer*>* FSM() { return m_pFsm; }
	D3DXVECTOR3 GetPosition() { return m_charPostion; }
	D3DXVECTOR3 GetForWard() { return m_charForward; }
};

