// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Engine.h"
#include "Terminal.h"
#include "Encoding.h"
#include "Palette.h"

//-----------------------------------------------------------------------------
int terminal_set8(const int8_t* value)
{
	if (!g_instance || !value) return -1;
	auto& encoding = g_instance->GetEncoding();
	return g_instance->SetOptions(encoding.Convert((const char*)value));
}

int terminal_set16(const int16_t* value)
{
	if (!g_instance || !value) return -1;
	return g_instance->SetOptions(UCS2Encoding().Convert((const char16_t*)value));
}

int terminal_set32(const int32_t* value)
{
	if (!g_instance || !value) return -1;
	return g_instance->SetOptions(UCS4Encoding().Convert((const char32_t*)value));
}

void terminal_color(color_t color)
{
	if (!g_instance) return;
	g_instance->SetForeColor(Color(color));
}

void terminal_bkcolor(color_t color)
{
	if (!g_instance) return;
	g_instance->SetBackColor(Color(color));
}

color_t color_from_name8(const int8_t* name)
{
	if (!g_instance || !name) return -1;
	auto& encoding = g_instance->GetEncoding();
	return Palette::Instance.Get(encoding.Convert((const char*)name));
}

color_t color_from_name16(const int16_t* name)
{
	if (!g_instance || !name) return -1;
	return Palette::Instance.Get(UCS2Encoding().Convert((const char16_t*)name));
}

color_t color_from_name32(const int32_t* name)
{
	if (!g_instance || !name) return -1;
	return Palette::Instance.Get(UCS4Encoding().Convert((const char32_t*)name));
}

void terminal_clear()
{
	if (!g_instance) return;
	g_instance->Clear();
}

#define TERMINAL_PRINT_OR_MEASURE(x, y, a, cast, measure) \
	if (!g_instance || !s) { \
		if (out_w) *out_w = 0; \
		if (out_h) *out_h = 0; \
		return; \
	} \
	auto size = g_instance->Print(x, y, w, h, a, cast, false, measure); \
	if (out_w) *out_w = size.width; \
	if (out_h) *out_h = size.height;

void terminal_print_ext8(int x, int y, int w, int h, int align, const int8_t* s, int* out_w, int* out_h)
{
	TERMINAL_PRINT_OR_MEASURE(x, y, align, g_instance->GetEncoding().Convert((const char*)s), false)
}

void terminal_print_ext16(int x, int y, int w, int h, int align, const int16_t* s, int* out_w, int* out_h)
{
	TERMINAL_PRINT_OR_MEASURE(x, y, align, UCS2Encoding().Convert((const char16_t*)s), false)
}

void terminal_print_ext32(int x, int y, int w, int h, int align, const int32_t* s, int* out_w, int* out_h)
{
	TERMINAL_PRINT_OR_MEASURE(x, y, align, UCS4Encoding().Convert((const char32_t*)s), false)
}