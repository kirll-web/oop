#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <string>
#include <iostream>


class CTriangle: public ISolidShape
{
public:
	
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const;
	std::string GetType() const override;
	 

	bool SetProperties(std::istream& stream);

	void Draw(ICanvas& canvas) override;

	Point GetVertex1() const;;
	Point GetVertex2() const;
	Point GetVertex3() const;
	
	~CTriangle() = default;
	
private:
	double GetSideLength(Point const& vertex1, Point const& vertex2) const;

	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};
