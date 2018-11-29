#pragma once

template<typename T> struct BasicPoint
{
	typedef T value_type;

	T x, y;

	BasicPoint() :
		x(0),
		y(0)
	{ }

	BasicPoint(T x, T y) :
		x(x),
		y(y)
	{ }

	BasicPoint(const BasicPoint<T>& from) :
		x(from.x),
		y(from.y)
	{ }

	inline bool operator==(BasicPoint<T> other) const
	{
		return x == other.x && y == other.y;
	}

	inline bool operator!= (BasicPoint<T> other) const
	{
		return x != other.x || y != other.y;
	}

	inline BasicPoint<T> operator+(BasicPoint<T> other)
	{
		return BasicPoint<T>(x + other.x, y + other.y);
	}

	inline BasicPoint<T> operator-(BasicPoint<T> other)
	{
		return BasicPoint<T>(x - other.x, y - other.y);
	}
};

typedef BasicPoint<int> Point;

typedef BasicPoint<float> PointF;