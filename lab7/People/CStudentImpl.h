#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{

private:
	std::string m_nameUniversity;
	int m_studentIDNumber;
public:
	CStudentImpl(const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& address,
		const std::string& nameUniversity,
		const int StudentIDNumber)
		: CPersonImpl<Base>(name, surname, patronymic, address),
		m_nameUniversity(nameUniversity), m_studentIDNumber(StudentIDNumber)
	{
	}


	std::string GetNameUniversity() const override
	{
		return m_nameUniversity;
	}

	int GetStudentIDNumber() const override
	{
		return m_studentIDNumber;
	}

};