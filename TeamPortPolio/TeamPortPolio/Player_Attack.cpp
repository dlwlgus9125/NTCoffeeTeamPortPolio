#include "stdafx.h"
#include "Player_State.h"


void Player_Attack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_ATTACK1);
}

void Player_Attack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
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

		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.4f)
		{
			if (pPlayer->GetMesh()->GetIndex() != state)pPlayer->GetMesh()->SetAnimationIndexBlend(state);
		}

	}

	else if (INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_S))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}


	else
	{
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.25f)
		{
			pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
		}

	}

}

void Player_Attack::OnEnd(cPlayer* pPlayer)
{
}
