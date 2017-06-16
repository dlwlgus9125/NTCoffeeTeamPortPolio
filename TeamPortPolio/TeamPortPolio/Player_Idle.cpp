#include "stdafx.h"
#include "Player_State.h"

void Player_Idle::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_STAND);
}

void Player_Idle::OnUpdate(cPlayer* pPlayer, float deltaTime)
{

	if (INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_S))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}
	
	if (INPUT->IsMouseDown(MOUSE_LEFT) || INPUT->IsMousePress(MOUSE_LEFT))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_ATTACK);
	}

	if (INPUT->IsKeyPress(MOUSE_RIGHT))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_DEFENCE);
	}
	
}

void Player_Idle::OnEnd(cPlayer* pPlayer)
{

}
