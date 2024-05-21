#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <string>
#include <iostream>


class CRectangle : public ISolidShape
{
public:
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;
	std::string GetType() const override;


	bool SetProperties(std::istream& stream);

	void Draw(ICanvas& canvas) override;

	double GetWidth()  const;
	double GetHeight()  const;

	~CRectangle() = default;
private:
	Point m_leftTopVertex;
	std::string m_outlineColor;
	std::string m_fillColor;
	double m_width;
	double m_height;
};