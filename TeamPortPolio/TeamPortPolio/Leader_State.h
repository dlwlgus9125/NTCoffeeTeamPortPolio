#pragma once
#include "cLeader.h"
//enum UNIT_STATE
//{
//	UNIT_STATE_STATE_IDLE,
//	UNIT_STATE_STATE_WALK,
//	UNIT_STATE_STATE_ATTACK,
//	UNIT_STATE_STATE_DEFENCE,
//};
class Leader_State_Idle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);

};

class Leader_State_Walk : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);

	void StateChanger(cLeader * pLeader);
};

class Leader_State_Pursuit : public IState<cLeader*>
{
	float fPassedTime;
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);

};

class Leader_State_Defence : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

