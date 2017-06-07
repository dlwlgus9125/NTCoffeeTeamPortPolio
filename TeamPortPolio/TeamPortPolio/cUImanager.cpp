#include "stdafx.h"
#include "cUImanager.h"
#include "cUITextView.h"
#include "cUIImageView.h"
#include "cUIButton.h"

cUIManager::cUIManager()
	: m_pTexture(NULL)
	, m_pSprite(NULL)
	/*, m_Hcursor(NULL)
	, m_cFinger(0)
	, m_cLClick(0)
	, m_cRClick(0)*/
	, m_pUIObject(NULL)
	, m_pLifeBar(NULL)
{
}

cUIManager::~cUIManager()
{
	
}

void cUIManager::OnEnter(Scenetag tag)
{
	//SetupCursor();
	D3DXCreateSprite(D3DDevice, &m_pSprite);

	SetCommonUI();

	switch (tag)
	{
	case 1:SetTownUI();
	case 2:SetFieldUI();
	}//ex;

	m_pUIObject = m_vecUIRoot[0];
}

void cUIManager::OnUpdate()
{
	
	for each (auto p in m_vecUIRoot)
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
	if (!pObj->GetisHidden() && GetIsUIOpen())
	{
		for each (cUIObject* p in m_vecUIRoot)
		{	
			if(pObj!=p)	p->SetIsHidden(true);
		}
	}
}

void cUIManager::Render_BloodofLifeBar(float maxHp, float CurrentHp)
{
	float value= CurrentHp / maxHp;
	float WidthOfLifeBar = m_pLifeBar->GetSize().nWidth;
	float HeightOfLifeBar= m_pLifeBar->GetSize().nHeight;
	//>>test
	static float a = 0;
	if (INPUT->IsKeyDown(VK_LEFT))a -= 11;
	if (a > WidthOfLifeBar*0.8) a = WidthOfLifeBar*0.8;
	if (a < 0) a = 0;
	//<<
	D3DXVECTOR3 p[2];
	p[0] = D3DXVECTOR3(WidthOfLifeBar* 1 / 10, HeightOfLifeBar * 0.5, 0);/*시작지점*/
	p[1] = D3DXVECTOR3(WidthOfLifeBar*0.1, HeightOfLifeBar* 0.5, 0);/*끝지점*/
	/* WidthOfLifeBar*value*/
	LPD3DXLINE pLine;
	D3DXCreateLine(D3DDevice, &pLine);
	pLine->SetWidth(m_pLifeBar->GetSize().nHeight*2/3);
	pLine->Begin();


	D3DXMATRIX out, view, proj, world;

	D3DDevice->GetTransform(D3DTS_VIEW, &view);
	D3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
	D3DDevice->GetTransform(D3DTS_WORLD, &world);

	D3DXMatrixIdentity(&out);
	out = world * view * proj;
	pLine->DrawTransform(p, 2, &out, D3DCOLOR_XRGB(0,255,0));
	pLine->End();
	pLine->Release();
}

//void cUIManager::SetupCursor()
//{
//	m_cFinger = (LoadCursorFromFile("cursor/gam1340.cur"));
//	m_cLClick = (LoadCursorFromFile("cursor/link select.cur"));
//	m_cRClick = (LoadCursorFromFile("cursor/unavalible.cur"));
//
//	m_Hcursor = m_cFinger;
//}
//void cUIManager::Update_Cursosr()
//{
//	if (GetKeyState(VK_LBUTTON)&0x8000)
//	{
//		m_Hcursor = m_cLClick;
//	}
//	else if (GetKeyState(VK_RBUTTON) & 0x8000)
//	{
//		m_Hcursor = m_cRClick;
//	}
//	else
//	{
//		m_Hcursor = m_cFinger;
//	}
//	SetCursor(m_Hcursor);
//}
void cUIManager::Render()
{


	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	for each(auto p in m_vecUIRoot)
	{
		if (p)p->Render(m_pSprite);
	}
	m_pSprite->End();
	//Render_BloodofLifeBar(10,10);
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
	SetLifeBar();
	SetQuest_UI();
	SetInventoryUI();
	SetMapUI();
}

