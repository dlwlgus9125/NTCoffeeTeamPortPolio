#pragma once
#include "ISteeringEntity.h"
#include "cSkinnedMesh.h"
#include "cObject.h"

class cCharacter : public cObject
{
protected:
	ISteeringEntity* m_CharacterEntity;
	ST_SPHERE        m_CollideSphere;
	ST_SPHERE        m_arrangeCollideSphere;
	cSkinnedMesh*    m_pSkinnedMesh;
	MODE_STATE       m_currentMode;
	int              m_currentIndex;
public:
	cCharacter();
	virtual ~cCharacter();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

	ST_SPHERE        GetSphere() { return m_CollideSphere; }
	ISteeringEntity* GetCharacterEntity() { return m_CharacterEntity; }
	cSkinnedMesh*    GetMesh() { return m_pSkinnedMesh; }
	MODE_STATE       GetMode() { return m_currentMode; }

	void             SetMode(int mode) { m_currentMode = (MODE_STATE)mode; }
	int              GetCurrentIndex() { return m_currentIndex; }
	void RenderSphere();

};

