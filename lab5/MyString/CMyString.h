#pragma once
#include <string>
#include <iostream>



class CMyString
{
public:
    // ����������� �� ���������
    CMyString();

    // �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
    CMyString(const char* pString);

    // �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
    CMyString(const char* pString, size_t length);

    //// ����������� �����������
    CMyString(CMyString const& other);

    //// ������������ �����������
    ////  ����������� ��������� � ������������ ���������� ������������ 
    CMyString(CMyString&& other) noexcept;

    //// �����������, ���������������� ������ ������� �� 
    //// ������ ����������� ���������� C++
    CMyString(std::string const& stlString);

    //// ���������� ������ - ����������� ������, ���������� ��������� ������
    ~CMyString();

    //// ���������� ����� ������ (��� ����� ������������ �������� �������)
    size_t GetLength() const;

    //// ���������� ��������� �� ������ �������� ������.
    //// � ����� ������� ����������� ������ ���� ����������� ������� ������
    //// ���� ���� ������ ������ 
    const char* GetStringData() const;

    //// ���������� ��������� � �������� ������� ������ �� ������ length ��������
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    //// ������� ������ (������ ���������� ����� ������� �����)
    void Clear();

    //// ���������� ����������� ������
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