#include "stdafx.h"
#include "Math.h"

Math::Math() { srand(time(NULL)); }
float Math::Magnitude(D3DXVECTOR3 vec) { return D3DXVec3Length(&vec); }
float Math::SqrMagnitude(D3DXVECTOR3 vec) { return	D3DXVec3LengthSq(&vec); }
float Math::Min(float a, float b) { return (a < b) ? b : a; }
float Math::Max(float a, float b) { return (a > b) ? b : a; }
float Math::Clamp(float num, float min, float max)
{
	if (num < min)return min;
	if (num > max)return max;
	else return num;
}
float Math::Distance(D3DXVECTOR3 from, D3DXVECTOR3 to) { return D3DXVec3Length(&(to - from)); }
float Math::SqrDistance(D3DXVECTOR3 from, D3DXVECTOR3 to) { return D3DXVec3LengthSq(&(to - from)); }


float Math::GetRotY(D3DXVECTOR3 dir)
{
	return atan2(-dir.x, -dir.z);
}
D3DXVECTOR3 Math::Nomalize(D3DXVECTOR3 vec) { D3DXVECTOR3 Nomal; D3DXVec3Normalize(&Nomal, &vec); return Nomal; }

D3DXVECTOR3 Math::Clamp(D3DXVECTOR3 v, float min, float max)
{
	D3DXVECTOR3 Nomal;
	Nomal = Nomalize(v);

	float vLength = Magnitude(v);
	float vMinLenth = Magnitude(Nomal*min);
	float vMaxLenth = Magnitude(Nomal*max);

	if (vLength < vMinLenth) { return Nomal*min; }
	if (vLength > vMaxLenth) { return Nomal*max; }
	else { return v; }

}

bool Math::IsCollided(ST_SPHERE c0, ST_SPHERE c1)
{
	float totalRadius = c0.fRadius + c1.fRadius;
	return Distance(c0.vCenter, c1.vCenter) <= totalRadius;
}

bool Math::IsCollided(MeshSpere c0, MeshSpere c1)
{
	float totalRadius = c0.m_radius + c1.m_radius;
	return Distance(c0.m_vCenter, c1.m_vCenter) <= totalRadius;
}


// 원과 원의 겹쳐진 벡터 반환
D3DXVECTOR3 Math::GetOverlappedVector(ST_SPHERE from, ST_SPHERE to)
{
	if (!IsCollided(from, to)) return D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Length = to.vCenter - from.vCenter;
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir, &Length);
	float magnitude = Magnitude(Length);
	float length = (from.fRadius + to.fRadius) - magnitude;
	return dir * length;
}


D3DXVECTOR3 Math::LocalToWorld(D3DXVECTOR3 local, D3DXVECTOR3 forward)
{
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationY(&matR, MATH->GetRotY(forward));
	D3DXMatrixTranslation(&matT, local.x, local.y, local.z);

	D3DXVECTOR3 localToWorld;
	matWorld = matR*matT;
	D3DXVec3TransformCoord(&localToWorld, &local, &matR);
	return localToWorld;
}