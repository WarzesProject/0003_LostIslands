#pragma once

#include "Atlas.h"
#include "Color.h"
#include "Tileset.h"

struct Leaf
{
	Leaf();
	Color color[4];
	int16_t dx, dy;
	char32_t code;
	uint8_t flags;
	uint8_t reserved;
	static const uint8_t CornerColored = 0x01;
};

struct Cell
{
	std::vector<Leaf> leafs;
};

struct Layer
{
	Layer(Size size);
	std::vector<Cell> cells;
	Rectangle crop;
};

struct Scene
{
	std::vector<Layer> layers;
	std::vector<Color> background;
};

struct Stage
{
	Size size;
	Scene frontbuffer;
	Scene backbuffer;
	void Resize(Size size);
};

struct State
{
	Size cellsize;      // Current cellsize; different from Options.window_cellsize in that this one is always properly set.
	Size half_cellsize; // Cached value used in leaf drawing.
	Color color;
	Color bkcolor;
	int composition;
	int layer;
	char32_t font_offset;
	State();
};

struct World
{
	Stage stage;
	State state;
};