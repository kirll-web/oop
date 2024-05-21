#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <string>
#include <iostream>


class CCircle : public ISolidShape
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

	Point GetCenter()  const;
	double GetRadius()  const;
	~CCircle() = default;
private:
	Point m_center;
	double m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};