#include "CLineSegment.h"
#include "Utils.h"
#include <math.h>

using namespace std;

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
	string information;
	information = "LineSegment A:" + to_string(GetArea()) + " P:" + to_string(GetPerimeter())
		+ " OC:" + m_outlineColor;
	return move(information);
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


std::string GetType() 
{
	return "Circle";
}


bool CLineSegment::SetProperties(std::istream& stream)
{
	std::vector<double*> numbers = {
		&m_startPoint.x,
		& m_startPoint.y,
		& m_endPoint.x,
		& m_endPoint.y,
	};

	std::vector<std::string*> colors = {
		&m_outlineColor,
	};
	return SetPropertiesShape(stream, numbers, colors);
}
