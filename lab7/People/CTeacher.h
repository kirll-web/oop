#pragma once
#include "ITeacher.h"
#include "CPersonImpl.h"

class CTeacher : public CPersonImpl<ITeacher>
{
private:
    std::string m_course;
public:
    CTeacher(const std::string& name,
        const std::string& surname,
        const std::string& patronymic,
        const std::string& address,
        const std::string& course)
        : CPersonImpl<ITeacher>(name, surname, patronymic, address)
        , m_course(course)
    {
    }

    std::string GetCourse() const override;
};