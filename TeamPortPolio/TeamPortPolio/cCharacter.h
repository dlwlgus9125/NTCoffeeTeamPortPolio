#pragma once
#include "ISteeringEntity.h"
#include "cSkinnedMesh.h"
#include "cObject.h"

enum FIGHT_STATE
{
	FIGHT_HIT,
	FIGHT_AVOID,
	FIGHT_BLOCK,
};

struct CharacterStatus
{
	float m_MaxHP;
	float m_HP;
	float m_Damage;
	int   m_avoid;
	int   m_defence;

	CharacterStatus()
	{
		m_MaxHP   = 100.0f;
		m_HP      = 100.0f;
		m_Damage  = 20.0f;
		m_avoid   = 2;
		m_defence = 2;
	}
	

	void SetHP(float Damage) { m_HP = MATH->Clamp(m_HP + Damage, 0.0f, m_MaxHP); }
};


class cCharacter : public cObject
{
protected:
	ISteeringEntity* m_CharacterEntity;
	ST_SPHERE        m_CollideSphere;
	ST_SPHERE        m_arrangeCollideSphere;
	ST_SPHERE        m_AttackCollideSphere;
	cSkinnedMesh*    m_pSkinnedMesh;
	MODE_STATE       m_currentMode;
	CharacterStatus  m_Status;
	bool             m_isDeath;
	//>>목표 타겟 평소엔 NULL
	cObject*         m_targetObject;
	//<<
	int              m_currentIndex;

	MeshSpere        m_MeshSphere;
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

	//전투용 충돌 체크
	ST_SPHERE        GetAttackCollider() { return m_AttackCollideSphere; }
	void             SetAttackColliderPos();

	void             SetDeath(bool death) { m_isDeath = death; }
	bool             IsDeath() { return m_isDeath; }

	FIGHT_STATE      Fight(cCharacter* attacker, cCharacter* defender);
};

