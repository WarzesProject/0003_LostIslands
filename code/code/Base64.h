#pragma once

class Base64
{
public:
	static std::vector<std::uint8_t> Decode(const std::string &s);
};