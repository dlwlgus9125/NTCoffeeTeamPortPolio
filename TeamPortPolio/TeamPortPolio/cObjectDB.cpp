#include "stdafx.h"
#include "cObjectDB.h"


cObjectDB::cObjectDB()
{
}

cObjectDB::~cObjectDB()
{
}

void cObjectDB::Setup()
{
	//							대분류					중분류					소분류									폴더 경로									파일명									u값					v값
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_BARN,					"obj/Construct/Human/Duskwood/Barn",				"duskwood_barn.obj",								0,					0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_BLACKSMITH,			"obj/Construct/Human/Duskwood/Blacksmith",			"duskwood_blacksmith.obj",					(float)1 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_CHAPEL,				"obj/Construct/Human/Duskwood/Chapel",				"duskwoodchapel.obj",						(float)2 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_FARM,					"obj/Construct/Human/Duskwood/Farm",				"duskwood_human_farm.obj",					(float)3 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_INN,					"obj/Construct/Human/Duskwood/Inn",					"duskwood_inn.obj",							(float)4 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_LUMBERMILL,			"obj/Construct/Human/Duskwood/Lumbermill",			"duskwood_lumbermill.obj",					(float)5 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_MAGETOWER,				"obj/Construct/Human/Duskwood/MageTower",			"duskwood_magetower.obj",					(float)6 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_STABLE,				"obj/Construct/Human/Duskwood/Stable",				"duskwood_stable.obj",						(float)7 / 8,				0	));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_TWOSTORYHOUSE,			"obj/Construct/Human/Duskwood/Two-story",			"duskwood_humantwostory.obj",						0,			(float)1 / 8));
																												
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ALCHEMYHUB, 			"obj/Construct/Human/Draenor/AlchemyHub",			"6hu_garrison_alchemy_hub.obj",				(float)1 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ALCHEMYRANK,			"obj/Construct/Human/Draenor/AlchemyRank",			"6hu_garrison_alchemy_rank1.obj",			(float)2 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ARMORY,					"obj/Construct/Human/Draenor/Armory",				"6hu_garrison_armory_v1.obj",				(float)3 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BARN,					"obj/Construct/Human/Draenor/Barn",					"6hu_garrison_barn_v1.obj",					(float)4 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BARRACKS,				"obj/Construct/Human/Draenor/Barracks",				"6hu_garrison_barracks_v2.obj",				(float)5 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BELLTOWER,				"obj/Construct/Human/Draenor/BellTower",			"6hu_garrison_belltower.obj",				(float)6 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BLACKSMITH,				"obj/Construct/Human/Draenor/Blacksmith",			"6hu_garrison_blacksmithing_hub.obj",		(float)7 / 8,		(float)1 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_FARM,					"obj/Construct/Human/Draenor/Farm",					"6hu_garrison_farm_v1.obj",							0,			(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_FOOTBRIDGE,				"obj/Construct/Human/Draenor/FootBridge",			"6hu_garrison_footbridge_v1.obj",			(float)1 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GARDENHOUSE,			"obj/Construct/Human/Draenor/GardenHouse",			"6hu_garrison_gardenhouse_v1.obj",			(float)2 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GATE1,					"obj/Construct/Human/Draenor/Gate1", 				"6hu_garrison_gate_v2.obj",					(float)3 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GATE2,					"obj/Construct/Human/Draenor/Gate2",				"6hu_garrison_gate_v3.obj",					(float)4 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_INFIRMARY,				"obj/Construct/Human/Draenor/Infirmary",			"6hu_garrison_infirmary_v2.obj",			(float)5 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_INN,					"obj/Construct/Human/Draenor/Inn",					"6hu_garrison_inn_v3.obj",					(float)6 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR1,			"obj/Construct/Human/Draenor/SmallStair1",			"6hu_garrison_stair_v1.obj",				(float)7 / 8,		(float)2 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR2,			"obj/Construct/Human/Draenor/SmallStair2",			"6hu_garrison_stair_v2.obj",						0,			(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR3,			"obj/Construct/Human/Draenor/SmallStair3",			"6hu_garrison_stair_v3.obj",				(float)1 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR1,			"obj/Construct/Human/Draenor/LargeStair1",			"6hu_garrison_stair02_v1.obj",				(float)2 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR2,			"obj/Construct/Human/Draenor/LargeStair2",			"6hu_garrison_stair02_v2.obj",				(float)3 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR3,			"obj/Construct/Human/Draenor/LargeStair3",			"6hu_garrison_stair02_v3.obj",				(float)4 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_MAGETOWER,				"obj/Construct/Human/Draenor/MageTower",			"6hu_garrison_magictower_v3.obj",			(float)5 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_MENAGERIE,				"obj/Construct/Human/Draenor/Menagerie",			"6hu_garrison_menagerie.obj",				(float)6 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_RETAININGWALL,			"obj/Construct/Human/Draenor/RetainingWall",		"6hu_garrison_retaining_wall.obj",			(float)7 / 8,		(float)3 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_RETAININGWALL_PILLAR,	"obj/Construct/Human/Draenor/RetainingWall_Pillar",	"6hu_garrison_retainingwall_pillar.obj",			0,			(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TOWER1,					"obj/Construct/Human/Draenor/Tower1",				"6hu_garrison_tower_v2.obj",				(float)1 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TOWER2,					"obj/Construct/Human/Draenor/Tower2",				"6hu_garrison_tower_v3.obj",				(float)2 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TRADINGPOST,			"obj/Construct/Human/Draenor/Tradingpost",			"6hu_garrison_tradingpost_v3.obj",			(float)3 / 8,		(float)4 / 8));
																										
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_BARRACKS,				"obj/Construct/Orc/Kalimdor/Barracks",				"orcbarracks.obj",							(float)4 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_BLACKSMITH,				"obj/Construct/Orc/Kalimdor/Blacksmith",			"orcblacksmith.obj",						(float)5 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_GREATHALL,				"obj/Construct/Orc/Kalimdor/GreatHall",				"orcgreathall.obj",							(float)6 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_HUT,					"obj/Construct/Orc/Kalimdor/Hut",					"orchut.obj",								(float)7 / 8,		(float)4 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_INN,					"obj/Construct/Orc/Kalimdor/Inn",					"orcinn.obj",										0,			(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_KENNEL,					"obj/Construct/Orc/Kalimdor/Kennel",				"orckennel.obj",							(float)1 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_MAGETOWER,				"obj/Construct/Orc/Kalimdor/MageTower",				"orcmagetower.obj",							(float)2 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_MEDIUM,					"obj/Construct/Orc/Kalimdor/Medium",				"orcmedium.obj",							(float)3 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_TOWER,					"obj/Construct/Orc/Kalimdor/Tower",					"orctower.obj",								(float)4 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_TWOSTORYHOUSE,			"obj/Construct/Orc/Kalimdor/Two-story",				"orctwostory.obj",							(float)5 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR,  E_S_OBJECTID_O_KD_ZEPPELINHOUSE,			"obj/Construct/Orc/Kalimdor/Zeppelinhouse",			"orczeppelinhouse.obj",						(float)6 / 8,		(float)5 / 8));
																																															
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_BEARPIT,				"obj/Construct/Orc/Northrend/Bearpit",				"nd_winterorc_bearpit.obj",					(float)7 / 8,		(float)5 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_CAP,					"obj/Construct/Orc/Northrend/Cap",					"nd_winterorc_cap1.obj",							0,			(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_CRANE,					"obj/Construct/Orc/Northrend/Crane",				"nd_orcwinter_crane.obj",					(float)1 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_FORGE,					"obj/Construct/Orc/Northrend/Forge",				"nd_winterorc_forge.obj",					(float)2 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_GATE,					"obj/Construct/Orc/Northrend/Gate",					"nd_winterorc_gate.obj",					(float)3 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_HORDEGUNSHIP,			"obj/Construct/Orc/Northrend/Hordegunship",			"nd_hordegunship.obj",						(float)4 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_HOVEL,					"obj/Construct/Orc/Northrend/Hovel",				"nd_winterorc_hovel.obj",					(float)5 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_SCAFFOLD,				"obj/Construct/Orc/Northrend/Scaffold",				"nd_winterorc_scaffoldng_01.obj",			(float)6 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_SHIP,					"obj/Construct/Orc/Northrend/Ship",					"orc_ship_01.obj",							(float)7 / 8,		(float)6 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_STABLE,					"obj/Construct/Orc/Northrend/Stable",				"nd_winterorc_stables.obj",							0,			(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_TOWER1,					"obj/Construct/Orc/Northrend/Tower1",				"nd_winterorc_tower.obj",					(float)1 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_TOWER2,					"obj/Construct/Orc/Northrend/Tower2",				"nd_winterorc_tower_open.obj",				(float)2 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_WALL1,					"obj/Construct/Orc/Northrend/Wall",					"nd_winterorc_wall.obj",					(float)3 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_WALL2,					"obj/Construct/Orc/Northrend/Wall2",				"nd_winterorc_wall2.obj",					(float)4 / 8,		(float)7 / 8));

	// 쓰레기값
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START,		E_S_OBJECTID_BLANK,						" ",												" ",										(float)7 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK2,						" ",												" ",										(float)7 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK3,						" ",												" ",										(float)7 / 8,		(float)7 / 8));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK4,						" ",												" ",										(float)7 / 8,		(float)7 / 8));
}																																																		
																																																		
void cObjectDB::Add(ST_OBJECTDATA* pData)																																								
{
	if (m_mapObject.find(pData->eSmallID) == m_mapObject.end())
	{
		m_mapObject[pData->eSmallID] = pData;
	}
}

void cObjectDB::Destroy()
{
	for each(auto it in m_mapObject)
	{
		SAFE_DELETE(it.second);
	}

	delete this;
}   