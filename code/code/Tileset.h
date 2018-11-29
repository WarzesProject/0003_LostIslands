#pragma once

#include "Atlas.h"
#include "OptionGroup.h"

class Tileset
{
public:
	Tileset(char32_t offset);
	virtual ~Tileset();
	char32_t GetOffset() const;
	virtual bool Provides(char32_t code);
	virtual std::shared_ptr<TileInfo> Get(char32_t code);
	virtual Size GetBoundingBoxSize() = 0; // FIXME: refactor to tile property
	virtual Size GetSpacing() const;

	static const char32_t kFontOffsetMultiplier = 0x01000000;
	static const char32_t kFontOffsetMask = 0xFF000000;
	static const char32_t kCharOffsetMask = 0x00FFFFFF;
	static std::shared_ptr<Tileset> Create(OptionGroup& options, char32_t offset);
	static bool IsFontOffset(char32_t offset);

protected:
	char32_t m_offset;
	std::unordered_map<char32_t, std::shared_ptr<TileInfo>> m_cache;
	Size m_spacing;
};

extern std::unordered_map<char32_t, std::shared_ptr<TileInfo>> g_codespace;

extern std::map<char32_t, std::shared_ptr<Tileset>> g_tilesets;

extern std::shared_ptr<Tileset> g_dynamic_tileset;

void AddTileset(std::shared_ptr<Tileset> tileset);

void RemoveTileset(std::shared_ptr<Tileset> tileset);

void RemoveTileset(char32_t offset);

bool IsDynamicTile(char32_t code);

Bitmap GenerateDynamicTile(char32_t code, Size size);

void UpdateDynamicTileset(Size cell_size);
