#pragma once

struct Event
{
	Event(int code) : code(code) {}
	Event(int code, std::unordered_map<int, int> &&properties) :
		code(code),
		properties(std::move(properties))
	{}

	int& operator[](int index)
	{
		return properties[index];
	}

	int code;
	std::unordered_map<int, int> properties;
};