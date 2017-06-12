#include "stdafx.h"
#include "cUIInventory.h"
#include "cUIItemSlot.h"
#include "cUIScrollBar.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIObject.h"
cUIInventory::cUIInventory()
	:m_pRoot(NULL)
	
	, m_pUIBackBoard(NULL)
	, m_pUIScrollBar(NULL)
{
}

cUIInventory::~cUIInventory()
{
}

void cUIInventory::SetUp()
{
	m_pRoot = new cUIObject();
	SetUpBackBoard(m_pRoot);
	SetUpScrollBar(m_pRoot);
}

cUIObject * cUIInventory::GetRootUI()
{
	return m_pRoot;
}

void cUIInventory::SetUpBackBoard(cUIObject * pRoot)
{
	m_pUIBackBoard = new cUIImageView;
	m_pUIBackBoard->SetFuntion(FUNTION_OPEN);
	m_pUIBackBoard->SetTexture("UI/wholeMapTest.png");
	pRoot->SetMoveRect(ST_SIZEN(pRoot->GetSize().nWidth, 100));
	pRoot->AddChild(m_pUIBackBoard);
}

void cUIInventory::SetUpSlot(cUIObject * pRoot)
{
	
	
}

void cUIInventory::SetUpScrollBar(cUIObject * pRoot)
{
	m_pUIScrollBar = new cUIScrollBar;
	m_pUIScrollBar->SetFuntion(FUNTION_OPEN);
	m_pUIScrollBar->SetTexture("UI/btn-main-menu.png");
	
	RECT rc;
	SetRect(&rc,
			m_pUIBackBoard->GetPosition().x + (m_pUIBackBoard->GetSize().nWidth*0.8),
			m_pUIBackBoard->GetPosition().y + (m_pUIBackBoard->GetSize().nHeight*0.2),
			m_pUIBackBoard->GetPosition().x + m_pUIBackBoard->GetSize().nWidth,
			m_pUIBackBoard->GetPosition().y + (m_pUIBackBoard->GetSize().nHeight*0.8));
	
	m_pUIScrollBar->SetLaneRect(rc);

	pRoot->AddChild(m_pUIScrollBar);
}
