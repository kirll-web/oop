#pragma once
#include "IPerson.h"

class IPupil : public IPerson
{
	virtual std::string GetNameSchool() const = 0;
	virtual std::string GetGrade() const = 0;
};