#pragma once
class cFrustum
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

	void PlaneSetup();

};

