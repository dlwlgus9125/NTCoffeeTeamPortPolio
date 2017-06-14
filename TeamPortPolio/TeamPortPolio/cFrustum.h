#pragma once

#define FRUSTUM cFrustum::Instance()
class cFrustum : public Singleton<cFrustum>
{
public:
	cFrustum();
	~cFrustum();

private:
	vector<D3DXPLANE>   m_vecPlane;

public:
	void Setup();
	void Update();
	bool IsIn(MeshSpere pShere/**/);
	bool cFrustum::IsIn(ST_SPHERE* pSphere);

	void PlaneSetup();

};

