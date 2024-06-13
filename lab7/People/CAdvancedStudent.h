#pragma once
#include "CStudentImpl.h"
#include "IAdvancedStudent.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
private:
    std::string m_dissertationTopic;
public:
    CAdvancedStudent(const std::string& name,
        const std::string& surname,
        const std::string& patronymic,
        const std::string& address,
        const std::string& nameUniversity,
        const int StudentIDNumber, std::string dissertationTopic)
        : CStudentImpl<IAdvancedStudent>(name, surname, patronymic, address, nameUniversity, StudentIDNumber)
        , m_dissertationTopic(dissertationTopic)
    {
    }

    std::string GetDissertationTopic() const override;
};