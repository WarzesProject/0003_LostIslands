﻿#pragma once

inline std::string WSTRtoUTF8(const std::wstring &wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	return cv.to_bytes(wstr);
}

template<typename T, typename char_t> bool try_parse(const std::basic_string<char_t>& s, T& out)
{
	std::basic_stringstream<char_t> stream(s);
	T temp;
	stream >> temp;
	if (stream.fail())
		return false;
	out = std::move(temp);
	return true;
}

template<typename T, typename char_t> bool try_parse(const std::basic_string<char_t>& s)
{
	T temp;
	return try_parse(s, temp);
}

template<typename T, typename char_t> bool try_parse(const std::basic_string<char_t>& s, T& out, std::ios_base& (*f)(std::ios_base&))
{
	std::basic_istringstream<char_t> stream(s);
	return !(stream >> f >> out).fail();
}

bool try_parse(const std::wstring& s, bool& out);

bool try_parse(const std::wstring& s, uint64_t& out);

bool try_parse(const std::wstring& s, wchar_t& out);

bool try_parse(const std::wstring& s, char32_t& out);

template<typename T, typename char_t> T parse(const std::basic_string<char_t>& s)
{
	T result;
	if (!try_parse(s, result)) result = T();
	return result;
}

template<typename T, typename char_t> T parse(const std::basic_string<char_t>& s, std::ios_base& (*f)(std::ios_base&))
{
	T result;
	if (!try_parse(s, result, f)) result = T();
	return result;
}

template<typename char_t, typename T> std::basic_string<char_t> to_string(const T& value)
{
	std::basic_ostringstream<char_t> stream;
	stream << value;
	return stream.str();
}

template<typename char_t> bool starts_with(const std::basic_string<char_t>& what, const std::basic_string<char_t>& with)
{
	return what.find(with) == 0;
}

template<typename char_t> bool ends_with(const std::basic_string<char_t>& what, const std::basic_string<char_t>& with)
{
	return with.length() <= what.length() && what.rfind(with) == what.length() - with.length();
}

template<typename char_t> std::basic_string<char_t> file_extension(const std::basic_string<char_t>& s)
{
	size_t n = s.find_last_of(char_t('.'));
	if (s.length() > 1 && n < s.length() - 1)
	{
		return s.substr(n + 1);
	}
	else
	{
		return std::basic_string<char_t>();
	}
}

template<typename T> T get_locked(const T& reference, std::mutex& lock)
{
	std::lock_guard<std::mutex> guard(lock);
	return reference;
}

template<typename char_t> std::basic_string<char_t> to_lower(std::basic_string<char_t> s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

// Because strcasecmp/wcscasecmp support is not uniform across platforms.
template<typename char_t> bool ci_compare(const std::basic_string<char_t>& s1, const std::basic_string<char_t>& s2)
{
	return to_lower(s1) == to_lower(s2);
}

template<typename char_t> std::basic_string<char_t> trim(const std::basic_string<char_t>& s)
{
	int start = 0, end = s.length() - 1;

	while (start < s.length() && ::isspace(s[start]))
		start++;

	while (end >= 0 && ::isspace(s[end]))
		end--;

	if (end >= start && (end - start + 1) <= (int)s.length())
		return s.substr(start, end - start + 1);
	else
		return std::basic_string<char_t>();
}

std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter);

uint64_t gettime();

inline uint64_t start_timing()
{
	return gettime();
}

inline uint64_t stop_timing(uint64_t start)
{
	return gettime() - start;
}

template<typename T> class average
{
public:
	average() :
		m_sum(),
		m_count()
	{ }

	void add(T value)
	{
		m_sum += value;
		m_count += 1;
	}

	T get()
	{
		T result = m_count ? m_sum / m_count : T();
		m_sum = T();
		m_count = 0;
		return result;
	}

private:
	T m_sum;
	size_t m_count;
};