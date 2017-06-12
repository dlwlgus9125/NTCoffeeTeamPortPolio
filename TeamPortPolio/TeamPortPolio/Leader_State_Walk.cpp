#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Walk::OnBegin(cLeader * pUnit)
{
}

void Leader_State_Walk::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetPath().size() > 0)
	{
		D3DXVECTOR3 LeaderPos = pLeader->GetCharacterEntity()->Pos();
		D3DXVECTOR3 targetPos = ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->Pos();
		targetPos.y = 0;
		LeaderPos.y = 0;

		float distance = MATH->Distance(LeaderPos, targetPos);

		if (distance > 0.5f)
		{
			pLeader->GetCharacterEntity()->Steering()->LeaderArrive(targetPos);
		}
		if (pLeader->GetIndex() == pLeader->GetPath().back())
		{
			pLeader->GetPath().pop_back();
		}

	}
	/*else
	{
		pLeader->FSM()->Play(LEADER_STATE_STATE_IDLE);
	}*/

	
}

void Leader_State_Walk::OnEnd(cLeader * pUnit)
{
}

void Leader_State_Walk::StateChanger(cLeader * pUnit)
{
}
