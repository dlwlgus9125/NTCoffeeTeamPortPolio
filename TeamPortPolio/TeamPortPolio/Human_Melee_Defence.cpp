#include "stdafx.h"
#include "Human_Melee_State.h"


void Human_State_Defence::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(F_SHEILDBLOCK);
}

void Human_State_Defence::OnUpdate(cUnit * pUnit, float deltaTime)
{
	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_ATTACK);
	}
	else if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_WALK);
	}

}

void Human_State_Defence::OnEnd(cUnit * pUnit)
{
}
