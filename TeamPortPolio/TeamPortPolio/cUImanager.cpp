#include "stdafx.h"
#include "cUImanager.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUIButton.h"
#include "cUIScrollBar.h"
#include "cUILifeBar.h"
#include "cUICursor.h"
cUIManager::cUIManager()
	: m_pTexture(NULL)
	,m_pCursor(NULL)//
{
	m_pCursor = new cUICursor;
	m_pCursor->SetupCursor();
}

cUIManager::~cUIManager()
{
	SAFE_DELETE(m_pCursor);
}

void cUIManager::OnEnter(int tag)
{
	SetCommonUI();
	switch (tag)
	{
	case 1:SetTownUI();
	case 2:SetFieldUI();
	}//ex;
	D3DXCreateSprite(D3DDevice, &g_Sprite);

}

void cUIManager::OnUpdate()
{
	m_pCursor->Update_Cursosr();
	for each (auto p in m_vecUIRoot)
	{
		p->Update();
		OpenOnlyOnewindow(p);
	}
}

void cUIManager::OnExit()
{
	for each (auto o in m_vecUIRoot)
	{
		if (o)o->Destroy();
	}
	SAFE_RELEASE(m_pTexture);
	
}


bool cUIManager::GetIsUIOpen()
{
	for each(auto p in m_vecUIRoot)
	{
		if (p->GetIsHidden() == false)
		{
			return true;
		}
	}
	return false;
}

void cUIManager::OpenOnlyOnewindow(cUIObject * pObj)
{
	if (!pObj->GetIsHidden())
	{
		for each (auto p in m_vecUIRoot)
		{
			if(pObj!=p)p->SetIsHidden(true);
		}	
	}
}


void cUIManager::SetLifeBar( int posX, int posY, char * szFullPath, float scale_x, float scale_y)
{
	cUIObject* pObj = new cUIObject;
	cUILifeBar* p = new cUILifeBar;
	p->SetScale(scale_x, scale_y);
	p->SetPosition(posX,posY);
	p->SetTexture(szFullPath);
	p->SetFuntion(FUNTION_LIFE_BAR);
	pObj->AddChild(p);
	m_vecUIRoot.push_back(pObj);
}

void cUIManager::Render()
{
	SetCursor(g_Cursor);
	
	for each(auto p in m_vecUIRoot)
	{
		if (p)p->Render(g_Sprite);
	}
}

void cUIManager::SetTownUI()
{
	//initialize town UI
}

void cUIManager::SetFieldUI()
{
	//initialize fieldUI
}

void cUIManager::SetCommonUI()
{
	SetUpLifeBar();
	SetUpQuest_UI();
	SetUpInventoryUI();
	//SetUpMapUI();
}

void cUIManager::SetUpLifeBar()
{
	SetLifeBar(0, 0, "UI/btn-med-over.png",0.2,0.2);
}

void cUIManager::SetUpQuest_UI()		
{
	//test
	cUIObject* pUiobj = new cUIObject();
	pUiobj->SetFuntion(FUNTION_NONE);
	pUiobj->SetScale(0.1,0.1);

	SetWindow(pUiobj, 0, 0, "UI/panel-info.png", "TITLE","text",1,1);
	SetButton(pUiobj, 50, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "¿­±â",0.5,1);
	SetButton(pUiobj, 250, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "´Ý±â");
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetUpInventoryUI()		
{
	//test
	cUIObject* pUiobj = new cUIObject();
	SetWindow(pUiobj, 200, 0, "UI/panel-info.png", "TITLE", "text");
	SetButton(pUiobj, 250, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "¿­±â");
	SetButton(pUiobj, 435, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "´Ý±â");
	SetScrollBar(pUiobj, 30, 0, "UI/panel-info.png", "UI/BT_STAND.png",0.2,0.5);
	SetUpItemList(pUiobj);
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetUpItemList(cUIObject* pParentUIobject)
{
	//SetWindow()
	
	
	
}
void cUIManager::SetUpMapUI()		
{
	// something to do
}

void cUIManager::SetTitleText(cUIObject* pParent, cUIImageView * pimageView, string text, float scale_x, float scale_y,D3DXCOLOR color)
{
	cUITextView* pText = new cUITextView;
	pText->SetScale(scale_x, scale_y);
	pText->SetText(text);
	pText->SetSize(ST_SIZEN(pimageView->GetSize().nWidth, 100));
	pText->SetPosition(D3DXVECTOR3(pimageView->GetPosition().x, pimageView->GetPosition().y + 5, pimageView->GetPosition().z));
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetTextColor(color);
	pText->SetFuntion(pimageView->GetFuntion());
	pParent->AddChild(pText);
}
void cUIManager::SetBodyText(cUIObject* pParent, cUIObject * ptextView, string text, float scale_x, float scale_y,D3DXCOLOR color)
{
	cUITextView* pText = new cUITextView;
	pText->SetScale(scale_x, scale_y);
	pText->SetText(text);
	pText->SetSize(ptextView->GetSize());
	pText->SetPosition(ptextView->GetPosition());
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetTextColor(color);
	pText->SetFuntion(ptextView->GetFuntion());
	pParent->AddChild(pText);
} 

void cUIManager::SetButton(cUIObject* pParentObj, int posX, int posY, char* szNor, char* szOver, char* szSel, int funtion, string sText, float scale_x, float scale_y, D3DXCOLOR textColor)
{
	cUIButton* pButton = new cUIButton;
	pButton->SetScale(scale_x, scale_y);
	pButton->SetTexture(szNor, szOver, szSel);
	pButton->SetPosition(posX, posY);
	pButton->SetFuntion((UI_FUNTION)funtion);
	pParentObj->AddChild(pButton);
	SetBodyText(pParentObj, pButton, sText, scale_x, scale_y,textColor);
}
void cUIManager::SetWindow(cUIObject* pParentObj, int posX, int posY,  char* texturePath, string sTitle, string vsBody, float scale_x, float scale_y, D3DXCOLOR Titlecolor, D3DXCOLOR Bodycolor)
{
	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetFuntion(FUNTION_WINDOW);
	pImageView->SetPosition(posX, posY);
	pImageView->SetTexture(texturePath);
	pImageView->SetScale(scale_x, scale_y);
	SetBodyText(pParentObj, pImageView, vsBody, scale_x, scale_y, Bodycolor);
	SetTitleText(pParentObj, pImageView, sTitle, scale_x, scale_y,Titlecolor);
	pParentObj->SetMoveRect(ST_SIZEN(posX+(pImageView->GetSize().nWidth*pImageView->m_fScaleX), 100));
	pParentObj->AddChild(pImageView);
}

void cUIManager::SetScrollBar(cUIObject * pParentObj,int posX, int posY, char * szLane, char * szHead, float scale_x, float scale_y)
{
	cUIScrollBar* pScrollhead = new cUIScrollBar;
	pScrollhead->SetFuntion(FUNTION_SCROLL_BAR);
	pScrollhead->SetLanePos(D3DXVECTOR3(posX,posY,0));
	pScrollhead->SetPosition(posX, posY);
	pScrollhead->SetTexture(szLane,szHead);
	pScrollhead->SetScale(scale_x, scale_y);
	pParentObj->AddChild(pScrollhead);
}