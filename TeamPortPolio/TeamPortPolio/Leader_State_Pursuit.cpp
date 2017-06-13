#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"

void Leader_State_Pursuit::OnBegin(cLeader * pUnit)
{

}

void Leader_State_Pursuit::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetTargetObject() == NULL)
	{
		pLeader->FSM()->Play(LEADER_STATE_STATE_IDLE);
	}


}

void Leader_State_Pursuit::OnEnd(cLeader * pUnit)
{
}
