
#include "ControllerCar.h"


ControllerCar::ControllerCar(Car& car)
{
    m_car = car;
}


bool ControllerCar::StartCar()
{
    std::string inputLine;
    const std::string commandInfo = "Info";
    const std::string commandEngineOn = "EngineOn";
    const std::string commandEngineOff = "EngineOff";
    const std::string commandSetGear = "SetGear";
    const std::string commandSetSpeed = "SetSpeed";
    const std::string commandExit = "exit";
    while (!std::cin.eof())
    {
        std::cout << "Input command or \"exit\" for exit: " << std::endl;
        std::cin >> inputLine;
        /// переделать на getline
        if (inputLine == commandInfo)
        {
            CommandInfo();
        }
        else if (inputLine == commandEngineOn)
        {
            ResponseCar response = m_car.TurnOnEngine();
            std::cout << response.message << std::endl;
        }
        else if (inputLine == commandEngineOff)
        {
            ResponseCar response = m_car.TurnOffEngine();
            std::cout << response.message << std::endl;
        }
        else if (inputLine == commandSetGear)
        {
            if (!CommandGear())
            {
                return false;
            }
        }
        else if (inputLine == commandSetSpeed)
        {
            if (!CommandSpeed())
            {
                return false;
            }
        }
        else if (inputLine == commandExit)
        {
            return true;
        }
        else if (std::cin.fail() || std::cin.bad())
        {
            std::cout << "Error input" << std::endl;
            return false;
        }
        else 
        {
            std::cout << "Unknow command" << std::endl;
        }
        inputLine = "";
    }

    return true;
}

bool ControllerCar::CommandSpeed() 
{
    std::string speedString;
    int speed;
    std::cout << "Enter speed: " << std::endl;
    std::cin >> speedString;

    try
    {
        speed = std::stoi(speedString.c_str());
    }
    catch (std::invalid_argument const&)
    {
        std::cout << "Error input speed" << std::endl;
        return false;
    }
    catch (std::out_of_range const&)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
        return false;
    }
    catch (std::string const& e)
    {
        std::cout << "Error " << e << std::endl;
        return false;
    }

    ResponseCar response = m_car.SetSpeed(speed);
    if (!response.isDone)
    {
        std::cout << response.message << std::endl;
    }
    else
    {
        std::cout << "Speed shifted to " << speed << std::endl;
    }

    return true;
}

bool  ControllerCar::CommandGear()
{
    std::string transmissionNumberString;
    int transmissionNumber;
    std::cout << "Enter transmission number from -1 to 5: " << std::endl;
    std::cin >> transmissionNumberString;

    try
    {
        transmissionNumber = std::stoi(transmissionNumberString.c_str());
    }
    catch (std::invalid_argument const&)
    {
        std::cout << "Error input  transmission number" << std::endl;
        return false;
    }
    catch (std::out_of_range const&)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
        return false;
    }
    catch (std::string const& e)
    {
        std::cout << "Error " << e << std::endl;
        return false;
    }

    ResponseCar response = m_car.SetGear(transmissionNumber);
    if (!response.isDone)
    {
        std::cout << response.message << std::endl;
    }
    else
    {
        std::cout << "Gear shifted to " << transmissionNumber << std::endl;
    }

    return true;
}

void ControllerCar::CommandInfo()
{
    std::cout << "Gear: " << m_car.GetGear() << std::endl;
    std::cout << "Speed: " << (m_car.GetSpeed() >= 0 ? m_car.GetSpeed() : m_car.GetSpeed() * -1) << std::endl;
    std::cout << "State engine: " << (m_car.GetEngineState() ? "on" : "off") << std::endl;

    std::cout << "Direction: ";
    switch (m_car.GetDirection())
    {
    case BACK_AND_FORTH:
        std::cout << "standing still" << std::endl;
        break;
    case FORTH:
        std::cout << "forward" << std::endl;
        break;
    case BACK:
        std::cout << "backward" << std::endl;
        break;
    default:
        std::cout << "Unknow direction" << std::endl;
        break;
    }
}