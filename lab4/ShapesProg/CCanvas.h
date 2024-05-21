#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include <vector>
#include "ICanvas.h"
#include "CColor.h"


class CCanvas :
	public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window) : m_window(window) {};

	void DrawLine(Point from, Point to, std::string lineColor);
	void DrawTriangle(std::vector<Point> points, std::string outlineColor, std::string  fillColor);
	void DrawCircle(Point center, double radius, std::string outlineColor, std::string fillColor);
	void DrawRectangle(Point leftTopVertex, double width, double height, std::string outlineColor, std::string fillColor);

	///TODO: сделать по диаграмме 

private:
	sf::RenderWindow& m_window ;
};