#include "Utils.h"
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

int main()
{
	SetConsoleOutputCP(1251);


	std::vector<IShape*> shapes;

	if (!ReadFromStream(shapes))
	{
		return 1;
	}
	IShape* shapeWithMinPerimeter = FindMinPerimeter(shapes);
	IShape* shapeWithMaxArea = FindMaxArea(shapes);

	if (shapeWithMinPerimeter != nullptr)
	{
		std::cout << "Shape with min perimeter:\n" << shapeWithMinPerimeter->ToString() << "\n";
	} 
	else 
	{
		std::cout << "No shape with minimum perimeter found" << std::endl;
	}

	if (shapeWithMaxArea != nullptr)
	{
		std::cout << "Shape with max area:\n" << shapeWithMaxArea->ToString() << "\n";
	}
	else
	{
		std::cout << "No shape with max area found" << std::endl;
	}

}

