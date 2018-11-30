// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Window.h"
#include "Size.h"
#include "Utility.h"

//-----------------------------------------------------------------------------
static int MapWindowsScancodeToTerminal(uint8_t scancode)
{
	static std::map<uint8_t, int> mapping =
	{
		{ SDLK_a,        TK_A },
		{ SDLK_b,        TK_B },
		{ SDLK_c,        TK_C },
		{ SDLK_d,        TK_D },
		{ SDLK_e,        TK_E },
		{ SDLK_f,        TK_F },
		{ SDLK_g,        TK_G },
		{ SDLK_h,        TK_H },
		{ SDLK_i,        TK_I },
		{ SDLK_j,        TK_J },
		{ SDLK_k,        TK_K },
		{ SDLK_l,        TK_L },
		{ SDLK_m,        TK_M },
		{ SDLK_n,        TK_N },
		{ SDLK_o,        TK_O },
		{ SDLK_p,        TK_P },
		{ SDLK_q,        TK_Q },
		{ SDLK_r,        TK_R },
		{ SDLK_s,        TK_S },
		{ SDLK_t,        TK_T },
		{ SDLK_u,        TK_U },
		{ SDLK_v,        TK_V },
		{ SDLK_w,        TK_W },
		{ SDLK_x,        TK_X },
		{ SDLK_y,        TK_Y },
		{ SDLK_z,        TK_Z },
		{ SDLK_1,        TK_1 },
		{ SDLK_2,        TK_2 },
		{ SDLK_3,        TK_3 },
		{ SDLK_4,        TK_4 },
		{ SDLK_5,        TK_5 },
		{ SDLK_6,        TK_6 },
		{ SDLK_7,        TK_7 },
		{ SDLK_8,        TK_8 },
		{ SDLK_9,        TK_9 },
		{ SDLK_0,        TK_0 },
		{ SDLK_RETURN,   TK_RETURN },
		{ SDLK_ESCAPE,   TK_ESCAPE },
		{ SDLK_BACKSPACE,TK_BACKSPACE },
		{ SDLK_TAB,      TK_TAB },
		{ SDLK_SPACE,    TK_SPACE },
		{ SDLK_MINUS,    TK_MINUS },
		{ SDLK_EQUALS,   TK_EQUALS },
		{ SDLK_LEFTBRACKET,TK_LBRACKET },
		{ SDLK_RIGHTBRACKET,TK_RBRACKET },
		{ SDLK_BACKSLASH,TK_BACKSLASH },
		{ SDLK_SEMICOLON,TK_SEMICOLON },
		{ SDLK_QUOTE,    TK_APOSTROPHE },
		{ SDLK_BACKQUOTE,TK_GRAVE },
		{ SDLK_COMMA,    TK_COMMA },
		{ SDLK_PERIOD,   TK_PERIOD },
		{ SDLK_SLASH,    TK_SLASH },
		{ SDLK_F1,       TK_F1 },
		{ SDLK_F2,       TK_F2 },
		{ SDLK_F3,       TK_F3 },
		{ SDLK_F4,       TK_F4 },
		{ SDLK_F5,       TK_F5 },
		{ SDLK_F6,       TK_F6 },
		{ SDLK_F7,       TK_F7 },
		{ SDLK_F8,       TK_F8 },
		{ SDLK_F9,       TK_F9 },
		{ SDLK_F10,      TK_F10 },
		{ SDLK_F11,      TK_F11 },
		{ SDLK_F12,      TK_F12 },
		{ SDLK_PAUSE,    TK_PAUSE },
		{ SDLK_INSERT,   TK_INSERT },
		{ SDLK_HOME,     TK_HOME },
		{ SDLK_PAGEUP,   TK_PAGEUP },
		{ SDLK_DELETE,   TK_DELETE },
		{ SDLK_END,      TK_END },
		{ SDLK_PAGEDOWN, TK_PAGEDOWN },
		{ SDLK_RIGHT,    TK_RIGHT },
		{ SDLK_LEFT,     TK_LEFT },
		{ SDLK_DOWN,     TK_DOWN },
		{ SDLK_UP,       TK_UP },
		{ SDLK_LSHIFT,   TK_SHIFT },
		{ SDLK_RSHIFT,   TK_SHIFT },
		{ SDLK_LCTRL,    TK_CONTROL },
		{ SDLK_RCTRL,    TK_CONTROL },
		{ SDLK_LALT,     TK_ALT },
		{ SDLK_RALT,     TK_ALT },
		{ SDLK_KP_0,     TK_KP_0 },
		{ SDLK_KP_1,     TK_KP_1 },
		{ SDLK_KP_2,     TK_KP_2 },
		{ SDLK_KP_3,     TK_KP_3 },
		{ SDLK_KP_4,     TK_KP_4 },
		{ SDLK_KP_5,     TK_KP_5 },
		{ SDLK_KP_6,     TK_KP_6 },
		{ SDLK_KP_7,     TK_KP_7 },
		{ SDLK_KP_8,     TK_KP_8 },
		{ SDLK_KP_9,     TK_KP_9 },
		{ SDLK_KP_MULTIPLY,TK_KP_MULTIPLY },
		{ SDLK_KP_PLUS,  TK_KP_PLUS },
		{ SDLK_KP_MINUS, TK_KP_MINUS },
		{ SDLK_KP_PERIOD,TK_KP_PERIOD },
		{ SDLK_KP_DIVIDE,TK_KP_DIVIDE }
	};

	return mapping[scancode];
}
//-----------------------------------------------------------------------------
bool Window::Init(EventHandler handler)
{
	m_eventHandler = handler;

	const Size size(640, 480);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.width, size.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	if (!initGL())
		return false;

	SDL_StartTextInput(); //Enable text input

	return true;
}
int Window::PumpEvents()
{
	input();

	// Leave only the last TK_REDRAW event.
	int redraws = 0;
	for (auto i = m_events.rbegin(); i != m_events.rend(); i++)
	{
		if (i->code == TK_REDRAW && ++redraws > 1)
			m_events.erase(std::next(i).base()); // Witchcraft.
	}

	int count = m_events.size();
	for (auto &event : m_events)
		m_eventHandler(std::move(event));
	m_events.clear();
	return count;
}
//-----------------------------------------------------------------------------
void Window::input()
{
	while (SDL_PollEvent(&m_curEvent) != 0)
	{
		if (m_curEvent.type == SDL_QUIT)
		{
			m_close = true;
			m_events.push_back(TK_CLOSE);
			return;
		}
		else if (m_curEvent.type == SDL_WINDOWEVENT)
		{
			windowEvent(m_curEvent);
			return;
		}
		else if (m_curEvent.type == SDL_TEXTINPUT)
		{
			TODO("WM_CHAR");
			return;
		}
		else if (m_curEvent.type == SDL_KEYDOWN || m_curEvent.type == SDL_KEYUP)
		{
			bool pressed = (m_curEvent.type == SDL_KEYDOWN);
			uint8_t scancode = m_curEvent.key.keysym.sym;			
			const int code = MapWindowsScancodeToTerminal(scancode);
			if (code > 0)
			{
				Event event(code | (pressed ? 0 : TK_KEY_RELEASED));
				event[code] = pressed ? 1 : 0;
				m_events.push_back(event);
			}

			return;
		}
		else if (m_curEvent.type == SDL_MOUSEMOTION)
		{
			Point precise_position(m_curEvent.motion.x, m_curEvent.motion.y);

			if (precise_position.x < 0) precise_position.x = 0;
			if (precise_position.y < 0) precise_position.y = 0;

			Event event(TK_MOUSE_MOVE);
			event[TK_MOUSE_PIXEL_X] = precise_position.x;
			event[TK_MOUSE_PIXEL_Y] = precise_position.y;
			m_events.push_back(event);
			return;
		}
		else if (m_curEvent.type == SDL_MOUSEWHEEL)
		{
			Event event(TK_MOUSE_SCROLL);
			event[TK_MOUSE_WHEEL] = m_curEvent.wheel.y > 0 ? -1 : +1;
			m_events.push_back(event);
			return;
		}
		else if (m_curEvent.type == SDL_MOUSEBUTTONDOWN || m_curEvent.type == SDL_MOUSEBUTTONUP)
		{
			bool pressed = m_curEvent.type == SDL_MOUSEBUTTONDOWN;
			if (pressed)
				m_consecutive_mouse_clicks = m_curEvent.button.clicks;

			int code = 0;
			switch (m_curEvent.button.button)
			{
			case SDL_BUTTON_LEFT:   code = TK_MOUSE_LEFT; break;
			case SDL_BUTTON_MIDDLE: code = TK_MOUSE_MIDDLE; break;
			case SDL_BUTTON_RIGHT:  code = TK_MOUSE_RIGHT; break;
			case SDL_BUTTON_X1:     code = TK_MOUSE_X1; break;
			case SDL_BUTTON_X2:     code = TK_MOUSE_X2; break;
			}

			Event event(code | (pressed ? 0 : TK_KEY_RELEASED));
			event[code] = pressed ? 1 : 0;
			event[TK_MOUSE_CLICKS] = pressed ? m_consecutive_mouse_clicks : 0;
			m_events.push_back(event);
		}
	}
}
//-----------------------------------------------------------------------------
void Window::Swap()
{
	SDL_GL_SwapWindow(m_window);
}
//-----------------------------------------------------------------------------
void Window::Close()
{	
	SDL_StopTextInput(); //Disable text input
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
//-----------------------------------------------------------------------------
bool Window::initGL()
{
	GLenum error = GL_NO_ERROR;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n",  error );
		return false;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n",  error );
		return false;
	}

	glClearColor(0.f, 0.f, 0.f, 1.f);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %d\n", error );
		return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void Window::SetTitle(const std::wstring &title)
{
	SDL_SetWindowTitle(m_window, WSTRtoUTF8(title).c_str());
}
//-----------------------------------------------------------------------------
void Window::SetClientSize(const Size& size)
{
	SDL_SetWindowSize(m_window, size.width, size.height);
	m_client_size = size;
}
//-----------------------------------------------------------------------------
void Window::SetSizeHints(Size increment, Size minimum_size)
{
	m_cell_size = increment;
	m_minimum_size = minimum_size;

	if (m_minimum_size.width < 1) m_minimum_size.width = 1;
	if (m_minimum_size.height < 1) m_minimum_size.height = 1;
}
//-----------------------------------------------------------------------------
Size Window::GetActualSize()
{
	return m_client_size;
}
//-----------------------------------------------------------------------------
void Window::windowEvent(const SDL_Event &event)
{
	switch (event.window.event)
	{
	case SDL_WINDOWEVENT_EXPOSED:
		m_events.push_back(TK_REDRAW);
		break;
	case SDL_WINDOWEVENT_SHOWN:
		m_events.push_back(TK_ACTIVATED);
		break;	
	//case SDL_WINDOWEVENT_HIDDEN:
	//	SDL_Log("Window %d hidden", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_MOVED:
	//	SDL_Log("Window %d moved to %d,%d", event.window.windowID, event.window.data1, event.window.data2);
	//	break;
	//case SDL_WINDOWEVENT_MINIMIZED:
	//	SDL_Log("Window %d minimized", event.window.windowID);
	//	break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		m_maximized = true;
		m_events.push_back(TK_INVALIDATE);
		break;
	case SDL_WINDOWEVENT_RESTORED:
		m_restored = true;
		m_events.push_back(TK_INVALIDATE);
		break;
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		if (m_maximized || m_restored)
		{
			m_maximized = m_restored = false;
			m_client_size.width = event.window.data1;
			m_client_size.height = event.window.data2;
			{
				Event event(TK_RESIZED);
				event[TK_WIDTH] = m_client_size.width;
				event[TK_HEIGHT] = m_client_size.height;
				m_events.push_back(event);
			}
		}
				
		if (m_resizing)
		{
			// During resizing, Windows does not return control so it is necessary
			// to send events directly to the Terminal.
			m_eventHandler(TK_INVALIDATE);
			m_eventHandler(TK_REDRAW);
		}
		else
		{
			m_events.push_back(TK_INVALIDATE);
			m_events.push_back(TK_REDRAW);
		}
		break;

	case SDL_WINDOWEVENT_RESIZED:
		m_client_size.width = event.window.data1;
		m_client_size.height = event.window.data2;
		{
			Size snapped = m_cell_size*std::floor(m_client_size / m_cell_size.As<float>());
			if (snapped != m_client_size)
				m_client_size = snapped;

			m_suppress_wm_paint_once = true;

			m_events.push_back(Event{ TK_RESIZED,{ { TK_WIDTH, m_client_size.width },{ TK_HEIGHT, m_client_size.height } } });
			m_events.push_back(TK_INVALIDATE);
			m_events.push_back(TK_REDRAW);

			m_resizing = false;
		}
		break;
	
	//case SDL_WINDOWEVENT_ENTER:
	//	SDL_Log("Mouse entered window %d", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_LEAVE:
	//	SDL_Log("Mouse left window %d", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_FOCUS_GAINED:
	//	SDL_Log("Window %d gained keyboard focus", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_FOCUS_LOST:
	//	SDL_Log("Window %d lost keyboard focus", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_CLOSE:
	//	SDL_Log("Window %d closed", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_TAKE_FOCUS:
	//	SDL_Log("Window %d is offered a focus", event.window.windowID);
	//	break;
	//case SDL_WINDOWEVENT_HIT_TEST:
	//	SDL_Log("Window %d has a special hit test", event.window.windowID);
	//	break;
	//default:
	//	SDL_Log("Window %d got unknown event %d", event.window.windowID, event.window.event);
	//	break;
	}
}
//-----------------------------------------------------------------------------