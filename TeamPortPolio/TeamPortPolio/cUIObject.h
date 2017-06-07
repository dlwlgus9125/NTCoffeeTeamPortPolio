#pragma once
#include "cObject.h"
enum UI_FUNTION
{
	FUNTION_NONE,
	FUNTION_OPEN,
	FUNTION_CLOSE,
	FUNTION_OK,
	FUNTION_PREV,
	FUNTION_NEXT,
	FUNTION_TEXT,
	FUNTION_TITLE,
	FUNTION_MAP,
	FUNTION_LIFE_BAR,

};

class cUIObject : public cObject
{
public:
	cUIObject();
	virtual	~cUIObject();

private:
	POINT m_CursorPos;
	POINT m_PrevCursorPos;
	bool m_isMove;
	SYNTHESIZE(ST_SIZEN, m_MoveRect, MoveRect);


protected:

	vector<cUIObject*>	m_vecChild;
	D3DXMATRIXA16		m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_SIZEN, m_stSize, Size);
	SYNTHESIZE(UI_FUNTION, m_Funtion, Funtion);

	bool	m_isHidden;			// 그릴지 말지 결정하는 변수
	bool	m_isNextPage;
public:
	virtual void SetPosition(float x, float y, float z = 0);
	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual void SetSize(int x, int y);

	void MoveWindow();
	bool GetisHidden() { return m_isHidden; }
	void SetIsHidden(bool ishidden) { m_isHidden = ishidden; }

};

