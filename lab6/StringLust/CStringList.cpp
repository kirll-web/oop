#include "CStringList.h"

CStringList::CStringList(const CStringList& other)
{
	try
	{
		if (other.IsEmpty())
		{
			Clear();
		}

		else if (this != &other)
		{
			Clear();

			for (const auto& str : other)
			{
				push_back(str);//переполнение стека из-за рекурсивного удаления элементов
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		Clear();//чтобы не было переполнения стека
		throw std::exception(e);
	}
}

CStringList::CStringList(CStringList&& other)
{
	try
	{
		if (other.m_size == 0)
		{
			Clear();
		}
		else if (this != &other)
		{
			Clear();
			m_head = std::move(other.m_head);
			m_size = other.m_size;
			other.Clear();
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		throw std::exception(e);
	}
}

CStringList::~CStringList()
{
	Clear();
	m_end.reset();
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

bool CStringList::IsNotEmpty() const
{
	return m_size > 0;
}

CStringList::CStringList() : m_size(0), m_head(nullptr)
{
}


CStringList::CIterator CStringList::push_back(const std::string& data) noexcept
{
	std::shared_ptr<Node> newElement = std::make_shared<Node>(data, nullptr, nullptr);
	if (IsEmpty())
	{
		m_head = std::move(newElement);
		m_head->prev = m_end.get();
		m_head->next = m_end;
		m_end->prev = m_head.get();
		m_end->next = m_head;
	}
	else
	{
		newElement->next = m_end;
		newElement->prev = m_end->prev;
		m_end->prev->next = std::move(newElement);
		m_end->prev = m_end->prev->next.get();
		m_end->prev->next = m_end;
	}

	++m_size;

	return CIterator(m_end->prev, this);
}

CStringList::CIterator CStringList::push_front(const std::string& data) noexcept
{
	std::shared_ptr<Node> newElement = std::make_shared<Node>(data, nullptr, nullptr);
	if (IsEmpty())
	{
		return push_back(data);
	}
	else
	{
		m_end->next = newElement;
		newElement->prev = m_end.get();
		m_head->prev = newElement.get();
		newElement->next = std::move(m_head);
		m_head = std::move(newElement);
	}

	++m_size;

	return CIterator(m_head.get(), this);
}

void CStringList::Clear() noexcept
{
	if (m_size == 0)
	{
		return;
	}

	while (m_head)
	{
		m_head = std::move(m_head->next);
	}
	m_size = 0;
}

CStringList& CStringList::operator=(CStringList const& other) noexcept
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
		push_back(str);
	}

	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
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
	m_size = other.m_size;
	m_end = other.m_end;
	other.Clear();
	//занулять самостоятельно

	return *this;
}

size_t CStringList::GetSize() const
{
	return m_size;
}


CStringList::CIterator CStringList::Insert(const CStringList::CIterator& it, const std::string& value)
{
	if (it == begin())
	{
		push_front(value);
		return begin();
	}
	else if (it == end())
	{
		push_back(value);
		return end();
	}
	else if (it.m_node == nullptr || it == nullptr)
	{
		throw std::out_of_range("Iterator is out of range");
	
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
	if (it == nullptr || it.m_node == m_end.get())
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
	else
	{
		Node* prevNode = it.m_node->prev;
		prevNode->next = std::move(it.m_node->next);
		prevNode->next->prev = prevNode;
	}
	--m_size;

	return it;
}