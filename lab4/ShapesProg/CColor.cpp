#include "CColor.h";

Color::Color(std::string color)
{
	red = std::stoi(color.substr(0, 2), nullptr, 16);
	green = std::stoi(color.substr(2, 2), nullptr, 16);
	blue = std::stoi(color.substr(4, 2), nullptr, 16);
}