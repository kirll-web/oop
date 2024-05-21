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
	
	return date.GetTimestamp();
}

SCENARIO("check days")
{
	CHECK(GetDays(31, Month::DECEMBER, 2019) == 18261);
	CHECK(GetDays(30, Month::DECEMBER, 2019) == 18260);
	CHECK(GetDays(30, Month::NOVEMBER, 2019) == 18230);
	CHECK(GetDays(29, Month::NOVEMBER, 2019) == 18229);
	CHECK(GetDays(13, Month::SEPTEMBER, 2019) == 18152);
	CHECK(GetDays(13, Month::JANUARY, 2019) == 17909);
	CHECK(GetDays(1, Month::JANUARY, 2019) == 17897);
	CHECK(GetDays(1, Month::NOVEMBER, 2019) == 18201);
	CHECK(GetDays(1, Month::JANUARY, 2015) == 16436);
	CHECK(GetDays(15, Month::JANUARY, 2015) == 16450);
	CHECK(GetDays(31, Month::JANUARY, 2015) == 16466);
	CHECK(GetDays(31, Month::DECEMBER, 2008) == 14244);
	CHECK(GetDays(1, Month::DECEMBER, 2008) == 14214);
	CHECK(GetDays(1, Month::JANUARY, 2008) == 13879);
	CHECK(GetDays(1, Month::JANUARY, 2009) == 14245);
	CHECK(GetDays(1, Month::SEPTEMBER, 2021) == 18871);
	CHECK(GetDays(13, Month::JANUARY, 2012) == 15352);
	CHECK(GetDays(13, Month::JANUARY, 2021) == 18640);
	CHECK(GetDays(13, Month::FEBRUARY, 2021) == 18671);
	CHECK(GetDays(28, Month::FEBRUARY, 2008) == 13937);
	CHECK(GetDays(1, Month::SEPTEMBER, 2021) == 18871);
	CHECK(GetDays(2, Month::SEPTEMBER, 2021) == 18872);
};
Month GetMonth(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };

	return date.GetMonth();
}

unsigned GetYear(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };

	return date.GetYear();
}

SCENARIO("check year")
{
	CHECK(GetYear(31, Month::DECEMBER, 2021) == 2021);
	CHECK(GetYear(1, Month::JANUARY, 2008) == 2008);
	CHECK(GetYear(1, Month::JANUARY, 2009) == 2009);
	CHECK(GetYear(13, Month::JANUARY, 2012) == 2012);
	CHECK(GetYear(1, Month::SEPTEMBER, 2021) == 2021);
	CHECK(GetYear(28, Month::FEBRUARY, 2008) == 2008);
	CHECK(GetYear(1, Month::SEPTEMBER, 2021) == 2021);
	CHECK(GetYear(2, Month::SEPTEMBER, 2021) == 2021);
	CHECK(GetYear(1, Month::SEPTEMBER, 1970) == 1970);
	CHECK(GetYear(1, Month::JANUARY, 1970) == 1970);
};

Month GetMonthWithTimestamp(unsigned timestamp)
{
	CDate date{ timestamp };

	return date.GetMonth();
}

SCENARIO("check month")
{
	CHECK(GetMonth(1, Month::SEPTEMBER, 2021) == Month::SEPTEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2021) == Month::DECEMBER);
	CHECK(GetMonth(1, Month::JANUARY, 2008) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2009) == Month::JANUARY);
	CHECK(GetMonth(13, Month::JANUARY, 2012) == Month::JANUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2008) == Month::FEBRUARY);
	CHECK(GetMonth(2, Month::SEPTEMBER, 2021) == Month::SEPTEMBER);
	CHECK(GetMonth(1, Month::JANUARY, 2012) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2013) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2014) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2015) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2016) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 2017) == Month::JANUARY);
	CHECK(GetMonth(1, Month::JANUARY, 1970) == Month::JANUARY);
	CHECK(GetMonth(31, Month::DECEMBER, 2012) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2013) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2014) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2015) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2016) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 2017) == Month::DECEMBER);
	CHECK(GetMonth(31, Month::DECEMBER, 1970) == Month::DECEMBER);
	CHECK(GetMonth(29, Month::FEBRUARY, 2012) == Month::FEBRUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2013) == Month::FEBRUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2014) == Month::FEBRUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2015) == Month::FEBRUARY);
	CHECK(GetMonth(29, Month::FEBRUARY, 2016) == Month::FEBRUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 2017) == Month::FEBRUARY);
	CHECK(GetMonth(28, Month::FEBRUARY, 1970) == Month::FEBRUARY);
};

