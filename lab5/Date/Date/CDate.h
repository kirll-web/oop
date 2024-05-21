#pragma once
#include <iostream>
#include <map>
#include <string>
#include <cmath>


enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

struct WrongAgeException {
    int age;
};

enum class WeekDay
{
    SATURDAY = 0, SUNDAY, MONDAY , TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY
};

// ���� � ������� ����-�����-���. ��� � ��������� �� 1970 �� 9999
class CDate
{
public:
    // �������������� ���� ��������� ����, ������� � �����.
    // ����������: ��� >= 1970
    CDate(unsigned day, Month month, unsigned year);

    // �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
    // ��������, 2 = 3 ������ 1970, 32 = 2 ������� 1970 ���� � �.�.
    explicit CDate(unsigned timestamp);

    // ����������� �� ���������. ������ ����, ������ 1 ������ 1970.
    CDate();

    // ���������� ���� ������ (�� 1 �� 31)
    unsigned GetDay() const;

    unsigned GetTimestamp() const;

    //// ���������� �����
    Month GetMonth() const;

    //// ���������� ���
    unsigned GetYear() const;

    //// ���������� ���� ������
    WeekDay GetWeekDay() const;

    //// ���������� ���������� � ������������ �������� ����.
    //// ��������, ����� ������ CDate date(99, static_cast<Month>(99), 10983);
    //// ��� �����:
    //// CDate date(1, January, 1970); --date;
    //// ����� date.IsValid() ������ ������� false;

    void IsValid() const;

    bool IsValidMonth(unsigned days, Month month, unsigned year) const;

    static bool IsLeapYear(unsigned year);
    unsigned GetDaysOfYears(unsigned year) const;
    unsigned GetDaysOfMonth(Month month, unsigned year) const;

    CDate& operator++()
    {
        ++m_days;
        return *this;
    }

    CDate operator++(int)
    {
        CDate tmpCopy(*this);
        ++*this; //������������ ��������� ����
        return tmpCopy;
    }

    CDate& operator--()
    {
        --m_days;
        return *this;
    }

    CDate operator--(int)
    {
        CDate tmpCopy(*this);
        --*this;
        return tmpCopy;
    }

    CDate& operator+=(const int days)
    {
        m_days += days;
        return *this;
    }

    //��� ������ ���������� int �� const ������
    CDate& operator-=(const int days)
    {
        m_days -= days;
        return *this;
    }

    friend CDate operator+(unsigned days, CDate const& date);
    friend CDate operator+(CDate const& left, unsigned days);
    friend CDate operator-(CDate const& date, unsigned days);
    friend unsigned operator-(CDate const& left, CDate const& right);
    friend bool operator!=(CDate const& left, CDate const& right);
    friend bool operator<(CDate const& left, CDate const& right);
    friend bool operator<=(CDate const& left, CDate const& right);
    friend bool operator>(CDate const& left, CDate const& right);
    friend bool operator>=(CDate const& left, CDate const& right);
    friend bool operator==(CDate const& left, CDate const& right);
    friend std::istream& operator>>(std::istream& in, CDate& date);
    friend std::ostream& operator<<(std::istream& in, CDate& date);

private:
    unsigned m_days = 0;
    static const unsigned s_MAX_DAYS = 2'932'896;
};

///���������:
///+ ����� isleapyear ������ ���� �����������
///+ ������� ������� s_ m_MAX_DAYS ���� ������� ����������� 
///+ GetDays ������������� � timstamp 
///+ ��� ������ ���������� int �� const ������ 
///+ .. ������� ���,����� ������ ���������� ���� ������������� ����������
///+ ������� ��������� ���� �� ����
///+ ������� ����� �������� ��������� ��� ��������, ����� ��� ���������� false
/// 
/// �������� ����� �������� ������
/// 
/// ������ ������� ��������