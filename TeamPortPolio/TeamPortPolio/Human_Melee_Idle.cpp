#include "stdafx.h"
#include "Human_Melee_State.h"

void Human_Melee_Idle::OnBegin(cUnit * pUnit)
{

}

void Human_Melee_Idle::OnUpdate(cUnit * pUnit, float deltaTime)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	float distance = MATH->Distance(pUnit->GetCharacterEntity()->Pos(), targetPos);

	if (distance > 0.1f)
	{
		pUnit->FSM()->Play(UNIT_STATE_MELEE_WALK);
	}
	else
	{
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		switch (pUnit->GetMode())
		{
		case FIGHTING_MODE: if ((FG_STATE)pUnit->GetMesh()->GetIndex() != FG_READYATTACK)
			pUnit->GetMesh()->SetAnimationIndexBlend(FG_READYATTACK); break;
		case DEFENDING_MODE:if ((FG_STATE)pUnit->GetMesh()->GetIndex() != FG_STAND)
			pUnit->GetMesh()->SetAnimationIndexBlend(FG_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;

}

void Human_Melee_Idle::OnEnd(cUnit * pUnit)
{
}
