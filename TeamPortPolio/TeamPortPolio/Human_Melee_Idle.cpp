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

	if (distance > 0.1f)
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_WALK);
	}
	else
	{
		switch (pUnit->GetMode())
		{
		case FIGHTING_MODE: if ((FOOTMAN_STATE)pUnit->GetMesh()->GetIndex() != F_READYATTACK)
			pUnit->GetMesh()->SetAnimationIndex(F_READYATTACK); break;
		case DEFENDING_MODE:if ((FOOTMAN_STATE)pUnit->GetMesh()->GetIndex() != F_STAND)
			pUnit->GetMesh()->SetAnimationIndex(F_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;
	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		if (cRay::RaySphereIntersect(INPUT->GetMousePosVector2(), pUnit->GetMeshSphere(), x,x2))
		{
			cout << "index : " << pUnit->GetCharacterEntity()->UniqueID() << endl;
		}
	}
}

void Human_State_Idle::OnEnd(cUnit * pUnit)
{
}
