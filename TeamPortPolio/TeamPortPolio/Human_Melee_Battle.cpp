#include "stdafx.h"
#include "Human_Melee_State.h"
#include "cLeader.h"

void Human_Melee_Battle::OnBegin(cUnit * pUnit)
{
	//FindTarget(pUnit);
	fPassedTime = 0.0f;
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLERUN);
	currentAttackIndex = FG_ATTACK1;
}

void Human_Melee_Battle::OnUpdate(cUnit * pUnit, float deltaTime)
{
	if (BattleTarget == NULL)
	{
		FindTarget(pUnit);

		D3DXVECTOR3 worldOffset = MATH->LocalToWorld(D3DXVECTOR3((pUnit->GetOffset().x + (pUnit->GetOffset().z*0.5F)), 0, 0), pUnit->GetLeader()->Forward());

		D3DXVECTOR3 dirToTarget = pUnit->GetTargetObject()->GetCharacterEntity()->Pos();
		D3DXVECTOR3 thisPos = pUnit->GetCharacterEntity()->Pos();

		D3DXVec3Normalize(&dirToTarget, &dirToTarget);
		D3DXVECTOR3 targetPos = ((cLeader*)pUnit->GetTargetObject())->GetCharacterEntity()->Pos() + worldOffset +(((cLeader*)pUnit->GetTargetObject())->GetCharacterEntity()->Forward()*10.0f);

		float distance = MATH->Distance(thisPos, targetPos);

		if (distance > 0.5f)
		{
			pUnit->GetCharacterEntity()->Steering()->UnitArrive(targetPos);
			pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		}
		else
		{
			FindNearTarget(pUnit);
		}
	}
	else
	{
		
		D3DXVECTOR3 dirToTarget = BattleTarget->GetCharacterEntity()->Pos();
		D3DXVECTOR3 thisPos = pUnit->GetCharacterEntity()->Pos();

		D3DXVec3Normalize(&dirToTarget, &dirToTarget);
		D3DXVECTOR3 targetPos = BattleTarget->GetCharacterEntity()->Pos();

		float distance = MATH->Distance(thisPos, targetPos);

		if (distance > 2.0f)
		{
			pUnit->GetCharacterEntity()->Steering()->UnitArrive(targetPos);
			pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
			FindNearTarget(pUnit);
		}
		else
		{

			if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
			{
				D3DXVECTOR3 dir = BattleTarget->GetCharacterEntity()->Pos() - pUnit->GetCharacterEntity()->Pos();
				D3DXVec3Normalize(&dir, &dir);
				pUnit->GetCharacterEntity()->SetForward(dir);

				if (pUnit->GetMesh()->GetIndex() != FG_ATTACK1)pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK1);
				else if (pUnit->GetMesh()->GetIndex() == FG_ATTACK1)pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK2);
				//else if (pUnit->GetMesh()->GetIndex() == FG_ATTACK2)pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK3);
			}
		}
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}
}

void Human_Melee_Battle::OnEnd(cUnit * pUnit)
{
}

void Human_Melee_Battle::StateChanger(cUnit * pUnit)
{
	FG_STATE state;
	//if (INPUT->IsMouseDown(MOUSE_LEFT))
	//{
	//	if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK1) { state = F_ATTACK2; fPassedTime = 0.0f; }
	//	else if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK2) { state = F_ATTACK3; fPassedTime = 0.0f; }
	//	else if ((FOOTMAN_STATE)pUnit->GetMesh()->Getindex() == F_ATTACK3) { state = F_ATTACK1; fPassedTime = 0.0f; }
	//	//else { state = F_READYATTACK; }
	//	if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	//	{
	//		pUnit->GetMesh()->SetAnimationIndexBlendBlend(state);
	//	}
	//}
	//else if (INPUT->IsMouseDown(MOUSE_RIGHT))
	//{
	//	pUnit->FSM()->Play(UNIT_Melee_STATE_DEFENCE);
	//}
	//else if (!INPUT->IsMouseDown(MOUSE_LEFT)&& fPassedTime> pUnit->GetMesh()->GetCurrentAnim()->GetPeriod()-0.005f)
	//{
	//	//pUnit->GetMesh()->SetAnimationIndexBlendBlend(F_READYATTACK);
	//	pUnit->FSM()->Play(UNIT_Melee_STATE_WALK);
	//}
	//cout << pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() << endl;
}

//자신과 충돌한 적을 찾는 함수
void Human_Melee_Battle::FindTarget(cUnit * pUnit)
{
	for (int i = 0; i < ((cLeader*)pUnit->GetTargetObject())->GetUnits().size(); i++)
	{
		if (MATH->IsCollided(((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->GetArrangeSphere(), pUnit->GetArrangeSphere()))
		{
			BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i];
		}
	}
}
//자신과 제일 가까운 적을 찾는 함수
void Human_Melee_Battle::FindNearTarget(cUnit * pUnit)
{
	D3DXVECTOR3 nextTargetPos, prevTargetPos;
	D3DXVECTOR3 pos = pUnit->GetCharacterEntity()->Pos();
	BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[0];
	for (int i = 1; i < ((cLeader*)pUnit->GetTargetObject())->GetUnits().size(); i++)
	{
	prevTargetPos = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i-1]->GetCharacterEntity()->Pos();
	nextTargetPos = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->GetCharacterEntity()->Pos();

	if (MATH->Distance(pos, prevTargetPos) > MATH->Distance(pos, nextTargetPos))
	{
		if (BattleTarget == NULL) 
		{ 
			
				BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i];
			
		}
		else
		{
			if (BattleTarget != ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i])
			{
				
					BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i];
				
			}
		}
	}
	
	}
}

