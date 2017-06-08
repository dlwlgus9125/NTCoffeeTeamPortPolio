#pragma once

class cUICursor
{
private:

	HCURSOR m_Cursor[3];
public:
	cUICursor();
	~cUICursor();

	void SetupCursor();
	void Update_Cursosr();


};
