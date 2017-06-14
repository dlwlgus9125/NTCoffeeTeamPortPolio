#include "stdafx.h"
#include "Player_State.h"


void Player_Attack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_ATTACK1);
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

		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod())
		{
			if (pPlayer->GetMesh()->GetIndex() != state)pPlayer->GetMesh()->SetAnimationIndexBlend(state);
		}
	}
	else
	{
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() + 0.2f)
		{
			pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
		}
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
		INPUT->IsKeyPress(VK_D))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}
}