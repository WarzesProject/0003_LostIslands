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

inline int terminal_set(const char *s)
{
	return terminal_set8((const int8_t*)s);
}

void terminal_color(color_t color);
void terminal_bkcolor(color_t color);
color_t color_from_name8(const int8_t* name);
color_t color_from_name16(const int16_t* name);
color_t color_from_name32(const int32_t* name);

inline color_t color_from_name(const char* name)
{
	return color_from_name8((const int8_t*)name);
}

inline color_t color_from_wname(const wchar_t* name)
{
	return TERMINAL_CAT(color_from_name, TERMINAL_WCHAR_SUFFIX)((const TERMINAL_WCHAR_TYPE*)name);
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

void terminal_clear();

void terminal_print_ext8(int x, int y, int w, int h, int align, const int8_t* s, int* out_w, int* out_h);
void terminal_print_ext16(int x, int y, int w, int h, int align, const int16_t* s, int* out_w, int* out_h);
void terminal_print_ext32(int x, int y, int w, int h, int align, const int32_t* s, int* out_w, int* out_h);

inline dimensions_t terminal_wprint(int x, int y, const wchar_t* s)
{
	dimensions_t ret;
	TERMINAL_CAT(terminal_print_ext, TERMINAL_WCHAR_SUFFIX)(x, y, 0, 0, TK_ALIGN_DEFAULT, (const TERMINAL_WCHAR_TYPE*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t terminal_print(int x, int y, const wchar_t* s)
{
	return terminal_wprint(x, y, s);
}

