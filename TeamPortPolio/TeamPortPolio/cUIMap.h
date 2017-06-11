#pragma once
class cUIButton;
class cUIImageView;
class cUITextView;
//∏Æ∆—≈‰∏µ«ÿº≠ ø»±Ê∞≈¿”
class cUIMap
{
private:
	cUIObject* m_pRoot;
	cUIButton* m_pButtonOpen;
	cUIButton* m_pButtonClose;
	cUIImageView* m_pMapImage;
	void SetUpOpenButton(cUIObject * pRoot);
	void SetUpCloseButton(cUIObject * pRoot);
	void SetUpMapImage(cUIObject * pRoot);

public:
	cUIMap();
	~cUIMap();

	void SetUp();
	cUIObject* GetRootUI();

	cUIImageView* GetMapImage();
	void SetMapImage(char * szFullPath);

	D3DXVECTOR3 GetMapLeftTop();
	void SetMapLeftTop(D3DXVECTOR3 pos);

};
