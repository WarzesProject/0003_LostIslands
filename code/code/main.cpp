// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Engine.h"
#include "Terminal.h"
#include "Log.h"

//-----------------------------------------------------------------------------
#if COMPILER_MSVC
#	pragma comment(lib, "lib/x86/SDL2.lib")
#	pragma comment(lib, "lib/x86/SDL2main.lib")
#	pragma comment(lib, "OpenGL32.lib")
#endif

bool UserInit(Terminal *terminal)
{
	terminal_set(
		"window: size=80x25, cellsize=auto, title='Omni: menu';"
		"font: default;"
		"input: filter={keyboard}"
		);
	terminal_color("green");
	terminal_set("output.vsync=false");


	return true;
}
void UserFrame(Terminal *terminal)
{
	terminal_clear();
	terminal_print(0, 3, L"[color=orange]3.[/color] Unicode support: Кириллица");
}
void UserClose(Terminal *terminal)
{

}

//-----------------------------------------------------------------------------
int main(int, char*[])
{
	Terminal terminal;
	terminal.Run();
	return 0;
}
//-----------------------------------------------------------------------------