#include "stdafx.h"
#include "Player_State.h"


void Player_Attack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndex(P_ATTACK1);
}

void Player_Attack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	StateChanger(pPlayer);
	P_STATE state;

	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK1)
		{
			state = P_ATTACK2;
		}
		else if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK2)
		{
			state = P_ATTACK3;
		}
		else if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK3)
		{
			state = P_ATTACK1;
		}

		pPlayer->GetMesh()->SetAnimationIndex(state);
	}
}

void Player_Attack::OnEnd(cPlayer* pPlayer)
{
}

void Player_Attack::StateChanger(cPlayer * pPlayer)
{
	if (INPUT->IsKeyPress(VK_W) ||
		INPUT->IsKeyPress(VK_A) ||
		INPUT->IsKeyPress(VK_S) ||
		INPUT->IsKeyPress(VK_D) &&
		INPUT->IsMouseDown(MOUSE_LEFT))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}
}