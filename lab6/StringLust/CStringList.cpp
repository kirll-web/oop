#include "CStringList.h"

CStringList::CStringList(): m_size(0), m_head(nullptr), m_tail(nullptr)
{
}

CStringList::CStringList(const CStringList& other)
{
}

CStringList::CStringList(CStringList&& other)
{
}

CStringList::~CStringList()
{
	Clear();
}

CStringList::CIterator::CIterator(CStringList::Node* node, bool isReverse, const CStringList *list)
{
	m_node = node;
	m_reverse = isReverse;
	m_list = list;
}

std::string& CStringList::CIterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return m_node->data;
}


bool CStringList::CIterator::operator==(CIterator const& other) const
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(CIterator const& other) const
{
	return !(*this == other);
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	if (m_reverse)
	{
		m_node = m_node == m_list->end().m_node ? m_list->m_tail : m_node->prev;
	}
	else
	{
		if (m_node == m_list->end().m_node)
		{
			throw std::out_of_range("Iterator is not in range");
		}
		m_node = m_node->next.get();
	}

	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	CIterator copy = *this;
	++(*this);
	return copy;
}


CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	if (m_reverse)
	{
		m_node = m_node == m_list->end().m_node ? m_list->m_head.get() : m_node->next.get();
	}
	else
	{
		if (m_node == m_list->m_tail)
		{
			throw std::out_of_range("Iterator is not in range");
		}
		m_node = m_node->prev;
	}

	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--(int)
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	CIterator copy = *this;
	--(*this);
	return copy;
}


CStringList::CIterator CStringList::CIterator::operator+(size_t index)
{

	for (size_t i = index; i > 0; i--)
	{

		++(*this);

		if (m_node == nullptr|| m_list->IsEmpty())
		{
			throw std::out_of_range("Iterator incrementing is impossible");
		}
		--index;
	}


	return *this;
}


CStringList::CIterator CStringList::CIterator::operator-(size_t index)
{
	for (size_t i = index; i > 0; i--)
	{
		--(*this);

		if (m_node == nullptr || m_list->IsEmpty())
		{
			throw std::out_of_range("Iterator incrementing is impossible");
		}
		--index;
	}


	return *this;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator+(size_t index)
{
	for (size_t i = index; i > 0; i--)
	{
		m_node = m_reverse ? m_node->prev : m_node->next.get();

		if (m_node == nullptr || m_list->IsEmpty())
		{
			throw std::out_of_range("Iterator incrementing is impossible");
		}
		--index;
	}


	return *this;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator-(size_t index)
{
	for (size_t i = index; i > 0; i--)
	{
		m_node = m_reverse ? m_node->prev : m_node->next.get();

		if (m_node == nullptr || m_list->IsEmpty())
		{
			throw std::out_of_range("Iterator incrementing is impossible");
		}
		--index;
	}


	return *this;
}

std::string* CStringList::CIterator::operator->() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return &m_node->data;
}

CStringList::CConstIterator::CConstIterator(CStringList::Node* node, bool isReverse, const CStringList* list)
{
	m_node = node;
	m_reverse = isReverse;
	m_list = list;
}


const std::string* CStringList::CConstIterator::operator->() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return &m_node->data;
}


const std::string& CStringList::CConstIterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Error read");
	}
	return m_node->data;
}

bool CStringList::CConstIterator::operator==(CConstIterator const& other) const
{
	return m_node == other.m_node;
}

bool CStringList::CConstIterator::operator!=(CConstIterator const& other) const
{
	return !(*this == other);
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator++()
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	m_node = m_reverse ? m_node->prev : m_node->next.get();

	return *this;
}

