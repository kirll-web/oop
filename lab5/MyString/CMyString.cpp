#include "CMyString.h"


char CMyString::s_emptyStr = '\0';

CMyString::CMyString() : m_str(&s_emptyStr), m_capacity(0), m_length(0) {};

// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
CMyString::CMyString(const char* pString) 
{
	size_t length = strlen(pString);
	SetCapacity(length + 1);
	m_length = length;	
	for (size_t i = 0; i < m_length; i++)
	{
		m_str[i] = pString[i];
	}

	m_str[length] = '\0';
}
//замерить покрытие
CMyString::CMyString(std::string const& stlString)
{
	size_t length = stlString.length();
	///
	SetCapacity(length + 1);
	m_length = length;

	for (size_t i = 0; i < m_length; i++)
	{
		m_str[i] = stlString[i];
	};
	m_str[length] = '\0';
	///можно вынести в приватный делигирующий конструктор
}

CMyString::CMyString(const char* pString, size_t length)
{
	SetCapacity(length + 1);
	m_length = length;
	for (size_t i = 0; i < length; i++)
	{
		m_str[i] = pString[i];
	}
	m_str[length] = '\0';
}


// конструктор копирования
CMyString::CMyString(CMyString const& other) 
{
	SetCapacity(other.m_length + 1);
	m_length = other.m_length;
	for (size_t i = 0; i < m_length; i++)
	{
		m_str[i] = other.m_str[i];
	}
	m_str[m_length] = '\0';
}

// перемещающий конструктор
//  реализуется совместно с перемещающим оператором присваивания 
CMyString::CMyString(CMyString&& other) noexcept
{
	if (&other != this)
	{
		Clear();
		m_str = other.m_str;
		m_capacity = other.m_capacity;
		m_length = other.m_length;
		other.Clear();
	}
}

void CMyString::SetCapacity(size_t requiredSize)
{
	if (requiredSize == 0)
	{
		throw std::invalid_argument("attempt at setting capacity to 0");
	}

	size_t newSize = GetNewSize(requiredSize);
	if (m_length < 1)
	{
		m_str = new char[newSize];
		m_capacity = newSize;
	}
	else if (m_capacity < newSize)
	{
		auto newStr = new char[newSize];
		if (m_str != nullptr && m_str != &s_emptyStr)
		{
			memcpy(newStr, m_str, sizeof(char) * m_capacity);
			Clear();
		}
		m_str = new char[newSize];
		m_str = std::move(newStr);
		m_capacity = newSize;
		delete[] newStr;
	}
}

size_t CMyString::GetNewSize(size_t requiredSize) const
{
	return(requiredSize > m_capacity) ? (std::max(requiredSize, m_capacity * 2)) : m_capacity;
}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
	if (m_str != nullptr && m_str != &s_emptyStr)
	{
		delete[] m_str;
	}
}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength() const
{
	return m_length;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		if (m_str != nullptr)
		{
			CMyString tmpCopy(other);
			std::swap(m_str, tmpCopy.m_str);
			std::swap(m_capacity, tmpCopy.m_capacity);
			std::swap(m_length, tmpCopy.m_length);
		}
	}

	return *this;
}

const char* CMyString::GetStringData() const
{
	return m_str;
}

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	CMyString str;
	str.SetCapacity(length + 1);
	str.m_length = length;

	if (start > m_length)
	{
		throw std::invalid_argument("Start cannot be more than length argument");
	}

	if (start + length > m_length)
	{
		throw std::invalid_argument("Start + length cannot be more than string length");
	}

	for (size_t i = 0; i < length; i++)
	{
		str.m_str[i] = m_str[i + start];
	}

	str.m_str[str.m_length] = '\0';

	return str;
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
	//сделать проверку на emptryStr
	if (m_str != &s_emptyStr && m_str != nullptr)
	{
		delete[] m_str;
	}
	m_str = &s_emptyStr;
	m_capacity = s_DEFAULT_CAPACITY;
	m_length = 0;
}

// Возвращает вместимость строки
size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (&other != this)
	{
		Clear();
		m_str = other.m_str;
		m_capacity = other.m_capacity;
		m_length = other.m_length;
		other.m_str = &s_emptyStr;
		other.m_capacity = 0;
		other.m_length = 0;
	}
	return *this;
}

// конструктор, инициализирующий строку данными из 
// строки стандартной библиотеки C++
char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::invalid_argument("Incorrect index of string");
	}
	return m_str[index];
}

char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::invalid_argument("Incorrect index of string");
	}

	return m_str[index];
}


