#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../MyString/CMyString.h"

bool CheckStringLength(CMyString str, int expectedLength)
{
	return str.GetLength() == expectedLength;
}

SCENARIO("check length")
{
	CHECK(CheckStringLength(CMyString{ "Hello world" }, 11));
	CHECK(CheckStringLength(CMyString{ "Hello" }, 5));
	CHECK(!CheckStringLength(CMyString{ "Hello string" }, 15));
	CHECK(CheckStringLength(std::string{ "Hello world" }, 11));
	CHECK(CheckStringLength(std::string{ "Hello" }, 5));
	CHECK(!CheckStringLength(std::string{ "Hello string" }, 15));
	CHECK(CheckStringLength(CMyString{ CMyString{"Hello world"} }, 11));
	CHECK(CheckStringLength(CMyString{ CMyString{"Hello"} }, 5));
	CHECK(!CheckStringLength(CMyString{ CMyString{"Hello"} }, 15));
	CHECK(CheckStringLength(CMyString{"Hello world", 3}, 3));
	CHECK(CheckStringLength(CMyString{"Hello", 5 }, 5));
	CHECK(!CheckStringLength(CMyString{ "Hello", 5 }, 6));
	CMyString str1("hello world");
	CMyString str2("hello");
	CHECK(CheckStringLength(str1, 11));
	CHECK(CheckStringLength(str2, 5));
	CHECK(!CheckStringLength(str2, 6));
};



bool CheckStringData(CMyString str, std::string expectedString)
{
	return str.GetStringData() == expectedString;
}

SCENARIO("check get string data")
{
	CHECK(CheckStringData(CMyString{ "Hello world"}, "Hello world"));
	CHECK(CheckStringData(CMyString{ "Hello" }, "Hello"));
	CHECK(CheckStringData(CMyString{ "Hello string" }, "Hello string"));
	CHECK(!CheckStringData(CMyString{ "Hello string" }, "Hello stringasasdasdasd"));
};


bool CheckStringCapacity(CMyString str, int expectedLength)
{
	return str.GetCapacity() == expectedLength;
}

SCENARIO("check capacity")
{
	CHECK(CheckStringCapacity(CMyString{ "Hello world" }, 15));
	CHECK(CheckStringCapacity(CMyString{ "Hello" }, 15));
	CHECK(!CheckStringCapacity(CMyString{ "Hello string" }, 18));
	CHECK(CheckStringCapacity(std::string{ "Hello world" }, 15));
	CHECK(CheckStringCapacity(std::string{ "Hello" }, 15));
	CHECK(!CheckStringCapacity(std::string{ "Hello string" }, 19));
	CHECK(CheckStringCapacity(CMyString{ CMyString{"Hello world"} }, 15));
	CHECK(CheckStringCapacity(CMyString{ CMyString{"Hello"} }, 15));
	CHECK(!CheckStringCapacity(CMyString{ CMyString{"Hello"} }, 18));
	CHECK(CheckStringCapacity(CMyString{ "Hello world", 3 }, 15));
	CHECK(CheckStringCapacity(CMyString{ "Hello", 5 }, 15));
	CHECK(!CheckStringCapacity(CMyString{ "Hello", 5 }, 18));
	CMyString str1("hello world");
	CMyString str2("hello");
	CHECK(CheckStringCapacity(str1, 15));
	CHECK(CheckStringCapacity(str2, 15));
	CHECK(!CheckStringCapacity(str2, 18));

	CMyString str3("hello world world");
	CHECK(CheckStringCapacity(str3, 30));
	CHECK(!CheckStringCapacity(str3, 19));
	CHECK(CheckStringCapacity(CMyString{ "hello world world", 3 }, 15));
	CHECK(!CheckStringCapacity(CMyString{ "hello world world", 3 }, 19));
	CHECK(CheckStringCapacity(CMyString{ CMyString{"hello world world"} }, 30));
	CHECK(!CheckStringCapacity(CMyString{ CMyString{"hello world world"} }, 19));
	CHECK(CheckStringCapacity(std::string{ "hello world world" }, 30));
	CHECK(!CheckStringCapacity(std::string{ "hello world world" }, 19));
	CHECK(CheckStringCapacity(CMyString{ "hello world world" }, 30));
	CHECK(!CheckStringCapacity(CMyString{ "hello world world" }, 19));
};

bool CheckOperatorEquality(CMyString const& left, CMyString const& right)
{
	return left == right;
}

