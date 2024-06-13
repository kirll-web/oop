#pragma once
#include <string>
#include <memory>
#include <iterator>
#include <stdexcept>
#include <iostream>

template <typename T>
class CMyList
{

private:
	struct Node {
		Node(const T& data, Node* prev, std::shared_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		T data;
		Node* prev;
		std::shared_ptr<Node> next;
	};

	size_t m_size;
	std::shared_ptr<Node> m_head = nullptr;
	std::shared_ptr<Node >m_end = std::make_shared<Node>(T(), nullptr, nullptr);


public:
	using value_type = T;


	// только узлы с данными должны конструировать и разрушать объкты с данными, а сторожевые не должны 
	CMyList() : m_size(0), m_head(nullptr)
	{
	}

	CMyList(const CMyList<T>& other) // конструктор копировани€ не может быть noexcept, т.к. push_back выдел€ет динамичску пам€ть
	{
		try
		{
			if (other.IsNotEmpty())
			{
				for (const auto& data : other)
				{
					push_back(data);
				}
			}
		}
		catch (const std::exception& e)
		{
			Clear();
			throw std::exception(e.what());
		}
	}

	CMyList(CMyList<T>&& other)
	{
		m_head = std::move(other.m_head);
		m_size = other.m_size;
		m_end = std::move(other.m_end);
		other.m_end = std::make_shared(T(), nullptr, nullptr);
		other.Clear();
	}

	~CMyList()
	{
		Clear();
		m_end.reset();
	}

	class CIterator
	{
		friend CMyList;

	protected:
		Node* m_node = nullptr;
		CMyList* m_list = nullptr;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = T&;
		CIterator() = default;

		CIterator(CMyList::Node* node, CMyList<T>* list)
		{
			m_node = node;
			m_list = list;
		}

		reference operator*() const
		{
			if (m_node == nullptr || *this == m_list->end())
			{
				throw std::out_of_range("Iterator is out of range");
			}

			return m_node->data;
		}


		CMyList::CIterator& operator++()
		{
			if (m_node != m_list->m_end.get() && m_node != nullptr)
			{
				m_node = m_node->next.get();
			}
			else
			{
				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		CMyList::CIterator operator++(int)
		{
			CIterator copy = *this;
			++(*this);
			return copy;
		}

		CMyList::CIterator& operator--()
		{
			if (m_node != nullptr && m_node != m_list->m_head.get())
			{
				m_node = m_node->prev;
			}
			else
			{
				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		CMyList::CIterator& operator--(int)
		{
			CIterator copy = *this;
			--(*this);
			return copy;
		}

		bool operator!=(CIterator const& other) const
		{
			return m_node != other.m_node;
		}

		bool operator==(CIterator const& other) const
		{
			return m_node == other.m_node;
		}

		pointer operator->() const
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Error read");
			}
			return m_node;
		}



	};

	class CConstIterator
	{
		friend CMyList;
		friend CIterator;

	private:
		CIterator iter;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const Node*;
		using reference = const T&;

		CConstIterator() = default;

		CConstIterator(CMyList::CIterator it)
		{
			iter = it;
		}

		const reference operator*() const
		{
			return *iter;
		}

		bool operator!=(CConstIterator const& other) const
		{
			return iter != other.iter;
		}

		bool operator==(CConstIterator const& other) const
		{
			return iter == other.iter;
		}

		const CMyList::CConstIterator& operator++()
		{
			++iter;
			return iter;
		}

		const CMyList::CConstIterator operator++(int)
		{
			CConstIterator copy = *this;
			++(*this);
			return copy;
		}

		const CMyList::CConstIterator& operator--()
		{
			--iter;
			return *this;
		}

		const CMyList::CConstIterator& operator--(int)
		{
			CConstIterator copy = iter;
			--(*this);
			return copy;
		}

		const pointer operator->() const
		{
			if (iter->m_node == nullptr)
			{
				throw std::out_of_range("Error read");
			}
			return iter->m_node;
		}

	};
	//std::reverse_iterator()
	//лучше воспользоватьс€ стандартным reverse оператор
	class CReverseIterator
	{
		friend CMyList;
	public:

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = T&;
		CReverseIterator() = default;
		pointer operator->() const
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Error read");
			}
			return m_node;
		}
		CReverseIterator(CMyList::Node* node, CMyList* list)
		{
			m_node = node;
			m_list = list;
		}

