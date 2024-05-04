#pragma once
#include <iostream>
#include <map>
// �����
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// ���� ������
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
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

    unsigned GetDays() const;

    //// ���������� �����
    Month GetMonth() const;

    //// ���������� ���
    //unsigned GetYear()const;

    //// ���������� ���� ������
    //WeekDay GetWeekDay()const;

    //// ���������� ���������� � ������������ �������� ����.
    //// ��������, ����� ������ CDate date(99, static_cast<Month>(99), 10983);
    //// ��� �����:
    //// CDate date(1, January, 1970); --date;
    //// ����� date.IsValid() ������ ������� false;
    //bool IsValid() const; // ��. ����������

    bool IsLeapYear(unsigned year) const;
    unsigned GetDaysOfYears(unsigned year) const;
    unsigned GetDaysOfMonth(Month month, unsigned year) const;
    
private:
    unsigned  m_days = 0;
};