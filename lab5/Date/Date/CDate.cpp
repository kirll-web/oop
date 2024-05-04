#include "CDate.h"

// инициализируем дату заданными днем, мес€цем и годом.
// примечание: год >= 1970
CDate::CDate(unsigned day, Month month, unsigned year)
{
   

    if (year < 1970)
    {
        std::cout << "The year 1970 was chosen because it cannot be set lower";
        year = 1970;
    }
    unsigned getDaysOfYears = GetDaysOfYears(year);
    unsigned getDaysOfMonth = GetDaysOfMonth(month, year);
    m_days = day + getDaysOfYears + getDaysOfMonth;
}

CDate::CDate() = default;

// инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
// например, 2 = 3 €нвар€ 1970, 32 = 2 феврал€ 1970 года и т.д.
CDate::CDate(unsigned timestamp) : m_days(timestamp) {}


// возвращает день мес€ца (от 1 до 31)
unsigned CDate::GetDay() const
{
    unsigned year = static_cast<unsigned>(m_days / 365.2425);
    unsigned yearFrom1970 = 1970 + year;
    unsigned daysAndMonth = m_days - GetDaysOfYears(yearFrom1970);
    unsigned month;
    unsigned days = 0;


    if (IsLeapYear(yearFrom1970))
    {
        month = daysAndMonth / 28;
    }
    else
    {
        month = daysAndMonth / 27;
    }

    days = daysAndMonth - GetDaysOfMonth(static_cast<Month>(month), yearFrom1970);

    if (month == 2 && days > 29 && IsLeapYear(yearFrom1970) || month == 2 && days > 28 && !IsLeapYear(yearFrom1970))
    {
        month += 1;
        days = daysAndMonth - GetDaysOfMonth(static_cast<Month>(month), yearFrom1970);
    }

    else if (days > 30)
    {
        month += 1;
        days = daysAndMonth - GetDaysOfMonth(static_cast<Month>(month), yearFrom1970);
    }

    return days;
}

///TODO: ƒќЅј¬»“№ ќ“ƒ≈Ћ№Ќ”ё ‘”Ќ ÷»ё,  ќ“ќ–јя ¬ќ«¬–јўј≈“  ќЋ»„≈—“¬ќ ƒЌ≈… ¬ ћ≈—я÷≈

Month CDate::GetMonth() const
{
    unsigned year = m_days / 365;
    unsigned yearFrom1970 = 1970 + year;
    unsigned daysAndMonth = m_days - GetDaysOfYears(yearFrom1970);

    return Month::JANUARY;
}
//// возвращает год
//unsigned CDate::GetYear() const
//{
//
//}
//// возвращает день недели
//WeekDay CDate::GetWeekDay() const
//{
//
//}
//// возвращает информацию о корректности хранимой даты.
//// Ќапример, после вызова CDate date(99, static_cast<Month>(99), 10983);
//// или после:
//// CDate date(1, January, 1970); --date;
//// метод date.IsValid() должен вернуть false;
//bool CDate::IsValid() const
//{
//}// —м. примечание

unsigned CDate::GetDays() const
{
    return m_days;
}

unsigned CDate::GetDaysOfMonth(Month month, unsigned year) const
{
    unsigned int days = 0;

    std::map<Month, int> m_daysFromMonthMapForNonLeapYear =
    {
             {Month::JANUARY, 0},
             {Month::FEBRUARY, 31},
             {Month::MARCH, 59},
             {Month::APRIL, 90},
             {Month::MAY, 120},
             {Month::JUNE, 151},
             {Month::JULY, 181},
             {Month::AUGUST, 212},
             {Month::SEPTEMBER, 243},
             {Month::OCTOBER, 273},
             {Month::NOVEMBER, 304},
             {Month::DECEMBER, 334}
    };


    std::map<Month, int> m_daysFromMonthMapForLeapYear =
    {
       {Month::JANUARY, 0},
       {Month::FEBRUARY, 31},
       {Month::MARCH, 60},
       {Month::APRIL, 91},
       {Month::MAY, 121},
       {Month::JUNE, 152},
       {Month::JULY, 182},
       {Month::AUGUST, 213},
       {Month::SEPTEMBER, 244},
       {Month::OCTOBER, 274},
       {Month::NOVEMBER, 305},
       {Month::DECEMBER, 335}
    };

    if (IsLeapYear(year))
    {
        return (m_daysFromMonthMapForLeapYear)[static_cast<Month>(month)];
    }
    else
    {
        return m_daysFromMonthMapForNonLeapYear[static_cast<Month>(month)];
    }
    return 1;
}

unsigned CDate::GetDaysOfYears(unsigned year) const
{
    /* int totalLeapYears = (year - 1970) / 4;
     totalLeapYears -= ((year - 1970) / 100);*/

    int totalLeapYears = (year) / 4;
    totalLeapYears -= (year) / 100;
    totalLeapYears += (year) / 400;

    int totalLeapYearsTo1970 = (1969) / 4;
    totalLeapYearsTo1970 -= (1970) / 100;
    totalLeapYearsTo1970 += (1970) / 400;

    totalLeapYears -= totalLeapYearsTo1970;

    if (IsLeapYear(year))
    {
        return (year - 1970 - totalLeapYears) * 365 + totalLeapYears * 366 - 1;
    }
    else
    {
        return (year - 1970 - totalLeapYears) * 365 + totalLeapYears * 366;
    }

    /* int days = 0;
     for (int y = 1970; y < year; ++y) {
         if (IsLeapYear(y)) {
             days += 366;
         }
         else {
             days += 365;
         }
     }
     return days;*/
}


bool CDate::IsLeapYear(unsigned year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}