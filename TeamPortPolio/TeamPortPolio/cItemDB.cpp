#include "stdafx.h"
#include "cItemDB.h"

void cItemDB::Setup()
{
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "�� �ҵ�", "���� ���� ª�� ���̴�.", 50, "image/item/sword/shortsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_LONGSWORD, "�� �ҵ�", "����� �� ���̴�.", 250, "image/item/sword/longsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_BASTARDSWORD, "�ٽ�Ÿ�� �ҵ�", "�߼� �糯 ���̴�.", 750, "image/item/sword/bastardsword.png"));
}

void cItemDB::Add(ST_ITEM * pData)
{
	if (m_mapObject.find(pData->eSmallID) == m_mapObject.end())
	{
		m_mapObject[pData->eSmallID] = pData;
	}
}

void cItemDB::Destroy()
{
	for each(auto it in m_mapObject)
	{
		SAFE_DELETE(it.second);
	}

	delete this;
}