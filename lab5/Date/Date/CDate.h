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

// ƒата в формате день-мес€ц-год. √од в диапазоне от 1970 до 9999
class CDate
{
public:
    // инициализируем дату заданными днем, мес€цем и годом.
    // примечание: год >= 1970
    CDate(unsigned day, Month month, unsigned year);

    // инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
    // например, 2 = 3 €нвар€ 1970, 32 = 2 феврал€ 1970 года и т.д.
    explicit CDate(unsigned timestamp);

    //  онструктор по умолчанию. —оздаЄт дату, равную 1 €нвар€ 1970.
    CDate();

    // возвращает день мес€ца (от 1 до 31)
    unsigned GetDay() const;

    unsigned GetTimestamp() const;

    //// возвращает мес€ц
    Month GetMonth() const;

    //// возвращает год
    unsigned GetYear() const;

    //// возвращает день недели
    WeekDay GetWeekDay() const;

    //// возвращает информацию о корректности хранимой даты.
    //// Ќапример, после вызова CDate date(99, static_cast<Month>(99), 10983);
    //// или после:
    //// CDate date(1, January, 1970); --date;
    //// метод date.IsValid() должен вернуть false;

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
        ++*this; //используетс€ инкремент выше
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

    //нет смысла передавать int по const ссылке
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

///«амечани€:
///+ метод isleapyear должен быть статическим
///+ сделать префикс s_ m_MAX_DAYS тоже сделать статическим 
///+ GetDays переименовать в timstamp 
///+ нет смысла передавать int по const ссылке 
///+ .. сделать так,чтобы вместо невалидной даты выбрасывалось исключение
///+ сделать вычитание даты из даты
///+ сделать тесты операций сравнени€ дл€ операций, когда она возвращает false
/// 
/// написать тесты операций вывода
/// 
/// писать инвалид аргумент