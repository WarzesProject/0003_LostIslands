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
		"window: size=80x25, cellsize=auto, title='Lost Island';"
		"font: default;"
		"input: filter={keyboard}"
		);
	terminal_color("green");
	terminal_set("output.vsync=false");

	terminal_color("white");
	terminal_set("U+E000: Media/Background.jpg");
	terminal_set("U+E001: Media/EasternDragon.png, resize=128x128, resize-filter=nearest");
	terminal_set("U+E002: Media/FiveElements.bmp, resize=128x128, resize-filter=bilinear");

	return true;
}
void UserFrame(Terminal *terminal)
{
	terminal_clear();
	
	terminal_put(0, 0, 0xE000); // Background
	terminal_put(5, 14, 0xE001); // Dragon
	terminal_put(5 + 18 * 1, 14, 0xE002); // FiveElements


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