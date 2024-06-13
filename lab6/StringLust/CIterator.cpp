#include "CStringList.h"

using value_type = std::string;
using difference_type = std::ptrdiff_t;
using pointer = CStringList::Node*;
using reference = std::string&;

CStringList::CIterator CStringList::begin() const
{
	return CStringList::CIterator(m_head.get(), this);
}

CStringList::CIterator CStringList::end() const
{
	return CStringList::CIterator(m_end.get(), this);
}

CStringList::CIterator::CIterator(CStringList::Node* node, const CStringList* list)
{
	m_node = node;
	m_list = list;
}

reference CStringList::CIterator::operator*() const
{
	if (*this == m_list->m_end.get())
	{
		throw std::out_of_range("Iterator is out of range");
	}

	return m_node->data;
}

bool CStringList::CIterator::operator!=(CIterator const& other) const
{
	return m_node != other.m_node;
}


CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (m_node != m_list->m_end.get())
	{
		m_node = m_node->next.get();
	}
	else
	{
		throw std::out_of_range("Iterator is out of range");
	}
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	CIterator copy = *this;
	++(*this);
	return copy;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (m_node != m_list->m_head.get())
	{
		m_node = m_node->prev;
	}
	else
	{
		throw std::out_of_range("Iterator is out of range");
	}
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--(int)
{
	CIterator copy = *this;
	--(*this);
	return copy;
}


bool CStringList::CIterator::operator<=(const CIterator& other) const
{
	return m_node->data <= other.m_node->data;
}

bool CStringList::CIterator::operator>=(const CIterator& other) const
{
	return m_node->data >= other.m_node->data;
}


bool CStringList::CIterator::operator==(CIterator const& other) const
{
	return m_node == other.m_node;
}


bool CStringList::CIterator::operator<(const CIterator& other) const
{
	return m_node->data < other.m_node->data;
}

bool CStringList::CIterator::operator>(const CIterator& other) const
{
	return m_node->data > other.m_node->data;
}

CStringList::CIterator CStringList::CIterator::operator+(size_t index)
{
	try
	{
		while (index > 0)
		{
			++(*this);
			--index;
		}
	}//лучше const + очищение. Лучше убрать, так как будет просто перевыброс. Надо обрабатывать там, где выбросится
	catch (std::out_of_range& e)
	{
		throw std::out_of_range(e.what());
	}

	return *this;
}

CStringList::CIterator CStringList::CIterator::operator-(size_t index)
{
	try
	{
		while (index > 0)
		{
			--(*this);
			--index;
		}
	}
	catch (std::out_of_range& e)
	{
		throw std::out_of_range(e.what());
	}

	return *this;
}

pointer CStringList::CIterator::operator->() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return m_node;
}