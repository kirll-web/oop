#include "CCircle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Utils.h"

using namespace std;


bool CCircle::SetProperties(std::istream& stream)
{
	std::vector<double*> numbers = {
		&m_center.x,
		&m_center.y,
		&m_radius,
	};

	std::vector<std::string*> colors = {
		&m_outlineColor,
		&m_fillColor
	};

	return SetPropertiesShape(stream, numbers, colors);
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	string information;
	information = "Circle Area:" + to_string(GetArea()) + "\n"
		+ " Perimeter:" + to_string(GetPerimeter()) + "\n"
		+ " Outline color:" + m_outlineColor + "\n" + " FC:" + m_fillColor + "\n"
		+ " Center: (" + to_string(m_center.x) + "\n" + to_string(m_center.y) + ")" + "\n"
		+ " Radius:" + to_string(m_radius) + "\n";
	return move(information);
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CCircle::GetType() const
{
	return "Circle";
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

Point CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas)
{
	Point center;
	center.x = m_center.x - m_radius;
	center.y = m_center.y - m_radius;
	/// разобратьс€ почему получаетс€ центр - радиус
	canvas.DrawCircle(center, m_radius, m_outlineColor, m_fillColor);
}