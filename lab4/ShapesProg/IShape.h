#pragma once
#include <string>
#include "ICanvas.h"
class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
	virtual std::string GetType() const = 0;
	virtual void Draw(ICanvas& canvas) = 0;
	virtual ~IShape() {};
};