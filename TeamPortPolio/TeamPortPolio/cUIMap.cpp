#include "stdafx.h"
#include "cUIMap.h"
#include "cUIButton.h"
#include "cUIImageView.h"
#include "cUITextView.h"
cUIMap::cUIMap()
	:m_pMapImage(NULL)
	,m_pButtonClose(NULL)
	,m_pButtonOpen(NULL)
	,m_pRoot(NULL)
{

}

cUIMap::~cUIMap()
{

}

void cUIMap::SetUpOpenButton(cUIObject* pRoot)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pButtonOpen = new cUIButton;
	m_pButtonOpen->SetFuntion(FUNTION_OPEN);
	m_pButtonOpen->SetPosition(rc.left, rc.bottom - 30);
	m_pButtonOpen->SetTexture("UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png");
	
	cUITextView* pText = new cUITextView;
	pText->SetText("¿­±â");
	pText->SetSize(m_pButtonOpen->GetSize());
	pText->SetPosition(rc.left, rc.bottom - 30);
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetFuntion(m_pButtonOpen->GetFuntion());
	pRoot->AddChild(m_pButtonOpen);
	pRoot->AddChild(pText);
}
void cUIMap::SetUpCloseButton(cUIObject* pRoot)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pButtonClose = new cUIButton;
	m_pButtonClose->SetFuntion(FUNTION_CLOSE);
	m_pButtonClose->SetTexture("UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png");
	
	D3DXVECTOR3 pos = D3DXVECTOR3(m_pMapImage->GetPosition().x + m_pMapImage->GetSize().nWidth - m_pButtonClose->GetSize().nWidth
		, m_pMapImage->GetPosition().y + m_pMapImage->GetSize().nHeight - m_pButtonClose->GetSize().nHeight, 0);

	m_pButtonClose->SetPosition(pos);
	cUITextView* pText = new cUITextView;
	pText->SetText("´Ý±â");
	pText->SetPosition(m_pButtonClose->GetPosition());
	pText->SetSize(m_pButtonClose->GetSize());
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetFuntion(FUNTION_CLOSE);
	
	pRoot->AddChild(m_pButtonClose);
	pRoot->AddChild(pText);

}
void cUIMap::SetUpMapImage(cUIObject* pRoot)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pMapImage = new cUIImageView;
	m_pMapImage->SetFuntion(FUNTION_OK);
	m_pMapImage->SetTexture("UI/wholeMapTest.png");
	m_pRoot->SetMoveRect(ST_SIZEN(m_pMapImage->GetSize().nWidth, 100));
	pRoot->AddChild(m_pMapImage);
}

void cUIMap::SetUp()
{
	m_pRoot = new cUIObject;	
	SetUpMapImage(m_pRoot);
	SetUpOpenButton(m_pRoot);
	SetUpCloseButton(m_pRoot);
}

cUIObject * cUIMap::GetRootUI()
{
	return m_pRoot; 
}

cUIImageView * cUIMap::GetMapImage()
{
	return m_pMapImage;
}

void cUIMap::SetMapImage(char* szFullPath)
{
	m_pMapImage->SetTexture(szFullPath);
}

D3DXVECTOR3 cUIMap::GetMapLeftTop()
{
	 return m_pMapImage->GetPosition(); 
}

void cUIMap::SetMapLeftTop(D3DXVECTOR3 pos)
{
	 m_pMapImage->SetPosition(pos); 
}
