#pragma once
#include <string>
class Color
{
public:
	Color(std::string color);

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	~Color() = default;
};