		reference operator*() const
		{
			if (m_node == nullptr || *this == m_list->rend())
			{
				throw std::out_of_range("Iterator is out of range");
			}

			return m_node->data;
		}

		bool operator!=(CReverseIterator const& other) const
		{
			return m_node != other.m_node;
		}

		bool operator==(CReverseIterator const& other) const
		{
			return m_node == other.m_node;
		}

		CMyList::CReverseIterator& operator++()
		{
			if (m_node != nullptr && m_node != m_list->rend().m_node)
			{
				m_node = m_node->prev;
			}
			else
			{

				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		CMyList::CReverseIterator operator++(int)
		{
			CReverseIterator copy = *this;
			++(*this);
			return copy;
		}

		CMyList::CReverseIterator& operator--()
		{
			if (m_node != nullptr && m_node != m_list->m_head.get())
			{
				m_node = m_node->next.get();
			}
			else
			{

				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		CMyList::CReverseIterator& operator--(int)
		{
			CReverseIterator copy = *this;
			--(*this);
			return copy;
		}

	private:
		CMyList::Node* m_node = nullptr;
		CMyList* m_list = nullptr;
	};

	//придумать как уменшить дублирование кода
	//придумать как создать const итератор из не const, но не наоборот


	class CConstReverseIterator
	{
		friend CMyList;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = T&;

		CConstReverseIterator() = default;

		CConstReverseIterator(CMyList<T>::Node* node, const CMyList<T>* list)
		{
			m_node = node;
			m_list = list;
		}

		const reference operator*() const
		{
			if (m_node == nullptr || *this == m_list->m_end.get())
			{
				throw std::out_of_range("Iterator is out of range");
			}

			return m_node->data;
		}

		bool operator!=(CConstReverseIterator const& other) const
		{
			return m_node != other.m_node;
		}

		bool operator==(CConstReverseIterator const& other) const
		{
			return m_node == other.m_node;
		}


		const CMyList<T>::CConstReverseIterator& operator++()
		{
			if (m_node != nullptr && m_node != m_list->m_end.get())
			{
				m_node = m_node->prev;
			}
			else
			{

				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		const CMyList<T>::CConstReverseIterator operator++(int)
		{
			CConstReverseIterator copy = *this;
			++(*this);
			return copy;
		}

		const CMyList<T>::CConstReverseIterator& operator--()
		{
			if (m_node != nullptr && m_node != m_list->m_head.get())
			{
				m_node = m_node->next.get();
			}
			else
			{

				throw std::out_of_range("Iterator is out of range");
			}
			return *this;
		}

		const CMyList<T>::CConstReverseIterator& operator--(int)
		{
			CConstReverseIterator copy = *this;
			--(*this);
			return copy;
		}


		const pointer operator->() const
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Error read");
			}
			return m_node;
		}

	private:
		CMyList::Node* m_node = nullptr;
		const CMyList* m_list;
	};

	bool IsEmpty() const
	{
		return m_size == 0;
	}

	bool IsNotEmpty() const
	{
		return m_size > 0;
	}

	CMyList<T>::CIterator push_back(const T& data)
	{
		try
		{
			std::shared_ptr<Node> newElement = std::make_shared<Node>(data, nullptr, nullptr);
			if (IsEmpty())// если сторожевой узел будет указывать на head, то многие операции стануть проще
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
		catch (const std::exception& e)
		{
			Clear();
			throw std::exception(e.what());
		}
	}

	CMyList<T>::CIterator push_front(const T& data)
	{
		try
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
		catch (const std::exception& e)
		{
			Clear();
			throw std::exception(e.what());
		}
	}

	void Clear() noexcept
	{
		if (m_size == 0)
		{
			return;
		}

		while (m_head)
		{
			m_head = std::move(m_head->next);
		}
		m_end->prev = nullptr;
		m_size = 0;
	}


	CMyList<T>& operator=(CMyList<T> const& other)
	{
		if (other.isEmpty())
		{
			Clear();
			return *this;
		}

		if (this == &other)
		{
			return *this;
		}

		CMyList<T> copy(other);

		for (const auto& str : copy)
		{
			std::swap(this, copy);
		}
	}

	CMyList<T>& operator=(CMyList<T>&& other) noexcept
	{
		if (other.isEmpty())
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
		m_end = std::move(other.m_end); // не оставл€ем в валидном состо€нии
		other.m_end = std::make_shared(T(), nullptr, nullptr);
		other.Clear();

		return *this;
	}

	size_t GetSize() const noexcept
	{
		return m_size;
	}

	CMyList<T>::CIterator Insert(const CMyList<T>::CIterator& it, const T& value)
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
		else if (it.m_node == nullptr)
		{
			throw std::out_of_range("Iterator is out of range");
		}

		std::shared_ptr<Node> newNode = std::make_shared<Node>(value, nullptr, nullptr);
		newNode->prev = it.m_node->prev;
		newNode->next = std::move(it.m_node->prev->next);
		it.m_node->prev->next = std::move(newNode);
		++m_size;

		return it;
	}

	CMyList<T>::CIterator Erase(const CMyList<T>::CIterator& it)
	{
		if (it.m_node == m_end.get())
		{
			throw std::out_of_range("Iterator is nullptr");
		}
		if (it.m_node == m_head.get())
		{
			m_head = std::move(m_head->next);

			if (m_head == nullptr)
			{
				Clear();// вызвали clear и ещЄ уменшьили размер.
				return it;
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
	// не нужен const 
	bool operator==(const CMyList<T> const& other) const
	{
		if (m_size != other.m_size) return false;

		int index = 0;// индекс не мен€ю

		auto itThis = *this->cbegin();
		auto itOther = *this->cbegin();
		while (index < m_size || itThis != this.cend() || itOther != itThis.cend())
		{
			if (*itThis != *itOther)
			{
				return false;
			}

			++index;
		}

		return true;
	}

	CMyList<T>::CIterator begin()
	{
		return CMyList::CIterator(m_head.get(), this);
	}

	CMyList<T>::CIterator end()
	{
		return CMyList<T>::CIterator(m_end.get(), this);
	}

	const CMyList<T>::CIterator begin() const
	{
		return CMyList::CIterator(m_head.get(), this);
	}

	const CMyList<T>::CIterator end() const
	{
		return CMyList<T>::CIterator(m_end.get(), this);
	}


	const CMyList::CConstIterator cbegin()
	{
		return CMyList::CConstIterator(begin());
	}

	const  CMyList::CConstIterator cend()
	{
		return  CMyList::CConstIterator(end());
	}

	CMyList::CReverseIterator rbegin()
	{
		return CMyList::CReverseIterator(m_end->prev, this);
	}

	CMyList::CReverseIterator rend()
	{
		return CMyList::CReverseIterator(m_end.get(), this);
	}

	CMyList::CReverseIterator rbegin() const
	{
		return CMyList::CReverseIterator(m_end->prev, this);
	}

	CMyList::CReverseIterator rend() const
	{
		return CMyList::CReverseIterator(m_end.get(), this);
	}

	const CMyList<T>::CConstReverseIterator rcbegin()
	{
		return CMyList<T>::CConstReverseIterator(m_end->prev, this);
	}

	const CMyList<T>::CConstReverseIterator rcend()
	{
		return CMyList<T>::CConstReverseIterator(m_end.get(), this);
	}
};