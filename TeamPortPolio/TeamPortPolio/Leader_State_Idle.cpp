#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"
#include "cPlayer.h"

void Leader_State_Idle::OnBegin(cLeader * pUnit)
{

}

void Leader_State_Idle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetPath().size() > 0)
	{
		pLeader->FSM()->Play(LEADER_STATE_STATE_WALK);
	}
}

void Leader_State_Idle::OnEnd(cLeader * pUnit)
{
}
