#pragma once

#include "Color.h"

class Palette
{
public:
	Palette();
	Color Get(std::wstring name);
	void Set(std::wstring name, Color base);
	static Palette Instance;

protected:
	std::unordered_map<std::wstring, Color> m_colors;
};