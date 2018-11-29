#pragma once

#include "Tileset.h"

class BitmapTileset : public Tileset
{
public:
	BitmapTileset(char32_t offset, std::vector<uint8_t> data, OptionGroup& options);
	Size GetBoundingBoxSize();

private:
	Size m_bounding_box_size;
};