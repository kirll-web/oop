#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"

class CPupil : public CPersonImpl<IPupil>
{
private:
    std::string m_nameSchool;
    std::string m_grade;

public:
    CPupil(const std::string& name,
        const std::string& surname,
        const std::string& patronymic,
        const std::string& address,
        const std::string& nameSchool,
        const std::string& grade)
        : CPersonImpl<IPupil>(name, surname, patronymic, address)
        , m_nameSchool(nameSchool), m_grade(grade)
    {
    }

    std::string GetNameSchool() const override;
    std::string GetGrade() const override;
};

