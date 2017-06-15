#pragma once
class IEntity;
class BallisticMotion
{
public:
	BallisticMotion(IEntity * entity,D3DXVECTOR3 vOrigin,D3DXVECTOR3 vtarget);
	~BallisticMotion();
	void UpdatevPos();
	IEntity* Entity() { return m_pEntity; }
	ST_SPHERE m_stSphere;
private:
	D3DXVECTOR3 m_vOrigin;
	D3DXVECTOR3 m_vTarget;
	float m_fGravity;; // 중력적용을 위한값.
	IEntity* m_pEntity;
	int m_speedMultiplier;

	void SetUpSpeedMultiplier(float distance);
};
