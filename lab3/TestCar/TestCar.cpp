
// TestCar.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "../CarProg/Car.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>


void SetGearWithEngineOff(const Car & car, Transmission gear, int expectedResult) {
	auto clone(car); 
	clone.TurnOffEngine();
	CHECK(!clone.SetGear(gear).isDone);
	CHECK(clone.GetGear() == expectedResult);
}

SCENARIO("cannot change gear with the engine off")
{
	Car car{};
	SetGearWithEngineOff(car, REVERS_GEAR, 0);
	SetGearWithEngineOff(car, SECOND_GEAR, 0);
	SetGearWithEngineOff(car, THIRD_GEAR, 0);
}

SCENARIO("cannot change speed with the engine off")
{
	Car car{};
	car.TurnOffEngine();
	car.SetSpeed(1);
	CHECK(car.GetSpeed() == 0);
}

void SetSpeedOutsideGearLimits(const Car& car, int speed, int expectedSpeed, Transmission gear) {
	auto clone(car); // сделали клон объекта;
	clone.TurnOnEngine();
	clone.SetGear(gear);
	CHECK(!clone.SetSpeed(speed).isDone);
	CHECK(clone.GetSpeed() == expectedSpeed);
}

SCENARIO("Cannot switch to speed outside gear limits")
{
	Car car{};
	SetSpeedOutsideGearLimits(car, 20, 0, NEUTRAL_GEAR);
	SetSpeedOutsideGearLimits(car, -20, 0, NEUTRAL_GEAR);
	SetSpeedOutsideGearLimits(car, -20, 0, FIRST_GEAR);
	SetSpeedOutsideGearLimits(car, 50, 0, FIRST_GEAR);

	/// сделать для каждой передачи 4 чека. Проверка валидных границ и невалидных границ
	/// сделать тоже самое для передачи
}


/// 1. НЕЛЬЗЯ ПЕРЕКЛЮЧИТЬ НА ПЕРЕДНЮЮ ПЕРЕДАЧУ, ЕСЛИ СТОИТ НЕЙТРАЛЬНАЯ, А АВТОМОБИЛЬ ЕДЕТ НАЗАД
SCENARIO("cannot shift into forward gear if it is in neutral and the car is moving backwards")
{
	Car car{};
	car.TurnOnEngine();
	car.SetGear(REVERS_GEAR);
	car.SetSpeed(20);
	car.SetGear(NEUTRAL_GEAR);
	CHECK(!car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.GetGear() == NEUTRAL_GEAR);
}

/// 2. НЕЛЬЗЯ ПЕРЕКЛЮЧИТЬ НА ПЕРЕДНЮЮ ПЕРЕДАЧУ, ЕСЛИ СТОИТ ЗАДНЯЯ И АВТОМОБИЛЬ ЕДЕТ НАЗАД
SCENARIO("You cannot shift into forward gear if the gear is in reverse and the car is moving backwards")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(REVERS_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(!car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.GetGear() == REVERS_GEAR);
}
/// 3. МОЖНО ПЕРЕКЛЮЧИТЬ НА ПЕРЕДНЮЮ ПЕРЕДАЧУ, ЕСЛИ СТОИТ ЗАДНЯЯ, А АВТОМОБИЛЬ СТОИТ НА МЕСТЕ
SCENARIO("you can switch to forward gear if it is in reverse and the car is stationary")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(REVERS_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(car.SetSpeed(0).isDone);
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.GetGear() == FIRST_GEAR);
}
/// 4. НЕЛЬЗЯ ПЕРЕКЛЮЧИТЬ НА ЗАДНЮЮ ПЕРЕДАЧУ, ЕСЛИ СТОИТ НЕЙТРАЛЬНАЯ, А АВТОМОБИЛЬ ЕДЕТ ВПЕРЁД
SCENARIO("cannot shift into reverse if the gear is in neutral and the car is moving forward")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(car.SetGear(NEUTRAL_GEAR).isDone);
	CHECK(!car.SetGear(REVERS_GEAR).isDone);
	CHECK(car.GetGear() == NEUTRAL_GEAR);
}

/// 5. НЕЛЬЗЯ ПЕРЕКЛЮЧИТЬ НА ЗАДНЮЮ ПЕРЕДАЧУ, ЕСЛИ СКОРОСТЬ НЕНУЛЕВАЯ И АВТОМОБИЛЬ ЕДЕТ НАЗАД
SCENARIO("it is impossible to shift into reverse gear if the speed is non-zero and the car is moving backwards")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(REVERS_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(car.SetGear(NEUTRAL_GEAR).isDone);
	CHECK(!car.SetGear(REVERS_GEAR).isDone);
	CHECK(car.GetGear() == NEUTRAL_GEAR);
}
/// 6. НЕЛЬЗЯ НА СЛЕДУЮЩУЮ ПЕРЕДАЧУ, ЕСЛИ НЕ НАБРАНА НЕОБХОДИМАЯ СКОРОСТЬ
SCENARIO("cannot change to the next gear if the required speed has not been reached")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(10).isDone);
	CHECK(!car.SetGear(SECOND_GEAR).isDone);
	CHECK(car.GetGear() == FIRST_GEAR);
}
/// 7. НА НЕЙТРАЛЬНОЙ ПЕРЕДАЧЕ МОЖНО ТОЛЬКО УМЕНЬШИТЬ ЗНАЧЕНИЕ, УВЕЛИЧИТЬ НЕЛЬЗЯ
SCENARIO("in neutral gear you can only decrease the value, you cannot increase it")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(car.SetGear(0).isDone);
	CHECK(car.SetSpeed(19).isDone);
	CHECK(car.GetSpeed() == 19);
	CHECK(!car.SetSpeed(25).isDone);
	CHECK(car.GetSpeed() == 19);
	/// добавить такой же тест для нейтралки

}
/// 10. ДВИГАТЕЛЬ НЕЛЬЗЯ ВЫКЛЮЧИТЬ ЕСЛИ СТОИТ НЕ НЕЙТРАЛКА И СКОРОСТЬ БОЛЬШЕ НУЛЯ

SCENARIO("The engine cannot be turned off if it is not in neutral and the speed is greater than zero")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(!car.TurnOffEngine().isDone);
	CHECK(car.GetEngineState() == true);
}

/// 11. ДВИГАТЕЛЬ НЕЛЬЗЯ ВЫКЛЮЧИТЬ ЕСЛИ СТОИТ НЕ НЕЙТРАЛКА 
SCENARIO("The engine cannot be turned off if it is not in neutral.")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(0).isDone);
	CHECK(!car.TurnOffEngine().isDone);
	CHECK(car.GetEngineState() == true);
}
/// 12. ДВИГАТЕЛЬ НЕЛЬЗЯ ВЫКЛЮЧИТЬ ЕСЛИ СТОИТ НЕЙТРАЛКА,А СКОРОСТЬ > 0
SCENARIO("The engine cannot be turned off if it is in neutral and the speed is > 0")
{
	Car car{};
	car.TurnOnEngine();
	CHECK(car.SetGear(FIRST_GEAR).isDone);
	CHECK(car.SetSpeed(20).isDone);
	CHECK(car.SetGear(NEUTRAL_GEAR).isDone);
	CHECK(!car.TurnOffEngine().isDone);
	CHECK(car.GetEngineState() == true);
}

