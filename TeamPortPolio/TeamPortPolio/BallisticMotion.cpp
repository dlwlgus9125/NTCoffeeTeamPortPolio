#include "stdafx.h"
#include "BallisticMotion.h"
#include "IEntity.h"

BallisticMotion::BallisticMotion(IEntity * entity, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vTarget) :
	m_pEntity(entity)
	, m_vTarget(vTarget)
	,m_vOrigin(vOrigin)

{
	m_stSphere.fRadius = entity->Radius();
	m_stSphere.vCenter = entity->Pos();
	m_stSphere.vCenter.y = entity->Pos().y + 1;
}

BallisticMotion::~BallisticMotion()
{
}

void BallisticMotion::UpdatevPos()
{
	if (Entity()->Pos().y < -1)return;

	D3DXVECTOR3 vToTarget = m_vTarget - m_vOrigin;

	float fdistance = D3DXVec3Length(&(vToTarget));
	float maxHeight = fdistance*COS45;

	SetUpSpeedMultiplier(fdistance);
	vToTarget.y = maxHeight - m_fGravity*m_speedMultiplier*2;
	m_fGravity += maxHeight / TIME->FPS();
	
	Entity()->SetForward(vToTarget);
	float speed = m_speedMultiplier*fdistance / (TIME->FPS());

	Entity()->AddPos(speed*Entity()->Forward());
	m_stSphere.vCenter = Entity()->Pos();
}

void BallisticMotion::SetUpSpeedMultiplier(float distance)
{
	if (distance < 10)m_speedMultiplier = 8;
	else if (distance > 30)m_speedMultiplier = 2;
	else m_speedMultiplier = 4;
}
