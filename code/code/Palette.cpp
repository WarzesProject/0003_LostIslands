// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Palette.h"
#include "Utility.h"

//-----------------------------------------------------------------------------
Palette Palette::Instance;

HSV Convert(Color in)
{
	int min = std::min(in.r, std::min(in.g, in.b));
	int max = std::max(in.r, std::max(in.g, in.b));
	int delta = max - min;

	uint8_t h = 0, s = 0, v = max;
	if (delta == 0)
		return HSV{ in.a, h, s, v };

	if (max > 0)
		s = 255 * delta / max;
	else
		return HSV{ in.a, h, s, v }; // 0, 0, 0?

	if (max == in.r)
		h = 0 + 43 * (in.g - in.b) / delta; // between yellow & magenta
	else if (max == in.g)
		h = 85 + 43 * (in.b - in.r) / delta; // between cyan & yellow
	else
		h = 171 + 43 * (in.r - in.g) / delta; // between magenta & cyan

	return HSV{ in.a, h, s, v };
}

Color Convert(HSV hsv)
{
	uint8_t region, remainder, p, q, t;

	if (hsv.s == 0)
		return Color{ hsv.a, hsv.v, hsv.v, hsv.v };

	region = hsv.h / 43;
	remainder = (hsv.h - (region * 43)) * 6;

	p = (hsv.v * (255 - hsv.s)) >> 8;
	q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
	t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
	case 0:  return Color{ hsv.a, hsv.v, t, p };
	case 1:  return Color{ hsv.a, q, hsv.v, p };
	case 2:  return Color{ hsv.a, p, hsv.v, t };
	case 3:  return Color{ hsv.a, p, q, hsv.v };
	case 4:  return Color{ hsv.a, t, p, hsv.v };
	default: return Color{ hsv.a, hsv.v, p, q };
	}
}

Palette::Palette()
{
	Set(L"transparent", Color{ 0, 0, 0, 0 });
	Set(L"none", Color{ 0, 0, 0, 0 });

	Set(L"black", Color{ 0,   0,   0 });
	Set(L"white", Color{ 255, 255, 255 });
	Set(L"grey", Color(127, 127, 127));
	Set(L"gray", Color(127, 127, 127));
	Set(L"red", Color(255, 0, 0));
	Set(L"flame", Color(255, 63, 0));
	Set(L"orange", Color(255, 127, 0));
	Set(L"amber", Color(255, 191, 0));
	Set(L"yellow", Color(255, 255, 0));
	Set(L"lime", Color(191, 255, 0));
	Set(L"chartreuse", Color(127, 255, 0));
	Set(L"green", Color(0, 255, 0));
	Set(L"sea", Color(0, 255, 127));
	Set(L"turquoise", Color(0, 255, 191));
	Set(L"cyan", Color(0, 255, 255));
	Set(L"sky", Color(0, 191, 255));
	Set(L"azure", Color(0, 127, 255));
	Set(L"blue", Color(0, 0, 255));
	Set(L"han", Color(63, 0, 255));
	Set(L"violet", Color(127, 0, 255));
	Set(L"purple", Color(191, 0, 255));
	Set(L"fuchsia", Color(255, 0, 255));
	Set(L"magenta", Color(255, 0, 191));
	Set(L"pink", Color(255, 0, 127));
	Set(L"crimson", Color(255, 0, 63));
}

static Color Shade(Color base, const std::wstring& shade)
{
	if (shade.empty())
		return base;

	HSV hsv = Convert(base);

	if (shade == L"darkest")
		hsv.v *= 0.25f;
	else if (shade == L"darker")
		hsv.v *= 0.50f;
	else if (shade == L"dark")
		hsv.v *= 0.75f;
	else if (shade == L"light")
		hsv.s *= 0.75f;
	else if (shade == L"lighter")
		hsv.s *= 0.50f;
	else if (shade == L"lightest")
		hsv.s *= 0.25f;
	else
		return base;

	return Convert(hsv);
}

Color Palette::Get(std::wstring name)
{
	if (name.empty())
		return Color{ 255, 255, 255 };

	auto i = m_colors.find(name);
	if (i != m_colors.end())
		return i->second;

	try
	{
		// Split '[shade ]name' color description
		std::wstring shade;
		size_t space_pos = name.find(L' ');
		if (space_pos != std::wstring::npos)
		{
			shade = name.substr(0, space_pos);
			name = name.substr(space_pos + 1);
		}

		if (name[0] == L'#')
		{
			// Hexadecimal numeric format: #AARRGGBB or #RRGGBB
			uint32_t value = parse<uint32_t>(name.substr(1), std::hex);
			if (!(value & 0xFF000000))
				value |= 0xFF000000;
			return Shade(Color{ value }, shade);
		}
		else if (name.find(L',') != std::wstring::npos)
		{
			// Comma-separated format: A,R,G,B or R,G,B
			auto parts = split(name, L',');
			if (parts.size() == 3)
			{
				// R,G,B
				Color base(parse<int>(parts[0]), parse<int>(parts[1]), parse<int>(parts[2]));
				return Shade(base, shade);
			}
			else if (parts.size() == 4)
			{
				// A,R,G,B
				Color base(parse<int>(parts[0]), parse<int>(parts[1]), parse<int>(parts[2]), parse<int>(parts[3]));
				return Shade(base, shade);
			}
		}
		else if (name[0] == L'-' || (std::isdigit(name[0])))
		{
			// Decimal numeric format
			uint32_t value = (uint32_t)parse<int64_t>(name, std::dec);
			if (!(value & 0xFF000000))
				value |= 0xFF000000;
			return Shade(Color{ value }, shade);
		}
	}
	catch (std::exception& e)
	{
		// Nothing...
	}

	return Color{ 255, 255, 255 };
}

void Palette::Set(std::wstring name, Color base)
{
	m_colors[name] = base;
	for (std::wstring shade : {L"darkest", L"darker", L"dark", L"light", L"lighter", L"lightest"})
		m_colors[shade + L" " + name] = Shade(base, shade);
}