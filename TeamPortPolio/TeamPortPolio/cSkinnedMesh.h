#pragma once

class IEntity;
class cSkinnedMesh
{
public:
	cSkinnedMesh();
	~cSkinnedMesh();

protected:
	LPD3DXFRAME m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXMATRIXA16 m_matWorld;

	// >> :
	float m_fBlendTime;
	float m_fPassedBlendTime;
	float m_fPassedTime;
	bool m_isAnimBlend;
	int m_currentIndex;

	// << :

	IEntity* m_pIEntity;
	LPD3DXANIMATIONSET m_currentAnim;
public:
	void Setup(char* szFolder, char* szFile);
	void SetIEntity(IEntity* IEntity) { m_pIEntity = IEntity; }
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);

	void SetAnimationIndexBlend(int nIndex);
	void SetAnimationChange(OUT cSkinnedMesh * pCurrentMesh, IN cSkinnedMesh * pChangeMesh);

	void SetIndex(int index) { m_currentIndex = index; }
	int  Getindex() { return m_currentIndex; }
	LPD3DXANIMATIONSET GetCurrentAnim() { return m_currentAnim; }
	float GetPassedTime() { return m_fPassedTime; }
};

