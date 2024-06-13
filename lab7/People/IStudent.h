#pragma once

#include "IPerson.h"

class IStudent : public IPerson
{
	virtual std::string GetNameUniversity() const = 0;
	virtual int GetStudentIDNumber() const = 0;
};