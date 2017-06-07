#include "stdafx.h"
#include "Human_Melee_State.h"

void Human_State_Idle::OnBegin(cUnit * pUnit)
{
	
}

void Human_State_Idle::OnUpdate(cUnit * pUnit, float deltaTime)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	float distance = MATH->Distance(pUnit->GetCharacterEntity()->Pos(), targetPos);

	if (distance > 0.3f)
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_WALK);
	}
	else
	{
		if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() != F_READYATTACK)pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	}

	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_ATTACK);
	}
	else if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_DEFENCE);
	}
}

void Human_State_Idle::OnEnd(cUnit * pUnit)
{
}
