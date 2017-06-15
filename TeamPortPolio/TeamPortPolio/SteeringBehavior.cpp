#include "stdafx.h"
#include "SteeringBehavior.h"
#include "cUnit.h"

SteeringBehavior::SteeringBehavior(IEntity* pEntity, float maxForce, float forceMultiplier)
{
	m_pEntity = pEntity;
	m_force = D3DXVECTOR3(0, 0, 0);
	m_forceMultiplier = forceMultiplier;
	m_maxForce = maxForce;
}

IEntity* SteeringBehavior::Entity() { return m_pEntity; }

void SteeringBehavior::AddForce(D3DXVECTOR3 force)
{
	float currentForce = MATH->Magnitude(m_force);
	float remainedForce = m_maxForce - currentForce;
	if (remainedForce > 0)
	{
		if ((MATH->Magnitude(force)) < remainedForce)
		{
			m_force += force;
		}
		else
		{
			D3DXVec3Normalize(&force, &force);
			m_force += force *remainedForce;
		}
	}

	//m_force += force;
}

// ���������� �ӵ� ����� ����
void SteeringBehavior::UpdateVelocity(float deltaTime)
{
	m_force = MATH->Clamp(m_force, 0, m_maxForce) * m_forceMultiplier;
	D3DXVECTOR3 acceleration = m_force / Entity()->Mass();
	D3DXVECTOR3 velocity = Entity()->Velocity() + acceleration * deltaTime;
	Entity()->SetVelocity(velocity);
	Entity()->SetForward(velocity);

	m_force = D3DXVECTOR3(0, 0, 0);
}

// ã�� : ��ǥ���� ã�ư��� �������� �ջ�
void SteeringBehavior::Seek(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 targetDir;
	D3DXVec3Normalize(&targetDir, &(targetPos - Entity()->Pos()));
	D3DXVECTOR3 targetVelocity = targetDir * Entity()->MaxSpeed();
	AddForce(targetVelocity - Entity()->Velocity());
}

// ���ϱ� : ��ǥ�����κ��� �־����� �������� �ջ�
void SteeringBehavior::Flee(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 targetDir;
	D3DXVec3Normalize(&targetDir, &(Entity()->Pos() - targetPos));
	D3DXVECTOR3 targetVelocity = targetDir * Entity()->MaxSpeed();
	AddForce(targetVelocity - Entity()->Velocity());
}

// ���� : ��ǥ������ �����ϴ� �������� �ջ�
void SteeringBehavior::Arrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	float distance = MATH->SqrMagnitude(vToTarget);
	//cout << "distance : " << distance << endl;
	if (distance > EPSILON)
	{

		D3DXVECTOR3 prevPos = Entity()->Pos();
		D3DXVECTOR3 movePos = Entity()->Pos();
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &vToTarget);
		Entity()->SetForward(dir);
		movePos += MATH->Clamp( Entity()->Forward()*distance*0.003f, 0.015f, 0.4f);
		//cout << 0.005f*distance << endl;
		Entity()->SetPos(movePos);
		/*const float multiplier = 2;
		float speed = MATH->Min(distance * multiplier, Entity()->MaxSpeed());
		D3DXVECTOR3 targetVelocity;
		D3DXVec3Normalize(&vToTarget, &vToTarget);
		targetVelocity = vToTarget*speed;
		AddForce(targetVelocity - Entity()->Velocity());*/
		//cout << "targetVelocity : " << targetVelocity.x << ", " << targetVelocity.y << ", " << targetVelocity.z << endl;
		//cout << MATH->SqrMagnitude(movePos - prevPos)*100 << endl;
		Entity()->SetSpeed(MATH->SqrMagnitude(movePos - prevPos)*100);
	
	}


}
void SteeringBehavior::LeaderArrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vPos = Entity()->Pos();
	
	D3DXVECTOR3 vToTarget = targetPos - vPos;
	float distance = MATH->SqrMagnitude(vToTarget);
	if (distance > EPSILON)
	{

		D3DXVECTOR3 prevPos = Entity()->Pos();
		D3DXVECTOR3 movePos = Entity()->Pos();
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &vToTarget);
		Entity()->SetForward(dir);
		movePos += MATH->Clamp(Entity()->Forward()*0.04f, 0.005f, 0.4f);
		//cout << 0.005f*distance << endl;
		Entity()->SetPos(movePos);
		Entity()->SetSpeed(MATH->SqrMagnitude(movePos - prevPos) * 100);

	}
}

void SteeringBehavior::UnitArrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vPos = Entity()->Pos();

	D3DXVECTOR3 vToTarget = targetPos - vPos;
	float distance = MATH->SqrMagnitude(vToTarget);
	if (distance > EPSILON)
	{
		D3DXVECTOR3 prevPos = Entity()->Pos();
		D3DXVECTOR3 movePos = Entity()->Pos();
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &vToTarget);
		Entity()->SetForward(dir);
		movePos += MATH->Clamp(Entity()->Forward()*0.05f, 0.005f, 0.4f)+ Entity()->Forward()*distance*0.000005f;
		//cout << 0.005f*distance << endl;
		Entity()->SetPos(movePos);
		Entity()->SetSpeed(MATH->SqrMagnitude(movePos - prevPos) * 100);
	}
}

// �߰�
void SteeringBehavior::Pursuit(IEntity* pTarget)
{
	D3DXVECTOR3 vToTarget = pTarget->Pos() - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float lookAheadTime = distance / (Entity()->MaxSpeed() + pTarget->MaxSpeed());
	Seek(pTarget->Pos() + pTarget->Velocity() * lookAheadTime);
}

