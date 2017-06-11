#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Idle::OnBegin(cLeader * pUnit)
{

}

void Leader_State_Idle::OnUpdate(cLeader * pUnit, float deltaTime)
{
	/*D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	float distance = MATH->Distance(pUnit->GetCharacterEntity()->Pos(), targetPos);

	if (distance > 0.5f)
	{
		pUnit->FSM()->Play(UNIT_STATE_STATE_WALK);
	}
	else
	{
		switch (pUnit->GetMode())
		{
		case FIGHTING_MODE: if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() != F_READYATTACK)
			pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK); break;
		case DEFENDING_MODE:if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() != F_STAND)
			pUnit->GetMesh()->SetAnimationIndexBlend(F_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;
	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		if (cRay::RaySphereIntersect(INPUT->GetMousePosVector2(), pUnit->GetMeshSphere(), x, x2))
		{
			cout << "index : " << pUnit->GetCharacterEntity()->UniqueID() << endl;
		}
	}*/
}

void Leader_State_Idle::OnEnd(cLeader * pUnit)
{
}
