#pragma once

class Resource
{
public:
	static std::vector<uint8_t> Open(std::wstring name, std::wstring prefix = L"");
};