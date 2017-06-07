#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_vPosition(0, 0, 0)
	, m_pParent(NULL)
	, m_stSize(0, 0)
	, m_isHidden(true)
	, m_isMove(false)
	, m_isNextPage(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cUIObject::~cUIObject()
{
}

void cUIObject::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void cUIObject::AddChild(cUIObject* pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}

void cUIObject::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		if (m_Funtion != FUNTION_OPEN)
		{
			m_matWorld._41 += m_pParent->m_matWorld._41;
			m_matWorld._42 += m_pParent->m_matWorld._42;
			m_matWorld._43 += m_pParent->m_matWorld._43;
		}
	}

	if (!m_isHidden)   MoveWindow();
	for each(auto c in m_vecChild)
	{
		if (m_isHidden&&c->GetFuntion() == FUNTION_OPEN)	c->Update();
		else if (!m_isHidden&&c->GetFuntion() != FUNTION_OPEN)	c->Update();
	}


}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	for each(auto c in m_vecChild)
	{
		if (m_isHidden && (c->GetFuntion() == FUNTION_OPEN)) { c->Render(pSprite); }
		else if (!m_isHidden) { c->Render(pSprite); }
	}
}

void cUIObject::Destroy()
{
	m_isHidden = true;

	for each(auto c in m_vecChild)
	{
		c->Destroy();
	}
	this->Release();
}

void cUIObject::SetSize(int x, int y)
{
	m_stSize.nWidth = x;
	m_stSize.nHeight = y;
}


void cUIObject::MoveWindow()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd,&pt);

	RECT rc;
	rc.left = m_vPosition.x;
	rc.right = m_vPosition.x + m_MoveRect.nWidth;
	rc.top = m_vPosition.y;
	rc.bottom = m_vPosition.y + m_MoveRect.nHeight;

	m_CursorPos = pt;
	

	if (m_isMove)
	{
		m_vPosition.x += (m_CursorPos.x - m_PrevCursorPos.x);
		m_vPosition.y += (m_CursorPos.y - m_PrevCursorPos.y);
	}

	m_PrevCursorPos = m_CursorPos;
	
	if (PtInRect(&rc, pt) &&GetKeyState(VK_LBUTTON) & 0x8000)m_isMove = true;
	else m_isMove = false;
}
