#pragma once
//�����丵�ؼ� �ȱ����
class cUIScrollBar;
class cUIItemSlot;
class cUIImageView;
class cUIObject;
class cUIInventory
{
public:
	cUIInventory();
	~cUIInventory();
	void SetUp();
	cUIObject* GetRootUI();
private:
	RECT m_RCLaneLect;
	cUIScrollBar* m_pUIScrollBar;
	cUIImageView* m_pUIBackBoard;
	cUIImageView*	m_pUISlot[10];
	
	cUIObject* m_pRoot;
	void SetUpBackBoard(cUIObject* pRoot);
	void SetUpSlot(cUIObject* pRoot);
	void SetUpScrollBar(cUIObject* pRoot);
};