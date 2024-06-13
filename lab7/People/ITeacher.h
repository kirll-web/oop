#pragma once

#include "IPerson.h"

class ITeacher : public IPerson
{
public:
	virtual std::string GetCourse() const = 0;
};