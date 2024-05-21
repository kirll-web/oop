#include "CRectangle.h"
#include <math.h>
#include "Utils.h"
#include "CColor.h"


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
	information = "Rectangle Area:" + std::to_string(GetArea()) + "\n"
		+ " Perimeter:" + std::to_string(GetPerimeter()) + "\n"
		+ " Outline color:" + m_outlineColor + "\n" + " Fill color:" + m_fillColor + "\n"
		+ " Width: " + std::to_string(GetWidth()) + "\n"
		+ " Height: " + std::to_string(GetHeight()) + +"\n"
		+ "Left bottom vertex: x = " + std::to_string(m_leftTopVertex.x) + "\n" + "y = " + std::to_string(m_leftTopVertex.y) + "\n";
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

void CRectangle::Draw(ICanvas& canvas)
{
	canvas.DrawRectangle(m_leftTopVertex, m_width, m_height, m_outlineColor, m_fillColor);
}
