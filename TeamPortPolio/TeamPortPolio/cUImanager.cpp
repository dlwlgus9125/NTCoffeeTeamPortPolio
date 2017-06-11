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
	, m_pSprite(NULL)
	, m_pCursor(NULL)
{
	m_pCursor = new cUICursor;
	m_pCursor->SetupCursor();
}

cUIManager::~cUIManager()
{
	SAFE_DELETE(m_pCursor);
}

void cUIManager::OnEnter(Scenetag tag)
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	SetCommonUI();

	switch (tag)
	{
	case 1:SetTownUI();
	case 2:SetFieldUI();
	}//ex;

}

void cUIManager::OnUpdate(float deltatime)
{
	//cObject* pCharactor = OBJECT->GetPlayer();
	m_pCursor->Update_Cursosr();
	for each (cUIObject* p in m_vecUIRoot)
	{
		p->Update();
		OpenOnlyOnewindow(p);
	}
}

void cUIManager::OnExit()
{
	for each (cUIObject* o in m_vecUIRoot)
	{
		if (o)o->Destroy();
	}
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite);

}


bool cUIManager::GetIsUIOpen()
{
	for each(cUIObject* p in m_vecUIRoot)
	{
		if (p->GetisHidden() == false)
		{
			return true;
		}
	}
	return false;
}

void cUIManager::OpenOnlyOnewindow(cUIObject * pObj)
{
	if (!pObj->GetisHidden())
	{
		for each (cUIObject* p in m_vecUIRoot)
		{
			if (pObj != p)p->SetIsHidden(true);
		}
	}
}


void cUIManager::SetLifeBar(int posX, int posY, char * szFullPath)
{
	cUIObject* pObj = new cUIObject;
	cUILifeBar* p = new cUILifeBar;
	p->SetPosition(posX, posY);
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
		if (p)p->Render(m_pSprite);
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
	SetLifeBar(0, 0, "UI/btn-med-over.png");
}

void cUIManager::SetUpQuest_UI()
{
	//test
	cUIObject* pUiobj = new cUIObject();
	vector<string> tex;
	tex.push_back("prev");
	tex.push_back("next");
	SetWindow(pUiobj, 0, 0, "UI/panel-info.png", "TITLE", tex);
	SetButton(pUiobj, 50, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "열기");
	SetButton(pUiobj, 0, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_NEXT, "다음");
	SetButton(pUiobj, 0, 400, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_PREV, "이전");
	SetButton(pUiobj, 235, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "닫기");
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetUpInventoryUI()
{
	//test
	cUIObject* pUiobj = new cUIObject();

	SetWindow(pUiobj, 200, 0, "UI/panel-info.png", "TITLE", "text");
	SetButton(pUiobj, 250, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "열기");
	SetButton(pUiobj, 435, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "닫기");


	SetScrollBar(pUiobj, 200, 0, "UI/panel-info.png", "UI/BT_STAND.png");
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetUpItemList()
{

	//SetWindow()



}
void cUIManager::SetUpMapUI()
{
	// something to do
}

void cUIManager::SetTitleText(cUIObject* pParent, cUIImageView * pimageView, string text, D3DXCOLOR color)
{
	cUITextView* pText = new cUITextView;
	pText->SetFuntion(FUNTION_TEXT);
	pText->SetText(text);
	pText->SetSize(ST_SIZEN(pimageView->GetSize().nWidth, 100));
	pText->SetPosition(D3DXVECTOR3(pimageView->GetPosition().x, pimageView->GetPosition().y + 5, pimageView->GetPosition().z));
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetTextColor(D3DCOLOR_XRGB(0, 0, 0));
	pText->SetFuntion(pimageView->GetFuntion());
	pParent->AddChild(pText);
}
void cUIManager::SetBodyText(cUIObject* pParent, cUIObject * ptextView, string text, D3DXCOLOR color)
{
	cUITextView* pText = new cUITextView;
	pText->SetFuntion(FUNTION_TEXT);
	pText->SetText(text);
	pText->SetSize(ptextView->GetSize());
	pText->SetPosition(ptextView->GetPosition());
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetTextColor(color);
	pText->SetFuntion(ptextView->GetFuntion());
	pParent->AddChild(pText);
}
void cUIManager::SetBodyText(cUIObject* pParent, cUIObject * ptextView, vector<string> text, D3DXCOLOR color)
{
	cUITextView* pText = new cUITextView;
	for (int i = 0; i < text.size(); i++)	pText->SetText(text[i]);
	pText->SetFuntion(FUNTION_TEXT);
	pText->SetSize(ptextView->GetSize());
	pText->SetPosition(ptextView->GetPosition());
	pText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pText->SetTextColor(color);
	pText->SetFuntion(ptextView->GetFuntion());
	pParent->AddChild(pText);
}
void cUIManager::SetWindow(cUIObject* pParentObj, int posX, int posY, char* texturePath, string sTitle, vector<string> vsBody, D3DXCOLOR Titlecolor, D3DXCOLOR Bodycolor)
{
	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetPosition(posX, posY);
	pImageView->SetTexture(texturePath);
	pParentObj->AddChild(pImageView);
	pParentObj->SetMoveRect(ST_SIZEN(pImageView->GetSize().nWidth, 100));
	SetTitleText(pParentObj, pImageView, sTitle, Titlecolor);
	SetBodyText(pParentObj, pImageView, vsBody, Bodycolor);
}
void cUIManager::SetButton(cUIObject* pParentObj, int posX, int posY, char* szNor, char* szOver, char* szSel, int funtion, string sText, D3DXCOLOR textColor)
{
	cUIButton* pButtonCancel = new cUIButton;
	pButtonCancel->SetTexture(szNor, szOver, szSel);
	pButtonCancel->SetPosition(posX, posY);
	pButtonCancel->SetFuntion((UI_FUNTION)funtion);
	pParentObj->AddChild(pButtonCancel);
	SetBodyText(pParentObj, pButtonCancel, sText, textColor);
}
void cUIManager::SetWindow(cUIObject* pParentObj, int posX, int posY, char* texturePath, string sTitle, string vsBody, D3DXCOLOR Titlecolor, D3DXCOLOR Bodycolor)
{
	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetPosition(posX, posY);
	pImageView->SetTexture(texturePath);
	pParentObj->AddChild(pImageView);
	pParentObj->SetMoveRect(ST_SIZEN(pImageView->GetSize().nWidth, 100));
	SetTitleText(pParentObj, pImageView, sTitle, Titlecolor);
	SetBodyText(pParentObj, pImageView, vsBody, Bodycolor);
}
void cUIManager::SetScrollBar(cUIObject * pParentObj, int posX, int posY, char * szLanePath, char * szHeadPath)
{
	cUIImageView* pLane = new cUIImageView;
	pLane->SetPosition(posX, posY);
	pLane->SetTexture(szLanePath);
	SetScrollHead(pParentObj, pLane, posX, posY, szHeadPath);

}
void cUIManager::SetScrollHead(cUIObject * pParentObj, cUIImageView* pLane, int posX, int posY, char * texturePath)
{
	cUIScrollBar* pScrollbar = new cUIScrollBar;
	pScrollbar->SetUIScrollLane(pLane);
	pScrollbar->SetPosition(posX, posY);
	pScrollbar->SetTexture(texturePath);
	pParentObj->AddChild(pLane);
	pParentObj->AddChild(pScrollbar);
}