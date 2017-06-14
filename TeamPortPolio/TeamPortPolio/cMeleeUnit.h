#pragma once
#include "cUnit.h"
class cMeleeUnit :
	public cUnit
{
public:
	cMeleeUnit(IEntity* pLeader, D3DXVECTOR3 offset);;
	~cMeleeUnit();
};

