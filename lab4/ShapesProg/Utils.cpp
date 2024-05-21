#include "Utils.h"


bool ReadFromStream(std::vector<IShape*>& shapes, ICanvas& canvas, sf::RenderWindow& window, std::istream& stream, std::ostream& ostream)
{
	std::string choice;
	while (stream >> choice)
	{
		if (choice.compare("linesegment") == 0)
		{
			CLineSegment* lineSegment = new CLineSegment;
			if (!lineSegment->SetProperties(stream)) ostream << "Incorrect input" << std::endl;
			else
			{
				shapes.push_back(lineSegment);
			}
		}
		else if (choice.compare("rectangle") == 0)
		{
			CRectangle* rectangle = new CRectangle;

			if (!rectangle->SetProperties(stream)) ostream << "Incorrect input" << std::endl;
			else
			{
				shapes.push_back(rectangle);
			}
		}
		else if (choice.compare("triangle") == 0)
		{
			CTriangle* triangle = new CTriangle;
			if (!triangle->SetProperties(stream)) ostream << "Incorrect input" << std::endl;
			else
			{
				shapes.push_back(triangle);
			}
		}
		else if (choice.compare("circle") == 0)
		{
			CCircle* circle = new CCircle;
			if (!circle->SetProperties(stream)) ostream << "Incorrect input" << std::endl;
			else
			{
				shapes.push_back(circle);
			}
		}
		else if (choice.compare("rollback") == 0)
		{
			if (shapes.size() > 0)
			{
				shapes.pop_back();
			}
			else
			{
				ostream << "Canvas is empty" << std::endl;
			}
		}
		else if (choice.compare("exit") == 0)
		{
			return true;
		}
		else if (stream.fail() || stream.bad())
		{
			ostream << "Error input" << std::endl;
			return false;
		}
		else
		{
			ostream << "Incorrect input" << std::endl;
			continue;
		}

		Redraw(shapes, canvas, window);
	}

	return true;
}

IShape* FindMinPerimeter(std::vector<IShape*>& shapes)
{
	double minPerimeter = DBL_MAX;
	double perimeter;
	IShape* shape = nullptr;
	for (auto iter : shapes)
	{
		perimeter = iter->GetPerimeter();
		if (minPerimeter > perimeter)
		{
			minPerimeter = perimeter;
			shape = iter;
		}
	}

	return shape;
}

IShape* FindMaxArea(std::vector<IShape*>& shapes)
{
	double maxArea = 0;
	double area;
	IShape* shape = nullptr;
	for (auto iter : shapes)
	{
		area = iter->GetArea();
		if (maxArea < area)
		{
			maxArea = area;
			shape = iter;
		}
	}

	return shape;
}


bool IsHexColor(const std::string& hex) {
	const std::regex hexColorRegex("^#?([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$");
	return std::regex_match(hex, hexColorRegex);
}

bool ReadColor(std::istream& stream, std::string & color) {
	std::string checkingColor;
	stream >> checkingColor;

	if (IsHexColor(checkingColor))
	{
		color = checkingColor;
		return true;
	}
	else 
	{
		return false;
	}
}

bool IsStrOnlyDigit(const std::string& number) 
{
	const std::regex digits_only("[+-]?([0-9]*[.])?[0-9]+");

	if (std::regex_match(number, digits_only))
	{
		return true;
	}

	return false;
}

double ConvertStringToDouble(const std::string & str)
{
	double number;
	try
	{
		number = std::stod(str.c_str());
	}
	catch (std::invalid_argument const&)
	{
		return STUB_MIN_NUMBER;
	}
	catch (std::out_of_range const&)
	{
		return STUB_MIN_NUMBER;
	}
	catch (std::string const& e)
	{
		return STUB_MIN_NUMBER;
	}

	return number;
}

bool ReadNumber(std::istream & stream, double & number)
{
	std::string line;
	stream >> line;
	double convertedNumber;
	if (IsStrOnlyDigit(line)) {
		convertedNumber = ConvertStringToDouble(line);

		if (convertedNumber != STUB_MIN_NUMBER)
		{
			number = convertedNumber;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool SetPropertiesShape(std::istream & stream, const std::vector<double*> & numbers, const std::vector<std::string*> &colors)
{
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (!ReadNumber(stream, *numbers[i]))
		{
			return false;
		}
	}

	for (size_t i = 0; i < colors.size(); i++)
	{
		if (!ReadColor(stream, *colors[i]))
		{
			return false;
		}
	}

	return true;
}

void Redraw(std::vector<IShape*>& drawables, ICanvas& canvas, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	/// разобраться с api, которое использую

	window.clear(sf::Color::White);
	for (auto drawable : drawables)
	{
		drawable->Draw(canvas);
	}
	window.display();
}