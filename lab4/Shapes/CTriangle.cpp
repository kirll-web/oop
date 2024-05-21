
#include "CTriangle.h"
#include <math.h>
#include "Utils.h"


bool CTriangle::SetProperties(std::istream& stream)
{
	std::vector<double*> numbers = {
		&m_vertex1.x,
		&m_vertex1.y,
		&m_vertex2.x,
		&m_vertex2.y,
		&m_vertex3.x,
		&m_vertex3.y,
	};

	std::vector<std::string*> colors = {
		&m_outlineColor,
		&m_fillColor
	};

	return SetPropertiesShape(stream, numbers, colors);
}


double CTriangle::GetArea() const
{
	double a = GetSideLength(m_vertex1, m_vertex2);
	double b = GetSideLength(m_vertex2, m_vertex3);
	double c = GetSideLength(m_vertex3, m_vertex1);
	double p = GetPerimeter() / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	double side1 = GetSideLength(m_vertex1, m_vertex2);
	double side2 = GetSideLength(m_vertex2, m_vertex3);
	double side3 = GetSideLength(m_vertex3, m_vertex1);
	return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
	std::string information;
	information = "Triangle Area:" + std::to_string(GetArea())
		+ " Perimeter:" + std::to_string(GetPerimeter())
		+ " Outline color:" + m_outlineColor + " Fill color:" + m_fillColor
		+ " Vertex 1(" + std::to_string(m_vertex1.x) + " " + std::to_string(m_vertex1.y)
		+ ") Vertex 2(" + std::to_string(m_vertex2.x) + " " + std::to_string(m_vertex2.y)
		+ ") Vertex 3(" + std::to_string(m_vertex3.x) + " " + std::to_string(m_vertex3.y) + ")";
	return move(information);
}

std::string CTriangle::GetType() const
{
	return "Triangle";
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

Point CTriangle::GetVertex1() const
{
	return m_vertex1;
}

Point CTriangle::GetVertex2() const
{
	return m_vertex2;
}

Point CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetSideLength(Point const& vertex1, Point const& vertex2) const
{
	return sqrt(pow(vertex1.x - vertex2.x, 2) + pow(vertex1.y - vertex2.y, 2));
}