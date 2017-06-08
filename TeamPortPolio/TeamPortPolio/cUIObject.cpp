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
	if (!m_isHidden)   MoveWindow();
	for each(auto c in m_vecChild)
	{
		if (m_isHidden&&c->GetFuntion() == FUNTION_OPEN
			||c->GetFuntion() == FUNTION_LIFE_BAR)	c->Update();
		else if (!m_isHidden&&c->GetFuntion() != FUNTION_OPEN)	c->Update();
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	
	for each(auto c in m_vecChild)
	{
		if (m_isHidden && (c->GetFuntion() == FUNTION_OPEN 
			|| c->GetFuntion()==FUNTION_LIFE_BAR)) { c->Render(pSprite); }
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
}

void cUIObject::SetSize(int x, int y)
{
	m_stSize.nWidth = x;
	m_stSize.nHeight = y;
}


void cUIObject::MoveWindow()
{
	POINT pt = INPUT->GetMousePos();

	RECT rc;
	SetRect(&rc, m_vPosition.x, m_vPosition.y, m_vPosition.x + m_MoveRect.nWidth, m_vPosition.y + m_MoveRect.nHeight);
	
	if (PtInRect(&rc, pt) && INPUT->IsMouseDown(MOUSE_LEFT))m_isMove = true;
	else if (INPUT->IsMouseUp(MOUSE_LEFT)) m_isMove = false;

	if (m_isMove)m_vPosition += INPUT->GetMouseDeltaInVector3();
}
