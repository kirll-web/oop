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
	information = "Circle A:" + to_string(GetArea())
		+ " P:" + to_string(GetPerimeter())
		+ " OC:" + m_outlineColor + " FC:" + m_fillColor
		+ " C(" + to_string(m_center.x) + " " + to_string(m_center.y) + ") "
		+ " R:" + to_string(m_radius);
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

