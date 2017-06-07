#pragma once
#include "cUnit.h"
//enum UNIT_STATE
//{
//	UNIT_STATE_STATE_IDLE,
//	UNIT_STATE_STATE_WALK,
//	UNIT_STATE_STATE_ATTACK,
//	UNIT_STATE_STATE_DEFENCE,
//};
class Human_State_Idle : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

};

class Human_State_Walk : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);
};

class Human_State_Attack : public IState<cUnit*>
{
	float fPassedTime;
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);
};

class Human_State_Defence : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);
};

