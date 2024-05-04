#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Date/CDate.h"
#include <vector>
#include <sstream>


SCENARIO("check lear year")
{
	CDate date{ 2 };
	CHECK(date.IsLeapYear(2014) == false);
	CHECK(date.IsLeapYear(2012) == true);
	CHECK(date.IsLeapYear(2010) == false);
	CHECK(date.IsLeapYear(2008) == true);
	CHECK(date.IsLeapYear(1970) == false);
	CHECK(date.IsLeapYear(2000) == true);
	CHECK(date.IsLeapYear(1990) == false);
};

unsigned GetDays(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };
	
	return date.GetDays();
}

SCENARIO("check days")
{
	CHECK(GetDays(31, Month::DECEMBER, 2019) == 18262);
	CHECK(GetDays(30, Month::DECEMBER, 2019) == 18261);
	CHECK(GetDays(30, Month::NOVEMBER, 2019) == 18231);
	CHECK(GetDays(29, Month::NOVEMBER, 2019) == 18230);
	CHECK(GetDays(13, Month::SEPTEMBER, 2019) == 18153);
	CHECK(GetDays(13, Month::JANUARY, 2019) == 17910);
	CHECK(GetDays(1, Month::JANUARY, 2019) == 17898);
	CHECK(GetDays(1, Month::NOVEMBER, 2019) == 18202);
	CHECK(GetDays(1, Month::JANUARY, 2015) == 16437);
	CHECK(GetDays(15, Month::JANUARY, 2015) == 16451);
	CHECK(GetDays(31, Month::JANUARY, 2015) == 16467);
	CHECK(GetDays(31, Month::DECEMBER, 2008) == 14245);
	CHECK(GetDays(1, Month::DECEMBER, 2008) == 14215);
	CHECK(GetDays(1, Month::JANUARY, 2008) == 13880);
	CHECK(GetDays(1, Month::JANUARY, 2009) == 14246);
	CHECK(GetDays(1, Month::SEPTEMBER, 2021) == 18872);
	CHECK(GetDays(13, Month::JANUARY, 2012) == 15353);
	CHECK(GetDays(13, Month::JANUARY, 2021) == 18641);
	CHECK(GetDays(13, Month::FEBRUARY, 2021) == 18672);
	CHECK(GetDays(28, Month::FEBRUARY, 2008) == 13938);
	CHECK(GetDays(1, Month::SEPTEMBER, 2021) == 18872);
	CHECK(GetDays(2, Month::SEPTEMBER, 2021) == 18873);
};


unsigned GetDay(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };

	return date.GetDay();
}

SCENARIO("check day")
{
	CHECK(GetDay(1, Month::SEPTEMBER, 2021) == 1);
	CHECK(GetDay(28, Month::FEBRUARY, 2008) == 28);
	CHECK(GetDay(1, Month::SEPTEMBER, 2021) == 1);
	CHECK(GetDay(2, Month::SEPTEMBER, 2021) == 2);
	CHECK(GetDay(13, Month::SEPTEMBER, 2019) == 13);
	CHECK(GetDay(1, Month::NOVEMBER, 2019) == 1);
	CHECK(GetDay(31, Month::DECEMBER, 2008) == 31);
	CHECK(GetDay(1, Month::DECEMBER, 2008) == 1);
	CHECK(GetDay(13, Month::FEBRUARY, 2021) == 13);
	CHECK(GetDay(13, Month::JANUARY, 2019) == 13);


	CHECK(GetDay(31, Month::DECEMBER, 2019) == 31);
	CHECK(GetDay(29, Month::NOVEMBER, 2019) == 29);
	CHECK(GetDay(30, Month::DECEMBER, 2019) == 30);
	CHECK(GetDay(30, Month::NOVEMBER, 2019) == 30);
	CHECK(GetDay(1, Month::JANUARY, 2019) == 1);
	CHECK(GetDay(1, Month::JANUARY, 2015) == 1);
	CHECK(GetDay(15, Month::JANUARY, 2015) == 15);
	CHECK(GetDay(31, Month::JANUARY, 2015) == 31);
	CHECK(GetDay(1, Month::JANUARY, 2008) == 1);
	CHECK(GetDay(1, Month::JANUARY, 2009) == 1);
	
	CHECK(GetDay(13, Month::JANUARY, 2012) == 13);
	CHECK(GetDay(13, Month::JANUARY, 2021) == 13);
	
	
};


Month GetMonth(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };

	return date.GetMonth();
}

SCENARIO("check month")
{
	CHECK(GetMonth(1, Month::JANUARY, 2008) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2009) == Month::JANUARY);
	CHECK(GetMonth(1, Month::SEPTEMBER, 2021) == Month::SEPTEMBER);
	CHECK(GetMonth(13, Month::JANUARY, 2012) == Month::JANUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2008) == Month::FEBRUARY);
	CHECK(GetMonth(1, Month::SEPTEMBER, 2021) == Month::SEPTEMBER);
	CHECK(GetMonth(2, Month::SEPTEMBER, 2021) == Month::SEPTEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2021) == Month::DECEMBER);
};