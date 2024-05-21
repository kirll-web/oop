// CarProg.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Car.h"
#include "ControllerCar.h"

int main()
{

    const Car c = Car();
    int speed = c.GetSpeed();


    Car car = Car();
    ControllerCar controllerCar = ControllerCar(car);
    if (!controllerCar.StartCar()) {
        return 1;
    }
    return 0;
}
///в тестированиях проверять состояние объекта
/// например:
/// SetGear и потом вызываем GetGear для проверки состояния автомобиля
