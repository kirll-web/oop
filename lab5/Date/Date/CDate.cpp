#include "CDate.h"

// инициализируем дату заданными днем, месяцем и годом.
// примечание: год >= 1970
CDate::CDate(unsigned day, Month month, unsigned year)
{
    if (!IsValidMonth(day, month, year))
    {
        throw "Invalid date";
    }
    unsigned getDaysOfYears = GetDaysOfYears(year);
    unsigned getDaysOfMonth = GetDaysOfMonth(month, year);
    m_days = day - 1 + getDaysOfYears + getDaysOfMonth;
}

CDate::CDate() = default;

CDate::CDate(unsigned timestamp) : m_days(timestamp) {}

WeekDay CDate::GetWeekDay() const
{
    int leapYears = 16;

    int leapDayCount = leapYears * 2;

    unsigned totalDays = 365 * 52 + leapDayCount;

    int weekday = ((m_days + 1) % 7 + totalDays % 7) % 7;

    int numberWeekDay = (weekday + 4) % 7;

    return static_cast<WeekDay>(numberWeekDay);
}

// возвращает день месяца (от 1 до 31)
unsigned CDate::GetDay() const
{
    unsigned year = GetYear();
    unsigned daysAndMonth = m_days - GetDaysOfYears(year);
    unsigned days = 0;

    days = daysAndMonth - GetDaysOfMonth(GetMonth(), year);

    return days + 1;
}

Month CDate::GetMonth() const
{
    unsigned year = GetYear();
    unsigned daysAndMonth = m_days + 1 - GetDaysOfYears(year);

    unsigned numberMonth = daysAndMonth / 32;
    
    int days = daysAndMonth - GetDaysOfMonth(static_cast<Month>(numberMonth + 1), year);

    if(!IsValidMonth(days, static_cast<Month>(numberMonth + 1), year))
    {
        ++numberMonth;
    }

    if (numberMonth == 12)
    {
        return static_cast<Month>(numberMonth);
    }
    else
    {
        return static_cast<Month>(numberMonth + 1);
    }
}

unsigned CDate::GetYear() const
{
    unsigned year = static_cast<unsigned>((m_days + 1) / 365.2425 - 0.002);
    unsigned yearFrom1970 = 1970 + year;

    return yearFrom1970;
}

void CDate::IsValid() const
{
    if (m_days > s_MAX_DAYS)
    {
        throw "Invalide date.";
    }
}

bool CDate::IsValidMonth(unsigned days, Month month, unsigned year) const
{
    std::map<Month, unsigned> daysInMonthMapForNonLeapYear =
    {
             {Month::JANUARY, 31},
             {Month::FEBRUARY, 28},
             {Month::MARCH, 31},
             {Month::APRIL, 30},
             {Month::MAY, 31},
             {Month::JUNE, 30},
             {Month::JULY, 31},
             {Month::AUGUST, 31},
             {Month::SEPTEMBER, 30},
             {Month::OCTOBER, 31},
             {Month::NOVEMBER, 30},
             {Month::DECEMBER, 31}
    };
    std::map<Month, unsigned> daysInMonthMapForLeapYear =
    {
        {Month::JANUARY, 31},
        {Month::FEBRUARY, 29},
        {Month::MARCH, 31},
        {Month::APRIL, 30},
        {Month::MAY, 31},
        {Month::JUNE, 30},
        {Month::JULY, 31},
        {Month::AUGUST, 31},
        {Month::SEPTEMBER, 30},
        {Month::OCTOBER, 31},
        {Month::NOVEMBER, 30},
        {Month::DECEMBER, 31}
    };


    if (IsLeapYear(year))
    {
        if (days <= daysInMonthMapForLeapYear[month])
        {
            return true;
        }
    }
    else
    {
        if (days <= daysInMonthMapForNonLeapYear[month])
        {
            return true;
        }
    }

    return false;
}

unsigned CDate::GetTimestamp() const
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
}

unsigned CDate::GetDaysOfYears(unsigned year) const
{
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
}

bool CDate::IsLeapYear(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


CDate operator+(CDate const& date, unsigned days)
{
    return CDate{ date.GetTimestamp() + days };
}

CDate operator+(unsigned days, CDate const& date)
{
    return CDate{ date + days };
}

CDate operator-(CDate const& date, unsigned days)
{
    return CDate{ date.GetTimestamp() - days };
}


bool operator!=(CDate const& left, CDate const& right)
{
    return !(left.m_days == right.m_days);
}

bool operator<(CDate const& left, CDate const& right)
{
    return left.m_days < right.m_days;
}

bool operator>(CDate const& left, CDate const& right)
{
    return left.m_days > right.m_days;
}

bool operator<=(CDate const& left, CDate const& right)
{
    return left.m_days <= right.m_days;
}

bool operator>=(CDate const& left, CDate const& right)
{
    return left.m_days >= right.m_days;
}

bool operator==(CDate const& left, CDate const& right)
{
    return left.m_days == right.m_days;
}

std::istream& operator>>(std::istream& in, CDate& date)
{
    unsigned days;
    unsigned month;
    unsigned year;

    if
        (
            !((in >> days) &&
                (in.get() == '.') &&
                (in >> month && month > 0 && month <= 12) &&
                (in.get() == '.') &&
                (in >> year && year >= 1970))
            )
    {
        in.setstate(std::ios_base::failbit | in.rdstate());
    }

    CDate newDate{ days, static_cast<Month>(month), year };

    date.m_days = newDate.GetTimestamp();

    return in;
}

//std::ostream& operator<<(std::ostream& out, CDate& date)
//{
//    out << std::to_string(date.GetTimestamp()) << '.'
//        << std::to_string(static_cast<unsigned>(date.GetMonth())) << '.'
//        << std::to_string(date.GetYear());
//
//    return out;
//}


unsigned operator-(CDate const& left, CDate const& right)
{
    return fabs(left.m_days - right.m_days);
}