#pragma once
#include "ISteeringEntity.h"
#include "cSkinnedMesh.h"
#include "cObject.h"


struct CharacterStatus
{
	float m_HP;
	float m_Damage;

};

class cCharacter : public cObject
{
protected:
	ISteeringEntity* m_CharacterEntity;
	ST_SPHERE        m_CollideSphere;
	ST_SPHERE        m_arrangeCollideSphere;
	ST_SPHERE        m_attackCollider;
	cSkinnedMesh*    m_pSkinnedMesh;
	MODE_STATE       m_currentMode;
	

	//>>목표 타겟 평소엔 NULL
	cObject*         m_targetObject;
	//<<
	int              m_currentIndex;
public:
	cCharacter();
	virtual ~cCharacter();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

	ST_SPHERE        GetSphere() { return m_CollideSphere; }
	ST_SPHERE        GetArrangeSphere() { return m_arrangeCollideSphere; }
	ISteeringEntity* GetCharacterEntity() { return m_CharacterEntity; }
	cSkinnedMesh*    GetMesh() { return m_pSkinnedMesh; }
	MODE_STATE       GetMode() { return m_currentMode; }

	void             SetMode(int mode) { m_currentMode = (MODE_STATE)mode; }
	int              GetIndex() { return m_currentIndex; }
	void             SetIndex(int index) { m_currentIndex = index; }
	void             RenderSphere();

	cObject*         GetTargetObject() { return m_targetObject; }
	void             SetTargetObject(cObject* object) { m_targetObject = object; }

	D3DXMATRIXA16 SetAttackCollider();
	ST_SPHERE     GetAttackCollider() { return m_attackCollider; }
};

