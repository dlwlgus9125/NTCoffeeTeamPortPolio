#include "stdafx.h"
#include "Human_Melee_State.h"


void Human_State_Defence::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndex(F_SHEILDBLOCK);
}

void Human_State_Defence::OnUpdate(cUnit * pUnit, float deltaTime)
{
	pUnit->FSM()->Play(UNIT_STATE_STATE_IDLE);
}

void Human_State_Defence::OnEnd(cUnit * pUnit)
{
}
