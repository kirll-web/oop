#include "CLineSegment.h"


bool CLineSegment::SetProperties(std::istream& stream)
{
	std::vector<double*> numbers = {
		&m_startPoint.x,
		&m_startPoint.y,
		&m_endPoint.x,
		&m_endPoint.y,
	};

	std::vector<std::string*> colors = {
		&m_outlineColor,
	};
	return SetPropertiesShape(stream, numbers, colors);
}


double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_endPoint.x - m_startPoint.x, 2) + pow(m_endPoint.y - m_startPoint.y, 2));
}

std::string CLineSegment::ToString() const
{
	std::string information;
	information = "LineSegment A:" + std::to_string(GetArea()) + "\n" + " P:" + std::to_string(GetPerimeter()) + "\n"
		+ " OC:" + m_outlineColor + "\n";
	return information;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

Point CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}


std::string CLineSegment::GetType() const
{
	return "Circle";
}


void CLineSegment::Draw(ICanvas& canvas)
{
	int color = stoi(m_outlineColor, nullptr, 16);
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}