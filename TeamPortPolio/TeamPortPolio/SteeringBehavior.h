#pragma once
#include "IEntity.h"

class cUnit;
// �����ൿ�� ó���ϴ� Ŭ����
class SteeringBehavior
{
	IEntity* m_pEntity;

	D3DXVECTOR3 m_force;				// ���������� �߻��� �������� ��
	float m_forceMultiplier;			// �������� �����ִ� ��
	float m_maxForce;					// �ִ� ������

	D3DXVECTOR3 m_wander;			// ��ȸ ����

public:
	SteeringBehavior(IEntity* pEntity, float maxForce = 2, float forceMultiplier = 200);

	IEntity* Entity();

	void AddForce(D3DXVECTOR3 force);

	//m_force += force;


// ���������� �ӵ� ����� ����
	void UpdateVelocity(float deltaTime);

	// ã�� : ��ǥ���� ã�ư��� �������� �ջ�
	void Seek(D3DXVECTOR3 targetPos);
	// ���ϱ� : ��ǥ�����κ��� �־����� �������� �ջ�
	void Flee(D3DXVECTOR3 targetPos);

	// ���� : ��ǥ������ �����ϴ� �������� �ջ�
	void Arrive(D3DXVECTOR3 targetPos);

	// ���� : �δ밡 ��ǥ������ 
	void LeaderArrive(D3DXVECTOR3 targetPos);

	// ���� : ������ ��ǥ������ 
	void UnitArrive(D3DXVECTOR3 targetPos);
	// �߰�
	void Pursuit(IEntity* pTarget);

	// ����
	void Evade(IEntity* pTarget);

	// ��ȸ
	void Wander(float distance, float radius, float jitter);

	// ��ֹ� ȸ��
	void AvoidObstacle(IEntity* pObstacle);

	// ��ֹ� ȸ�� (����)
	void AvoidObstacle(vector<cUnit*> obstacles);

	// ��ħ ����
	void ConstrainOverlap(IEntity* pTarget);

	// ��ħ ����
	void ConstrainOverlap(vector<IEntity*> targets);

	void OffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset);

	// �� �̵�
	/*void FollowPath(Grid& grid, vector<int>& path, float seekDistance)
	{
		if (path.size() == 0) return;

		Vector targetPos = grid.TilePos(path.back());

		if (path.size() > 1)
		{
			Seek(targetPos);

			if (MATH->SqrDistance(Entity()->Pos(), targetPos) < seekDistance * seekDistance)
			{
				path.pop_back();
			}
		}
		else
		{
			Arrive(targetPos);

			if (MATH->SqrDistance(Entity()->Pos(), targetPos) < 20)
			{
				path.pop_back();
				m_force = Vector(0, 0);
				Entity()->SetVelocity(Vector(0, 0));
			}
		}
	}*/
};