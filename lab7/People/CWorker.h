#pragma once

#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker : public CPersonImpl<IWorker>
{
private:
    std::string m_specialty;
public:
    CWorker(const std::string& name,
        const std::string& surname,
        const std::string& patronymic,
        const std::string& address,
        const std::string& specialty)
        : CPersonImpl<IWorker>(name, surname, patronymic, address)
        , m_specialty(specialty)
    {
    }

    std::string GetSpecialty() const override;
};
