#include "stdafx.h"
#include "Melee_State.h"
#include "cLeader.h"

void Melee_Battle::OnBegin(cUnit * pUnit)
{
	//FindTarget(pUnit);
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLERUN);
}

void Melee_Battle::OnUpdate(cUnit * pUnit, float deltaTime)
{
	if (BattleTarget == NULL)
	{
		Charge(pUnit);
	}
	else
	{
		D3DXVECTOR3 thisPos = pUnit->GetCharacterEntity()->Pos();

		D3DXVECTOR3 targetPos = BattleTarget->GetCharacterEntity()->Pos();

		float distance = MATH->Distance(thisPos, targetPos);

		if (distance > 1.0f)
		{
			pUnit->GetCharacterEntity()->Steering()->UnitArrive(targetPos);
			pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

			FindNearTarget(pUnit);
		}
		else
		{
			if (((cCharacter*)BattleTarget)->IsDeath() == true)
			{
				if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
				{
					pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
				}
				BattleTarget = NULL;
				FindNearTarget(pUnit);
			}
			else if (((cCharacter*)BattleTarget)->GetMesh()->GetIndex() != FG_DEATH)
			{
				BattleWithTarget(pUnit);
			}
		}
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}
}

void Melee_Battle::OnEnd(cUnit * pUnit)
{
	pUnit->SetTargetObject(NULL);
}

void Melee_Battle::StateChanger(cUnit * pUnit)
{
	FG_STATE state;

}

//자신과 충돌한 적을 찾는 함수
void Melee_Battle::FindTarget(cUnit * pUnit)
{
	for (int i = 0; i < ((cLeader*)pUnit->GetTargetObject())->GetUnits().size(); i++)
	{
		if (((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->IsDeath() == false)
		{
			if (MATH->IsCollided(((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->GetArrangeSphere(), pUnit->GetArrangeSphere()))
			{
				BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i];
			}
		}
	}
}
//자신과 제일 가까운 적을 찾는 함수
void Melee_Battle::FindNearTarget(cUnit * pUnit)
{
	if (TIME->UpdateOneSecond() == true)
	{
		D3DXVECTOR3 nextTargetPos, prevTargetPos;
		D3DXVECTOR3 pos = pUnit->GetCharacterEntity()->Pos();
		for (int i = 1; i < ((cLeader*)pUnit->GetTargetObject())->GetUnits().size(); i++)
		{
			if (((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->IsDeath() == false)
			{
				prevTargetPos = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i - 1]->GetCharacterEntity()->Pos();
				nextTargetPos = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i]->GetCharacterEntity()->Pos();

				if (MATH->Distance(pos, prevTargetPos) > MATH->Distance(pos, nextTargetPos))
				{
					BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i];
				}
				else
				{
					BattleTarget = ((cLeader*)pUnit->GetTargetObject())->GetUnits()[i - 1];
				}
			}
		}
	}
}

void Melee_Battle::Charge(cUnit * pUnit)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(D3DXVECTOR3((pUnit->GetOffset().x + (pUnit->GetOffset().z*0.5F)), 0, 0), pUnit->GetLeader()->Forward());

	D3DXVECTOR3 thisPos = pUnit->GetCharacterEntity()->Pos();

	D3DXVECTOR3 targetPos = worldOffset + pUnit->GetLeader()->Pos() - pUnit->GetLeader()->Forward();

	float distance = MATH->Distance(thisPos, targetPos);

	if (distance > 1.0f)
	{
		pUnit->GetCharacterEntity()->Steering()->UnitArrive(targetPos);
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		FindTarget(pUnit);
	}
	else
	{
		FindNearTarget(pUnit);
	}
}

void Melee_Battle::Battle(cUnit * pUnit)
{
}

void Melee_Battle::BattleWithTarget(cUnit * pUnit)
{
	if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	{
		D3DXVECTOR3 dir = BattleTarget->GetCharacterEntity()->Pos() - pUnit->GetCharacterEntity()->Pos();
		D3DXVec3Normalize(&dir, &dir);
		pUnit->GetCharacterEntity()->SetForward(dir);

		switch (pUnit->GetMesh()->GetIndex())
		{
		case FG_ATTACK1:
			pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK2);
			break;
		default:
			pUnit->GetMesh()->SetAnimationIndexBlend(FG_ATTACK1);
			break;
		}

		if (MATH->IsCollided(pUnit->GetAttackCollider(), ((cCharacter*)BattleTarget)->GetSphere()))
		{
			switch (pUnit->Fight(pUnit, (cCharacter*)BattleTarget))
			{
			case FIGHT_AVOID:((cCharacter*)BattleTarget)->GetMesh()->SetAnimationIndexBlend(FG_SHEILDBLOCK); break;
			case FIGHT_BLOCK:((cCharacter*)BattleTarget)->GetMesh()->SetAnimationIndexBlend(FG_SHEILDBLOCK); break;
			case FIGHT_HIT:((cCharacter*)BattleTarget)->GetMesh()->SetAnimationIndexBlend(FG_HIT); break;
			}
		}
	}
}

