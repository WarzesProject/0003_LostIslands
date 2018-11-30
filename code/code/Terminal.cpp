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
	m_wnd.PumpEvents();
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
	if (event.code == TK_REDRAW)
	{
		Render();
		return 0;
	}
	else if (event.code == TK_INVALIDATE)
	{
		m_viewport_modified = true;
		return 0;
	}
	else if (event.code == TK_RESIZED)
	{
		// Remove all unprocessed resize events as the latest one overrides them.
		for (auto i = m_input_queue.begin(); i != m_input_queue.end(); )
		{
			if (i->code == TK_RESIZED)
				i = m_input_queue.erase(i);
			else
				i++;
		}

		float scale_factor = kScaleSteps[m_scale_step];
		Size &cellsize = m_world.state.cellsize;
		Size size
		(
			std::floor(event[TK_WIDTH] / scale_factor / cellsize.width),
			std::floor(event[TK_HEIGHT] / scale_factor / cellsize.height)
		);

		if (size == m_world.stage.size)
		{
			// This event do not changes stage size, ignore.
			return 0;
		}
		else
		{
			// Translate pixels to cells.
			event[TK_WIDTH] = size.width;
			event[TK_HEIGHT] = size.height;
		}
	}
	else if (event.code == TK_MOUSE_MOVE)
	{
		int& pixel_x = event[TK_MOUSE_PIXEL_X];
		int& pixel_y = event[TK_MOUSE_PIXEL_Y];

		// Shift coordinates relative to stage area
		pixel_x -= m_stage_area.left;
		pixel_y -= m_stage_area.top;

		// Scale coordinates back to virtual pixels.
		pixel_x *= m_stage_area_factor.width;
		pixel_y *= m_stage_area_factor.height;

		// Cell location of mouse pointer
		Size& cellsize = m_world.state.cellsize;
		Point location(pixel_x / cellsize.width, pixel_y / cellsize.height);
		location = Rectangle(m_world.stage.size).Clamp(location);
		event[TK_MOUSE_X] = location.x;
		event[TK_MOUSE_Y] = location.y;

		// If application do not read events fast enough, do not flood it with mouse moves.
		if (!m_input_queue.empty() && m_input_queue.back().code == TK_MOUSE_MOVE)
		{
			// Replace the last, yet unread event with the most recent one.
			m_input_queue.back() = event;
			return 0;
		}

		// Ignore mouse movement events that do not change coarse cursor location.
		if (!m_options.input_precise_mouse)
		{
			Point last_location{ m_vars[TK_MOUSE_X], m_vars[TK_MOUSE_Y] };

			// Search for last mouse movement event in the queue.
			for (auto i = m_input_queue.rbegin(); i != m_input_queue.rend(); i++)
			{
				if (i->code == TK_MOUSE_MOVE)
				{
					last_location = Point{ (*i)[TK_MOUSE_X], (*i)[TK_MOUSE_Y] };
					break;
				}
			}

			if (location == last_location)
			{
				return 0;
			}
		}
	}
	else if ((event.code & 0xFF) == TK_ALT && m_options.input_alt_functions)
	{
		m_alt_pressed = event.properties[TK_ALT];
	}
	
	if (m_options.input_alt_functions && m_alt_pressed)
	{
		if (event.code == TK_G)
		{
			// Alt+G: toggle grid
			m_show_grid = !m_show_grid;
			Render();
			return 0;
		}
		else if (event.code == TK_RETURN)
		{
			// Alt+ENTER: toggle fullscreen.
			m_vars[TK_FULLSCREEN] = !m_vars[TK_FULLSCREEN];
			m_options.window_fullscreen = m_vars[TK_FULLSCREEN];
			m_wnd.SetFullscreen(m_options.window_fullscreen);
			return 0;
		}
		else if (event.code == TK_MINUS || event.code == TK_EQUALS || event.code == TK_0 ||
			event.code == TK_KP_MINUS || event.code == TK_KP_PLUS || event.code == TK_KP_0)
		{
			if (m_vars[TK_FULLSCREEN])
			{
				// No scaling in fullscreen mode (does not make sense anyway).
				return 0;
			}

			// Alt+(plus/minus/zero): adjust user window scaling.
			if ((event.code == TK_MINUS || event.code == TK_KP_MINUS) && m_scale_step > 0)
			{
				m_scale_step -= 1;
			}
			else if ((event.code == TK_EQUALS || event.code == TK_KP_PLUS) && m_scale_step < kScaleSteps.size() - 1)
			{
				m_scale_step += 1;
			}
			else if ((event.code == TK_0 || event.code == TK_KP_0) && m_scale_step != 1)
			{
				m_scale_step = 1;
			}

			float scale = kScaleSteps[m_scale_step];

			if (m_options.window_resizeable || m_options.window_client_size.Area() == 0)
			{
				// Resizeable window always snaps to cell borders.
				m_wnd.SetSizeHints(m_world.state.cellsize * scale, m_options.window_minimum_size);
				m_wnd.SetClientSize(m_world.state.cellsize * m_world.stage.size * scale);
			}
			else
			{
				// Overriden client-size is scaled with everything else.
				m_wnd.SetClientSize(m_options.window_client_size * scale);
			}

			return 0;
		}
		else if (event.code == TK_F)
		{
			m_options.output_texture_filter = g_texture_filter =
				(g_texture_filter == GL_LINEAR) ? GL_NEAREST : GL_LINEAR;
			g_atlas.ApplyTextureFilter();
			Render();
			return 0;
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------
