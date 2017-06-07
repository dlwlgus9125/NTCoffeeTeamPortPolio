#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
	: m_dwDrawTextFormat(DT_LEFT | DT_TOP)
	, m_dwTextColor(D3DCOLOR_XRGB(0, 0, 0))
{
	SetUpFont();
}


cUITextView::~cUITextView()
{
	m_pFont->Release();
}


void cUITextView::SetText(string Text)
{
	m_vecText.push_back(Text);
}

string cUITextView::GetText(bool Pageofnext)
{
	if(Pageofnext)
	{
		return m_vecText.back();
	}
	else return m_vecText.front();
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;
	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWidth, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	m_pFont->DrawText(NULL, GetText(m_pParent->m_isNextPage).c_str(), GetText(m_pParent->m_isNextPage).length(), &rc, m_dwDrawTextFormat, m_dwTextColor);

	//cUIObject::Render(pSprite);
}

void cUITextView::SetUpFont()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	fd.Height = 25;
	fd.Width = 12;
	fd.Weight = FW_BOLD;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "±¼¸²Ã¼");

	D3DXCreateFontIndirect(D3DDevice, &fd, &m_pFont);
}

