#pragma once

#include "Texture.h"

struct TexCoords
{
	TexCoords();
	TexCoords(float tu1, float tv1, float tu2, float tv2);
	float tu1, tv1, tu2, tv2;
};

enum class TileAlignment
{
	Unknown,
	Center,
	DeadCenter,
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

std::wostream& operator<<(std::wostream& s, const TileAlignment& value);
std::wistream& operator>>(std::wistream& s, TileAlignment& value);

class Tileset;

class AtlasTexture;

struct TileInfo
{
	TileInfo();
	Tileset* tileset;
	AtlasTexture* texture;
	Bitmap bitmap;
	Rectangle useful_space;
	Rectangle total_space;
	TexCoords texture_coords;
	Point offset;
	Size spacing;
	TileAlignment alignment;
	bool is_animated;
};

class AtlasTexture
{
public:
	AtlasTexture(Size initial_size);
	AtlasTexture(std::shared_ptr<TileInfo> sprite);
	bool IsEmpty() const;
	bool Add(std::shared_ptr<TileInfo> tile);
	void Remove(std::shared_ptr<TileInfo> tile, bool copy_bitmap_back = false);
	void Bind();
	void Defragment();
	void ApplyTextureFilter();

private:
	bool TryGrow();
	TexCoords CalcTexCoords(const Rectangle& region);
	Texture m_texture;
	Bitmap m_canvas;
	std::list<Rectangle> m_dirty_regions;
	std::list<Rectangle> m_spaces;
	std::list<std::shared_ptr<TileInfo>> m_tiles;
};

class Atlas
{
public:
	void Add(std::shared_ptr<TileInfo> tile);
	void Remove(std::shared_ptr<TileInfo> tile);
	void Defragment();
	void CleanUp();
	void Clear();
	void ApplyTextureFilter();

private:
	std::list<std::shared_ptr<AtlasTexture>> m_textures;
};

extern Atlas g_atlas;