SCENARIO("check operator ==")
{
	CHECK(CheckOperatorEquality(CMyString { "hello world" }, CMyString { "hello world\0" }));
	CHECK(!CheckOperatorEquality(CMyString{ "hello world" }, CMyString{ "hello worl" }));
	CHECK(CheckOperatorEquality(CMyString{ "h" }, CMyString{ "h" }));
	CHECK(!CheckOperatorEquality(CMyString{ "h" }, CMyString{ "2h" }));
	CHECK(CheckOperatorEquality(CMyString{ "" }, CMyString{ "" }));
}

bool CheckOperatorInequalityy(CMyString const& left, CMyString const& right)
{
	return left != right;
}

SCENARIO("check operator !=")
{
	CHECK(!CheckOperatorInequalityy(CMyString{ "hello world" }, CMyString{ "hello world" }));
	CHECK(CheckOperatorInequalityy(CMyString{ "hello world" }, CMyString{ "hello worl" }));
	CHECK(!CheckOperatorInequalityy(CMyString{ "h" }, CMyString{ "h" }));
	CHECK(CheckOperatorInequalityy(CMyString{ "h" }, CMyString{ "2h" }));
	CHECK(!CheckOperatorInequalityy(CMyString{ "" }, CMyString{ "" }));
}

SCENARIO("check operator =")
{
	CMyString str1{ "hello world" };
	CMyString str2{ "hello" };
	str1 = str2;
	CHECK(str1.GetLength() == str2.GetLength());
	CHECK(str1.GetCapacity() == str2.GetCapacity());
	CHECK(str1 == str2);
	str1 = str1;
	CHECK(str1.GetLength() == str2.GetLength());
	CHECK(str1.GetCapacity() == str2.GetCapacity());
	CHECK(str1 == str2);
}

CMyString GetNewStringFromCMyStringPlusCMyString(std::string left, std::string right)
{
	CMyString str1{ left };
	CMyString str2{ right };
	str1 += str2;

	return str1;
}

SCENARIO("check operator +=")
{
	CHECK(GetNewStringFromCMyStringPlusCMyString("hello", "world").GetLength() == 10);
	CHECK(GetNewStringFromCMyStringPlusCMyString("hello", "world").GetCapacity() == 15);
	CHECK(GetNewStringFromCMyStringPlusCMyString("hello", "world") == "helloworld");

	CHECK(GetNewStringFromCMyStringPlusCMyString("hello ", "world").GetLength() == 11);
	CHECK(GetNewStringFromCMyStringPlusCMyString("hello ", "world").GetCapacity() == 15);
	CHECK(GetNewStringFromCMyStringPlusCMyString("hello ", "world") == "hello world");

	CHECK(!(GetNewStringFromCMyStringPlusCMyString("hello", "world").GetLength() == 12));
	CHECK(!(GetNewStringFromCMyStringPlusCMyString("hello ", "world").GetCapacity() == 17));
	CHECK(!(GetNewStringFromCMyStringPlusCMyString("hello ", "world") == "helloworld"));
}

SCENARIO("check substring")
{
	CHECK(CMyString{ "hello world" }.SubString(0, 6) == "hello ");
	CHECK(!(CMyString{ "hello world" }.SubString(0, 3) == "hello"));
	CHECK(CMyString{"hello world"}.SubString(0, 5) == "hello");
	CHECK(CMyString{ "hello world" }.SubString(2, 5) == "llo w");
	CHECK(CMyString{ "hello world" }.SubString(10, 1) == "d");
	CHECK(CMyString{ "hello world" }.SubString(10, 0) == "\0");
}

bool CheckOperatorPlusWithCharsAndCMyString(const char* str1, CMyString str2, std::string expectedStr)
{
	CMyString str = str1 + str2;
	return str.GetStringData() == expectedStr;
}

SCENARIO("check operator + with char* and CMyString")
{
	CHECK(CheckOperatorPlusWithCharsAndCMyString({ "" }, CMyString{ "hello world" }, "hello world"));
	CHECK(CheckOperatorPlusWithCharsAndCMyString({ "\0" }, CMyString{ "hello world" }, "hello world"));
	CHECK(!CheckOperatorPlusWithCharsAndCMyString({ "" }, CMyString{ "hello world" }, "hello world2"));
	CHECK(!CheckOperatorPlusWithCharsAndCMyString({ "\0" }, CMyString{ "hello world" }, "hello world2"));
	CHECK(CheckOperatorPlusWithCharsAndCMyString({ "hello" }, CMyString{ "hello world" }, "hellohello world"));
	CHECK(CheckOperatorPlusWithCharsAndCMyString({ "hello " }, CMyString{ "hello world" }, "hello hello world"));
	CHECK(!CheckOperatorPlusWithCharsAndCMyString({ "hello" }, CMyString{ "hello world" }, "hellohello world2"));
	CHECK(!CheckOperatorPlusWithCharsAndCMyString({ "hello " }, CMyString{ "hello world" }, "hello hello world2"));
}

