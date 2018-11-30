#pragma once

class Terminal;
extern bool UserInit(Terminal *terminal);
extern void UserFrame(Terminal *terminal);
extern void UserClose(Terminal *terminal);

/*
* Utility macro trick which allows macro-in-macro expansion
*/
#define TERMINAL_CAT(a, b) TERMINAL_PRIMITIVE_CAT(a, b)
#define TERMINAL_PRIMITIVE_CAT(a, b) a ## b

/*
* wchar_t has different sized depending on platform. Furthermore, it's size
* can be changed for GCC compiler.
*/
#if !defined(__SIZEOF_WCHAR_T__)
#  if defined(_WIN32)
#    define __SIZEOF_WCHAR_T__ 2
#  else
#    define __SIZEOF_WCHAR_T__ 4
#  endif
#endif

#if __SIZEOF_WCHAR_T__ == 2
#define TERMINAL_WCHAR_SUFFIX 16
#define TERMINAL_WCHAR_TYPE int16_t
#else // 4
#define TERMINAL_WCHAR_SUFFIX 32
#define TERMINAL_WCHAR_TYPE int32_t
#endif

/*
* Text printing alignment.
*/
#define TK_ALIGN_DEFAULT       0
#define TK_ALIGN_LEFT          1
#define TK_ALIGN_RIGHT         2
#define TK_ALIGN_CENTER        3
#define TK_ALIGN_TOP           4
#define TK_ALIGN_BOTTOM        8
#define TK_ALIGN_MIDDLE       12

/*
* Terminal uses unsigned 32-bit value for color representation in ARGB order (0xAARRGGBB), e. g.
* a) solid red is 0xFFFF0000
* b) half-transparent green is 0x8000FF00
*/
typedef uint32_t color_t;

typedef struct dimensions_t_
{
	int width;
	int height;
}
dimensions_t;

int terminal_set8(const int8_t* value);
int terminal_set16(const int16_t* value);
int terminal_set32(const int32_t* value);
void terminal_clear();
void terminal_clear_area(int x, int y, int w, int h);
void terminal_crop(int x, int y, int w, int h);
void terminal_layer(int index);
void terminal_color(color_t color);
void terminal_bkcolor(color_t color);
void terminal_composition(int mode);
void terminal_font8(const int8_t* name);
void terminal_font16(const int16_t* name);
void terminal_font32(const int32_t* name);
void terminal_put(int x, int y, int code);
void terminal_put_ext(int x, int y, int dx, int dy, int code, color_t* corners);
int terminal_pick(int x, int y, int index);
color_t terminal_pick_color(int x, int y, int index);
color_t terminal_pick_bkcolor(int x, int y);
void terminal_print_ext8(int x, int y, int w, int h, int align, const int8_t* s, int* out_w, int* out_h);
void terminal_print_ext16(int x, int y, int w, int h, int align, const int16_t* s, int* out_w, int* out_h);
void terminal_print_ext32(int x, int y, int w, int h, int align, const int32_t* s, int* out_w, int* out_h);
void terminal_measure_ext8(int w, int h, const int8_t* s, int* out_w, int* out_h);
void terminal_measure_ext16(int w, int h, const int16_t* s, int* out_w, int* out_h);
void terminal_measure_ext32(int w, int h, const int32_t* s, int* out_w, int* out_h);
int terminal_read_str8(int x, int y, int8_t* buffer, int max);
int terminal_read_str16(int x, int y, int16_t* buffer, int max);
int terminal_read_str32(int x, int y, int32_t* buffer, int max);
const int8_t* terminal_get8(const int8_t* key, const int8_t* default_);
const int16_t* terminal_get16(const int16_t* key, const int16_t* default_);
const int32_t* terminal_get32(const int32_t* key, const int32_t* default_);
color_t color_from_name8(const int8_t* name);
color_t color_from_name16(const int16_t* name);
color_t color_from_name32(const int32_t* name);

inline int terminal_set(const char *s)
{
	return terminal_set8((const int8_t*)s);
}

inline int terminal_wset(const wchar_t *s)
{
	return TERMINAL_CAT(terminal_set, TERMINAL_WCHAR_SUFFIX)((const TERMINAL_WCHAR_TYPE*)s);
}

inline void terminal_font(const char* name)
{
	terminal_font8((const int8_t*)name);
}

inline void terminal_wfont(const wchar_t* name)
{
	TERMINAL_CAT(terminal_font, TERMINAL_WCHAR_SUFFIX)((const TERMINAL_WCHAR_TYPE*)name);
}

