#include "stdafx.h"
#include "Player_State.h"

void Player_Walk::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_WALK);

}

void Player_Walk::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	D3DXVECTOR3 prevPos = pPlayer->GetCharacterEntity()->Pos();
	D3DXVECTOR3 movePos = pPlayer->GetCharacterEntity()->Pos();
	float rotY = 0.0f;
	if (INPUT->IsKeyPress(VK_W))
	{
		movePos += pPlayer->GetCharacterEntity()->Forward() * 0.03;
		if (INPUT->IsKeyPress(VK_SHIFT))
		{
			movePos += pPlayer->GetCharacterEntity()->Forward() * 0.03;
		}
	}
	else if (INPUT->IsKeyPress(VK_S))
	{
		movePos -= pPlayer->GetCharacterEntity()->Forward() * 0.03;
	}
	pPlayer->GetCharacterEntity()->SetPos(movePos);
	


	StateChanger(pPlayer, prevPos, movePos);

	if (MATH->Distance(prevPos, movePos) <= 0.0f)
	{
		pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
	}

}

void Player_Walk::OnEnd(cPlayer* pPlayer)
{

}

void Player_Walk::StateChanger(cPlayer * pPlayer, D3DXVECTOR3 prevPos, D3DXVECTOR3 movePos)
{
	if (0.001f <= MATH->Distance(prevPos, movePos) && MATH->Distance(prevPos, movePos) <= 0.04f)
	{
		if(pPlayer->GetMesh()->GetIndex()!=P_WALK)pPlayer->GetMesh()->SetAnimationIndexBlend(P_WALK);
	}
	else if (0.04f < MATH->Distance(prevPos, movePos))
	{
		if (pPlayer->GetMesh()->GetIndex() != P_RUN)pPlayer->GetMesh()->SetAnimationIndexBlend(P_RUN);
	}
}

void Player_Walk::Move(cPlayer * pPlayer)
{
}

