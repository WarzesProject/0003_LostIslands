#pragma once

#include "Point.h"
#include "Size.h"

template<typename T> struct BasicRectangle
{
	T left, top, width, height;

	BasicRectangle() :
		left(),
		top(),
		width(),
		height()
	{ }

	BasicRectangle(T left, T top, T width, T height) :
		left(left),
		top(top),
		width(width),
		height(height)
	{ }

	BasicRectangle(BasicSize<T> size) :
		left(),
		top(),
		width(size.width),
		height(size.height)
	{ }

	BasicRectangle(BasicPoint<T> location, BasicSize<T> size) :
		left(location.x),
		top(location.y),
		width(size.width),
		height(size.height)
	{ }

	template<typename U> BasicRectangle(const BasicRectangle<U>& from) :
		left(from.left),
		top(from.top),
		width(from.width),
		height(from.height)
	{ }

	BasicPoint<T> Location() const
	{
		return BasicPoint<T>(left, top);
	}

	BasicSize<T> Size() const
	{
		return BasicSize<T>(width, height);
	}

	T Area() const
	{
		return width*height;
	}

	bool Contains(BasicPoint<T> point) const
	{
		return
			(point.x >= left) &&
			(point.y >= top) &&
			(point.x < left + width) &&
			(point.y < top + height);
	}

	bool Contains(BasicRectangle<T> rectangle) const
	{
		return
			(rectangle.left >= left) &&
			(rectangle.top >= top) &&
			(rectangle.left + rectangle.width <= left + width) &&
			(rectangle.top + rectangle.height <= top + height);
	}

	BasicRectangle<T> Intersection(BasicRectangle<T> other) const
	{
		T right = left + width;
		T bottom = top + height;
		T other_right = other.left + other.width;
		T other_bottom = other.top + other.height;

		if ((other.left > right) ||
			(other_right < left) ||
			(other.top > bottom) ||
			(other_bottom < top))
		{
			return BasicRectangle<T>(left, top, 0, 0);
		}

		BasicRectangle<T> result;
		result.left = std::max(left, other.left);
		result.top = std::max(top, other.top);
		result.width = std::min(right, other_right) - result.left;
		result.height = std::min(bottom, other_bottom) - result.top;
		return result;
	}

	BasicPoint<T> Clamp(BasicPoint<T> point) const
	{
		if (point.x < left)
			point.x = left;
		if (point.y < top)
			point.y = top;
		if (point.x >= left + width)
			point.x = left + width - 1;
		if (point.y >= top + height)
			point.y = top + height - 1;
		return point;
	}

	template<typename U> BasicRectangle<T> operator+(BasicPoint<U> offset) const
	{
		return BasicRectangle<T>(left + offset.x, top + offset.y, width, height);
	}

	template<typename U> BasicRectangle<T> operator+(BasicSize<U> delta) const
	{
		return BasicRectangle<T>(left, top, width + delta.width, height + delta.height);
	}

	template<typename U> BasicRectangle<T> operator-(BasicPoint<U> offset) const
	{
		return BasicRectangle<T>(left - offset.x, top - offset.y, width, height);
	}

	template<typename U> BasicRectangle<T> operator-(BasicSize<U> delta) const
	{
		return BasicRectangle<T>(left, top, width - delta.width, height - delta.height);
	}

	template<typename U> BasicRectangle<T> operator*(BasicSize<U> factor) const
	{
		return BasicRectangle<T>(left * factor.width, top * factor.height, width * factor.width, height * factor.height);
	}

	template<typename U> BasicRectangle<T> operator/(BasicSize<U> factor) const
	{
		return BasicRectangle<T>(left / factor.width, top / factor.height, width / factor.width, height / factor.height);
	}

	template<typename U> BasicRectangle<T>& operator+=(BasicPoint<U> offset)
	{
		left += offset.x;
		top += offset.y;
		return (*this);
	}

	template<typename U> BasicRectangle<T>& operator+=(BasicSize<U> delta)
	{
		width += delta.width;
		height += delta.height;
		return (*this);
	}

	template<typename U> BasicRectangle<T>& operator-=(BasicPoint<U> offset)
	{
		left -= offset.x;
		top -= offset.y;
		return (*this);
	}

	template<typename U> BasicRectangle<T>& operator-=(BasicSize<U> delta)
	{
		width -= delta.width;
		height -= delta.height;
		return (*this);
	}

	template<typename U> BasicRectangle<T>& operator*=(BasicSize<U> factor)
	{
		left *= factor.width;
		top *= factor.height;
		width *= factor.width;
		height *= factor.height;
		return (*this);
	}

	template<typename U> BasicRectangle<T>& operator/=(BasicSize<U> factor)
	{
		left /= factor.width;
		top /= factor.height;
		width /= factor.width;
		height /= factor.height;
		return (*this);
	}
};

typedef BasicRectangle<int> Rectangle;

typedef BasicRectangle<float> RectangleF;