// ����
void SteeringBehavior::Evade(IEntity* pTarget)
{
	D3DXVECTOR3 vToTarget = pTarget->Pos() - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float lookAheadTime = distance / (Entity()->MaxSpeed() + pTarget->MaxSpeed());
	Flee(pTarget->Pos() + pTarget->Velocity() * lookAheadTime);
}

// ��ȸ
void SteeringBehavior::Wander(float distance, float radius, float jitter)
{
	/*float randomX = MATH->Random(-1.0f, 1.0f) * jitter;
	float randomY = MATH->Random(-1.0f, 1.0f) * jitter;
	m_wander += Vector(randomX, randomY);
	m_wander = m_wander.Normalize() * radius;

	Vector targetPos = Entity()->Pos() + Entity()->Forward() * distance + m_wander;
	AddForce(targetPos - Entity()->Pos());*/
}

// ��ֹ� ȸ��
void SteeringBehavior::AvoidObstacle(IEntity* pObstacle)
{
	//if (Entity()->Velocity().SqrMagnitude() < EPSILON) return;

	//float sensingLength = Entity()->Speed();
	//float expandRadius = Entity()->Radius() + pObstacle->Radius();
	//float breakingForceWeight = 0.005f;

	//Vector localPos = MATH->WorldToLocal(pObstacle->Pos() - Entity()->Pos(), Entity()->Forward());

	//// �������� & ��ֹ� �浹 üũ
	//if (localPos.x > EPSILON && localPos.x - pObstacle->Radius() < sensingLength
	//	&& abs(localPos.y) < expandRadius)
	//{
	//	// �浹 ��ġ ���
	//	float A = sqrt(expandRadius * expandRadius - localPos.y * localPos.y);
	//	float collidedX = localPos.x - A;

	//	// ������
	//	float breakingForce = -(sensingLength - collidedX) * breakingForceWeight;

	//	// �������� ���
	//	float overlappedY = expandRadius - abs(localPos.y);
	//	float lateralForce = (localPos.y > 0) ? -overlappedY : overlappedY;

	//	AddForce(MATH->LocalToWorld(Vector(breakingForce, lateralForce), Entity()->Forward()));
	//}
}

// ��ֹ� ȸ�� (����)
void SteeringBehavior::AvoidObstacle(vector<cUnit*> obstacles)
{
	////if (MATH->SqrMagnitude( Entity()->Velocity().SqrMagnitude() < EPSILON) return;
	//float sensingLength = Entity()->Speed();

	//float closestX = 999999.9f;
	//IEntity* closestEntity = NULL;

	//for (int i = 0; i < obstacles.size(); i++)
	//{
	//	float expandRadius = Entity()->Radius() + obstacles[i]->GetCharacterEntity()->Radius();
	//	D3DXVECTOR3 localPos = MATH->WorldToLocal(obstacles[i]->GetCharacterEntity()->Pos() - Entity()->Pos(), Entity()->Forward());

	//	// �������� & ��ֹ� �浹 üũ
	//	if (localPos.x > EPSILON && localPos.x - obstacles[i]->Radius() < sensingLength
	//		&& abs(localPos.y) < expandRadius)
	//	{
	//		// �浹 ��ġ ���
	//		float A = sqrt(expandRadius * expandRadius - localPos.y * localPos.y);
	//		float collidedX = localPos.x - A;

	//		if (collidedX < closestX)
	//		{
	//			closestX = collidedX;
	//			closestEntity = obstacles[i];
	//		}
	//	}
	//}

	//if (closestEntity != NULL)
	//{
	//	AvoidObstacle(closestEntity);
	//}
}

// ��ħ ����
void SteeringBehavior::ConstrainOverlap(IEntity* pTarget)
{
	if (pTarget->IsDeath() == false)
	{
		D3DXVECTOR3 vEntity = pTarget->Pos() - Entity()->Pos();
		float distance = MATH->Magnitude(vEntity);
		float totalRadius = Entity()->Radius() + pTarget->Radius();

		if (distance < totalRadius)
		{
			D3DXVec3Normalize(&vEntity, &vEntity);
			pTarget->AddPos(vEntity * (distance)*0.01f);
		}
	}
}

// ��ħ ����
void SteeringBehavior::ConstrainOverlap(vector<IEntity*> targets)
{
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i]->IsDeath() == false)
		{
			ST_SPHERE thisSphere(Entity()->Pos(), Entity()->Radius());
			ST_SPHERE itSphere(targets[i]->Pos(), targets[i]->Radius());
			if (MATH->IsCollided(thisSphere, itSphere))
			{
				D3DXVECTOR3 pushDir = MATH->GetOverlappedVector(thisSphere, itSphere);
				Entity()->SetPos(Entity()->Pos() - pushDir);
				ConstrainOverlap(targets[i]);
			}
		}
	}
}

void SteeringBehavior::OffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(offset, pLeader->Forward());
	D3DXVECTOR3 targetPos = pLeader->Pos() + worldOffset;
	targetPos.y=0;
	float distance = MATH->Distance(Entity()->Pos(), targetPos);
	float arrivalTime = distance / Entity()->MaxSpeed();
	Arrive(targetPos + pLeader->Velocity() * arrivalTime);

	/*cout << "worldOffset : " << worldOffset.x << ", " << worldOffset.y << ", " << worldOffset.z << endl;
	cout << "targetPos : " << targetPos.x << ", " << targetPos.y << ", " << targetPos.z << endl;
	*/
}