#pragma once

#include "Tileset.h"

class DynamicTileset : public Tileset
{
public:
	DynamicTileset(char32_t offset, OptionGroup& options);
	DynamicTileset(char32_t offset, Size tile_size);
	Size GetBoundingBoxSize();
	bool Provides(char32_t code);
	std::shared_ptr<TileInfo> Get(char32_t code);
private:
	Size m_tile_size;
};