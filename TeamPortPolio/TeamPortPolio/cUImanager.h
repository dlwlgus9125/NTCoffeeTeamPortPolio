#pragma once
class cUIObject;
class cUIImageView;
class cUIButton;
class cUITextView;
class cUIScrollBar;
class cUILifeBar;
class cUICursor;
class cUIMap;
class cUIChractorView;
class cUIInventory;
#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{

private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	cUICursor*				m_pCursor;
	vector<cUIObject*>		m_vecUIRoot;

	cUIMap* m_pUIMap;
	cUIChractorView* m_pUICharactorView;
	cUIInventory* m_pUIInventory;

	void SetWindow(cUIObject* pParentObj, int posX, int posY,  char * texturePath, string sTitle, string sBody, float scale_x = 1, float scale_y = 1, D3DXCOLOR Titlecolor = D3DCOLOR_XRGB(0, 0, 0), D3DXCOLOR Bodycolor = D3DCOLOR_XRGB(0, 0, 0));
	void SetButton(cUIObject* pParentObj, int posX, int posY,  char* szNor, char* szOver, char* szSel, int funtion, string sText, float scale_x = 1, float scale_y = 1, D3DXCOLOR textColor = D3DCOLOR_XRGB(0, 0, 0));

	void SetTitleText(cUIObject* pParent, cUIImageView* ptextView, string text, float scale_x = 1, float scale_y = 1, D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	void SetBodyText(cUIObject* pParent, cUIObject * ptextView, string text, float scale_x = 1, float scale_y = 1, D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 0));

	void OpenOnlyOnewindow(cUIObject* pObj);

	
	void SetScrollBar(cUIObject * pParentObj, int posX, int posY, char * szLane, char * szHead, float scale_x=1, float scale_y=1);

	void SetLifeBar(int posX, int posY, char* szFullPath, float scale_x = 1, float scale_y = 1 );
	void SetCommonUI();
	void SetUpLifeBar();
	void SetUpInventoryUI();
	void SetUpItemList(cUIObject* pParentUIobject);

	void SetUpQuest_UI();
	void SetUpMapUI();

	void SetTownUI();
	void SetFieldUI();

public:
	cUIManager();
	~cUIManager();

	void OnEnter(int tag);
	void OnUpdate();
	void OnExit();
	void Render();

	bool GetIsUIOpen();
	cUIObject* GetCurrentUI();

};
