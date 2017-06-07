#pragma once
class cUIObject;
class cUIImageView;
class cUIButton;
class cUITextView;
enum Scenetag;
class cUIManager
{

private:
	LPDIRECT3DTEXTURE9		m_pTexture;

	LPD3DXSPRITE			m_pSprite;
	D3DXIMAGE_INFO			m_stImageInfo;
	
	vector<cUIObject*>		m_vecUIRoot;
	cUIObject* m_pUIObject;
	
	cUIImageView* m_pLifeBar;
	
	


	void SetUpWindow(cUIObject* pParentObj, int posX, int posY, char * texturePath, string sTitle, vector<string> sBody, D3DXCOLOR Titlecolor = D3DCOLOR_XRGB(0, 0, 0), D3DXCOLOR Bodycolor = D3DCOLOR_XRGB(0, 0, 0));
	void SetUpWindow(cUIObject* pParentObj, int posX, int posY, char * texturePath, string sTitle, string sBody, D3DXCOLOR Titlecolor = D3DCOLOR_XRGB(0, 0, 0), D3DXCOLOR Bodycolor = D3DCOLOR_XRGB(0, 0, 0));
	void SetUpButton(cUIObject* pParentObj, int posX, int posY, char* szNor, char* szOver, char* szSel, int funtion, string sText, D3DXCOLOR textColor = D3DCOLOR_XRGB(0, 0, 0));

	void SetTitleText(cUIObject* pParent, cUIImageView* ptextView, string text, D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	void SetBodyText(cUIObject* pParent, cUIObject * ptextView, vector<string> text, D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	void SetBodyText(cUIObject* pParent, cUIObject * ptextView, string text, D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 0));

	void OpenOnlyOnewindow(cUIObject* pObj);

	void SetCommonUI();
	void SetQuest_UI();
	void SetInventoryUI();
	void SetMapUI();
	void SetLifeBar();

	void SetTownUI();
	void SetFieldUI();


	void Render_BloodofLifeBar(float maxHp, float CurrentHp);

public:
	cUIManager();
	~cUIManager();

	void OnEnter(Scenetag);
	void OnUpdate();
	void OnExit();
	void Render();

	/*HCURSOR m_Hcursor;
	HCURSOR m_cFinger;
	HCURSOR m_cLClick;
	HCURSOR m_cRClick;
	void SetupCursor();

	void Update_Cursosr();*/

	bool GetIsUIOpen();

};
