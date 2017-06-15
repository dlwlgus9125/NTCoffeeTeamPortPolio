#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"

void Leader_State_Idle::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)pLeader->GetUnits()[i]->FSM()->Play(UNIT_STATE_MELEE_IDLE);
	}
}

void Leader_State_Idle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetTargetObject()!=NULL)
	{
		pLeader->FSM()->Play(LEADER_STATE_PURSUIT);
	}
	else if (pLeader->GetPath().size() > 0)
	{
		pLeader->FSM()->Play(LEADER_STATE_WALK);
	}
}

void Leader_State_Idle::OnEnd(cLeader * pUnit)
{
}
