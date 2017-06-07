#include "stdafx.h"
#include "Human_Melee_State.h"

void Human_State_Walk::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(F_BATTLEWALK);
}

void Human_State_Walk::OnUpdate(cUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	float distance = MATH->Distance(pUnit->GetCharacterEntity()->Pos(), targetPos);

	if (distance > 0.2f)
	{
		pUnit->GetCharacterEntity()->Steering()->OffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());		
		pUnit->FSM()->Play(UNIT_STATE_STATE_IDLE);	
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

void Human_State_Walk::OnEnd(cUnit * pUnit)
{
}

void Human_State_Walk::StateChanger(cUnit * pUnit)
{
	if (pUnit->GetMesh()->Getindex() != F_BATTLEWALK&&0.005f <= pUnit->GetCharacterEntity()->Speed() && pUnit->GetCharacterEntity()->Speed() <= 0.5f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(F_BATTLEWALK);
	}
	else if (pUnit->GetMesh()->Getindex() != F_BATTLERUN&&0.5f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(F_BATTLERUN);
	}
	else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	}
}