void cUIManager::SetQuest_UI()		
{
	cUIObject* pUiobj = new cUIObject();
	vector<string> tex;
	tex.push_back("prev");
	tex.push_back("next");
	SetUpWindow(pUiobj, 0, 0, "UI/panel-info.png", "TITLE", tex);
	SetUpButton(pUiobj, 50, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "열기");
	SetUpButton(pUiobj, 0, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_NEXT, "다음");
	SetUpButton(pUiobj, 0, 400, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_PREV, "이전");
	SetUpButton(pUiobj, 235, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "닫기");
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetInventoryUI()		
{
	cUIObject* pUiobj = new cUIObject();
	vector<string> tex;
	tex.push_back("prev");
	tex.push_back("next");
	SetUpWindow(pUiobj, 200, 0, "UI/panel-info.png", "TITLE", tex);
	SetUpButton(pUiobj, 250, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_OPEN, "열기");
	SetUpButton(pUiobj, 200, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_NEXT, "다음");
	SetUpButton(pUiobj, 200, 400, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_PREV, "이전");
	SetUpButton(pUiobj, 435, 435, "UI/BT_STAND.png", "UI/BT_MOUSE_OVER.png", "UI/BT_SELECT.png", FUNTION_CLOSE, "닫기");
	m_vecUIRoot.push_back(pUiobj);
}
void cUIManager::SetMapUI()		
{
}
void cUIManager::SetLifeBar()		
{
	cUIObject* pobj = new cUIObject();
	m_pLifeBar = new cUIImageView;
	m_pLifeBar->SetPosition(0, 0);
	m_pLifeBar->SetTexture("UI/btn-med-over.png");
	m_pLifeBar->SetFuntion(FUNTION_LIFE_BAR);
	pobj->AddChild(m_pLifeBar);
	m_vecUIRoot.push_back(m_pLifeBar);
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
void cUIManager::SetUpWindow(cUIObject* pParentObj, int posX, int posY, char* texturePath, string sTitle, vector<string> vsBody, D3DXCOLOR Titlecolor, D3DXCOLOR Bodycolor)
{
	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetPosition(posX, posY);
	pImageView->SetTexture(texturePath);
	pParentObj->AddChild(pImageView);
	pParentObj->SetMoveRect(ST_SIZEN(pImageView->GetSize().nWidth, 100));
	SetTitleText(pParentObj, pImageView, sTitle, Titlecolor);
	SetBodyText(pParentObj, pImageView, vsBody, Bodycolor);
}
void cUIManager::SetUpButton(cUIObject* pParentObj, int posX, int posY, char* szNor, char* szOver, char* szSel, int funtion, string sText, D3DXCOLOR textColor)
{
	cUIButton* pButtonCancel = new cUIButton;
	pButtonCancel->SetTexture(szNor, szOver, szSel);
	pButtonCancel->SetPosition(posX, posY);
	pButtonCancel->SetFuntion((UI_FUNTION)funtion);
	pParentObj->AddChild(pButtonCancel);
	SetBodyText(pParentObj, pButtonCancel, sText, textColor);
}
void cUIManager::SetUpWindow(cUIObject* pParentObj, int posX, int posY, char* texturePath, string sTitle, string vsBody, D3DXCOLOR Titlecolor, D3DXCOLOR Bodycolor)
{
	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetPosition(posX, posY);
	pImageView->SetTexture(texturePath);
	pParentObj->AddChild(pImageView);
	pParentObj->SetMoveRect(ST_SIZEN(pImageView->GetSize().nWidth, 100));
	SetTitleText(pParentObj, pImageView, sTitle, Titlecolor);
	SetBodyText(pParentObj, pImageView, vsBody, Bodycolor);
}