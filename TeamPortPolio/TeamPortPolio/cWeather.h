#pragma once

class cWeather
{
	vector<ST_PC_VERTEX>	m_vecParticleVertex;

public:
	cWeather();
	~cWeather();

	void Setup(int count);
	void Update(float fMove, float fSpeed);
	void Render(char* sFullPath);
};