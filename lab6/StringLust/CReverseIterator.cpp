#include "CStringList.h"

using value_type = std::string;
using difference_type = std::ptrdiff_t;
using pointer = CStringList::Node*;
using reference = std::string&;

CStringList::CReverseIterator CStringList::rbegin() const
{
	return CStringList::CReverseIterator(m_end->prev, this);
}

CStringList::CReverseIterator CStringList::rend() const
{
	return CStringList::CReverseIterator(m_end.get(), this);
}


pointer CStringList::CReverseIterator::operator->() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return m_node;
}


CStringList::CReverseIterator::CReverseIterator(CStringList::Node* node, const CStringList* list)
{
	m_node = node;
	m_list = list;
}

reference CStringList::CReverseIterator::operator*() const
{
	if (*this == nullptr || *this == m_list->m_end.get())
	{
		throw std::out_of_range("Iterator is out of range");
	}

	return m_node->data;
}

bool CStringList::CReverseIterator::operator!=(CReverseIterator const& other) const
{
	return m_node != other.m_node;
}

bool CStringList::CReverseIterator::operator==(CReverseIterator const& other) const
{
	return m_node == other.m_node;
}

CStringList::CReverseIterator& CStringList::CReverseIterator::operator++()
{
	if (m_node != m_list->m_end.get())
	{
		m_node = m_node->prev;
	}
	else
	{
		throw std::out_of_range("Iterator is out of range");
	}
	return *this;
}

CStringList::CReverseIterator CStringList::CReverseIterator::operator++(int)
{
	CReverseIterator copy = *this;
	++(*this);
	return copy;
}

CStringList::CReverseIterator& CStringList::CReverseIterator::operator--()
{
	if (m_node != m_list->m_head.get())
	{
		m_node = m_node->next.get();
	}
	else
	{
		throw std::out_of_range("Iterator is out of range");
	}
	return *this;
}

CStringList::CReverseIterator& CStringList::CReverseIterator::operator--(int)
{
	CReverseIterator copy = *this;
	--(*this);
	return copy;
}

bool CStringList::CReverseIterator::operator<=(const CReverseIterator& other) const
{
	return m_node->data <= other.m_node->data;
}

bool CStringList::CReverseIterator::operator>=(const CReverseIterator& other) const
{
	return m_node->data >= other.m_node->data;
}


bool CStringList::CReverseIterator::operator<(const CReverseIterator& other) const
{
	return m_node->data < other.m_node->data;
}

bool CStringList::CReverseIterator::operator>(const CReverseIterator& other) const
{
	return m_node->data > other.m_node->data;
}


CStringList::CReverseIterator CStringList::CReverseIterator::operator+(size_t index)
{
	try
	{
		while (index > 0)
		{
			++(*this);
			index;
		}
	}
	catch (std::out_of_range& e)
	{
		throw std::out_of_range(e.what());
	}

	return *this;
}

CStringList::CReverseIterator CStringList::CReverseIterator::operator-(size_t index)
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

