// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Geometry.h"
#include "Utility.h"
#include "Bitmap.h"
#include "Log.h"
#include <NanoJPEG.h>

std::string to_string(const Jpeg::Decoder::DecodeResult& value)
{
	switch (value)
	{
	case Jpeg::Decoder::OK: return "OK";
	case Jpeg::Decoder::NotAJpeg: return "not a JPEG";
	case Jpeg::Decoder::Unsupported: return "unsupported format";
	case Jpeg::Decoder::OutOfMemory: return "out of memory";
	case Jpeg::Decoder::InternalError: return "internal error";
	case Jpeg::Decoder::SyntaxError: return "syntax error";
	default: return "unknown error";
	}
}

Bitmap LoadJPEG(std::istream& stream)
{
	std::istreambuf_iterator<char> eos;
	std::string contents(std::istreambuf_iterator<char>(stream), eos);
	std::unique_ptr<Jpeg::Decoder> decoder(new Jpeg::Decoder((const unsigned char*)contents.data(), contents.size()));

	if (decoder->GetResult() != Jpeg::Decoder::OK)
	{
		throw std::runtime_error(std::string("Failed to load JPEG resource: ") + to_string(decoder->GetResult()));
	}

	Size size(decoder->GetWidth(), decoder->GetHeight());

	if (size.width <= 0 || size.height <= 0)
	{
		throw std::runtime_error(std::string("Failed to load JPEG resource: internal loader error"));
	}

	Bitmap result(size, Color());
	uint8_t* data = decoder->GetImage();
	bool is_color = decoder->IsColor();

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			if (is_color)
			{
				result(x, y) = Color(0xFF, data[0], data[1], data[2]);
				data += 3;
			}
			else
			{
				result(x, y) = Color(0xFF, data[0], data[0], data[0]);
				data += 1;
			}
		}
	}

	return result;
}