#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"

void Leader_State_Battle::OnBegin(cLeader * pLeader)
{
	//pLeader->SetPath(ASTAR->GetPath(pLeader->GetIndex(), pLeader->GetTargetIndex()));
	//>>전투 시작과 동시에 휘하 유닛에게 상대 부대 id를 넘김
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
		pLeader->GetUnits()[i]->FSM()->Play(UNIT_STATE_MELEE_BATTLE);
	}
		
	
}

void Leader_State_Battle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetTargetObject() == NULL)
	{
		pLeader->FSM()->Play(LEADER_STATE_STATE_IDLE);
	}
	D3DXVECTOR3 pos = pLeader->GetCharacterEntity()->Pos();
	D3DXVECTOR3 targetPos = pLeader->GetTargetObject()->GetCharacterEntity()->Pos()+ pLeader->GetTargetObject()->GetCharacterEntity()->Forward();

	
	float distance = MATH->Distance(pos, targetPos);

	if (distance > 0.5f)
	{
		pLeader->GetCharacterEntity()->Steering()->LeaderArrive(targetPos);
		//pLeader->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}




	//else if (((cCharacter*)pLeader->GetTargetObject())->GetIndex() != pLeader->GetTargetIndex())
	//{
	//	pLeader->PathClear();
	//	pLeader->SetTargetIndex(((cCharacter*)pLeader->GetTargetObject())->GetIndex());
	//	//pLeader->SetPath(ASTAR->GetPath(pLeader->GetIndex(), pLeader->GetTargetIndex()));
	//}
	//else if (pLeader->GetPath().size() > 0)
	//{

	//	D3DXVECTOR3 LeaderPos = pLeader->GetCharacterEntity()->Pos();
	//	D3DXVECTOR3 targetPos = ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->Pos();
	//	//targetPos.y = 0;
	//	//LeaderPos.y = 0;

	//	float distance = MATH->Distance(LeaderPos, targetPos);

	//	if (distance > 0.01f)
	//	{

	//		pLeader->GetCharacterEntity()->Steering()->LeaderArrive(targetPos);

	//		if (MATH->IsCollided(pLeader->GetSphere(), ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->GetSphere()))
	//		{
	//			//cout << "Path Back : " << pLeader->GetPath().back() << endl;
	//			vector<int> n_path = pLeader->GetPath();
	//			n_path.pop_back();
	//			pLeader->SetPath(n_path);
	//			cout << "pop!" << endl;
	//		}
	//	}

	//}
	//else if (MATH->IsCollided(pLeader->GetSphere(), ASTAR->GetGraph()->GetNode(pLeader->GetTargetIndex())->GetSphere()))
	//{
	//	pLeader->GetPath().clear();
	//	D3DXVECTOR3 pos = ASTAR->GetGraph()->GetNode(pLeader->GetIndex())->Pos();//pLeader->GetCharacterEntity()->Pos();
	//	D3DXVECTOR3 targetpos = ASTAR->GetGraph()->GetNode(pLeader->GetTargetIndex())->Pos();
	//	cout << "clear!" << endl;
	//	pLeader->FSM()->Play(LEADER_STATE_STATE_IDLE);
	//}


}

void Leader_State_Battle::OnEnd(cLeader * pUnit)
{
}
