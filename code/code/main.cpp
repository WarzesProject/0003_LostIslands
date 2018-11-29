// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Engine.h"
#include "Terminal.h"

//-----------------------------------------------------------------------------
#if COMPILER_MSVC
#	pragma comment(lib, "lib/x86/SDL2.lib")
#	pragma comment(lib, "lib/x86/SDL2main.lib")
#	pragma comment(lib, "OpenGL32.lib")
#endif

bool UserInit(Terminal *terminal)
{
	return true;
}
void UserFrame(Terminal *terminal)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
}
void UserClose(Terminal *terminal)
{

}

//-----------------------------------------------------------------------------
int main(int, char*[])
{
	terminal_open();
	terminal_close();
	return 0;
}
//-----------------------------------------------------------------------------