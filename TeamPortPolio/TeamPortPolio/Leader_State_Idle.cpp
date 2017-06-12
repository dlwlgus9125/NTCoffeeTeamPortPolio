#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"
#include "cPlayer.h"

void Leader_State_Idle::OnBegin(cLeader * pUnit)
{

}

void Leader_State_Idle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	
	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		/*for (int i = 0; i < ASTAR->GetGraph()->NodeCount(); i++)
		{
			*/
			/*	if (cRay::RaySphereIntersect(INPUT->GetMousePosVector2(), ASTAR->GetGraph()->GetNode(i)->GetMesh(), ASTAR->GetGraph()->GetNode(0)->Pos().x, ASTAR->GetGraph()->GetNode(149)->Pos().x))
				{*/
					pLeader->SetTargetIndex(OBJECT->GetPlayer()->GetUnitLeader()->GetIndex());
						cout << "index : " << pLeader->GetIndex() << endl;
					if (pLeader->GetIndex() != pLeader->GetTargetIndex())
					{
						pLeader->SetPath(ASTAR->GetPath(pLeader->GetIndex(), pLeader->GetTargetIndex()));
						//break;
					}
					
				//}			
		//}
	}
	if (pLeader->GetPath().size() > 0)
	{
		pLeader->FSM()->Play(LEADER_STATE_STATE_WALK);
	}
}

void Leader_State_Idle::OnEnd(cLeader * pUnit)
{
}
