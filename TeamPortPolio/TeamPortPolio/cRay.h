#pragma once

struct stRay
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDirection;

	stRay() : vOrigin(0,0,0), vDirection(0,0,0){}
};

class cRay
{

public:
	cRay();
	~cRay();

	static stRay& CalculatePickingRay(D3DXVECTOR2& cursorPos);
	static bool IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT D3DXVECTOR3& collidedPos);
	static bool IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT int& index, OUT D3DXVECTOR3& outPos, IN float& minX, IN float& maxX);
	static bool IsMounseInMap(IN D3DXVECTOR2& cursorPos, IN float& minX, IN float& maxX);
};

