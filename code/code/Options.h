#pragma once

#include "Size.h"

struct Options
{
	// Terminal
	std::wstring terminal_encoding;
	bool terminal_encoding_affects_put;

	// Window
	Size window_size;
	Size window_cellsize;
	Size window_client_size;
	std::wstring window_title;
	std::wstring window_icon;
	bool window_resizeable;
	Size window_minimum_size;
	bool window_fullscreen;

	// Output
	bool output_postformatting;
	bool output_vsync;
	int output_tab_width;
	int output_texture_filter;

	// Input
	bool input_precise_mouse;
	char32_t input_cursor_symbol;
	int input_cursor_blink_rate;
	bool input_mouse_cursor;
	std::set<int> input_filter;
	bool input_alt_functions;
	
	Options();
};