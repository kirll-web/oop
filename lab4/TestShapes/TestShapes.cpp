#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/CCircle.h"
#include "../Shapes/Utils.h"
#include <vector>
#include <sstream>


SCENARIO("check triangle")
{
	std::stringstream str("0.0 0.0 0.0 5.0 5.0 0.0 000000 00ff00");
	CTriangle triangle;
	CHECK(triangle.SetProperties(str));
	CHECK(std::round(triangle.GetPerimeter() * 100) / 100 == 17.07);
	CHECK(std::round(triangle.GetArea() * 100) / 100 == 12.5);
	CHECK(triangle.GetOutlineColor() == "000000");
	CHECK(triangle.GetFillColor() == "00ff00");
}

SCENARIO("check linesegment")
{
	std::stringstream str("400 120 450 120 ff00ff");
	CLineSegment line;
	line.SetProperties(str);
	CHECK(line.GetPerimeter() == 50);
	CHECK(line.GetArea() == 0);
	CHECK(line.GetOutlineColor() == "ff00ff");
	std::cout << line.ToString();
}

SCENARIO("check rectangle")
{
	std::stringstream str("10.3 20.15 30.7 40.4 ff0000 00ff00");
	CRectangle rect;
	rect.SetProperties(str);
	CHECK(rect.GetPerimeter() == 142.2);
	CHECK(rect.GetArea() == 1240.28);
	CHECK(rect.GetOutlineColor() == "ff0000");
	CHECK(rect.GetFillColor() == "00ff00");
	std::cout << rect.ToString();
}

SCENARIO("check circle")
{
	std::stringstream str("5.0 5.0 5 000000 00ff00");
	CCircle circle;
	circle.SetProperties(str);
	CHECK(std::round(circle.GetPerimeter() * 100)/ 100 == 31.42);
	CHECK(std::round(circle.GetArea() * 100)/100 == 78.54);
	CHECK(circle.GetOutlineColor() == "000000");
	CHECK(circle.GetFillColor() == "00ff00");
}



SCENARIO("check find min perimetr")
{
	std::vector<IShape*> shapes;
	std::stringstream str1("400 120 450 120 ff00ff");
	CLineSegment line;
	shapes.push_back(&line);
	line.SetProperties(str1);
	std::stringstream str2("10.3 20.15 30.7 40.4 ff0000 00ff00");
	CRectangle rect;
	rect.SetProperties(str2);
	shapes.push_back(&rect);
	std::stringstream str3("5.0 5.0 5 000000 00ff00");
	CCircle circle;
	circle.SetProperties(str3);
	shapes.push_back(&circle);
	std::stringstream str4("0.0 0.0 0.0 5.0 5.0 0.0 000000 00ff00");
	CTriangle triangle;
	triangle.SetProperties(str4);
	shapes.push_back(&triangle);

	IShape* minShape = FindMinPerimeter(shapes);
	
	CHECK(minShape->GetType() == "Triangle");
}

SCENARIO("check find max area")
{
	std::vector<IShape*> shapes;
	std::stringstream str1("400 120 450 120 ff00ff");
	CLineSegment line;
	shapes.push_back(&line);
	line.SetProperties(str1);
	std::stringstream str2("10.3 20.15 30.7 40.4 ff0000 00ff00");
	CRectangle rect;
	rect.SetProperties(str2);
	shapes.push_back(&rect);
	std::stringstream str3("5.0 5.0 5 000000 00ff00");
	CCircle circle;
	circle.SetProperties(str3);
	shapes.push_back(&circle);
	std::stringstream str4("0.0 0.0 0.0 5.0 5.0 0.0 000000 00ff00");
	CTriangle triangle;
	triangle.SetProperties(str4);
	shapes.push_back(&triangle);

	IShape* maxArea = FindMaxArea(shapes);

	CHECK(maxArea->GetType() == "Rectangle");
}




