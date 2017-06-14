#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include <cmath>
#include <time.h>

#define MATH				Math::Instance()


class Math : public Singleton<Math>
{
public:
	Math();

	D3DXVECTOR3 Nomalize(D3DXVECTOR3 vec);

	float Magnitude(D3DXVECTOR3 vec);
	float SqrMagnitude(D3DXVECTOR3 vec);
	float Min(float a, float b);
	float Max(float a, float b);
	float Clamp(float num, float min, float max);

	float Distance(D3DXVECTOR3 from, D3DXVECTOR3 to);
	float SqrDistance(D3DXVECTOR3 from, D3DXVECTOR3 to);


	float GetRotY(D3DXVECTOR3 dir);
	D3DXVECTOR3 Clamp(D3DXVECTOR3 v, float min, float max);
	bool IsCollided(ST_SPHERE c0, ST_SPHERE c1);
	bool IsCollided(MeshSpere c0, MeshSpere c1);


	// ���� ���� ������ ���� ��ȯ
	D3DXVECTOR3 GetOverlappedVector(ST_SPHERE from, ST_SPHERE to);
	D3DXVECTOR3 LocalToWorld(D3DXVECTOR3 local, D3DXVECTOR3 forward);


};