#pragma once

#include "Tileset.h"
#include "Encoding.h"

class TrueTypeTileset : public Tileset
{
public:
	TrueTypeTileset(char32_t offset, std::vector<uint8_t> data, OptionGroup& options);
	bool Provides(char32_t code);
	std::shared_ptr<TileInfo> Get(char32_t code);
	Size GetBoundingBoxSize();

private:
	FT_UInt GetGlyphIndex(char32_t code);
	Size m_tile_size;
	TileAlignment m_alignment;
	std::unique_ptr<Encoding8> m_codepage;
	std::vector<uint8_t> m_font_data;
	std::shared_ptr<FT_Library> m_font_library;
	std::shared_ptr<FT_Face> m_font_face;
	FT_Render_Mode m_render_mode;
	FT_Int32 m_hinting;
	bool m_monospace;
	bool m_use_box_drawing;
	bool m_use_block_elements;
};