SCENARIO("check month with timestamp")
{

	CHECK(GetMonthWithTimestamp(14244) == Month::DECEMBER);
	CHECK(GetMonthWithTimestamp(17909) ==  Month::JANUARY);
	CHECK(GetMonthWithTimestamp(18261) == Month::DECEMBER);
	CHECK(GetMonthWithTimestamp(18261) == Month::DECEMBER);
	CHECK(GetMonthWithTimestamp(18260) == Month::DECEMBER);
	CHECK(GetMonthWithTimestamp(18230) == Month::NOVEMBER);
	CHECK(GetMonthWithTimestamp(18229) == Month::NOVEMBER);
	CHECK(GetMonthWithTimestamp(18152) == Month::SEPTEMBER );
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
	CHECK(GetDay(1, Month::JANUARY, 1970) == 1);
};

unsigned GetDayWithTimestamp(unsigned timestamp)
{
	CDate date{ timestamp };

	return date.GetDay();
}

SCENARIO("check day with timestamp")
{
	CHECK(GetDayWithTimestamp(1) == 2);
	CHECK(GetDayWithTimestamp(18261) ==  31);
	CHECK(GetDayWithTimestamp(18260) == 30);
	CHECK(GetDayWithTimestamp(18230) ==  30);
	CHECK(GetDayWithTimestamp(18229) ==  29);
	CHECK(GetDayWithTimestamp(18152) ==  13);
	CHECK(GetDayWithTimestamp(17909) ==  13);
	CHECK(GetDayWithTimestamp(17897) ==  1);
	CHECK(GetDayWithTimestamp(18201) ==  1);
	CHECK(GetDayWithTimestamp(16436) ==  1);
	CHECK(GetDayWithTimestamp(16466) ==  31);
	CHECK(GetDayWithTimestamp(13879) ==  1);
	CHECK(GetDayWithTimestamp(18671) ==  13);
};


WeekDay GetWeekDay(unsigned days, Month month, unsigned year)
{
	CDate date{ days, month, year };

	return date.GetWeekDay();
}


