#pragma once

#include "Rectangle.h"
#include "Color.h"

enum class ResizeFilter
{
	Nearest,
	Bilinear,
	Bicubic
};

std::wostream& operator<<(std::wostream& s, const ResizeFilter& value);
std::wistream& operator>>(std::wistream& s, ResizeFilter& value);

enum class ResizeMode
{
	Stretch,
	Fit,
	Crop
};

std::wostream& operator<<(std::wostream& s, const ResizeMode& value);
std::wistream& operator>>(std::wistream& s, ResizeMode& value);

class Bitmap
{
public:
	Bitmap();
	Bitmap(Size size, Color color);
	Bitmap(Size size, const Color* data);
	Bitmap(const Bitmap& from);
	Bitmap(Bitmap&& from);
	void Swap(Bitmap& other);
	Bitmap& operator=(Bitmap other);
	Size GetSize() const;
	bool IsEmpty() const;
	void Blit(const Bitmap& src, Rectangle src_region, Point dst_location);
	void Blit(const Bitmap& src, Point location);
	void BlitUnchecked(const Bitmap& src, Point location);
	Bitmap Extract(Rectangle region);
	const Color& operator() (Point p) const;
	const Color& operator() (int x, int y) const;
	Color& operator() (Point p);
	Color& operator() (int x, int y);
	const Color* GetData() const;
	bool HasAlpha() const;
	void MakeTransparent(Color color);
	Bitmap Resize(Size size, ResizeFilter filter, ResizeMode mode);
	Point CenterOfMass() const;

protected:
	Size m_size;
	std::vector<Color> m_data;
};