#pragma once

#include "stdafx.h"
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include <vector>
#include <sstream>
#include <Windows.h>
#include <regex>



const std::string SHAPE_TYPE_LINESEGMENT = "linesegment",
				  SHAPE_TYPE_RECTANGLE = "rectangle",
				  SHAPE_TYPE_TRIANGLE = "triangle",
				  SHAPE_TYPE_CIRCLE = "circle";

const double STUB_MIN_NUMBER = -5,
			 STUB_MAX_NUMBER = 0;

bool ReadFromStream(std::vector<IShape*>& shapes, ICanvas& canvas, sf::RenderWindow& window, std::istream& stream = std::cin, std::ostream& ostream = std::cout);
IShape* FindMinPerimeter(std::vector<IShape*>& shapes);
IShape* FindMaxArea(std::vector<IShape*>& shapes);
bool IsHexColor(const std::string& hex);
bool IsStrOnlyDigit(const std::string& number);
double ConvertStringToDouble(const std::string& str);
bool ReadNumber(std::istream& stream, double& number);
bool ReadColor(std::istream& stream, std::string& color);
bool SetPropertiesShape(std::istream& stream, const std::vector<double*>& numbers, const std::vector<std::string*>& colors);
void Redraw(std::vector<IShape*>& drawables, ICanvas& canvas, sf::RenderWindow& window);
