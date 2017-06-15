#include "stdafx.h"
#include "Melee_State.h"


void Melee_Defence::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_SHEILDBLOCK);
}

void Melee_Defence::OnUpdate(cUnit * pUnit, float deltaTime)
{
	pUnit->FSM()->Play(UNIT_STATE_MELEE_IDLE);
}

void Melee_Defence::OnEnd(cUnit * pUnit)
{
}
