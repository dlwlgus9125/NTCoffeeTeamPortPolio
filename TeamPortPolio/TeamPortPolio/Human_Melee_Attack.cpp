#include "stdafx.h"
#include "Human_Melee_State.h"


void Human_State_Attack::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK1);
	fPassedTime = 0.0f;
}

void Human_State_Attack::OnUpdate(cUnit * pUnit, float deltaTime)
{
	fPassedTime += deltaTime;
	StateChanger(pUnit);
}

void Human_State_Attack::OnEnd(cUnit * pUnit)
{
}

void Human_State_Attack::StateChanger(cUnit * pUnit)
{
	FG_STATE state;
	//if (INPUT->IsMouseDown(MOUSE_LEFT))
	//{
	//	if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK1) { state = F_ATTACK2; fPassedTime = 0.0f; }
	//	else if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK2) { state = F_ATTACK3; fPassedTime = 0.0f; }
	//	else if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK3) { state = F_ATTACK1; fPassedTime = 0.0f; }
	//	//else { state = F_READYATTACK; }
	//	if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	//	{
	//		pUnit->GetMesh()->SetAnimationIndexBlendBlend(state);
	//	}
	//}
	//else if (INPUT->IsMouseDown(MOUSE_RIGHT))
	//{
	//	pUnit->FSM()->Play(UNIT_STATE_STATE_DEFENCE);
	//}
	//else if (!INPUT->IsMouseDown(MOUSE_LEFT)&& fPassedTime> pUnit->GetMesh()->GetCurrentAnim()->GetPeriod()-0.005f)
	//{
	//	//pUnit->GetMesh()->SetAnimationIndexBlendBlend(F_READYATTACK);
	//	pUnit->FSM()->Play(UNIT_STATE_STATE_WALK);
	//}
	//cout << pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() << endl;
}
