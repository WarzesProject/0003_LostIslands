#pragma once

template<typename T> 
struct BasicSize
{
	BasicSize() = default;
	BasicSize(T w, T h) : width(w), height(h) {}
	template<typename U> BasicSize(const BasicSize<U> &from) : width(from.width), height(from.height) {}

	bool operator==(const BasicSize<T> &other) const
	{
		return width == other.width && height == other.height;
	}

	bool operator!=(const BasicSize<T> &other) const
	{
		return width != other.width || height != other.height;
	}

	BasicSize<T> operator+(const BasicSize<T> &other) const
	{
		return BasicSize<T>(width + other.width, height + other.height);
	}

	BasicSize<T> operator-(const BasicSize<T> &other) const
	{
		return BasicSize<T>(width - other.width, height - other.height);
	}

	template<typename U, typename R = typename std::common_type<T, U>::type> BasicSize<R> operator*(const BasicSize<U> &factor) const
	{
		return BasicSize<R>(width*factor.width, height*factor.height);
	}

	template<typename U> BasicSize<T> operator*(U factor) const
	{
		return BasicSize<T>(T(width*factor), T(height*factor));
	}

	template<typename U> BasicSize<T>& operator*=(U factor)
	{
		width *= factor;
		height *= factor;
		return *this;
	}

	template<typename U, typename R = typename std::common_type<T, U>::type> BasicSize<R> operator/(const BasicSize<U> &factor) const
	{
		return BasicSize<R>(width / factor.width, height / factor.height);
	}

	template<typename U> BasicSize<T> operator/(U factor) const
	{
		return BasicSize<T>(T(width / factor), T(height / factor));
	}

	template<typename U> BasicSize<T>& operator/=(U factor)
	{
		width /= factor;
		height /= factor;
		return *this;
	}

	T Area() const
	{
		return width*height;
	}

	template<typename U> BasicSize<U> As() const
	{
		return BasicSize<U>(width, height);
	}

	T width = 0;
	T height = 0;
};

typedef BasicSize<int> Size;
typedef BasicSize<float> SizeF;

namespace std
{
	template<typename T> BasicSize<T> floor(BasicSize<T> value)
	{
		return BasicSize<T>(std::floor(value.width), std::floor(value.height));
	}
}