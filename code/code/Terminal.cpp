// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Terminal.h"
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
	if (init())
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
	close();
}
//-----------------------------------------------------------------------------
bool Terminal::init()
{
	if (!m_wnd.Init(std::bind(&Terminal::onWindowEvent, this, std::placeholders::_1)))
		return false;

	return true;
}
//-----------------------------------------------------------------------------
void Terminal::frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

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