#pragma once
#include <map>

#define OBJECTDB cObjectDB::GetInstance() 

// enum�� struct�� stdafx�� ������!!
// ��з�
enum E_L_OBJECTID
{
	E_L_OBJECTID_START,
	E_L_OBJECTID_HUMAN,
	E_L_OBJECTID_ORC,
	E_L_OBJECTID_END,
};

// �ߺз�
enum E_M_OBJECTID
{
	// HUMAN
	E_M_OBJECTID_H_START,
	E_M_OBJECTID_H_DUSKWOOD,
	E_M_OBJECTID_H_DRAENOR,
	E_M_OBJECTID_H_END,

	// ORC
	E_M_OBJECTID_O_START,
	E_M_OBJECTID_O_KALIMDOR,
	E_M_OBJECTID_O_NORTHREND,
	E_M_OBJECTID_O_END,
};

// �Һз�
enum E_S_OBJECTID
{
	E_S_OBJECTID_H_DW_START,
	E_S_OBJECTID_H_DW_BARN,
	E_S_OBJECTID_H_DW_BLACKSMITH,
	E_S_OBJECTID_H_DW_CHAPEL,
	E_S_OBJECTID_H_DW_FARM,
	E_S_OBJECTID_H_DW_INN,
	E_S_OBJECTID_H_DW_LUMBERMILL,
	E_S_OBJECTID_H_DW_MAGETOWER,
	E_S_OBJECTID_H_DW_STABLE,
	E_S_OBJECTID_H_DW_TWOSTORYHOUSE,
	E_S_OBJECTID_H_DW_END,

	E_S_OBJECTID_H_DN_START,
	E_S_OBJECTID_H_DN_ALCHEMYHUB,
	E_S_OBJECTID_H_DN_ALCHEMYRANK,
	E_S_OBJECTID_H_DN_ARMORY,
	E_S_OBJECTID_H_DN_BARN,
	E_S_OBJECTID_H_DN_BARRACKS,
	E_S_OBJECTID_H_DN_BELLTOWER,
	E_S_OBJECTID_H_DN_BLACKSMITH,
	E_S_OBJECTID_H_DN_FARM,
	E_S_OBJECTID_H_DN_FOOTBRIDGE,
	E_S_OBJECTID_H_DN_GARDENHOUSE,
	E_S_OBJECTID_H_DN_GATE1,
	E_S_OBJECTID_H_DN_GATE2,
	E_S_OBJECTID_H_DN_INFIRMARY,
	E_S_OBJECTID_H_DN_INN,
	E_S_OBJECTID_H_DN_SMALLSTAIR1,
	E_S_OBJECTID_H_DN_SMALLSTAIR2,
	E_S_OBJECTID_H_DN_SMALLSTAIR3,
	E_S_OBJECTID_H_DN_LARGESTAIR1,
	E_S_OBJECTID_H_DN_LARGESTAIR2,
	E_S_OBJECTID_H_DN_LARGESTAIR3,
	E_S_OBJECTID_H_DN_MAGETOWER,
	E_S_OBJECTID_H_DN_MENAGERIE,
	E_S_OBJECTID_H_DN_RETAININGWALL,
	E_S_OBJECTID_H_DN_RETAININGWALL_PILLAR,
	E_S_OBJECTID_H_DN_TOWER1,
	E_S_OBJECTID_H_DN_TOWER2,
	E_S_OBJECTID_H_DN_TRADINGPOST,
	E_S_OBJECTID_H_DN_END,
	
	E_S_OBJECTID_O_KD_START,
	E_S_OBJECTID_O_KD_BARRACKS,
	E_S_OBJECTID_O_KD_BLACKSMITH,
	E_S_OBJECTID_O_KD_GREATHALL,
	E_S_OBJECTID_O_KD_HUT,
	E_S_OBJECTID_O_KD_INN,
	E_S_OBJECTID_O_KD_KENNEL,
	E_S_OBJECTID_O_KD_MAGETOWER,
	E_S_OBJECTID_O_KD_MEDIUM,
	E_S_OBJECTID_O_KD_TOWER,
	E_S_OBJECTID_O_KD_TWOSTORYHOUSE,
	E_S_OBJECTID_O_KD_ZEPPELINHOUSE,
	E_S_OBJECTID_O_KD_END,

	E_S_OBJECTID_O_NR_START,
	E_S_OBJECTID_O_NR_BEARPIT,
	E_S_OBJECTID_O_NR_CAP,
	E_S_OBJECTID_O_NR_CRANE,
	E_S_OBJECTID_O_NR_FORGE,
	E_S_OBJECTID_O_NR_GATE,
	E_S_OBJECTID_O_NR_HORDEGUNSHIP,
	E_S_OBJECTID_O_NR_HOVEL,
	E_S_OBJECTID_O_NR_SCAFFOLD,
	E_S_OBJECTID_O_NR_SHIP,
	E_S_OBJECTID_O_NR_STABLE,
	E_S_OBJECTID_O_NR_TOWER1,
	E_S_OBJECTID_O_NR_TOWER2,
	E_S_OBJECTID_O_NR_WALL1,
	E_S_OBJECTID_O_NR_WALL2,
	E_S_OBJECTID_O_NR_END,

	E_S_OBJECTID_BLANK,
	E_S_OBJECTID_BLANK2,
	E_S_OBJECTID_BLANK3,
	E_S_OBJECTID_BLANK4,
};

struct ST_OBJECTDATA
{
	E_L_OBJECTID eLargeID;
	E_M_OBJECTID eMiddleID;
	E_S_OBJECTID eSmallID;

	char* szFolder;
	char* szFile;

	float fU, fV;

	ST_OBJECTDATA(E_L_OBJECTID largeID, E_M_OBJECTID middleID, E_S_OBJECTID smallID, char* folder, char* file, float u, float v)
	{
		eLargeID = largeID;
		eMiddleID = middleID;
		eSmallID = smallID;
		szFolder = folder;
		szFile = file;
		fU = u;
		fV = v;
	}
};


class cObjectDB
{
	map<int, ST_OBJECTDATA*> m_mapObject;
	SINGLETONE(cObjectDB);

public:
	void Setup();
	void Add(ST_OBJECTDATA* pData);
	void Destroy();
	ST_OBJECTDATA* GetMapObject(int smallID) { return m_mapObject[smallID]; }
};