const CStringList::CConstIterator CStringList::CConstIterator::operator++(int)
{
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	CStringList::CConstIterator copy = *this;
	++(*this);
	return copy;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator--()
{
	if (*this == nullptr)
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	m_node = m_reverse ? m_node->next.get() : m_node->prev;

	return *this;
}

const CStringList::CConstIterator& CStringList::CConstIterator::operator--(int)
{
	
	if (*this == nullptr || m_list->IsEmpty())
	{
		throw std::out_of_range("Iterator cannot be incremented");
	}

	CStringList::CConstIterator copy = *this;
	--(*this);
	return copy;
}


void CStringList::Push_front(const std::string& data)
{
	std::unique_ptr<Node> newElement = std::make_unique<Node>(data, nullptr, nullptr);

	if (IsEmpty())
	{
		m_head = std::move(newElement);
		m_tail = m_head.get();
	}
	else
	{
		m_head->prev = newElement.get();
		newElement->next = std::move(m_head);
		m_head = std::move(newElement);
	}

	++m_size;
}

void CStringList::Push_back( const std::string& data )
{
	std::unique_ptr<Node> newElement = std::make_unique<Node>(data, nullptr, nullptr);


	if (IsEmpty())
	{
		m_head = std::move(newElement);
		m_tail = m_head.get();
	}
	else
	{
		newElement->prev = m_tail;
		m_tail->next = std::move(newElement);
		m_tail = m_tail->next.get();
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
	if (other.m_size == 0)
	{
		Clear();
		return *this;
	}

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
	if (other.m_size == 0)
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

std::string& CStringList::operator[](size_t index)
{
	CIterator b = begin();

	for (int i = 0; i < index; i++)
	{
		++b;
	};

	return b.m_node->data;
}

CStringList::CIterator CStringList::begin() const
{
	return CStringList::CIterator(m_head.get(), false, this);
}

CStringList::CIterator CStringList::end() const
{
	return CStringList::CIterator(m_tail->next.get(), false, this);
}

const CStringList::CConstIterator CStringList::Cbegin() const
{
	return CStringList::CConstIterator(m_head.get(), false, this);
}

const CStringList::CConstIterator CStringList::Cend() const
{
	return CStringList::CConstIterator(m_tail->next.get(), false, this);
}

CStringList::CIterator CStringList::Rbegin() const
{
	return CStringList::CIterator(m_tail, true, this);
}

CStringList::CIterator CStringList::Rend() const
{
	return CStringList::CIterator(m_tail->next.get(), true, this);
}

const CStringList::CConstIterator CStringList::Rcbegin() const
{
	return CStringList::CConstIterator(m_tail, true, this);
}

const CStringList::CConstIterator CStringList::Rcend() const
{
	return CStringList::CConstIterator(m_tail->next.get(), true, this);
}

CStringList::CIterator CStringList::Insert(const CStringList::CIterator& it, const std::string& value)
{
	if (it == begin())
	{
		Push_front(value);
		return begin();
	}
	else if (it == end())
	{
		Push_back(value);
		return end();
	}


	std::unique_ptr<Node> newNode = std::make_unique<Node>(value, nullptr, nullptr);
	newNode->prev = it.m_node->prev;
	newNode->next = std::move(it.m_node->prev->next);
	it.m_node->prev->next = std::move(newNode);
	++m_size;

	return it;
}

CStringList::CIterator CStringList::Erase(const CStringList::CIterator& it)
{
	if (it == nullptr)
	{
		throw std::out_of_range("Iterator is nullptr");
	}
	if (it == m_head.get())
	{
		m_head = std::move(m_head->next);

		if (m_head == nullptr)
		{
			Clear();
		}
	}
	else if (it == m_tail)
	{
		m_tail->prev->next.release();
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

ptrdiff_t CStringList::CIterator::operator-(const CIterator& other) const
{
	ptrdiff_t distance = 0;
	CIterator temp = other;
	while (temp != *this)
	{
		++temp;
		++distance;
		if (temp.m_node == nullptr)
		{
			throw std::out_of_range("Iterators not in the same list");
		}
	}
	return distance;
}

//CStringList::CIterator CStringList::CIterator::operator+(ptrdiff_t n) const
//{
//    CIterator temp = *this;
//    while (n > 0 && temp.m_node)
//    {
//        temp.m_node = temp.m_reverse ? temp.m_node->prev : temp.m_node->next.get();
//        --n;
//    }
//    while (n < 0 && temp.m_node)
//    {
//        temp.m_node = temp.m_reverse ? temp.m_node->next.get() : temp.m_node->prev;
//        ++n;
//    }
//    return temp;
//}

CStringList::CIterator& CStringList::CIterator::operator+(ptrdiff_t n)
{
	CStringList::CIterator temp = it;
	while (n > 0 && temp.m_node)
	{
		temp.m_node = temp.m_reverse ? temp.m_node->prev : temp.m_node->next.get();
		--n;
	}
	while (n < 0 && temp.m_node)
	{
		temp.m_node = temp.m_reverse ? temp.m_node->next.get() : temp.m_node->prev;
		++n;
	}
	return temp;
}

CStringList::CIterator CStringList::CIterator::operator-(ptrdiff_t n) const
{
	return *this + (-n);
}

bool CStringList::CIterator::operator<=(const CIterator& other) const
{
	return !(m_node->data > other.m_node->data);
}

bool CStringList::CIterator::operator>=(const CIterator& other) const
{
	return !(m_node->data < other.m_node->data);
}

bool CStringList::CIterator::operator<(const CIterator& other) const
{
	return (*this - other) < 0;
}

bool CStringList::CIterator::operator>(const CIterator& other) const
{
	return (*this - other) > 0;
}