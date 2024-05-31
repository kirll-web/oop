#include "CStringList.h"



CStringList::CStringList() : m_size(0), m_head(nullptr), m_tail(nullptr) {}

CStringList::CStringList(const CStringList& other)
{
	*this = other;
}


CStringList::~CStringList()
{
	Clear();
}


CStringList::CStringList(CStringList&& other) 
{
	*this = other;
}


CStringList::CIterator::CIterator(CStringList::Node* node, bool isReverse)
{
	m_node = node;
	m_reverse = isReverse;
}

std::string& CStringList::CIterator::operator*() const
{
	try
	{
		if(m_node == nullptr) throw std::out_of_range("Iterator is null");

		return m_node->data;
	}
	catch(const std::exception &e)
	{
		throw std::out_of_range(e.what());
	}
	
}

bool CStringList::CIterator::operator!=(CIterator const& other) const
{
	return m_node != other.m_node;
}

bool CStringList::CIterator::operator==(CIterator const& other) const
{
	return m_node == other.m_node;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	m_node = m_reverse ? m_node->prev : m_node->next.get();
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator++(int)
{
	CIterator copy = *this;
	++(*this);
	return copy;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	m_node = m_reverse ? m_node->next.get() : m_node->prev;
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--(int)
{
	CIterator copy = *this;
	--(*this);
	return *this;
}


CStringList::CIterator CStringList::CIterator::operator+(size_t index)
{
	for (size_t i = index; i > 0; i--)
	{
		m_node = m_reverse ? m_node->prev : m_node->next.get();

		if (m_node == nullptr)
		{
			throw std::out_of_range("Iterator incrementing is impossible");
		}
		--index;
	}


	return CStringList::CIterator(m_node);
}

CStringList::CIterator CStringList::CIterator::operator-(size_t index)
{
	for (size_t i = index; i > 0; i--)
	{
		if (m_node )
		{

		}
		m_node = m_reverse ? m_node->next.get() : m_node->prev;

		if (m_node == nullptr)
		{
			throw std::out_of_range("Iterator decrementing is impossible");
		}
		--index;
	}


	return CStringList::CIterator(m_node);
}

CStringList::CConstIterator::CConstIterator(CStringList::Node* node, bool isReverse) : m_node(node), m_reverse(isReverse) {}

const std::string& CStringList::CConstIterator::operator*() const
{
	return m_node->data;
}

bool CStringList::CConstIterator::operator!=(CConstIterator const& other) const
{
	return m_node != other.m_node;
}

std::string* CStringList::CIterator::operator->() const
{
	return &m_node->data;
}


bool CStringList::CConstIterator::operator==(CConstIterator const& other) const
{
	return m_node == other.m_node;
}

const std::string* CStringList::CConstIterator::operator->() const
{
	return &m_node->data;
}

void CStringList::Push_front(const std::string& data)
{
	if (!IsEmpty())
	{
		std::unique_ptr<Node> newElement = std::make_unique<Node>(data, nullptr, std::move(m_head));
		m_head = std::move(newElement);
		m_head->next->prev = m_head.get();
	}
	else
	{
		std::unique_ptr<Node> newElement = std::make_unique<Node>(data, nullptr, std::move(m_head));
		m_head = std::move(newElement);
		m_tail = m_head.get();
	}

	++m_size;
}

void CStringList::Push_back(const std::string& data)
{
	std::unique_ptr<Node> newElement = std::make_unique<Node>(data, m_tail, nullptr);
	if (IsNotEmpty())
	{
		m_tail->next = std::move(newElement);
		m_tail = m_tail->next.get();
	}
	else
	{
		m_head = std::move(newElement);
		m_tail = m_head.get();
	}
	
	++m_size;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

bool CStringList::IsNotEmpty() const
{
	return m_size > 0;
}

CStringList::CIterator CStringList::Insert(const CStringList::CIterator& it, const std::string& value)
{
	if (IsEmpty() || it == begin())
	{
		Push_front(value);
		return begin();
	}

	std::unique_ptr<Node> newNode = std::make_unique<Node>(value, it.m_node->prev, std::move(it.m_node->prev->next));
	it.m_node->prev->next = std::move(newNode);
	++m_size;

	return CStringList::CIterator(it.m_node);
}

CStringList::CIterator CStringList::Erase(const CStringList::CIterator& it)
{
	if (it == nullptr)
	{
		throw std::out_of_range("Iterator is nullptr");
	}
	if (m_size == 1)
	{
		Clear();
		return begin();
	}
	if (it == m_head.get())
	{
		m_head->next->prev = nullptr;
		m_head = std::move(m_head->next);
	}
	else if (it == m_tail)
	{
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
	}
	else
	{
		Node* prevNode = it.m_node->prev;
		prevNode->next = std::move(it.m_node->next);
		prevNode->next->prev = prevNode;
	}
	--m_size;

	return it;
}

void CStringList::Clear() noexcept
{
	if (m_head == nullptr)
	{
		return;
	}

	while (m_head)
	{
		m_head = std::move(m_head->next);
	}
	m_tail = nullptr;
	m_size = 0;
}


CStringList& CStringList::operator=(CStringList const& other)
{
	if (this == &other)
	{
		return *this;
	}

	Clear();

	for (const auto& str : other)
	{
		Push_back(str);
	}

	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) 
{
	if (!other.m_size)
	{
		Clear();
		return *this;
	}

	if (this == &other)
	{
		return *this;
	}

	Clear();

	m_head = std::move(other.m_head);
	m_tail = other.m_tail;
	m_size = other.m_size;
	other.Clear();

	return *this;
}
const CStringList::CConstIterator CStringList::Cend() const
{
	return CStringList::CConstIterator(m_tail->next.get());
}

CStringList::CIterator CStringList::begin() const
{
	return CStringList::CIterator(m_head.get(), false);
}

CStringList::CIterator CStringList::end() const
{
	return CStringList::CIterator(m_tail->next.get());
}

const CStringList::CConstIterator CStringList::Cbegin() const
{
	return CStringList::CConstIterator(m_head.get());
}

CStringList::CIterator CStringList::Rbegin() const
{
	return CStringList::CIterator(m_tail, true);
}

CStringList::CIterator CStringList::Rend() const
{
	return CStringList::CIterator(m_head->prev, true);
}

const CStringList::CConstIterator CStringList::Rcbegin() const
{
	return CStringList::CConstIterator(m_tail, true);

}

const CStringList::CConstIterator CStringList::Rcend() const
{
	return CStringList::CConstIterator(m_head->prev, true);
}

//переделать итераторы и тесты с алгоритмами
//copy. sort, что нить на max. min, transform