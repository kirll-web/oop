#include "CRectangle.h"
#include <math.h>
#include "Utils.h"


bool CRectangle::SetProperties(std::istream& stream)
{
	std::vector<double*> numbers = {
		&m_leftTopVertex.x,
		&m_leftTopVertex.y,
		&m_width,
		&m_height
	};

	std::vector<std::string*> colors = {
		&m_outlineColor,
		&m_fillColor
	};

	return SetPropertiesShape(stream, numbers, colors);

}


double CRectangle::GetArea() const
{
	return m_width * m_height;
}

std::string CRectangle::GetType() const
{
	return "Rectangle";
}

double CRectangle::GetPerimeter() const
{
	return m_width * 2 + m_height * 2;
}

std::string CRectangle::ToString() const
{
	std::string information;
	information = "Rectangle Area:" + std::to_string(GetArea())
		+ " Perimeter:" + std::to_string(GetPerimeter())
		+ " Outline color:" + m_outlineColor + " Fill color:" + m_fillColor
		+ " Width: " + std::to_string(GetWidth()) + " "
		+ " Height: " + std::to_string(GetHeight()) + " "
		+ "Left bottom vertex: x = " + std::to_string(m_leftTopVertex.x) + " y = " + std::to_string(m_leftTopVertex.y);
	return move(information);
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

double CRectangle::GetWidth() const 
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

