#pragma once
class cUIImageView;
class cUITextView;
class cUILifeBar;
class cUIChractorView
{
private:
	cUIObject*		m_pRoot;
	cUIImageView*	m_pCharactorFace;
	cUILifeBar*		m_pLifeBar;

	void SetUpFace(cUIObject * pRoot);

	void SetUpLifeBar(cUIObject * pRoot);

public:
	cUIChractorView();
	~cUIChractorView();
	
	cUIObject * GetRootUI();
	void SetUp();

};
