

#include "IShape.h"
#include "CCanvas.h"
#include "Utils.h"
#include <fstream>
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <algorithm>


int main()
{
	std::ifstream file("1.txt");
	sf::RenderWindow window(sf::VideoMode(800, 600), "Canvas", sf::Style::Default | sf::Style::Close);
	CCanvas canvas(window);
	std::vector<IShape*> shapes;
	std::cout << "Enter shape:" << std::endl
		<< "rectangle `left top point` `width` `height` `outline color` `fill color` " << std::endl
		<< "circle `center point` `radius` `outline color` `fill color` " << std::endl
		<< "triangle `point 1` `point 2` `point 3` `outline color` `fill color` " << std::endl
		<< "linesegment `point 1` `point 2` `fill color` " << std::endl << std::endl;

	ReadFromStream(shapes, canvas, window, file);
	std::cout << "Min perimeter: " << std::endl << FindMinPerimeter(shapes)->ToString() << std::endl;
	std::cout << "Max area: " << std::endl << FindMaxArea(shapes)->ToString() << std::endl;

	while (window.isOpen())
	{
		Redraw(shapes, canvas, window);
	}

    return 0;
}