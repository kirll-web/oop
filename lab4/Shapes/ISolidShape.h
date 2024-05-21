#pragma once
#include "IShape.h"
#include <string>

class ISolidShape : public IShape
{
public:
	virtual std::string GetFillColor() const = 0;
	virtual ~ISolidShape() {};
};