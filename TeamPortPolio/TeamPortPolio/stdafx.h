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

//<<::
// Mouse Whell
#define VK_WHELLUP		120
#define VK_WHELLDOWN	-120

// <<: KEY 
// Getkeysate "0x8000" == "KF_UP"
#define VK_A			0x41
#define VK_B			0x42
#define VK_C			0x43
#define VK_D			0x44
#define VK_E			0x45
#define VK_F			0x46
#define VK_G			0x47
#define VK_H			0x48
#define VK_I			0x49
#define VK_J			0x49
#define VK_K			0x4A
#define VK_L			0x4B
#define VK_M			0x4C
#define VK_N			0x4E
#define VK_O			0x4F
#define VK_P			0x50
#define VK_Q			0x51
#define VK_R			0x52
#define VK_S			0x53
#define VK_T			0x54
#define VK_U			0x55
#define VK_V			0x56
#define VK_W			0x57
#define VK_X			0x58
#define VK_Y			0x59
#define VK_Z			0x5A


// NUM KEY
#define VK_0		0x30
#define VK_1		0x31
#define VK_2		0x32
#define VK_3		0x33
#define VK_4		0x34
#define VK_5		0x35
#define VK_6		0x36
#define VK_7		0x37
#define VK_8		0x38
#define VK_9		0x39
// <<:

enum SCENE_TAG
{
	SCENE_NONE, SCENE_TITLE, SCENE_LOADING, SCENE_TOWN, SCENE_LOGIN,
};

enum UI_TAG
{
	UI_NONE, UI_OBJECT, UI_IMAGE, UI_TEXT, UI_BUTTON, UI_MINIMAP, 
};

enum UI_STATE
{
	UI_IDLE, UI_MOUSEOVER, UI_PRESSED, UI_CLICKED, UI_SELECTED, 
};

enum FONT_TAG
{
	FONT_DEF,
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

#define WND_WIDTH 1280
#define WND_HEIGHT 768

#define MAX_LOADSTRING 100

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

// �÷��̾� ��� �߰�.
enum PLAYER_MODE_STATE
{
	IDLE_PLAYER_MODE,
	WALK_PLAYER_MODE,
	FIGHTING_PLAYER_MODE,
	DEFENDING_PLAYER_MODE,
};
//

struct ST_TAB
{
	string text;
	D3DXVECTOR3 pos;
	int state;

	ST_TAB(string text, D3DXVECTOR3 pos, int state)
	{
		this->text = text;
		this->pos = pos;
		this->state = state;
	}
};

enum MODE_STATE
{
	FIGHTING_MODE, 
	DEFENDING_MODE,
};

/////////////////////////////////////////////////////////////////
// �ִϸ��̼� Ű ��
/////////////////////////////////////////////////////////////////
// �÷��̾� Ű��
enum P_STATE // P: Player
{
	P_STAND,
	P_WALK,
	P_BACKWALK,
	P_RUN,
	P_READYATTACK,
	P_BATTLEWALK,
	P_BATTLERUN,
	P_ATTACK1,
	P_ATTACK2,
	P_ATTACK3,
	P_SHEILDBLOCK,
	P_SHEILDUP,
	P_HIT,
	P_BATTLECRY,
	P_KNOCKDOWN,
	P_DEATH,
	//���� ��� �߰�.
	//P_BOWATTACK1,
	//P_BOWATTACK2,
};



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
#include "cFontManager.h"
//<<
#include "cRay.h"

