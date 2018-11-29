// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Engine.h"
#include "Terminal.h"

Terminal *g_terminal = nullptr;
//-----------------------------------------------------------------------------
int terminal_open()
{
	g_terminal = new Terminal();
	g_terminal->Run();

	return 0;
}
//-----------------------------------------------------------------------------
void terminal_close()
{
	SafeDelete(g_terminal);
}
//-----------------------------------------------------------------------------