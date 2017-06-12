#include "stdafx.h"
#include "cUIChractorView.h"
#include"cUIImageView.h"
#include "cUITextView.h"
#include "cUILifeBar.h"
cUIChractorView::cUIChractorView()
	:m_pRoot(NULL)
	,m_pCharactorFace(NULL)
	,m_pLifeBar(NULL)
{
}

cUIChractorView::~cUIChractorView()
{
}
void cUIChractorView::SetUpFace(cUIObject* pRoot)
{
	m_pCharactorFace = new cUIImageView;
	m_pCharactorFace->SetPosition(0, 0);
	m_pCharactorFace->SetFuntion(FUNTION_LIFE_BAR);
	m_pCharactorFace->SetTexture("UI/btn-main-menu.png");
	pRoot->AddChild(m_pCharactorFace);
}
void cUIChractorView::SetUpLifeBar(cUIObject* pRoot)
{
	m_pLifeBar = new cUILifeBar;
	m_pLifeBar->SetPosition(m_pCharactorFace->GetSize().nWidth, 0);
	m_pLifeBar->SetFuntion(FUNTION_LIFE_BAR);
	m_pLifeBar->SetTexture("UI/btn-med-over.png");
	pRoot->AddChild(m_pLifeBar);
}


cUIObject * cUIChractorView::GetRootUI()
{
	return m_pRoot;
}

void cUIChractorView::SetUp()
{
	m_pRoot = new cUIObject;
	m_pRoot->SetPosition(0, 0);
	SetUpFace(m_pRoot);
	SetUpLifeBar(m_pRoot);
}