inline dimensions_t terminal_print(int x, int y, const char* s)
{
	dimensions_t ret;
	terminal_print_ext8(x, y, 0, 0, TK_ALIGN_DEFAULT, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}



inline dimensions_t terminal_wprint(int x, int y, const wchar_t* s)
{
	dimensions_t ret;
	TERMINAL_CAT(terminal_print_ext, TERMINAL_WCHAR_SUFFIX)(x, y, 0, 0, TK_ALIGN_DEFAULT, (const TERMINAL_WCHAR_TYPE*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_print_ext(int x, int y, int w, int h, int align, const char* s)
{
	dimensions_t ret;
	terminal_print_ext8(x, y, w, h, align, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_wprint_ext(int x, int y, int w, int h, int align, const wchar_t* s)
{
	dimensions_t ret;
	TERMINAL_CAT(terminal_print_ext, TERMINAL_WCHAR_SUFFIX)(x, y, w, h, align, (const TERMINAL_WCHAR_TYPE*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_measure(const char* s)
{
	dimensions_t ret;
	terminal_measure_ext8(0, 0, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_wmeasure(const wchar_t* s)
{
	dimensions_t ret;
	TERMINAL_CAT(terminal_measure_ext, TERMINAL_WCHAR_SUFFIX)(0, 0, (const TERMINAL_WCHAR_TYPE*)s, &ret.width, &ret.height);
	return ret;
}


inline dimensions_t terminal_measure_ext(int w, int h, const char* s)
{
	dimensions_t ret;
	terminal_measure_ext8(w, h, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_wmeasure_ext(int w, int h, const wchar_t* s)
{
	dimensions_t ret;
	TERMINAL_CAT(terminal_measure_ext, TERMINAL_WCHAR_SUFFIX)(w, h, (const TERMINAL_WCHAR_TYPE*)s, &ret.width, &ret.height);
	return ret;
}

inline int terminal_read_str(int x, int y, char* buffer, int max)
{
	return terminal_read_str8(x, y, (int8_t*)buffer, max);
}

inline int terminal_read_wstr(int x, int y, wchar_t* buffer, int max)
{
	return TERMINAL_CAT(terminal_read_str, TERMINAL_WCHAR_SUFFIX)(x, y, (TERMINAL_WCHAR_TYPE*)buffer, max);
}

inline const char* terminal_get(const char* key, const char* default_ =(const char*)0)
{
	return (const char*)terminal_get8((const int8_t*)key, (const int8_t*)default_);
}

inline const wchar_t* terminal_wget(const wchar_t* key, const wchar_t* default_ =(const wchar_t*)0)
{
	return (const wchar_t*)TERMINAL_CAT(terminal_get, TERMINAL_WCHAR_SUFFIX)((const TERMINAL_WCHAR_TYPE*)key, (const TERMINAL_WCHAR_TYPE*)default_);
}

inline color_t color_from_name(const char* name)
{
	return color_from_name8((const int8_t*)name);
}

inline color_t color_from_wname(const wchar_t* name)
{
	return TERMINAL_CAT(color_from_name, TERMINAL_WCHAR_SUFFIX)((const TERMINAL_WCHAR_TYPE*)name);
}

inline int terminal_set(const wchar_t* s)
{
	return terminal_wset(s);
}

inline void terminal_color(const char* name)
{
	terminal_color(color_from_name(name));
}

inline void terminal_color(const wchar_t* name)
{
	terminal_color(color_from_wname(name));
}

inline void terminal_bkcolor(const char* name)
{
	terminal_bkcolor(color_from_name(name));
}

inline void terminal_bkcolor(const wchar_t* name)
{
	terminal_bkcolor(color_from_wname(name));
}

inline void terminal_font(const wchar_t* name)
{
	terminal_wfont(name);
}

inline void terminal_put_ext(int x, int y, int dx, int dy, int code)
{
	terminal_put_ext(x, y, dx, dy, code, 0);
}

inline dimensions_t terminal_print(int x, int y, const wchar_t* s)
{
	return terminal_wprint(x, y, s);
}

inline dimensions_t terminal_print_ext(int x, int y, int w, int h, int align, const wchar_t* s)
{
	return terminal_wprint_ext(x, y, w, h, align, s);
}

inline dimensions_t terminal_measure(const wchar_t* s)
{
	return terminal_wmeasure(s);
}

inline dimensions_t terminal_measure_ext(int w, int h, const wchar_t* s)
{
	return terminal_wmeasure_ext(w, h, s);
}

inline int terminal_read_str(int x, int y, wchar_t* buffer, int max)
{
	return terminal_read_wstr(x, y, buffer, max);
}

inline color_t color_from_name(const wchar_t* name)
{
	return color_from_wname(name);
}

inline int terminal_pick(int x, int y)
{
	return terminal_pick(x, y, 0);
}

inline color_t terminal_pick_color(int x, int y)
{
	return terminal_pick_color(x, y, 0);
}

inline const wchar_t* terminal_get(const wchar_t* key, const wchar_t* default_ = (const wchar_t*)0)
{
	return terminal_wget(key, default_);
}

template<typename T, typename C> T terminal_get(const C* key, const T& default_ = T())
{
	const C* result_str = terminal_get(key, (const C*)0);
	if (result_str[0] == C(0))
		return default_;
	T result;
	return (bool)(std::basic_istringstream<C>(result_str) >> result) ? result : default_;
}

/*
* Color routines
*/
inline color_t color_from_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return ((color_t)a << 24) | (r << 16) | (g << 8) | b;
}