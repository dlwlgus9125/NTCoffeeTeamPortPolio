#include "stdafx.h"
#include "Human_Melee_State.h"


void Human_Melee_Defence::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_SHEILDBLOCK);
}

void Human_Melee_Defence::OnUpdate(cUnit * pUnit, float deltaTime)
{
	pUnit->FSM()->Play(UNIT_STATE_MELEE_IDLE);
}

void Human_Melee_Defence::OnEnd(cUnit * pUnit)
{
}
