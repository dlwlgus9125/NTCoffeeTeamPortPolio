#pragma once
#include "cUIObject.h"
class cItem;
class cUIScrollBar;
class cUIItemSlot:public cUIObject
{
private:
	struct ItemSlot
	{
		cItem* pItem;
		LPDIRECT3DTEXTURE9 pBackTex;
		LPDIRECT3DTEXTURE9 pItemTex;
		ItemSlot() 
		{
			pItem = NULL;
			pBackTex = NULL;
			pItemTex = NULL;
		}
		ItemSlot(cItem* pitem, LPDIRECT3DTEXTURE9 pB, LPDIRECT3DTEXTURE9 pi)
		{
			pItem = pitem;
			pBackTex = pB;
			pItemTex = pi;
		}
	};

	int m_nScrolledIndex;
	SYNTHESIZE(cUIScrollBar*, m_pbar, ScrollBar);
	ItemSlot m_stItemSlot[10];
	LPDIRECT3DTEXTURE9 m_aTexture[2];
public:
	cUIItemSlot();
	~cUIItemSlot();
	void SetTexture();
	virtual void Update()override;
	virtual void Render(LPD3DXSPRITE pSprite)override;
	

	
};
