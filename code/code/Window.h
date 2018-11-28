#pragma once

class Window
{
public:
	typedef std::function<int(Event)> EventHandler;
	
	bool Init(EventHandler handler);
	void Input();
	void Swap();
	void Close();

	bool IsClose() const { return m_close; }

private:
	bool initGL();
	EventHandler m_eventHandler;
	SDL_Window *m_window = nullptr;
	SDL_GLContext m_context = nullptr;
	SDL_Event m_curEvent;
	bool m_close = false;
};