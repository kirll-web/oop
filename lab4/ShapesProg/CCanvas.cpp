#include "CCanvas.h"
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>

void CCanvas::DrawLine(Point from, Point to, std::string lineColor)
{
	Color color = Color(lineColor);
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y));
	line[1].position = sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y));

	line[0].color = sf::Color(sf::Color(color.red, color.green, color.blue));;
	line[1].color = sf::Color(sf::Color(color.red, color.green, color.blue));;

	m_window.draw(line);
}

void CCanvas::DrawTriangle(std::vector<Point> points, std::string outlineColor, std::string  fillColor)
{
	Color fColor = Color(fillColor);
	Color out—olor = Color(outlineColor);

	sf::ConvexShape convex;

	convex.setPointCount(3);

	for (int i = 0; i < points.size(); ++i)
	{
		convex.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	convex.setOutlineColor(sf::Color(out—olor.red, out—olor.green, out—olor.blue));
	convex.setOutlineThickness(5.0);
	convex.setFillColor(sf::Color(fColor.red, fColor.green, fColor.blue));

	m_window.draw(convex);
}

void CCanvas::DrawRectangle(Point leftTopVertex, double width, double height, std::string outlineColor, std::string fillColor)
{
	Color f—olor = Color(fillColor);
	Color out—olor = Color(outlineColor);

	sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	rectangle.setPosition(static_cast<float>(leftTopVertex.x), static_cast<float>(leftTopVertex.y));
	rectangle.setOutlineColor(sf::Color(out—olor.red, out—olor.green, out—olor.blue));
	rectangle.setOutlineThickness(5.0);
	rectangle.setFillColor(sf::Color(f—olor.red, f—olor.green, f—olor.blue));
	m_window.draw(rectangle);
}

void CCanvas::DrawCircle(Point center, double radius, std::string outlineColor, std::string fillColor)
{
	Color f—olor = Color(fillColor);
	Color out—olor = Color(outlineColor);
	sf::CircleShape circle;
	circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
	circle.setRadius(static_cast<float>(radius));
	circle.setOutlineColor(sf::Color(out—olor.red, out—olor.green, out—olor.blue));
	circle.setOutlineThickness(5.0);
	circle.setFillColor(sf::Color(f—olor.red, f—olor.green, f—olor.blue));
	m_window.draw(circle);
}