bool CheckOperatorPlusWithCMyStringAndCMyString(CMyString str1, CMyString str2, std::string expectedStr)
{
	CMyString str = str1 + str2;
	return str == expectedStr;
}

SCENARIO("check operator + with CMyString and CMyString")
{
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{ "hello world" }, "hello worldhello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{ "hello world" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "" }, CMyString{ "hello world" }, "hello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "" }, CMyString{ "hello world" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString (CMyString{ "hello world" }, CMyString{ "" }, "hello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" },  CMyString{ "" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{ "\0" }, "hello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{ "\0" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{}, "hello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{ "hello world" }, CMyString{}, "hello hello world"));
	CHECK(CheckOperatorPlusWithCMyStringAndCMyString( CMyString{}, CMyString{ "hello world" }, "hello world"));
	CHECK(!CheckOperatorPlusWithCMyStringAndCMyString(CMyString{}, CMyString{ "hello world" }, "hello hello world"));
}

bool CheckOperatorPlusWithStlStringAndCMyString(std::string str1, CMyString str2, std::string expectedStr)
{
	CMyString str = str1 + str2;
	return str == expectedStr;
}

SCENARIO("check operator + with stlString and CMyString")
{
	CHECK(CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{ "hello world" }, "hello worldhello world"));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{ "hello world" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithStlStringAndCMyString(std::string{""}, CMyString{"hello world"}, "hello world"));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString(std::string{""}, CMyString{"hello world"}, "hello hello world"));
	CHECK(CheckOperatorPlusWithStlStringAndCMyString( std::string{ "hello world" }, CMyString{ "" }, "hello world"));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{ "" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithStlStringAndCMyString(std::string{""}, CMyString{"\0"}, ""));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString(std::string{ "" }, CMyString{ "\0" }, "hello"));
	CHECK(CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{ "\0" }, "hello world"));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{ "\0" }, "hello hello world"));
	CHECK(CheckOperatorPlusWithStlStringAndCMyString(std::string{ "hello world" }, CMyString{}, "hello world"));
	CHECK(!CheckOperatorPlusWithStlStringAndCMyString( std::string{ "hello world" }, CMyString{}, "hello hello world"));
}

bool CheckOperatorLessThan(CMyString str1, CMyString str2)
{
	return str1 < str2;
}

bool CheckOperatorGreaterThan(CMyString str1, CMyString str2)
{
	return str1 > str2;
}

bool CheckOperatorGreaterThanOrEqual(CMyString str1, CMyString str2)
{
	return str1 >= str2;
}

bool CheckOperatorLessThanEqual(CMyString str1, CMyString str2)
{
	return str1 <= str2;
}

SCENARIO("check operator greater than")
{
	CHECK(CheckOperatorGreaterThan(CMyString{ "hello world1111" }, CMyString{ "hello world" }));
	CHECK(!CheckOperatorGreaterThan(CMyString{ "hello world" }, CMyString{ "hello world" }));
	CHECK(!CheckOperatorGreaterThan(CMyString{ "hello world" }, CMyString{ "hello world1111" }));
	CHECK(!CheckOperatorGreaterThan(CMyString{ "\0" }, CMyString{ "\0" }));
	CHECK(!CheckOperatorGreaterThan(CMyString{ "\0" }, CMyString{ "1" }));
	CHECK(CheckOperatorGreaterThan(CMyString{ "1" }, CMyString{ "\0" }));
	CHECK(CheckOperatorGreaterThan(CMyString{ "1" }, CMyString{}));
	CHECK(!CheckOperatorGreaterThan(CMyString{ }, CMyString{ "1" }));
	CHECK(!CheckOperatorGreaterThan(CMyString{}, CMyString{}));
	CHECK(!CheckOperatorGreaterThan(CMyString{ "\0"}, CMyString{}));
}

