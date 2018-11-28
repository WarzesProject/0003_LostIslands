#pragma once

#include "Window.h"

class Terminal
{
public:
	Terminal();
	~Terminal();
	
	void Run();

private:
	bool init();
	void frame();
	void close();
	
	int onWindowEvent(Event event);

#if PLATFORM_EMSCRIPTEN
	friend void loopHandler();
#endif

	Window m_wnd;
};

extern Terminal *g_instance;