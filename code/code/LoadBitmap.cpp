// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "LoadBitmap.h"

//-----------------------------------------------------------------------------
Bitmap LoadBMP(std::istream& stream);
Bitmap LoadPNG(std::istream& stream);
Bitmap LoadJPEG(std::istream& stream);

Bitmap LoadBitmap(const std::vector<uint8_t>& data)
{
	if (data.size() < 4)
		throw std::runtime_error("LoadBitmap: invalid data size");

	unsigned char magic_bytes[4] = { data[0], data[1], data[2], data[3] };

	// FIXME: rewrite bitmap loading routines. Maybe just use stb_image?
	std::istringstream stream{ std::string((const char*)&data[0], data.size()) };

	if (!strncmp((const char*)magic_bytes, "\x89PNG", 4))
	{
		// This must be PNG resource
		return LoadPNG(stream);
	}
	else if (!strncmp((const char*)magic_bytes, "BM", 2))
	{
		// This must be BMP DIB resource
		return LoadBMP(stream);
	}
	else if (!strncmp((const char*)magic_bytes, "\xFF\xD8", 2))
	{
		// Must be a JPEG rsource
		return LoadJPEG(stream);
	}
	else
	{
		throw std::runtime_error("unsupported image format");
	}
}
