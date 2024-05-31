#pragma once
#include <string>
#include <memory>

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList & other);
	CStringList(const CStringList && other);
	~CStringList();

	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), pPrev(prev), pNext(std::move(next)) { }
		std::string data;
		Node* pPrev;
		std::unique_ptr<Node> pNext;
	};

	class CIterator : std::iterator<std::bidirectional_iterator_tag, std::string>
	{
		friend class CStringList;
	public:
		CIterator(CStringList::Node* node);
		CIterator() = default;
		std::string& operator * () const;
		bool operator!=(CIterator const& other) const;
		bool operator==(CIterator const& other) const;
		CIterator& operator++();
		CIterator& operator--();
		CIterator operator+(size_t index);
		std::string* operator->()const;
	private:
		CStringList::Node* m_node = nullptr;
	};

	class CConstIterator : std::iterator<std::bidirectional_iterator_tag, std::string>
	{
		friend class CStringList;
	public:
		CConstIterator(CStringList::Node* node);
		CConstIterator() = default;
		const std::string& operator * () const;
		bool operator!=(CConstIterator const& other) const;
		bool operator==(CConstIterator const& other) const;
		const std::string* operator->()const;
	private:
		CStringList::Node* m_node = nullptr;
	};

private:
	size_t m_size;
	std::unique_ptr<Node> m_head = nullptr;
	Node* m_tail = nullptr;
};