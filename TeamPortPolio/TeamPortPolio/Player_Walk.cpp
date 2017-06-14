#include "stdafx.h"
#include "Player_State.h"

void Player_Walk::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndex(P_WALK);
	
}

void Player_Walk::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	if (INPUT->IsKeyPress(VK_SHIFT))
	{
		pPlayer->GetMesh()->SetAnimationIndex(P_RUN);
	}
	else if (INPUT->IsKeyPress(VK_S))
	{
		pPlayer->GetMesh()->SetAnimationIndex(P_BACKWALK);
	}
	else
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}

	if (pPlayer->GetCharacterEntity()->Speed() <= 0.0f)
	{
		pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
	}

}

void Player_Walk::OnEnd(cPlayer* pPlayer)
{

}

void Player_Walk::StateChanger(cPlayer * pPlayer)
{
// 모드 추가할것.
}