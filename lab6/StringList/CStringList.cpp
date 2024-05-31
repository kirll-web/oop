#include "CStringList.h"
#include "../../lab6/StringLust/CStringList.h"

CStringList::CIterator::CIterator(CStringList::Node* node)
{
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	// TODO: вставьте здесь оператор return
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	// TODO: вставьте здесь оператор return
}

CStringList::CIterator CStringList::CIterator::operator+(size_t index)
{
	return CIterator();
}

std::string* CStringList::CIterator::operator->() const
{
	return nullptr;
}

CStringList::CConstIterator::CConstIterator(CStringList::Node* node)
{
}

const std::string& CStringList::CConstIterator::operator*() const
{
	// TODO: вставьте здесь оператор return
}

bool CStringList::CConstIterator::operator!=(CConstIterator const& other) const
{
	return false;
}

bool CStringList::CConstIterator::operator==(CConstIterator const& other) const
{
	return false;
}

const std::string* CStringList::CConstIterator::operator->() const
{
	return nullptr;
}
