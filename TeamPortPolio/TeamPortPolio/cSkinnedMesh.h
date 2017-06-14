#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cTextureManager;

private:
	//�ϳ��� ����
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;
	// ��ü���� ����
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vForward;
	int                         m_currentIndex;

	//Blend��
	float                       m_fBlendTime;
	float                       m_fPassedBlendTime;
	float                       m_fPassedTime;
	bool                        m_isAnimBlend;

	//���� �ִϸ��̼� ����ð� Ȯ�ο�
	LPD3DXANIMATIONSET m_currentAnim;

	//�浹�� Ȯ�ο�
	D3DXMATRIX      m_colliderMat;
	ST_BONE*        m_colliderBone;
public:
	cSkinnedMesh(cSkinnedMesh* pSkinnedMesh);
	~cSkinnedMesh(void);

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	int  GetIndex() { return m_currentIndex; }
	void SetRandomTrackPosition(); // �׽�Ʈ��
	void SetPosition(D3DXVECTOR3 v, D3DXVECTOR3 dir)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
		m_vForward = dir;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}
	ST_BONE* GetAttackBone()
	{
		return m_colliderBone;
	}
	LPD3DXANIMATIONSET GetCurrentAnim() { return m_currentAnim; }
	float GetPassedTime() { return m_fPassedTime; }
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();

	void ItemCollider(ST_BONE* pBoneCollider);

	void FindBone(ST_BONE* pBone);
	
};

