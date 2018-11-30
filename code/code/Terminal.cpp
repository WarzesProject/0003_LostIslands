// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Terminal.h"
#include "OpenGL.h"
#include "Log.h"
#include "Utility.h"
#include "Config.h"
#include "Palette.h"
#include "Geometry.h"

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
	for (auto &var : m_vars)
		var = 0;

	// Save main thread ID so we can catch threading violations.
	m_main_thread_id = std::this_thread::get_id();
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

	ProbeOpenGL();

	SetOptionsInternal(L"window: size=80x25, icon=default; font: default; terminal.encoding=utf8; input.filter={keyboard}");

	LOG(Info, "Terminal initialization complete");
	LOG(Info, "--------------------------------");

	if (!UserInit(this))
		return false;

	return true;
}
//-----------------------------------------------------------------------------
void Terminal::frame()
{
	UserFrame(this);
	Refresh();
	
	
	m_wnd.Input();
}
//-----------------------------------------------------------------------------
void Terminal::close()
{
	UserClose(this);
	g_codespace.clear();
	g_tilesets.clear();
	g_atlas.Clear();
	m_wnd.Close();
}
//-----------------------------------------------------------------------------
int Terminal::onWindowEvent(Event event)
{
	return 0;
}
//-----------------------------------------------------------------------------
