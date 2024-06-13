#pragma once
#include <string>
#include <memory>
#include <iterator>
#include <stdexcept>
#include <iostream>

class CStringList
{
public:
	using value_type = std::string;
	struct Node {
		Node(const std::string& data, Node* prev, std::shared_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::shared_ptr<Node> next;
	};

	//Конструкторы: по умолчанию, 
	CStringList();
	//копирования 
	CStringList(const CStringList& other);
	//перемещения
	CStringList(CStringList&& other);
	//Деструктор
	~CStringList();

	class CIterator 
	{
		friend CStringList;
	public:
		//должен быть biddirectional 
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = std::string&;

		CIterator(CStringList::Node* node, const CStringList* list = nullptr);
		CIterator() = default;
		reference operator * () const;
		bool operator!=(CIterator const& other) const;
		bool operator==(CIterator const& other) const;
		CIterator& operator++();
		CIterator operator++(int);
		CIterator& operator--();
		CIterator& operator--(int);
		bool operator<=(const CIterator& other) const;
		bool operator>=(const CIterator& other) const;
		bool operator<(const CIterator& other) const;
		bool operator>(const CIterator& other) const;
		CIterator operator+(size_t index);
		CIterator operator-(size_t index);
		pointer operator->()const;

		friend std::ostream& operator<<(std::ostream& out, CIterator& it)
		{
			out << it.m_node->data;

			return out;
		}



	private:
		CStringList::Node* m_node = nullptr;
		const CStringList* m_list = nullptr;
	};

	class CReverseIterator
	{
		friend CStringList;
	public:
		
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = std::string&;

		CReverseIterator(CStringList::Node* node, const CStringList* list = nullptr);
		CReverseIterator() = default;
		reference operator * () const;
		bool operator!=(CReverseIterator const& other) const;
		bool operator==(CReverseIterator const& other) const;
		CReverseIterator& operator++();
		CReverseIterator operator++(int);
		CReverseIterator& operator--();
		CReverseIterator& operator--(int);
		bool operator<=(const CReverseIterator& other) const;
		bool operator>=(const CReverseIterator& other) const;
		bool operator<(const CReverseIterator& other) const;
		bool operator>(const CReverseIterator& other) const;
		CStringList::CReverseIterator operator+(size_t index);
		CReverseIterator operator-(size_t index);
		pointer operator->()const;


	private:
		CStringList::Node* m_node = nullptr;
		const CStringList* m_list = nullptr;
	};


	class CConstIterator 
	{
		friend CStringList;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = std::string&;
		CConstIterator(CStringList::Node* node, const CStringList* list = nullptr);
		CConstIterator() = default;
		const reference operator * () const;
		bool operator!=(CConstIterator const& other) const;
		bool operator==(CConstIterator const& other) const;
		const CConstIterator& operator++();
		const CConstIterator operator++(int);
		const CConstIterator& operator--();
		const CConstIterator& operator--(int);

		bool operator<=(const CConstIterator& other) const;

		bool operator>=(const CConstIterator& other) const;

		bool operator<(const CConstIterator& other) const;

		bool operator>(const CConstIterator& other) const;

		const CConstIterator& operator+(size_t index);
		const CConstIterator& operator-(size_t index);
		const pointer operator->()const;

	private:
		CStringList::Node* m_node = nullptr;
		const CStringList* m_list;
	};

	class CConstReverseIterator
	{
		friend CStringList;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = Node*;
		using reference = std::string&;
		CConstReverseIterator(CStringList::Node* node,  const CStringList* list = nullptr);
		CConstReverseIterator() = default;
		const reference operator * () const;
		bool operator!=(CConstReverseIterator const& other) const;
		bool operator==(CConstReverseIterator const& other) const;
		const CConstReverseIterator& operator++();
		const CConstReverseIterator operator++(int);
		const CConstReverseIterator& operator--();
		const CConstReverseIterator& operator--(int);

		bool operator<=(const CConstReverseIterator& other) const;

		bool operator>=(const CConstReverseIterator& other) const;

		bool operator<(const CConstReverseIterator& other) const;

		bool operator>(const CConstReverseIterator& other) const;

		const CConstReverseIterator& operator+(size_t index);
		const CConstReverseIterator& operator-(size_t index);
		const pointer operator->()const;

	private:
		CStringList::Node* m_node = nullptr;
		const CStringList* m_list;
	};
	//Добавление строки в начало и 
	CStringList::CIterator push_front(const std::string& data) noexcept;
	//в конец списка(за время O(1))
	CStringList::CIterator push_back(const std::string& data) noexcept;
	//Узнать количество элементов(за время O(1)),
	size_t GetSize() const;
	// а также узнать пуст список или нет
	bool IsEmpty() const;
	bool IsNotEmpty() const;
	//Вставка элемента в позицию, задаваемую итератором(за время О(1))
	CStringList::CIterator Insert(const CStringList::CIterator& it, const std::string& value);
	//Удаление элемента в позиции, задаваемой итератором(за время О(1))
	CStringList::CIterator Erase(const CStringList::CIterator& it);

	//Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
	void Clear() noexcept;

	
	CStringList& operator=(CStringList const& other) noexcept;
	CStringList& operator=(CStringList && other) noexcept;
	
	CStringList::CIterator begin() const;
	CStringList::CIterator end() const;

	const CStringList::CConstIterator cbegin() const;
	const CStringList::CConstIterator cend() const;
	CStringList::CReverseIterator rbegin() const;
	CStringList::CReverseIterator rend() const;
	const CStringList::CConstReverseIterator rcbegin() const;
	const CStringList::CConstReverseIterator rcend() const;
	
private:
	size_t m_size;
	std::shared_ptr<Node> m_head = nullptr;
	std::shared_ptr<Node >m_end = std::make_shared<Node>("", nullptr, nullptr);

};
//должен быть biddirectional 
//Операторы присваивания(копирующий и перемещающий)
//для бегин и end const и не const
// не должно быть оператора []
//cbegin и cend с маленькой буквы
//должен быть сторожевой узел end