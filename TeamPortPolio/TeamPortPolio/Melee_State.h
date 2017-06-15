#pragma once
#include "cUnit.h"
//enum UNIT_STATE
//{
//	UNIT_Melee_STATE_IDLE,
//	UNIT_Melee_STATE_WALK,
//	UNIT_Melee_STATE_ATTACK,
//	UNIT_Melee_STATE_DEFENCE,
//};
class Melee_Idle : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

};

class Melee_Walk : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);
};

class Melee_Battle : public IState<cUnit*>
{
	cObject* BattleTarget;
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);

	void StateChanger(cUnit * pUnit);

	void FindTarget(cUnit * pUnit);

	void FindNearTarget(cUnit * pUnit);

	void Charge(cUnit * pUnit);

	void Battle(cUnit * pUnit);

	void BattleWithTarget(cUnit* pUnit);
};

class Melee_Defence : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);
};


class Melee_Death : public IState<cUnit*>
{
public:
	void OnBegin(cUnit* pUnit);

	void OnUpdate(cUnit* pUnit, float deltaTime);

	void OnEnd(cUnit* pUnit);
};
