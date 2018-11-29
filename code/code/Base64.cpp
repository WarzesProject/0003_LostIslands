// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Base64.h"

//-----------------------------------------------------------------------------
static const signed char b64_indexes[] = // TODO: reformat
{
	/* 0 - 31 / 0x00 - 0x1f */
	-1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	/* 32 - 63 / 0x20 - 0x3f */
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, 62, -1, -1, -1, 63  /* ... , '+', ... '/' */
	,   52, 53, 54, 55, 56, 57, 58, 59  /* '0' - '7'          */
	,   60, 61, -1, -1, -1,  0, -1, -1  /* '8', '9', ...      */
										/* 64 - 95 / 0x40 - 0x5f */
	,   -1, 0,  1,  2,  3,  4,  5,  6   /* ..., 'A' - 'G'     */
	,   7,  8,  9,  10, 11, 12, 13, 14  /* 'H' - 'O'          */
	,   15, 16, 17, 18, 19, 20, 21, 22  /* 'P' - 'W'          */
	,   23, 24, 25, -1, -1, -1, -1, -1  /* 'X', 'Y', 'Z', ... */
										/* 96 - 127 / 0x60 - 0x7f */
	,   -1, 26, 27, 28, 29, 30, 31, 32  /* ..., 'a' - 'g'     */
	,   33, 34, 35, 36, 37, 38, 39, 40  /* 'h' - 'o'          */
	,   41, 42, 43, 44, 45, 46, 47, 48  /* 'p' - 'w'          */
	,   49, 50, 51, -1, -1, -1, -1, -1  /* 'x', 'y', 'z', ... */

	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1

	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1

	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1

	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
	,   -1, -1, -1, -1, -1, -1, -1, -1
};
//-----------------------------------------------------------------------------
std::vector<std::uint8_t> Base64::Decode(const std::string& s)
{
	if (s.empty())
	{
		return std::vector<std::uint8_t>();
	}

	if (s.length() % 4 != 0)
	{
		throw std::invalid_argument("[Base64::Decode] Malformed string, not a multilply of four in length");
	}

	size_t size = (s.length() / 4) * 3;
	if (s[s.length() - 1] == '=') size -= 1;
	if (s[s.length() - 2] == '=') size -= 1;

	std::vector<std::uint8_t> result(size);

	auto b64code = [&](unsigned char c) -> unsigned char
	{
		signed char b;

		if (c >= 0x7F || (b = b64_indexes[c]) == -1)
		{
			throw std::invalid_argument("[Base64::Decode] Invalid character in string");
		}

		return (unsigned char)b;
	};

	size_t index = 0;

	for (size_t i = 0; i<s.length() / 4; i++)
	{
		std::uint32_t block = 0;

		for (size_t j = 0; j<4; j++) block = (block << 6) | (b64code(s[i * 4 + j]) & 0xFF);

		for (size_t j = 0; j<3 && index<size; j++)
		{
			result[index++] = ((unsigned char*)&block)[2 - j];
		}
	}

	return result;
}
//-----------------------------------------------------------------------------