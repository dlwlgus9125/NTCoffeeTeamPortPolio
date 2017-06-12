#pragma once
#include "cObjectManager.h"

enum UI_FUNTION
{
	FUNTION_NONE,
	FUNTION_OPEN,
	FUNTION_CLOSE,
	
	FUNTION_OK,
	FUNTION_NO,

	FUNTION_LIFE_BAR,
};

class cUIObject
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

	D3DXMATRIXA16 m_Matrix;
	vector<cUIObject*>	m_vecChild;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_SIZEN, m_stSize, Size);
	SYNTHESIZE(UI_FUNTION, m_Funtion, Funtion);
	
	float m_fScaleX, m_fScaleY;
	SYNTHESIZE(bool, m_isOnClick, OnClick);			//선택한 유아이창의 트루펄스 변수
	SYNTHESIZE(bool, m_isHidden, IsHidden);			// 그릴지 말지 결정하는 변수
	bool GetIsMove() { return m_isMove; }
public:
	virtual void SetPosition(float x, float y, float z = 0);
	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual void SetSize(int x, int y);
	void SetScale(float x, float y);
	void MoveWindow();
};

