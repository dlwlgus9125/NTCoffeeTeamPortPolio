#pragma once
#include "cUIObject.h"
class cItem;
class cUIScrollBar;
class cUIItemSlot:public cUIObject
{
public:
	cUIItemSlot();
	~cUIItemSlot();
	void SetTexture();
	virtual void Update()override;
	virtual void Render(LPD3DXSPRITE pSprite)override;
	
private:
	struct ItemSlot
	{
		cItem* pItem;
		LPDIRECT3DTEXTURE9 pBackTex;
		LPDIRECT3DTEXTURE9 pItemTex;
		bool isInShow;
		ItemSlot() {}
		ItemSlot(cItem* pitem, LPDIRECT3DTEXTURE9 pB, LPDIRECT3DTEXTURE9 pi)
		{
			pItem = pitem;
			pBackTex = pB;
			pItemTex = pi;
		}
	};
	SYNTHESIZE(float, m_fScrolledRate, ScrollRate);
	SYNTHESIZE(cUIScrollBar*, m_pbar, ScrollBar);
	vector<ItemSlot> m_vecSlot;
	
};
