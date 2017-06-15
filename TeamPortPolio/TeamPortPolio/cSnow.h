#pragma once

class cSnow
{
	vector<ST_PC_VERTEX>	m_vecParticleVertex;

public:
	cSnow();
	~cSnow();

	void Setup();
	void Update();
	void Render();
};