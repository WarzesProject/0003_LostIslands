#pragma once

enum class BOM
{
	None = -1,
	UTF8 = 0,
	UTF16LE,
	UTF16BE,
	UTF32LE,
	UTF32BE,
	ASCII_Flag = 0x10,
	ASCII_UTF8 = ASCII_Flag,
	ASCII_UTF16LE,
	ASCII_UTF16BE,
	ASCII_UTF32LE,
	ASCII_UTF32BE
};

BOM DetectBOM(std::istream& stream);

void PlaceBOM(std::ostream& stream, BOM bom);

size_t GetBOMSize(BOM bom);

std::wostream& operator<<(std::wostream& stream, BOM bom);