SCENARIO("check week day")
{
	CHECK(GetWeekDay(1, Month::DECEMBER, 2019) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(2, Month::DECEMBER, 2019) == WeekDay::MONDAY);
	CHECK(GetWeekDay(3, Month::DECEMBER, 2019) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(4, Month::DECEMBER, 2019) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(5, Month::DECEMBER, 2019) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(6, Month::DECEMBER, 2019) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(7, Month::DECEMBER, 2019) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(8, Month::DECEMBER, 2019) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(9, Month::DECEMBER, 2019) == WeekDay::MONDAY);
	CHECK(GetWeekDay(10, Month::DECEMBER, 2019) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(11, Month::DECEMBER, 2019) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(12, Month::DECEMBER, 2019) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(13, Month::DECEMBER, 2019) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(14, Month::DECEMBER, 2019) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(15, Month::DECEMBER, 2019) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(16, Month::DECEMBER, 2019) == WeekDay::MONDAY);
	CHECK(GetWeekDay(17, Month::DECEMBER, 2019) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(18, Month::DECEMBER, 2019) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(19, Month::DECEMBER, 2019) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(20, Month::DECEMBER, 2019) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(21, Month::DECEMBER, 2019) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(22, Month::DECEMBER, 2019) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(23, Month::DECEMBER, 2019) == WeekDay::MONDAY);
	CHECK(GetWeekDay(24, Month::DECEMBER, 2019) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(25, Month::DECEMBER, 2019) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(26, Month::DECEMBER, 2019) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(27, Month::DECEMBER, 2019) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(28, Month::DECEMBER, 2019) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(29, Month::DECEMBER, 2019) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(30, Month::DECEMBER, 2019) == WeekDay::MONDAY);
	CHECK(GetWeekDay(31, Month::DECEMBER, 2019) == WeekDay::TUESDAY);

	CHECK(GetWeekDay(1, Month::JANUARY, 2008) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(2, Month::JANUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(3, Month::JANUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(4, Month::JANUARY, 2008) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(5, Month::JANUARY, 2008) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(6, Month::JANUARY, 2008) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(7, Month::JANUARY, 2008) == WeekDay::MONDAY);
	CHECK(GetWeekDay(8, Month::JANUARY, 2008) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(9, Month::JANUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(10, Month::JANUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(11, Month::JANUARY, 2008) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(12, Month::JANUARY, 2008) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(13, Month::JANUARY, 2008) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(14, Month::JANUARY, 2008) == WeekDay::MONDAY);
	CHECK(GetWeekDay(15, Month::JANUARY, 2008) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(16, Month::JANUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(17, Month::JANUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(18, Month::JANUARY, 2008) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(19, Month::JANUARY, 2008) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(20, Month::JANUARY, 2008) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(21, Month::JANUARY, 2008) == WeekDay::MONDAY);
	CHECK(GetWeekDay(22, Month::JANUARY, 2008) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(23, Month::JANUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(24, Month::JANUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(25, Month::JANUARY, 2008) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(26, Month::JANUARY, 2008) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(27, Month::JANUARY, 2008) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(28, Month::JANUARY, 2008) == WeekDay::MONDAY);
	CHECK(GetWeekDay(29, Month::JANUARY, 2008) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(30, Month::JANUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(31, Month::JANUARY, 2008) == WeekDay::THURSDAY);

	CHECK(GetWeekDay(1, Month::FEBRUARY, 2008) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(2, Month::FEBRUARY, 2008) == WeekDay::SATURDAY); 
	CHECK(GetWeekDay(3, Month::FEBRUARY, 2008) == WeekDay::SUNDAY); 
	CHECK(GetWeekDay(4, Month::FEBRUARY, 2008) == WeekDay::MONDAY);  
	CHECK(GetWeekDay(5, Month::FEBRUARY, 2008) == WeekDay::TUESDAY);  
	CHECK(GetWeekDay(6, Month::FEBRUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(7, Month::FEBRUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(8, Month::FEBRUARY, 2008) == WeekDay::FRIDAY);   
	CHECK(GetWeekDay(9, Month::FEBRUARY, 2008) == WeekDay::SATURDAY); 
	CHECK(GetWeekDay(10, Month::FEBRUARY, 2008) == WeekDay::SUNDAY);   
	CHECK(GetWeekDay(11, Month::FEBRUARY, 2008) == WeekDay::MONDAY); 
	CHECK(GetWeekDay(12, Month::FEBRUARY, 2008) == WeekDay::TUESDAY);   
	CHECK(GetWeekDay(13, Month::FEBRUARY, 2008) == WeekDay::WEDNESDAY); 
	CHECK(GetWeekDay(14, Month::FEBRUARY, 2008) == WeekDay::THURSDAY);  
	CHECK(GetWeekDay(15, Month::FEBRUARY, 2008) == WeekDay::FRIDAY);   
	CHECK(GetWeekDay(16, Month::FEBRUARY, 2008) == WeekDay::SATURDAY);  
	CHECK(GetWeekDay(17, Month::FEBRUARY, 2008) == WeekDay::SUNDAY);    
	CHECK(GetWeekDay(18, Month::FEBRUARY, 2008) == WeekDay::MONDAY);    
	CHECK(GetWeekDay(19, Month::FEBRUARY, 2008) == WeekDay::TUESDAY);  

	CHECK(GetWeekDay(27, Month::FEBRUARY, 2008) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(28, Month::FEBRUARY, 2008) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(29, Month::FEBRUARY, 2008) == WeekDay::FRIDAY);

	CHECK(GetWeekDay(1, Month::DECEMBER, 2009) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(2, Month::DECEMBER, 2009) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(3, Month::DECEMBER, 2009) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(4, Month::DECEMBER, 2009) == WeekDay::FRIDAY);
	CHECK(GetWeekDay(5, Month::DECEMBER, 2009) == WeekDay::SATURDAY);
	CHECK(GetWeekDay(6, Month::DECEMBER, 2009) == WeekDay::SUNDAY);
	CHECK(GetWeekDay(7, Month::DECEMBER, 2009) == WeekDay::MONDAY);

	CHECK(GetWeekDay(28, Month::DECEMBER, 2009) == WeekDay::MONDAY);
	CHECK(GetWeekDay(29, Month::DECEMBER, 2009) == WeekDay::TUESDAY);
	CHECK(GetWeekDay(30, Month::DECEMBER, 2009) == WeekDay::WEDNESDAY);
	CHECK(GetWeekDay(31, Month::DECEMBER, 2009) == WeekDay::THURSDAY);
	CHECK(GetWeekDay(1, Month::JANUARY, 1970) == WeekDay::THURSDAY);
};



bool CheckOperatorGreaterThan(CDate left, CDate right)
{
	return left > right;
}

SCENARIO("check operator >")
{
	CHECK(CheckOperatorGreaterThan({ 1, Month::DECEMBER, 1969 }, { 2, Month::DECEMBER, 1969 }) == false);
	CHECK(CheckOperatorGreaterThan({ 2, Month::DECEMBER, 1969 }, { 1, Month::DECEMBER, 1969 }) == true);
	CHECK(CheckOperatorGreaterThan({ 31, Month::DECEMBER, 9999 }, { 1, Month::JANUARY, 1970 }) == true);
	CHECK(CheckOperatorGreaterThan({ 1, Month::JANUARY, 1970 }, { 2, Month::JANUARY, 1970 }) == false);
};


bool CheckOperatorLessThan(CDate left, CDate right)
{
	return left < right;
}

SCENARIO("check operator <")
{
	CHECK(CheckOperatorLessThan({ 1, Month::DECEMBER, 1969 }, { 2, Month::DECEMBER, 1969 }) == true);
	CHECK(CheckOperatorLessThan({ 2, Month::DECEMBER, 1969 }, { 1, Month::DECEMBER, 1969 }) == false);
	CHECK(CheckOperatorLessThan({ 31, Month::DECEMBER, 9999 }, { 1, Month::JANUARY, 1970 }) == false);
	CHECK(CheckOperatorLessThan({ 1, Month::JANUARY, 1970 }, { 2, Month::JANUARY, 1970 }) == true);
};

unsigned CheckOperatorPostfixPlusPlus(CDate date)
{
	return date++.GetTimestamp();
}

SCENARIO("check operator date++")
{
	CHECK(CheckOperatorPostfixPlusPlus({ 31, Month::DECEMBER, 2019 }) == 18261);
	CHECK(CheckOperatorPostfixPlusPlus({ 30, Month::DECEMBER, 2019 }) == 18260);
	CHECK(CheckOperatorPostfixPlusPlus({ 30, Month::NOVEMBER, 2019 }) == 18230);
	CHECK(CheckOperatorPostfixPlusPlus({ 29, Month::NOVEMBER, 2019 }) == 18229);
	CHECK(CheckOperatorPostfixPlusPlus({ 13, Month::SEPTEMBER, 2019 }) == 18152);
	CHECK(CheckOperatorPostfixPlusPlus({ 13, Month::JANUARY, 2019 }) == 17909);
	CHECK(CheckOperatorPostfixPlusPlus({ 1, Month::JANUARY, 2019 }) == 17897);
	CHECK(CheckOperatorPostfixPlusPlus({ 1, Month::NOVEMBER, 2019 }) == 18201);
	CHECK(CheckOperatorPostfixPlusPlus({ 1, Month::JANUARY, 2015 }) == 16436);
	CHECK(CheckOperatorPostfixPlusPlus(CDate(13003)) == 13003);
	CHECK(CheckOperatorPostfixPlusPlus(CDate(0)) == 0);
};


CDate CheckOperatorPrefixPlusPLus(CDate date)
{
	return ++date;
}

SCENARIO("check operator ++date")
{
	CHECK(CheckOperatorPrefixPlusPLus({ 31, Month::DECEMBER, 2019 }).GetTimestamp() == 18262);
	CHECK(CheckOperatorPrefixPlusPLus({ 30, Month::DECEMBER, 2019 }).GetTimestamp() == 18261);
	CHECK(CheckOperatorPrefixPlusPLus({ 30, Month::NOVEMBER, 2019 }).GetTimestamp() == 18231);
	CHECK(CheckOperatorPrefixPlusPLus({ 29, Month::NOVEMBER, 2019 }).GetTimestamp() == 18230);
	CHECK(CheckOperatorPrefixPlusPLus({ 13, Month::SEPTEMBER, 2019 }).GetTimestamp() == 18153);
	CHECK(CheckOperatorPrefixPlusPLus({ 13, Month::JANUARY, 2019 }).GetTimestamp() == 17910);
	CHECK(CheckOperatorPrefixPlusPLus({ 1, Month::JANUARY, 2019 }).GetTimestamp() == 17898);
	CHECK(CheckOperatorPrefixPlusPLus({ 1, Month::NOVEMBER, 2019 }).GetTimestamp() == 18202);
	CHECK(CheckOperatorPrefixPlusPLus({ 1, Month::JANUARY, 2015 }).GetTimestamp() == 16437);
	CHECK(CheckOperatorPrefixPlusPLus(CDate(13003)).GetTimestamp() == 13004);
	CHECK(CheckOperatorPrefixPlusPLus(CDate(0)).GetTimestamp() == 1);
};

unsigned CheckOperatorPostfixMinusMinus(CDate date)
{
	return date--.GetTimestamp();
}

SCENARIO("check operator date--")
{
	CHECK(CheckOperatorPostfixMinusMinus({ 31, Month::DECEMBER, 2019 }) == 18261);
	CHECK(CheckOperatorPostfixMinusMinus({ 30, Month::DECEMBER, 2019 }) == 18260);
	CHECK(CheckOperatorPostfixMinusMinus({ 30, Month::NOVEMBER, 2019 }) == 18230);
	CHECK(CheckOperatorPostfixMinusMinus({ 29, Month::NOVEMBER, 2019 }) == 18229);
	CHECK(CheckOperatorPostfixMinusMinus({ 13, Month::SEPTEMBER, 2019 }) == 18152);
	CHECK(CheckOperatorPostfixMinusMinus({ 13, Month::JANUARY, 2019 }) == 17909);
	CHECK(CheckOperatorPostfixMinusMinus({ 1, Month::JANUARY, 2019 }) == 17897);
	CHECK(CheckOperatorPostfixMinusMinus({ 1, Month::NOVEMBER, 2019 }) == 18201);
	CHECK(CheckOperatorPostfixMinusMinus({ 1, Month::JANUARY, 2015 }) == 16436);
	CHECK(CheckOperatorPostfixMinusMinus(CDate(13003)) == 13003);
	CHECK(CheckOperatorPostfixMinusMinus(CDate(0)) == 0);
};


CDate CheckOperatorPrefixMinusMinus(CDate date)
{
	return --date;
}

SCENARIO("check operator --date")
{
	CHECK(CheckOperatorPrefixMinusMinus({ 31, Month::DECEMBER, 2019 }).GetTimestamp() == 18260);
	CHECK(CheckOperatorPrefixMinusMinus({ 30, Month::DECEMBER, 2019 }).GetTimestamp() == 18259);
	CHECK(CheckOperatorPrefixMinusMinus({ 30, Month::NOVEMBER, 2019 }).GetTimestamp() == 18229);
	CHECK(CheckOperatorPrefixMinusMinus({ 29, Month::NOVEMBER, 2019 }).GetTimestamp() == 18228);
	CHECK(CheckOperatorPrefixMinusMinus({ 13, Month::SEPTEMBER, 2019 }).GetTimestamp() == 18151);
	CHECK(CheckOperatorPrefixMinusMinus({ 13, Month::JANUARY, 2019 }).GetTimestamp() == 17908);
	CHECK(CheckOperatorPrefixMinusMinus({ 1, Month::JANUARY, 2019 }).GetTimestamp() == 17896);
	CHECK(CheckOperatorPrefixMinusMinus({ 1, Month::NOVEMBER, 2019 }).GetTimestamp() == 18200);
	CHECK(CheckOperatorPrefixMinusMinus({ 1, Month::JANUARY, 2015 }).GetTimestamp() == 16435);
	CHECK(CheckOperatorPrefixMinusMinus(CDate(13003)).GetTimestamp() == 13002);
	CHECK(CheckOperatorPrefixMinusMinus(CDate(1)).GetTimestamp() == 0);
};

bool CheckOperatorAdditionWithAssignment(CDate date, unsigned days, unsigned expectResult)
{
	date += days;
	return expectResult == date.GetTimestamp();
}

SCENARIO("check operator Date+= days")
{
	CHECK(CheckOperatorAdditionWithAssignment({ 31, Month::DECEMBER, 2019 }, 5, 18266));
	CHECK(CheckOperatorAdditionWithAssignment({ 30, Month::DECEMBER, 2019 }, 3, 18263));
	CHECK(CheckOperatorAdditionWithAssignment({ 30, Month::NOVEMBER, 2019 }, -5, 18225));
};

bool CheckOperatorMinusWithAssignment(CDate date, unsigned days, unsigned expectResult)
{
	date -= days;
	return expectResult == date.GetTimestamp();
}

SCENARIO("check operator Date-= days")
{
	CHECK(CheckOperatorMinusWithAssignment({ 31, Month::DECEMBER, 2019 }, 5, 18256));
	CHECK(CheckOperatorMinusWithAssignment({ 30, Month::DECEMBER, 2019 }, 3, 18257));
	CHECK(CheckOperatorMinusWithAssignment({ 30, Month::NOVEMBER, 2019 }, -5, 18235));
};

bool CheckOperatorDaysPlusDate(CDate date, unsigned days, unsigned expectResult)
{
	CDate newDate =  days + date;
	return expectResult == newDate.GetTimestamp();
}

SCENARIO("check operator Days Plus Date")
{
	CHECK(CheckOperatorDaysPlusDate({ 31, Month::DECEMBER, 2019 }, 5, 18266));
	CHECK(CheckOperatorDaysPlusDate({ 30, Month::DECEMBER, 2019 }, 3, 18263));
	CHECK(CheckOperatorDaysPlusDate({ 30, Month::NOVEMBER, 2019 }, -5, 18225));
};

bool CheckOperatorDatePlusDays(CDate date, unsigned days, unsigned expectResult)
{
	CDate newDate = date + days;
	return expectResult == newDate.GetTimestamp();
}

SCENARIO("check operator Date Plus Days")
{
	CHECK(CheckOperatorDatePlusDays({ 31, Month::DECEMBER, 2019 }, 5, 18266));
	CHECK(CheckOperatorDatePlusDays({ 30, Month::DECEMBER, 2019 }, 3, 18263));
	CHECK(CheckOperatorDatePlusDays({ 30, Month::NOVEMBER, 2019 }, -5, 18225));
};

SCENARIO("check operators comparison")
{
	CHECK(CDate(31, Month::MARCH, 2008) == CDate(31, Month::MARCH, 2008));
	CHECK((CDate(31, Month::MARCH, 2008) == CDate(30, Month::MARCH, 2008)) == false);
	CHECK(CDate(31, Month::MARCH, 2008) >= CDate(30, Month::MARCH, 2008));
	CHECK((CDate(28, Month::MARCH, 2008) >= CDate(30, Month::MARCH, 2008)) == false);
	CHECK(CDate(30, Month::MARCH, 2008) <= CDate(31, Month::MARCH, 2008));
	CHECK((CDate(30, Month::MARCH, 2008) <= CDate(25, Month::MARCH, 2008)) == false);
	CHECK(CDate(31, Month::MARCH, 2008) > CDate(30, Month::MARCH, 2008));
	CHECK((CDate(25, Month::MARCH, 2008) > CDate(30, Month::MARCH, 2008)) == false);
	CHECK(CDate(30, Month::MARCH, 2008) < CDate(31, Month::MARCH, 2008));
	CHECK((CDate(30, Month::MARCH, 2008) < CDate(25, Month::MARCH, 2008)) == false);
	CHECK(CDate(31, Month::MARCH, 2008) != CDate(30, Month::MARCH, 2008));
	CHECK((CDate(31, Month::MARCH, 2008) != CDate(31, Month::MARCH, 2008)) == false);
};

bool CheckOperatorInput(std::string strDate)
{
	CDate date;
	std::stringstream in;
	in << strDate;
	in >> date;
	if (!in.fail())
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
};

bool CheckOperatorDateMinusDate(CDate left, CDate right, unsigned expectResult)
{
	unsigned days = left - right;
	return expectResult == days;
}

SCENARIO("check operator Date minus Date")
{
	CHECK(CheckOperatorDateMinusDate({ 31, Month::DECEMBER, 2019 }, { 30, Month::DECEMBER, 2019 }, 1));
	CHECK(CheckOperatorDateMinusDate({ 31, Month::DECEMBER, 2019 }, { 25, Month::DECEMBER, 2019 }, 6));
};

std::ostream& operator<<(std::ostream& out, CDate& date)
{
	out << std::to_string(date.GetTimestamp()) << '.'
		<< std::to_string(static_cast<unsigned>(date.GetMonth())) << '.'
		<< std::to_string(date.GetYear());

	return out;
}

bool CheckOperatorOutput(std::string strDate)
{
	CDate date;
	std::stringstream in;
	std::ostringstream out;
	in << strDate;
	in >> date;
	out << date;

	if (!in.fail() && out.bad() && out.str() == strDate)
	{
		return true;
	}

	return false;
}

SCENARIO("check input operator output")
{
	CHECK(CheckOperatorInput("01.01.1970"));
	CHECK(CheckOperatorInput("12.01.2001"));
	CHECK(CheckOperatorInput("12.11.2001"));
	CHECK(CheckOperatorInput("31.12.9999"));
};