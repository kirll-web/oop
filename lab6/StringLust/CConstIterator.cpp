#include "CStringList.h"

using value_type = std::string;
using difference_type = std::ptrdiff_t;
using pointer = CStringList::Node*;
using reference = std::string&;

const CStringList::CConstIterator CStringList::cbegin() const
{
	return CStringList::CConstIterator(m_head.get(), this);
}

const CStringList::CConstIterator CStringList::cend() const
{
	return CStringList::CConstIterator(m_end.get(), this);
}

CStringList::CConstIterator::CConstIterator(CStringList::Node* node, const CStringList* list)
{
	m_node = node;
	m_list = list;
}

const reference CStringList::CConstIterator::operator*() const
{
	if (*this == nullptr || *this == m_list->m_end.get())
	{
		throw std::out_of_range("Iterator is out of range");
	}

	return m_node->data;
}

bool CStringList::CConstIterator::operator!=(CConstIterator const& other) const
{
	return m_node != other.m_node;
}

bool CStringList::CConstIterator::operator==(CConstIterator const& other) const
{
	return m_node == other.m_node;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator++()
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

const CStringList::CConstIterator CStringList::CConstIterator::operator++(int)
{
	CConstIterator copy = *this;
	++(*this);
	return copy;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator--()
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

const CStringList::CConstIterator& CStringList::CConstIterator::operator--(int)
{
	CConstIterator copy = *this;
	--(*this);
	return copy;
}

bool CStringList::CConstIterator::operator<=(const CConstIterator& other) const
{
	return m_node->data <= other.m_node->data;
}

bool CStringList::CConstIterator::operator>=(const CConstIterator& other) const
{
	return m_node->data >= other.m_node->data;
}




bool CStringList::CConstIterator::operator<(const CConstIterator& other) const
{
	return m_node->data < other.m_node->data;
}

bool CStringList::CConstIterator::operator>(const CConstIterator& other) const
{
	return m_node->data > other.m_node->data;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator+(size_t index)
{
	try
	{
		while (index > 0)
		{
			++(*this);
			++index;
		}
	}
	catch (std::out_of_range& e)
	{
		throw std::out_of_range(e.what());
	}

	return *this;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator-(size_t index)
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

const pointer CStringList::CConstIterator::operator->() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return m_node;
}
