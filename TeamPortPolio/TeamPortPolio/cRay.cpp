#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
{
}


cRay::~cRay()
{
}

// ȭ�� Ŭ�� �� ray��ȯ�ϴ� �Լ�
stRay& cRay::CalculatePickingRay(D3DXVECTOR2& cursorPos)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 viewport;
	D3DDevice->GetViewport(&viewport);

	D3DXMATRIX projection;
	D3DDevice->GetTransform(D3DTS_PROJECTION, &projection);

	px = (((2.0f * cursorPos.x) / viewport.Width) - 1.0f) / projection(0, 0);
	py = (((-2.0f * cursorPos.y) / viewport.Height) + 1.0f) / projection(1, 1);

	stRay ray;
	ray.vOrigin = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	ray.vDirection = D3DXVECTOR3(px, py, 1.0f);
	return ray;
}

// ȭ�� Ŭ�� �� �ش� �Ž��� ���˵� ��ġ ��ȯ���ִ� �Լ�
bool cRay::IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT D3DXVECTOR3& collidedPos)
{
	stRay ray = CalculatePickingRay(cursorPos);

	// >> ���� ��ȯ
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	// <<

	BOOL intersect = false;
	DWORD faceIndex = 0;
	float u = 0;
	float v = 0;
	float t = 0;
	for (int i = 0; i < pMesh->GetNumFaces(); i++)
	{
		D3DXIntersect(pMesh, &ray.vOrigin, &ray.vDirection, &intersect, &faceIndex, &u, &v, &t, 0, 0);
		if (intersect)	
		{
			collidedPos = ray.vOrigin + ray.vDirection * t;
			break;
		}
		faceIndex++;
	}

	return intersect;
}

// ȭ�� Ŭ�� �� �ش� �Ž��� ���˵� ������ �ε��� ��ȯ���ִ� �Լ�
bool cRay::IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT int& index, OUT D3DXVECTOR3& outPos, IN float& minX, IN float& maxX)
{
	// �� �ۿ� �ִٸ� �ٷ� false;
	if(!IsMounseInMap(cursorPos, minX, maxX)) return false;

	stRay ray = CalculatePickingRay(cursorPos);

	// >> ���� ��ȯ
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	// <<

	// >> ���� ���� �� �ʱ�ȭ
	BOOL intersect = false;
	DWORD faceIndex = -1;
	float u = 0;
	float v = 0;
	float t = 0;
	// << 

	// >> �Ž��� �浹 �˻�
	for (int i = 0; i < pMesh->GetNumFaces(); i++)
	{
		D3DXIntersect(pMesh, &ray.vOrigin, &ray.vDirection, &intersect, &faceIndex, &u, &v, &t, 0, 0);
		if (intersect)
		{
			index = (int)faceIndex;
			outPos = ray.vOrigin + ray.vDirection * t;
			break;
		}
		faceIndex++;
	}
	// <<

	return intersect;
}

// >> �� �� �𼭸� �׺κ��� �������� �� ���ο� Ŀ���� �ִ��� Ȯ�����ִ� �Լ�
bool cRay::IsMounseInMap(IN D3DXVECTOR2& cursorPos, IN float& minX, IN float& maxX)
{
	stRay ray = CalculatePickingRay(cursorPos);

	// >> ���� ��ȯ
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	//<<
	
	D3DXVECTOR3 v0 = D3DXVECTOR3(minX * -1, 0, maxX * -1);
	D3DXVECTOR3 v1 = D3DXVECTOR3(minX * -1, 0, maxX * +1);
	D3DXVECTOR3 v2 = D3DXVECTOR3(minX * +1, 0, maxX * +1);
	D3DXVECTOR3 v3 = D3DXVECTOR3(minX * +1, 0, maxX * -1);

	if (!D3DXIntersectTri(&v0, &v1, &v2, &ray.vOrigin, &ray.vDirection, 0, 0, 0) &&
		!D3DXIntersectTri(&v0, &v2, &v3, &ray.vOrigin, &ray.vDirection, 0, 0, 0)) return false;

	//v0 = D3DXVECTOR3(minX * -1, -20, maxX * -1);
	//v1 = D3DXVECTOR3(minX * -1, -20, maxX * +1);
	//v2 = D3DXVECTOR3(minX * +1, -20, maxX * +1);
	//v3 = D3DXVECTOR3(minX * +1, -20, maxX * -1);
	//
	//if (D3DXIntersectTri(&v0, &v1, &v2, &ray.vOrigin, &ray.vDirection, 0, 0, 0) ||
	//	D3DXIntersectTri(&v0, &v2, &v3, &ray.vOrigin, &ray.vDirection, 0, 0, 0)) return false;

	return true;
}