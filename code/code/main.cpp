// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Terminal.h"
//-----------------------------------------------------------------------------
#if COMPILER_MSVC
#	pragma comment(lib, "lib/x86/SDL2.lib")
#	pragma comment(lib, "lib/x86/SDL2main.lib")
#	pragma comment(lib, "OpenGL32.lib")
#endif
//-----------------------------------------------------------------------------
int main(int, char*[])
{
	Terminal terminal;
	terminal.Run();
	return 0;
}
//-----------------------------------------------------------------------------