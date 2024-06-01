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

	//������������: �� ���������, 
	CStringList();
	//����������� 
	CStringList(const CStringList& other);
	//�����������
	CStringList(CStringList&& other);
	//����������
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
	//���������� ������ � ������ � 
	void Push_front(const std::string& data);
	//� ����� ������(�� ����� O(1))
	void Push_back(const std::string& data);
	//������ ���������� ���������(�� ����� O(1)),
	size_t GetSize() const;
	// � ����� ������ ���� ������ ��� ���
	bool IsEmpty() const;
	bool IsNotEmpty() const;
	//������� �������� � �������, ���������� ����������(�� ����� �(1))
	CStringList::CIterator Insert(const CStringList::CIterator& it, const std::string& value);
	//�������� �������� � �������, ���������� ����������(�� ����� �(1))
	CStringList::CIterator Erase(const CStringList::CIterator& it);
	//������� ��� �������� �� ������(�� ����� �(N) � �������������� ������ O(1) � ������� �����)
	void Clear() noexcept;

	//��������� ������������(���������� � ������������)
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