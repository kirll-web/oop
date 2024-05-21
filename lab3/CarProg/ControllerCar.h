#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <optional>
#include <fstream>
#include "Car.h"

class ControllerCar
{
public:
    ControllerCar(Car& car);

    bool StartCar();

private:
    Car m_car;

    bool CommandSpeed();


    bool CommandGear();


    void CommandInfo();
};