SCENARIO("check operator less than")
{
	CHECK(!CheckOperatorLessThan(CMyString{ "hello world1111" }, CMyString{ "hello world" }));
	CHECK(!CheckOperatorLessThan(CMyString{ "hello world" }, CMyString{ "hello world" }));
	CHECK(CheckOperatorLessThan(CMyString{ "hello world" }, CMyString{ "hello world1111" }));
	CHECK(!CheckOperatorLessThan(CMyString{ "\0" }, CMyString{ "\0" }));
	CHECK(CheckOperatorLessThan(CMyString{ "\0" }, CMyString{ "1" }));
	CHECK(!CheckOperatorLessThan(CMyString{ "1" }, CMyString{ "\0" }));
	CHECK(!CheckOperatorLessThan(CMyString{ "1" }, CMyString{}));
	CHECK(CheckOperatorLessThan(CMyString{ }, CMyString{ "1" }));
	CHECK(!CheckOperatorLessThan(CMyString{}, CMyString{}));
	CHECK(!CheckOperatorLessThan(CMyString{ "\0" }, CMyString{}));
}

SCENARIO("check operator greater than or equal")
{
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "hello world1111" }, CMyString{ "hello world" }));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "hello world" }, CMyString{ "hello world" }));
	CHECK(!CheckOperatorGreaterThanOrEqual(CMyString{ "hello world" }, CMyString{ "hello world1111" }));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "\0" }, CMyString{ "\0" }));
	CHECK(!CheckOperatorGreaterThanOrEqual(CMyString{ "\0" }, CMyString{ "1" }));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "1" }, CMyString{ "\0" }));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "1" }, CMyString{}));
	CHECK(!CheckOperatorGreaterThanOrEqual(CMyString{ }, CMyString{ "1" }));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{}, CMyString{}));
	CHECK(CheckOperatorGreaterThanOrEqual(CMyString{ "\0" }, CMyString{}));
}

SCENARIO("check operator less than or equal")
{
	CHECK(!CheckOperatorLessThanEqual(CMyString{ "hello world1111" }, CMyString{ "hello world" }));
	CHECK(CheckOperatorLessThanEqual(CMyString{ "hello world" }, CMyString{ "hello world" }));
	CHECK(CheckOperatorLessThanEqual(CMyString{ "hello world" }, CMyString{ "hello world1111" }));
	CHECK(CheckOperatorLessThanEqual(CMyString{ "\0" }, CMyString{ "\0" }));
	CHECK(CheckOperatorLessThanEqual(CMyString{ "\0" }, CMyString{ "1" }));
	CHECK(!CheckOperatorLessThanEqual(CMyString{ "1" }, CMyString{ "\0" }));
	CHECK(!CheckOperatorLessThanEqual(CMyString{ "1" }, CMyString{}));
	CHECK(CheckOperatorLessThanEqual(CMyString{ }, CMyString{ "1" }));
	CHECK(CheckOperatorLessThanEqual(CMyString{}, CMyString{}));
	CHECK(CheckOperatorLessThanEqual(CMyString{ "\0" }, CMyString{}));
}

bool CheckOperatorInput(std::string strData)
{
	CMyString str;
	std::stringstream in;
	in << strData;
	in >> str;
	if (!in.fail() && str.GetStringData() == strData)
	{
		return true;
	}

	return false;
}

SCENARIO("check input operator ")
{
	CHECK(CheckOperatorInput("01.01.1970"));
	CHECK(CheckOperatorInput("12.01.2001"));
	CHECK(CheckOperatorInput("12.11.2001"));
	CHECK(CheckOperatorInput("31.12.9999"));
	CHECK(CheckOperatorInput("hello world hello asdasdnajsdjajdaj"));
};

bool CheckOperatorOutput(std::string strData)
{
	CMyString str;
	std::stringstream in;
	std::ostringstream out;
	in << strData;
	in >> str;
	out << str;

	if (!in.fail() && !out.bad() && out.str() == strData)
	{
		return true;
	}

	return false;
}

SCENARIO("check input operator output")
{
	CHECK(CheckOperatorOutput("01.01.1970"));
	CHECK(CheckOperatorOutput("12.01.2001"));
	CHECK(CheckOperatorOutput("12.11.2001"));
	CHECK(CheckOperatorOutput("31.12.9999"));
	CHECK(CheckOperatorOutput("hello world hello asdasdnajsdjajdaj"));
};

bool CheckOperatorIndex(CMyString str, unsigned i, const char expectedResult)
{
	return str[i] == expectedResult;
}

SCENARIO("check input operator []")
{
	CHECK(CheckOperatorIndex("01.01.1970", 2, '.'));
	CHECK(CheckOperatorIndex("12.01.2001", 1, '2'));
	CHECK(CheckOperatorIndex("12.11.2001", 8, '0'));
	CHECK(!CheckOperatorIndex("31.12.9999", 2, 'b'));
	CHECK(CheckOperatorIndex("hello world hello asdasdnajsdjajdaj", 20, 'd'));
};

