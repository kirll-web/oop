#pragma once
#include <string>
#include <memory>
#include <iterator>
#include <stdexcept>
#include <iostream>

class CStringList
{
public:
	struct Node {
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
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
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = std::string*;
		using reference = std::string&;

		CIterator(CStringList::Node* node, bool isReverse = false, const CStringList* list = nullptr);
		CIterator() = default;
		std::string& operator * () const;
		bool operator!=(CIterator const& other) const;
		bool operator==(CIterator const& other) const;
		CIterator& operator++();
		CIterator operator++(int);
		CIterator& operator--();
		CIterator& operator--(int);
		bool operator<=(const CIterator& other) const;
		bool operator>=(const CIterator& other) const;
		ptrdiff_t operator-(const CIterator& other) const;
		CStringList::CIterator operator-(ptrdiff_t n) const;
		CIterator& operator+(ptrdiff_t n);
		friend CIterator operator+(const CIterator& it, ptrdiff_t n);
		bool operator<(const CIterator& other) const;
		bool operator>(const CIterator& other) const;
		//CStringList::CIterator operator+(ptrdiff_t n) const;
		CIterator operator+(size_t index);
		CIterator operator-(size_t index);
		std::string* operator->()const;
	private:
		CStringList::Node* m_node = nullptr;
		bool m_reverse = false;
		const CStringList* m_list = nullptr;
	};

	class CConstIterator 
	{
		friend CStringList;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = std::string*;
		using reference = std::string&;
		CConstIterator(CStringList::Node* node, bool isReverse = false, const CStringList* list = nullptr);
		CConstIterator() = default;
		const std::string& operator * () const;
		bool operator!=(CConstIterator const& other) const;
		bool operator==(CConstIterator const& other) const;
		const CConstIterator& operator++();
		const CConstIterator operator++(int);
		const CConstIterator& operator--();
		const CConstIterator& operator--(int);

		const CConstIterator& operator+(size_t index);
		const CConstIterator& operator-(size_t index);
		const std::string* operator->()const;
	private:
		CStringList::Node* m_node = nullptr;
		bool m_reverse = false;
		const CStringList* m_list;
	};
	//Добавление строки в начало и 
	void Push_front(const std::string& data);
	//в конец списка(за время O(1))
	void Push_back(const std::string& data);
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

	//Операторы присваивания(копирующий и перемещающий)
	CStringList& operator=(CStringList const& other);
	CStringList& operator=(CStringList && other);
	std::string& operator[](size_t index);
	CStringList::CIterator begin() const;
	CStringList::CIterator end() const;
	const CStringList::CConstIterator Cbegin() const;
	const CStringList::CConstIterator Cend() const;
	CStringList::CIterator Rbegin() const;
	CStringList::CIterator Rend() const;
	const CStringList::CConstIterator Rcbegin() const;
	const CStringList::CConstIterator Rcend() const;
	
private:
	size_t m_size;
	std::unique_ptr<Node> m_head = nullptr;
	Node* m_tail = nullptr;
};