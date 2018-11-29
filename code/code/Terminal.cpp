// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Terminal.h"
#include "OpenGL.h"

extern bool UserInit(Terminal *terminal);
extern void UserFrame(Terminal *terminal);
extern void UserClose(Terminal *terminal);
//-----------------------------------------------------------------------------
#if PLATFORM_EMSCRIPTEN
void loopHandler()
{
	g_instance->frame();
	if (g_instance->m_wnd.IsClose())
		emscripten_cancel_main_loop();
}
#endif
//-----------------------------------------------------------------------------
Terminal *g_instance = nullptr;
//-----------------------------------------------------------------------------
Terminal::Terminal()
{
	g_instance = this;
}
//-----------------------------------------------------------------------------
Terminal::~Terminal()
{
	g_instance = nullptr;
}
//-----------------------------------------------------------------------------
void Terminal::Run()
{
	if (init() && UserInit(this))
	{
#if PLATFORM_EMSCRIPTEN
		emscripten_set_main_loop(loopHandler, -1, 1);
#elif PLATFORM_WINDOWS
		bool quit = false;
		while (!quit)
		{
			frame();
			quit = m_wnd.IsClose();
		}
#endif
	}
	UserClose(this);
	close();
}
//-----------------------------------------------------------------------------
bool Terminal::init()
{
	if (!m_wnd.Init(std::bind(&Terminal::onWindowEvent, this, std::placeholders::_1)))
		return false;

	ProbeOpenGL();

	return true;
}
//-----------------------------------------------------------------------------
void Terminal::frame()
{
	UserFrame(this);
	m_wnd.Swap();
	m_wnd.Input();
}
//-----------------------------------------------------------------------------
void Terminal::close()
{
	m_wnd.Close();
}
//-----------------------------------------------------------------------------
int Terminal::onWindowEvent(Event event)
{
	return 0;
}
//-----------------------------------------------------------------------------