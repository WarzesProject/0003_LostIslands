#pragma once

struct OptionGroup
{
	std::wstring name;
	std::map<std::wstring, std::wstring> attributes;
};

std::list<OptionGroup> ParseOptions2(const std::wstring& s, bool semicolon_comments = false);

std::wstring read_until3(const wchar_t*& p, const std::wstring& until);