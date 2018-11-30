#pragma once

#include "Event.h"
#include "Size.h"
#include "Point.h"

// For internal usage
#define TK_REDRAW        0x1001
#define TK_INVALIDATE    0x1002
#define TK_ACTIVATED     0x1004

class Window
{
public:
	typedef std::function<int(Event)> EventHandler;
	
	bool Init(EventHandler handler);
	
	void Swap();
	void Close();

	bool IsClose() const { return m_close; }

	void SetIcon(const std::wstring& filename) {}
	void SetTitle(const std::wstring &title);
	void SetSizeHints(Size increment, Size minimum_size);
	void SetClientSize(const Size& size);
	void SetVSync(bool enabled) {}
	void SetResizeable(bool resizeable) {}
	void SetFullscreen(bool fullscreen) {}
	void SetCursorVisibility(bool visible) {}

	Size GetActualSize();

	int PumpEvents();
private:
	bool initGL();
	void input();
	void windowEvent(const SDL_Event &event);
	EventHandler m_eventHandler;
	SDL_Window *m_window = nullptr;
	SDL_GLContext m_context = nullptr;
	SDL_Event m_curEvent;
	bool m_close = false;

	Size m_cell_size;
	Size m_minimum_size = Size(1,1);
	Point m_location;
	Size m_client_size;
	bool m_fullscreen = false;
	bool m_resizeable = false;

	bool m_maximized = false;
	bool m_restored = false;
	uint64_t m_last_mouse_click = 0;
	int m_consecutive_mouse_clicks = 0;
	bool m_suppress_wm_paint_once = false;
	bool m_mouse_cursor_enabled = true;
	bool m_mouse_cursor_visible = true;
	std::list<Event> m_events;
	bool m_resizing = false;
	bool m_has_been_shown = false;
};