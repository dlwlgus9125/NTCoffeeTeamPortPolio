#include "stdafx.h"
#include "cFontManager.h"

LPD3DXFONT cFontManager::GetFont(FONT_TAG e)
{
	if (m_mapFont.find(e) != m_mapFont.end()) return m_mapFont[e];

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (e == FONT_DEF)
	{
		fd.Height = 16;									// height�� width�� �ٲٸ� �۾� ũ�Ⱑ �ٲ�
		fd.Width = 8;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "����ü");				// ����ü ���� ����
	}

	if (e == FONT_SHOP)
	{
		fd.Height = 10;									// height�� width�� �ٲٸ� �۾� ũ�Ⱑ �ٲ�
		fd.Width = 5;
		fd.Weight = FW_NORMAL;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "����ü");				// ����ü ���� ����
	}


	D3DXCreateFontIndirect(D3DDevice, &fd, &m_mapFont[e]);
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}