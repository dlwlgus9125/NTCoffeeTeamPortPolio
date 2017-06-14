#include "stdafx.h"
#include "Player_State.h"

void Player_Idle::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_STAND);
}

void Player_Idle::OnUpdate(cPlayer* pPlayer, float deltaTime)
{

	if (INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_A))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}

	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_ATTACK);
	}

}

void Player_Idle::OnEnd(cPlayer* pPlayer)
{

}
