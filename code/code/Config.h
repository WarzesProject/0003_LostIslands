#pragma once

#include "Utility.h"

template<typename char_t> struct ci_less : // FIXME: --> Utility
	std::binary_function<std::basic_string<char_t>, std::basic_string<char_t>, bool>
{
	struct nocase_compare :
		public std::binary_function<char_t, char_t, bool>
	{
		bool operator()(const char_t& c1, const char_t& c2) const
		{
			return std::tolower(c1) < std::tolower(c2);
		}
	};

	bool operator()(const std::basic_string<char_t>& s1, const std::basic_string<char_t>& s2) const
	{
		return std::lexicographical_compare // XXX: simple strcasecmp?
			(
				s1.begin(), s1.end(),
				s2.begin(), s2.end(),
				nocase_compare()
				);
	}
};

class Config
{
public:
	void Reload();
	bool TryGet(std::wstring name, std::wstring& out);
	std::map<std::wstring, std::wstring> List(const std::wstring& section);
	void Set(std::wstring name, std::wstring value);
	static Config& Instance();

	template<typename T> bool TryGet(std::wstring name, T& out)
	{
		std::wstring temp;
		if (!TryGet(std::move(name), temp))
			return false;
		return try_parse(temp, out);
	}

private:
	Config();
	//std::wstring GuessConfigFilename();
	void Update(std::wstring section, std::wstring property, std::wstring value);

	struct Property
	{
		std::wstring m_value;
	};

	struct Section
	{
		std::map<std::wstring, Property, ci_less<wchar_t>> m_properties;
	};

	std::wstring m_filename;
	std::map<std::wstring, Section, ci_less<wchar_t>> m_sections;
};