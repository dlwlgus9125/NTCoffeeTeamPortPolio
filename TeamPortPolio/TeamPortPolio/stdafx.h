// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <afxwin.h>
#include <windows.h>
#include <process.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <conio.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//>> �ڷ���
#include <vector>
#include <map>
#include <list>
#include <queue>
//<<

//>> ���
#include <string>
#include <set>
#include <functional>
#include <iostream>
#include <assert.h>
#include <ctime>
#include <dshow.h>
#pragma comment(lib, "Strmiids.lib")

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <mmsystem.h >
#pragma comment(lib, "winmm.lib")

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

using namespace std;
//<<

enum SCENE_TAG
{
	SCENE_NONE, SCENE_TITLE, SCENE_LOADING, SCENE_TOWN, SCENE_LOGIN,
};

//>> define �� ����ü
extern HWND	g_hWnd;
extern HCURSOR g_Cursor;
extern LPD3DXSPRITE g_Sprite;
#define SAFE_RELEASE(p) { if(p) p->Release(); p = NULL; }
#define SAFE_DELETE(p) { if(p) delete p; p = NULL; }	// << :
#define SAFE_ADD_REF(p) { if(p) p->AddRef() ; }
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = NULL;}
// >> : 
#define SINGLETONE(class_name) \
		private : \
			class_name(void) ;  \
			~class_name(void) ; \
		public :\
			static class_name* GetInstance() \
			{ \
				static class_name instance ; \
				return &instance ; \
			} 

#define EPSILON             0.0001f
#define ANGLE_TO_RADIAN		0.0174533f
#define RADIAN_TO_ANGLE		57.2958f


struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };

	bool operator == (ST_PNT_VERTEX pnt) { return p == pnt.p&&n == pnt.n	&&t == pnt.t; }
};


struct ST_POS_SAMPLE
{
	int			n;
	D3DXVECTOR3 v;

	ST_POS_SAMPLE()
		: n(0), v(0, 0, 0)
	{
	}
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION  v;

	ST_ROT_SAMPLE()
		: n(0), v(0, 0, 0, 0)
	{
	}
};

struct MeshSpere
{
	LPD3DXMESH       m_pMeshSphere;
	D3DMATERIAL9    m_stMtlSphere;
	D3DXVECTOR3     m_vCenter;
	float           m_radius;
	MeshSpere() {};
};

struct ST_SPHERE
{
	ST_SPHERE() {}
	ST_SPHERE(D3DXVECTOR3 pos, float radius) { vCenter = pos; fRadius = radius; }
	bool isPicked;
	D3DXVECTOR3 vCenter;
	float fRadius;
};

struct ST_SIZEN
{
	int nWidth;
	int nHeight;
	ST_SIZEN() : nWidth(0), nHeight(0) {}
	ST_SIZEN(int _w, int _h) : nWidth(_w), nHeight(_h) {}
};

enum MODE_STATE
{
	FIGHTING_MODE, 
	DEFENDING_MODE,
};

/////////////////////////////////////////////////////////////////
// �ִϸ��̼� Ű ��
/////////////////////////////////////////////////////////////////
// ����
enum FG_STATE // F: Footman, G: Grunt
{
	FG_STAND,
	FG_WALK,
	FG_BACKWALK,
	FG_RUN,
	FG_READYATTACK,
	FG_BATTLEWALK,
	FG_BATTLERUN,
	FG_ATTACK1,
	FG_ATTACK2,
	FG_ATTACK3,
	FG_SHEILDBLOCK,
	FG_SHEILDUP,
	FG_HIT,
	FG_BATTLECRY,
	FG_KNOCKDOWN,
	FG_DEATH,
};

// �ú�
enum BOWMAN_STATE
{
	B_STAND,
	B_WALK,
	B_BACKWALK,
	B_RUN,
	B_READYATTACK,
	B_BATTLEWALK,
	B_BATTLERUN,
	B_BOWATTACK1,
	B_BOWATTACK2,
	B_BOWSHEILD,
	B_HIT,
	B_BATTLECRY,
	B_KNOCKDOWN,
	B_DEATH,
};

// �⺴
enum KNIGHT_STATE
{
	K_STAND,
	K_WALK,
	K_RUN,
	K_HIT,
	K_BATTLECRY,
	K_DEATH,
};

enum ITEM_TAG
{
	ITEM_NONE = 0,
	ITEM_MELEE,
	ITEM_RANGE,
};

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}


//>>include
#include "Singleton.h"
#include "cCamera.h"
#include "cDeviceManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cTimeManager.h"
#include "Math.h"
#include "cTextureManager.h"
#include "cStateMachine.h"
#include "cAstarManager.h"
#include "cObjectDB.h"
#include "cObject.h"
#include "cMapManager.h"
#include "cUIManager.h"
//<<
#include "cRay.h"

