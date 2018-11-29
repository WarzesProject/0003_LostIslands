// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Options.h"
//-----------------------------------------------------------------------------
Options::Options() :
	terminal_encoding_affects_put(true),
	window_size(0, 0),
	window_cellsize(0, 0),
	window_title(L"BearLibTerminal"),
	window_icon(L":default_icon"),
	window_resizeable(false),
	window_minimum_size(1, 1),
	window_fullscreen(false),
	output_postformatting(true),
	output_vsync(true),
	output_tab_width(4),
	output_texture_filter(GL_LINEAR),
	input_precise_mouse(false),
	input_cursor_symbol('_'),
	input_cursor_blink_rate(500),
	input_mouse_cursor(true),
	input_alt_functions(true)
{ }