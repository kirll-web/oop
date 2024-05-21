#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <optional>
#include <fstream>

struct ResponseCar
{
    bool isDone;
    std::string message;
};

const enum Transmission
{
    REVERS_GEAR = -1,
    NEUTRAL_GEAR = 0,
    FIRST_GEAR = 1,
    SECOND_GEAR = 2,
    THIRD_GEAR = 3,
    FOURTH_GEAR = 4,
    FIFTH_GEAR = 5,
};

const enum Direction
{
    FORTH = 1,
    BACK_AND_FORTH = 0,
    BACK = -1
};


class Car
{
public:


    int GetSpeed() const;
    int GetGear() const;
    Direction GetDirection() const;
    bool GetEngineState() const;
    int GetTransmision() const;
    ResponseCar SetSpeed(int speed);
    ResponseCar TurnOffEngine();
    ResponseCar TurnOnEngine();
    ResponseCar SetGear(int gear);
    
private:
   
    const enum Transmission
    {
        REVERS_GEAR = -1,
        NEUTRAL_GEAR = 0,
        FIRST_GEAR = 1,
        SECOND_GEAR = 2,
        THIRD_GEAR = 3,
        FOURTH_GEAR = 4,
        FIFTH_GEAR = 5,
    };


    std::map<Transmission, int, int> m_speedRanges = {
        {REVERS_GEAR, -20, 0},
        {FIRST_GEAR, 0, 30},
        {SECOND_GEAR, 20, 50},
        {THIRD_GEAR, 30, 60},
        {FOURTH_GEAR, 40, 90},
        {FIFTH_GEAR, 50, 150},
    };


    int m_currentSpeed = 0;
    Transmission m_currentTransmission = Transmission::NEUTRAL_GEAR;
    bool m_isEngineOn = false;
    Direction m_direction = Direction::BACK_AND_FORTH;
    bool IsSpeedInTransmissionRange(int speed, Transmission currentGear) const;
    void ChangeDirection();
};

