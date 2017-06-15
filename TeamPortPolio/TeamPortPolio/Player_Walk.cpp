#include "stdafx.h"
#include "Player_State.h"

void Player_Walk::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_WALK);

}

void Player_Walk::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	bool isMove = true;

	if (isMove == true)
	{
		Move(pPlayer);
	}

	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		isMove = false;

		pPlayer->FSM()->Play(PLAYER_STATE_ATTACK);
	}
}

void Player_Walk::OnEnd(cPlayer* pPlayer)
{

}

void Player_Walk::StateChanger(cPlayer * pPlayer, D3DXVECTOR3 prevPos, D3DXVECTOR3 movePos)
{
	if (INPUT->IsKeyPress(VK_W) && 0.001f <= MATH->Distance(prevPos, movePos) && MATH->Distance(prevPos, movePos) <= 0.04f)
	{
		if (pPlayer->GetMesh()->GetIndex() != P_WALK)pPlayer->GetMesh()->SetAnimationIndexBlend(P_WALK);
	}
	else if (INPUT->IsKeyPress(VK_S))
	{
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_WALK);
	}
	else if (INPUT->IsKeyPress(VK_SHIFT) && 0.04f < MATH->Distance(prevPos, movePos))
	{
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_RUN);
	}
}

void Player_Walk::Move(cPlayer * pPlayer)
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
	if (INPUT->IsKeyPress(VK_S))
	{
		movePos -= pPlayer->GetCharacterEntity()->Forward() * 0.03;
	}

	pPlayer->GetCharacterEntity()->SetPos(movePos);

	StateChanger(pPlayer, prevPos, movePos);

	if (MATH->Distance(prevPos, movePos) == 0.0f)
	{
		pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
	}
}

