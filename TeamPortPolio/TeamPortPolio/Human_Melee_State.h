#pragma once
#include "cUnit.h"
//enum UNIT_STATE
//{
//	UNIT_Melee_STATE_IDLE,
//	UNIT_Melee_STATE_WALK,
//	UNIT_Melee_STATE_ATTACK,
//	UNIT_Melee_STATE_DEFENCE,
//};
class Human_Melee_Idle : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

};

class Human_Melee_Walk : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);
};

class Human_Melee_Battle : public IState<cUnit*>
{
	float fPassedTime;
	cObject* BattleTarget;
	FG_STATE currentAttackIndex;
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);

	void FindTarget(cUnit * pUnit);

	void FindNearTarget(cUnit * pUnit);
	
};

class Human_Melee_Defence : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);
};

