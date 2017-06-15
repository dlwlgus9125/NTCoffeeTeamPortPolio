#include "stdafx.h"
#include "Melee_State.h"

void Melee_Idle::OnBegin(cUnit * pUnit)
{

}

void Melee_Idle::OnUpdate(cUnit * pUnit, float deltaTime)
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
		case FIGHTING_MODE: pUnit->GetMesh()->SetAnimationIndexBlend(FG_READYATTACK); break;
		case DEFENDING_MODE:pUnit->GetMesh()->SetAnimationIndexBlend(FG_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;

}

void Melee_Idle::OnEnd(cUnit * pUnit)
{
}
