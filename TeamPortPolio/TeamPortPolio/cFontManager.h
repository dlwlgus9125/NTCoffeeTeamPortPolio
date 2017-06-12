#pragma once
#include "Singleton.h"

#define FONT cFontManager::GetInstance()

class cFontManager : public Singleton<cFontManager>
{
	map<FONT_TAG, LPD3DXFONT>	m_mapFont;

public:
	LPD3DXFONT GetFont(FONT_TAG e);
	void Destroy();
};

