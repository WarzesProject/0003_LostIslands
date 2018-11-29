// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Bitmap.h"
#include "Utility.h"
#include "Log.h"
#include <PicoPNG.h>

Bitmap LoadPNG(std::istream& stream)
{
	std::string in_buffer((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	std::vector<unsigned char> out_buffer;
	unsigned long width, height;

	if (decodePNG(out_buffer, width, height, (const unsigned char*)in_buffer.c_str(), in_buffer.size(), true))
	{
		throw std::runtime_error("PNG decode failed");
	}

	// Not very efficient, though still pretty fast. TODO: benchmark, rewrite
	for (size_t i = 0; i<width*height * 4; i += 4)
	{
		uint8_t temp = out_buffer[i + 0];
		out_buffer[i + 0] = out_buffer[i + 2];
		out_buffer[i + 2] = temp;
	}

	LOG(Trace, L"Loaded PNG image, " << width << L"x" << height);
	return Bitmap(Size(width, height), (Color*)out_buffer.data());
}