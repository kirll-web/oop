#pragma once

#include "IShape.h"
#include "CPoint.h"
#include <vector>
class CLineSegment : public IShape
{
public:
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

	bool SetProperties(std::istream& stream);
	std::string GetType() const override;
	~CLineSegment() = default;
private:
	Point m_startPoint;
	Point m_endPoint;
	std::string m_outlineColor;
};