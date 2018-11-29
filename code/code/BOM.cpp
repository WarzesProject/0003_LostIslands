// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "BOM.h"

//-----------------------------------------------------------------------------
static uint8_t BOM_Bytes[][4] =
{
	{ 0xEF, 0xBB, 0xBF },       // UTF-8
	{ 0xFF, 0xFE },             // UTF-16 LE
	{ 0xFE, 0xFF },             // UTF-16 BE
	{ 0xFF, 0xFE, 0x00, 0x00 }, // UTF-32 LE
	{ 0x00, 0x00, 0xFE, 0xFF }  // UTF-32 BE
};

size_t GetBOMSize(BOM bom)
{
	switch (bom)
	{
	case BOM::UTF8:
		return 3;
	case BOM::UTF16LE:
	case  BOM::UTF16BE:
		return 2;
	case BOM::UTF32LE:
	case BOM::UTF32BE:
		return 4;
	default:
		return 0;
	}
}

BOM DetectBOM(std::istream& stream)
{
	uint8_t mark[4] = { 0 };
	size_t mark_size = 0;

	// Try to read some bytes and rewind.
	stream.read((char*)mark, 4);
	mark_size = stream.gcount();
	stream.seekg(0); // Assumes the stream was at its beginning.
	stream.clear(); // Because EOF is possible.

	if (mark_size == 4) // May be UTF-32 (four byte BOM)
	{
		if (::memcmp(mark, BOM_Bytes[(int)BOM::UTF32LE], 4) == 0)
			return BOM::UTF32LE;
		else if (::memcmp(mark, BOM_Bytes[(int)BOM::UTF32BE], 4) == 0)
			return BOM::UTF32BE;
	}

	if (mark_size >= 3) // May be UTF-8 (three byte BOM)
	{
		if (::memcmp(mark, BOM_Bytes[(int)BOM::UTF8], 3) == 0)
			return BOM::UTF8;
	}

	if (mark_size >= 2) // May be UTF-16 (two byte BOM)
	{
		if (::memcmp(mark, BOM_Bytes[(int)BOM::UTF16LE], 2) == 0)
			return BOM::UTF16LE;
		else if (::memcmp(mark, BOM_Bytes[(int)BOM::UTF16BE], 2) == 0)
			return BOM::UTF16BE;
	}

	// Failed to find an exact BOM marker. Try to guess file encoding
	// based on values of first bytes, assuming the first one or two
	// characters will be ASCII.
	if (mark_size >= 4)
	{
		if (!mark[0] && !mark[1] && !mark[2] && mark[3] <= 0x7f)     // 0 0 0 ?
			return BOM::ASCII_UTF32BE;
		else if (!mark[0] && mark[1] && !mark[2] && mark[3])          // 0 ? 0 ?
			return BOM::ASCII_UTF16BE;
		else if (mark[0] <= 0x7f && !mark[1] && !mark[2] && !mark[3]) // ? 0 0 0
			return BOM::ASCII_UTF32LE;
		else if (mark[0] && !mark[1] && mark[2] && !mark[3])          // ? 0 ? 0
			return BOM::ASCII_UTF16LE;
	}

	// If both are ASCII, assume compatible UTF-8.
	if (mark_size >= 2)
	{
		if (mark[0] <= 0x7f && mark[1] <= 0x7f)
			return BOM::ASCII_UTF8;
	}

	return BOM::None;
}

void PlaceBOM(std::ostream& stream, BOM bom)
{
	switch (bom)
	{
	case BOM::UTF8:
	case BOM::UTF16LE:
	case BOM::UTF16BE:
	case BOM::UTF32LE:
	case BOM::UTF32BE:
		stream.write((const char*)BOM_Bytes[(int)bom], GetBOMSize(bom));
		break;
	default:
		break;
	}
}

std::wostream& operator<<(std::wostream& stream, BOM bom)
{
	switch (bom)
	{
	case BOM::None:          stream << L"None";            break;
	case BOM::UTF8:          stream << L"UTF-8";           break;
	case BOM::UTF16LE:       stream << L"UTF-16 LE";       break;
	case BOM::UTF16BE:       stream << L"UTF-16 BE";       break;
	case BOM::UTF32LE:       stream << L"UTF-32 LE";       break;
	case BOM::UTF32BE:       stream << L"UTF-32 BE";       break;
	case BOM::ASCII_UTF8:    stream << L"ASCII UTF-8";     break;
	case BOM::ASCII_UTF16LE: stream << L"ASCII UTF-16 LE"; break;
	case BOM::ASCII_UTF16BE: stream << L"ASCII UTF-16 BE"; break;
	case BOM::ASCII_UTF32LE: stream << L"ASCII UTF-32 LE"; break;
	case BOM::ASCII_UTF32BE: stream << L"ASCII UTF-32 BE"; break;
	};

	return stream;
}