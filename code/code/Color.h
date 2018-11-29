#pragma once

struct Color
{
	Color() :
		b(0), g(0), r(0), a(0)
	{ }

	Color(std::uint8_t alpha, std::uint8_t red, std::uint8_t green, std::uint8_t blue) :
		b(blue), g(green), r(red), a(alpha)
	{ }

	Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) :
		b(blue), g(green), r(red), a(0xFF)
	{ }

	Color(std::uint32_t bgra)
	{
		*(std::uint32_t*)this = bgra;
	}

	bool operator== (const Color& another) const
	{
		return *(const std::uint32_t*)this == *(const std::uint32_t*)&another;
	}

	bool operator!= (const Color& another) const
	{
		return !(*this == another);
	}

	operator uint32_t() const
	{
		return *(const std::uint32_t*)this;
	}

	Color operator+ (Color other)
	{
		return Color(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	uint8_t b, g, r, a; // BGRA8 format
};

struct HSV
{
	HSV() :
		h(0), s(0), v(0), a(255)
	{ }

	HSV(uint8_t h, uint8_t s, uint8_t v) :
		h(h), s(s), v(v), a(255)
	{ }

	HSV(uint8_t a, uint8_t h, uint8_t s, uint8_t v) :
		h(h), s(s), v(v), a(a)
	{ }

	uint8_t h, s, v, a;
};