
#include "Car.h"

ResponseCar Car::SetGear(int gearNumber)
{

    Transmission gear = static_cast<Transmission>(gearNumber);

    if (!m_isEngineOn)
    {
        return
        {
            false,
            "You cannot change gear with the engine off"
        };
    }

    if (gear < REVERS_GEAR || gear > FIFTH_GEAR)
    {
        return
        {
            false,
            "No such transmission exists"
        };
    }

    if (gear == REVERS_GEAR && m_currentSpeed != 0)
    {
        return
        {
            false,
            "It is impossible to put the reverse gear while driving"
        };
    }

    if ((m_direction == Direction::BACK || m_currentTransmission == Transmission::REVERS_GEAR) && gear > Transmission::NEUTRAL_GEAR && m_currentSpeed != 0)
    {
        return
        {
            false,
            "You can't shift into forward gear when driving in revers"
        };
    }

    if (!IsSpeedInTransmissionRange(m_currentSpeed, gear))
    {
        return
        {
            false,
            "You can't shift into forward gear when driving in revers"
        };
    }

    m_currentTransmission = gear;

    return
    {
        true,
        "Gear shift to " + m_currentTransmission
    };
}

ResponseCar Car::TurnOnEngine()
{
    m_isEngineOn = true;
    return
    {
        true,
        "The engine turned on"
    };
}

ResponseCar Car::TurnOffEngine()
{
    if (m_currentTransmission == NEUTRAL_GEAR && m_currentSpeed == 0)
    {
        m_isEngineOn = false;
        return
        {
            true,
            "The engine turned off"
        };
    }
    else
    {
        return
        {
            false,
            "To turn off the engine, the gear must be in neutral and zero speed."
        };
    }
}

ResponseCar Car::SetSpeed(int speed)
{

    if (!m_isEngineOn)
    {
        return
        {
            false,
            "Speed cannot be change when the engine is off"
        };
    }

    if (m_currentTransmission == REVERS_GEAR) {
        speed *= -1;
    }

    if (m_currentTransmission != REVERS_GEAR && speed < 0)
    {
        return
        {
            false,
            "Speed cannot be less than zero"
        };
    }

    if (!IsSpeedInTransmissionRange(speed, m_currentTransmission))
    {
        return
        {
            false,
            "In neutral gear, you can only change to a speed that is less than the current speed"
        };
    }

    m_currentSpeed = speed;
    ChangeDirection();
  

    return
    {
        true,
        "Speed switched to " + std::to_string(m_currentSpeed) /// добавить сообщеине о переключении скорости
    };
}

void Car::ChangeDirection()
{
    if (m_currentSpeed > 0)
    {
        m_direction = Direction::FORTH;
    }
    else if (m_currentSpeed < 0) {
        m_direction = Direction::BACK;
    }
    else
    {
        m_direction = Direction::BACK_AND_FORTH;
    }
}

//—осто€ние двигател€(включен или выключен) Ц метод
bool Car::GetEngineState() const
{
    return m_isEngineOn;
}
//Ќаправление движени€(вперед, назад или стоим на месте) Ц метод
Direction  Car::GetDirection() const
{
    return m_direction;
}
//“екуща€ скорость движени€(целое число от 0 до максимальной скорости) Ц метод 
int Car::GetSpeed() const
{
    return  abs(m_currentSpeed);
    /// лучше вз€ть по модул€
    /// через метод 
}
//“екуща€ выбранна€ передача[-1..5] Ц метод 
int Car::GetGear() const
{
    return m_currentTransmission;
}

bool Car::IsSpeedInTransmissionRange(int speed, Transmission gear) const
{

    /// переделать через map


    switch (gear)
    {
    case REVERS_GEAR:
        return (speed <= 0 && speed >= -20) ? true : false;
    case NEUTRAL_GEAR:
        return (speed >= abs(m_currentSpeed)) ? true : false;
    case FIRST_GEAR:
        return (speed >= 0 && speed <= 30) ? true : false;
    case SECOND_GEAR:
        return (speed >= 20 && speed <= 50) ? true : false;
    case THIRD_GEAR:
        return (speed >= 30 && speed <= 60) ? true : false;
    case FOURTH_GEAR:
        return (speed >= 40 && speed <= 90) ? true : false;
    case FIFTH_GEAR:
        return (speed >= 50 && speed <= 150) ? true : false;
    default:
        return false;
    }
}

int Car::GetTransmision() const
{
    return m_currentTransmission;
}