CMyString operator+(const CMyString & left, const CMyString & right)
{
	size_t leftLength = left.m_length;
	size_t rightLength = right.m_length;
	size_t totalLength = leftLength + rightLength;
	CMyString str;
	str.SetCapacity(totalLength + 1);
	str.m_length = totalLength;
	size_t i = 0;
	//порефакторить метод
	if (left.m_str != nullptr && left.m_str != &left.s_emptyStr)
	{
		for (; i < leftLength; i++)
		{
			str[i] = left.m_str[i];
		}
	}

	if (right.m_str != nullptr && right.m_str != &str.s_emptyStr)
	{
		for (unsigned j = 0; j < rightLength; j++)
		{
			if (i >= totalLength) break;

			str[i] = right[j];
			i++;
		}
	}

	str.m_str[totalLength] = '\0';

	return str;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t totalLength= m_length + other.m_length;
	SetCapacity(totalLength + 1);

	int j = 0;
	for (size_t i = 0; i < other.m_length; i++)
	{
		m_str[i + m_length] = other.m_str[i];
	}

	m_str[totalLength] = '\0';
	m_length = totalLength;
	return *this;
}



CMyString operator+(const std::string& stlString, const CMyString& right)
{
	size_t stlStringLength = stlString.length();
	size_t rightLength = right.m_length;
	size_t totalLength = stlStringLength + rightLength;
	CMyString str;
	str.SetCapacity(totalLength + 1);
	str.m_length = totalLength;

	size_t i = 0;
	if (!stlString.empty())
	{
		for (; i < stlStringLength; i++)
		{
			str[i] = stlString[i];
		}
	}

	if (right.m_str != nullptr && right.m_str != &str.s_emptyStr)
	{
		for (unsigned j = 0; j < rightLength; j++)
		{
			if (i >= totalLength) break;
			
			str[i] = right[j];
			i++;
		}
	}

	str.m_str[totalLength] = '\0';
	return str;
}

CMyString operator+(const char* charStr, const CMyString& right)
{
	size_t sizeCharStr = strlen(charStr);
	size_t sizeRight = right.m_length;
	size_t totalLength = sizeCharStr + right.m_length;

	CMyString str;
	str.SetCapacity(totalLength + 1);
	str.m_length = totalLength;
	unsigned i = 0;
	//устранить дублирование
	if (charStr != nullptr && charStr != &str.s_emptyStr)
	{
		for (; i < sizeCharStr; i++)
		{
			str[i] = charStr[i];
		}
	}

	if (right.m_str != nullptr && right.m_str != &str.s_emptyStr)
	{
		for (unsigned j = 0; j < sizeRight; j++)
		{
			if (i >= totalLength) break;
			
			str[i] = right[j];
			i++;
		}
	}

	str.m_str[totalLength] = '\0';

	return str;
}

bool operator==(CMyString const& left, CMyString const& right)
{
	if (left.GetLength() != right.GetLength())
	{
		return false;
	}
	//заменить на length m_capacity
	for (size_t i = 0; i < left.m_length; i++)
	{
		if (left[i] != right[i])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(CMyString const& left, CMyString const& right)
{
	return !(left == right);
}


bool operator>(CMyString const& left, CMyString const& right)
{
	for (size_t i = 0; i < left.m_length; i++)
	{
		if (i >= right.m_length)
		{
			return true;
		}

		if (left[i] < right[i])
		{
			return false;
		}
	}

	if (left.m_length <= right.m_length)
	{
		return false;
	}

	return true;
}

bool operator<(CMyString const& left, CMyString const& right)
{

	for (size_t i = 0; i < left.m_length; i++)
	{
		if (i >= right.m_length)
		{
			return false;
		}

		if (left[i] > right[i])
		{
			return false;
		}
	}

	if (left.m_length >= right.m_length)
	{
		return false;
	}

	return true;
}


bool operator<=(CMyString const& left, CMyString const& right)
{
	for (size_t i = 0; i < left.m_length; i++)
	{
		if (i >= right.m_length)
		{
			return false;
		}

		if (left[i] > right[i])
		{
			return false;
		}
	}

	if (left.m_length > right.m_length)
	{
		return false;
	}

	return true;
}


bool operator>=(CMyString const& left, CMyString const& right)
{
	for (size_t i = 0; i < left.m_length; i++)
	{
		if (i >= right.m_length)
		{
			return true;
		}

		if (left[i] < right[i])
		{
			return false;
		}
	}

	if (left.m_length < right.m_length)
	{
		return false;
	}

	return true;
}

std::istream& operator>>(std::istream& in, CMyString& str)
{
	std::string tempStr;
	std::getline(in, tempStr);
	size_t length = tempStr.length();

	str.Clear();

	str.SetCapacity(length + 1);

	for (unsigned i = 0; i < length; i++)
	{
		str.m_str[i] = tempStr[i];
	}

	str.m_str[length] = '\0';
	str.m_length = length;

	return in;
}

std::ostream& operator<<(std::ostream& out, CMyString& str)
{
	out << str.m_str;

	return out;
}
