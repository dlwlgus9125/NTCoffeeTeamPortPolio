#pragma once
#include "stdafx.h"
#include "cUICursor.h"

cUICursor::cUICursor()
{
}

cUICursor::~cUICursor()
{
}

void cUICursor::SetupCursor()
{
	m_Cursor[0] = (LoadCursorFromFile("cursor/gam1340.cur"));
	m_Cursor[1] = (LoadCursorFromFile("cursor/link select.cur"));
	m_Cursor[2] = (LoadCursorFromFile("cursor/unavalible.cur"));
}


void cUICursor::Update_Cursosr()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		g_Cursor = m_Cursor[1];
	}
	else 	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		g_Cursor = m_Cursor[2];
	}
	else
	{
		g_Cursor = m_Cursor[0];
	}
	SetCursor(g_Cursor);
}
