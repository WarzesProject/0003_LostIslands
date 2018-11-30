#pragma once

#include "Window.h"
#include "Stage.h"
#include "Options.h"
#include "OptionGroup.h"
#include "Encoding.h"
#include "Event.h"

static const std::vector<float> kScaleSteps =
{
	0.75f, 1.0f, 1.25f, 1.5f, 2.0f, 3.0f
};

static const int kScaleDefault = 1;

/*
* Virtual key-codes for internal terminal states/variables.
* These can be accessed via terminal_state function.
*/
#define TK_WIDTH            0xC0 /* Terminal window size in cells */
#define TK_HEIGHT           0xC1
#define TK_CELL_WIDTH       0xC2 /* Character cell size in pixels */
#define TK_CELL_HEIGHT      0xC3
#define TK_COLOR            0xC4 /* Current foregroung color */
#define TK_BKCOLOR          0xC5 /* Current background color */
#define TK_LAYER            0xC6 /* Current layer */
#define TK_COMPOSITION      0xC7 /* Current composition state */
#define TK_CHAR             0xC8 /* Translated ANSI code of last produced character */
#define TK_WCHAR            0xC9 /* Unicode codepoint of last produced character */
#define TK_EVENT            0xCA /* Last dequeued event */
#define TK_FULLSCREEN       0xCB /* Fullscreen state */

/*
* Input result codes for terminal_read function.
*/
#define TK_INPUT_NONE          0
#define TK_INPUT_CANCELLED    -1

class Terminal
{
public:
	Terminal();
	~Terminal();
	
	void Run();

	int SetOptions(const std::wstring& value);
	void Clear();
	void Clear(int x, int y, int w, int h);
	void SetCrop(int x, int y, int w, int h);
	void SetLayer(int layer_index);
	void SetForeColor(Color color);
	void SetBackColor(Color color);
	void SetComposition(int mode);
	void SetFont(std::wstring name);
	void Put(int x, int y, int code);
	void PutExtended(int x, int y, int dx, int dy, int code, Color* corners);
	int Pick(int x, int y, int index);
	Color PickForeColor(int x, int y, int index);
	Color PickBackColor(int x, int y);
	Size Print(int x, int y, int w, int h, int align, std::wstring str, bool raw, bool measure_only);

	const Encoding8& GetEncoding() const;

private:
	bool init();
	void frame();
	void close();
	
	int onWindowEvent(Event event);

#if PLATFORM_EMSCRIPTEN
	friend void loopHandler();
#endif

	void SetOptionsInternal(const std::wstring& params);
	void ValidateWindowOptions(OptionGroup& group, Options& options);
	void ValidateInputOptions(OptionGroup& group, Options& options);
	void ValidateOutputOptions(OptionGroup& group, Options& options);
	void ValidateTerminalOptions(OptionGroup& group, Options& options);
	void ValidateLoggingOptions(OptionGroup& group, Options& options);
	bool ParseInputFilter(const std::wstring& s, std::set<int>& out);
	void PutInternal(int x, int y, int dx, int dy, char32_t code, Color* colors);
	void Refresh();
	void Render();
	int Redraw();
	void ConfigureViewport();

	Window m_wnd;
	World m_world;
	Options m_options;

	bool m_show_grid = false;
	bool m_viewport_modified = false;
	Rectangle m_viewport_scissors;
	bool m_viewport_scissors_enabled;
	int m_scale_step = kScaleDefault;
	Rectangle m_stage_area;
	SizeF m_stage_area_factor;

	std::deque<Event> m_input_queue;
	std::array<int32_t, 256> m_vars;
	std::unique_ptr<Encoding8> m_encoding;

	std::thread::id m_main_thread_id;
	enum state_t { kHidden, kVisible, kClosed } m_state = kHidden;

	bool m_alt_pressed = false; // For alt-functions interception.
};

extern Terminal *g_instance;