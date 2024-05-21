#pragma once
#include "CPoint.h"
#include <string>
#include <vector>
#include "CColor.h"

class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to, std::string lineColor) = 0;
	virtual void DrawTriangle(std::vector<Point> points, std::string outlineColor, std::string  fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, std::string outlineColor, std::string fillColor) = 0;
	virtual void DrawRectangle(Point leftTopVertex, double width, double height, std::string outlineColor, std::string fillColor) = 0;
};