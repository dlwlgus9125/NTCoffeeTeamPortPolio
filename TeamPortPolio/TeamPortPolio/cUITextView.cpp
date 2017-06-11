#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
	: m_dwDrawTextFormat(DT_LEFT | DT_TOP)
	, m_dwTextColor(D3DCOLOR_XRGB(0, 0, 0))
{
}


cUITextView::~cUITextView()
{
	m_pFont->Release();
}


void cUITextView::SetText(string Text)
{
	m_sText = Text;
}

string cUITextView::GetText()
{
	return m_sText;
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	D3DXVECTOR3 pos;
	if (m_Funtion == FUNTION_OPEN)pos = m_vPosition;
	else  pos = m_vPosition + m_pParent->GetPosition();


	RECT rc;
	SetRect(&rc, (int)pos.x, (int)pos.y, (int)pos.x + ((int)m_stSize.nWidth)*m_fScaleX, (int)pos.y + ((int)m_stSize.nHeight)*m_fScaleX);
	SetUpFont(20,25);

	m_pFont->DrawText(NULL, GetText().c_str(), GetText().length(), &rc, m_dwDrawTextFormat, m_dwTextColor);

	SAFE_RELEASE(m_pFont);
}

void cUITextView::SetUpFont(float width,float height)
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	fd.Height = height;
	fd.Width = width;
	fd.Weight = FW_BOLD;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "±¼¸²Ã¼");

	D3DXCreateFontIndirect(D3DDevice, &fd, &m_pFont);
}

