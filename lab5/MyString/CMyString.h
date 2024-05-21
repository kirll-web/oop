#pragma once
#include <string>
#include <iostream>



class CMyString
{
public:
    // конструктор по умолчанию
    CMyString();

    // конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
    CMyString(const char* pString);

    // конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
    CMyString(const char* pString, size_t length);

    //// конструктор копирования
    CMyString(CMyString const& other);

    //// перемещающий конструктор
    ////  реализуется совместно с перемещающим оператором присваивания 
    CMyString(CMyString&& other) noexcept;

    //// конструктор, инициализирующий строку данными из 
    //// строки стандартной библиотеки C++
    CMyString(std::string const& stlString);

    //// деструктор класса - освобождает память, занимаемую символами строки
    ~CMyString();

    //// возвращает длину строки (без учета завершающего нулевого символа)
    size_t GetLength() const;

    //// возвращает указатель на массив символов строки.
    //// В конце массива обязательно должен быть завершающий нулевой символ
    //// даже если строка пустая 
    const char* GetStringData() const;

    //// возвращает подстроку с заданной позиции длиной не больше length символов
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    //// очистка строки (строка становится снова нулевой длины)
    void Clear();

    //// Возвращает вместимость строки
    size_t GetCapacity() const;
   
   

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& moved);
    CMyString& operator+=(CMyString const& other);
    
 
    char & operator[](size_t index);
    char& operator[](size_t index) const;


    friend CMyString operator+(const CMyString& left, const CMyString& right);
    friend CMyString operator+(const std::string& stlString, const CMyString& right);
    friend CMyString operator+(const char* charStr, const CMyString& right);
    friend bool operator==(CMyString const& left, CMyString const& right);
    friend bool operator!=(CMyString const& left, CMyString const& right);
    friend bool operator<(CMyString const& left, CMyString const& right);
    friend bool operator>(CMyString const& left, CMyString const& right);
    friend bool operator<=(CMyString const& left, CMyString const& right);
    friend bool operator>=(CMyString const& left, CMyString const& right);
    friend std::istream& operator>>(std::istream& in, CMyString& str);
    friend std::ostream& operator<<(std::ostream& out, CMyString& str);
    
private:
    static const unsigned s_DEFAULT_CAPACITY = 15;
    char* m_str = nullptr;
    size_t m_capacity = s_DEFAULT_CAPACITY;
    size_t m_length = 0;
    size_t GetNewSize(size_t requiredSize) const;
    void SetCapacity(size_t requiredSize);
    static char s_emptyStr;
};