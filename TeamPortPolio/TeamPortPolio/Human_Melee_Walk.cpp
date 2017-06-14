#include "stdafx.h"
#include "Human_Melee_State.h"

void Human_Melee_Walk::OnBegin(cUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
}

void Human_Melee_Walk::OnUpdate(cUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	
	targetPos.y = 0;
	D3DXVECTOR3 pos = pUnit->GetCharacterEntity()->Pos();
	pos.y = 0;
	float distance = MATH->Distance(pos, targetPos);

	if (distance > 0.1f)
	{
		pUnit->GetCharacterEntity()->Steering()->OffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		
	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());		
		pUnit->FSM()->Play(UNIT_STATE_MELEE_IDLE);	
	}


	
}

void Human_Melee_Walk::OnEnd(cUnit * pUnit)
{
}

void Human_Melee_Walk::StateChanger(cUnit * pUnit)
{
	if (pUnit->GetMesh()->GetIndex() != FG_BATTLEWALK&&0.002f <= pUnit->GetCharacterEntity()->Speed() && pUnit->GetCharacterEntity()->Speed() <= 0.05f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
	}
	else if (pUnit->GetMesh()->GetIndex() != FG_BATTLERUN&&0.05f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLERUN);
	}/*
	else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	}*/
}
