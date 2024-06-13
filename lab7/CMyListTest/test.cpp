#include "pch.h"
#include "../CMyList/CMyList.h"
#include <vector>
#include <string>
using namespace std;
TEST(TestEmptyList, EmptyList)
{
	CMyList<int> listInt;
	CMyList<string> listString;
	EXPECT_NO_THROW(CMyList<int> list);
	EXPECT_EQ(listInt.GetSize(), 0);
	EXPECT_TRUE(listInt.GetSize() != 1);
	EXPECT_EQ(listString.GetSize(), 0);
	EXPECT_TRUE(listString.GetSize() != 1);
}

TEST(TestNotEmptyListAndPushBack, NotEmptyListAndPushBack)
{
	CMyList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_EQ(list.GetSize(), 3);
	EXPECT_TRUE(list.GetSize() != 2);
	CMyList<string> listString;
	listString.push_back("1asdasdasdsa1");
	listString.push_back("1asdasdasdsa2");
	listString.push_back("1asdasdasdsa3");
	EXPECT_EQ(list.GetSize(), 3);
	EXPECT_TRUE(list.GetSize() != 2);
}

TEST(TestNotEmptyListAndPushFront, NotEmptyListAndPushFront)
{
	CMyList<string> list;
	list.push_back("1");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_TRUE(list.GetSize() != 2);
	list.push_back("1asdasdasdsa");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_TRUE(list.GetSize() != 3);
	list.push_back("1asdasdasdsa1");
	list.push_back("1asdasdasdsa2");
	list.push_back("1asdasdasdsa3");
	EXPECT_EQ(list.GetSize(), 5);
	EXPECT_TRUE(list.GetSize() != 3);
}


TEST(TestIsEmpty, IsEmpty)
{
	CMyList<string>  list;
	EXPECT_TRUE(list.IsEmpty());
	std::string str = "hello world";
	list.push_front(str);
	EXPECT_TRUE(!list.IsEmpty());
}

TEST(TestIsNotEmpty, IsNotEmpty)
{
	CMyList<string>  list;
	std::string str = "hello world";
	list.push_front(str);
	EXPECT_TRUE(list.IsNotEmpty());
}

void TestIteratorForRange()
{
	CMyList<string>  list;
	std::vector <std::string> vec{"1","2","3", "4"};
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	list.push_back("4");
	int index = 0;
	for (auto it = list.begin(); it != list.end(); it++)
	{
		EXPECT_TRUE(*it == vec[index]);
		++index;
	}
}

TEST(TestForRange, ForRange)
{
	EXPECT_NO_THROW(TestIteratorForRange());
}

void TestConstIteratorForRange()
{
	CMyList<string>  list;
	std::vector <std::string> vec{ "1","2","3", "4" };
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	list.push_back("4");
	int index = 0;
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		EXPECT_TRUE(*it == vec[index]);
		++index;
	}
}

void TestConstIterator()
{
	CMyList<int>  list;
	list.push_back(1);
	list.push_back(2);
	CMyList<int>::CConstIterator b = list.cbegin();
	b++;
}

TEST(TestConstIteratorForConst, ConstIteratorForRange)
{
	EXPECT_NO_THROW(TestConstIteratorForRange());


	CMyList<string>  list;
	std::vector <std::string> vec{ "1","2","3", "4" };
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	
	EXPECT_NO_THROW(TestConstIterator());
}

TEST(TestClearList, ClearList) 
{
	CMyList<string> list;
	string str = "hello world";
	list.push_back(str);
	list.push_back("asdasdasdsadsa");
	list.push_back("str");
	list.push_back(str);
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
}

TEST(TestBegin, TestBegin)
{
	CMyList<string> list;
	std::string str = "hello world";
	list.push_back(str);
	EXPECT_TRUE(*list.begin() == str);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_ANY_THROW(*list.begin());
}

TEST(TestInsert, Insert) 
{
	CMyList<string> list;
	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	EXPECT_NO_THROW(list.Insert(list.begin(), vec[0]));
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_TRUE(!list.IsEmpty());
	EXPECT_TRUE(*list.begin() ==vec[0]);
	EXPECT_TRUE(!list.IsEmpty());
	EXPECT_TRUE(*list.cbegin() == vec[0]);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_NO_THROW(list.Insert(list.begin(), vec[1]));
	EXPECT_NO_THROW(list.Insert(list.end(), vec[1]));
	EXPECT_NO_THROW(list.Clear());
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
}

TEST(TestErase, Erase)
{
	CMyList<string> list;
	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
	for (int i = 0; i < vec.size(); i++)
	{
		list.push_back(vec[i]);
	}
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_NO_THROW(list.Erase(list.begin()));
	EXPECT_TRUE(list.GetSize() == 2);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_ANY_THROW(list.Erase(list.end()));
	EXPECT_TRUE(list.IsEmpty());
}


void TestReverseIteratorForRange()
{
	CMyList<string> list;
	std::vector <std::string> vec{ "1","2","3", "4" };
	std::vector <std::string> vecExpect{  "4","3","2", "1", };
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	list.push_back("4");
	int index = 0;
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		EXPECT_TRUE(*it == vecExpect[index]);
		++index;
	}
}

TEST(TestReverseIterator, ReverseIterator)
{
	EXPECT_NO_THROW(TestReverseIteratorForRange());
}


TEST(TestTransform, Transform)
{
	CMyList<string> list;
	CMyList<string> list2;
	list.push_front("1");
	list.push_front("2");
	list.push_front("3");
	list.push_front("4");

	auto it = std::transform(list.begin(), list.end(), std::back_inserter(list2), [](std::string n)
		{ return n + "a"; });

	std::vector <std::string> vecExpect{ "1a","2a","3a", "4a"};
	int index = 0;
	EXPECT_NO_THROW(for (auto it = list2.rbegin(); it != list2.rend(); it++)
	{
		EXPECT_TRUE(*it == vecExpect[index]);
		++index;
	});
}

TEST(TestFind, Find)
{
	CMyList<string> list;
	list.push_front("1");
	list.push_front("2");
	list.push_front("3");

	CMyList<string>::CIterator find = std::find(list.begin(), list.end(), "2");

	EXPECT_TRUE(*find == "2");
}

TEST(TestOperatorPostPlusPlus, OperatorPostPlusPlus)
{
	CMyList<string> list;
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");

	EXPECT_NO_THROW(list.begin()++);
	EXPECT_ANY_THROW(list.end()++);

	string expectRes1 = "1";
	string expectRes2 = "2";
	EXPECT_NO_THROW(*(list.begin()++) == expectRes1);
	auto it = list.begin();
	EXPECT_TRUE(*(it++) == expectRes1);
	EXPECT_TRUE(*it == expectRes2);
}

TEST(TestOperatorPrefPlusPlus, OperatorPrefPlusPlus)
{
	CMyList<string> list;
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");

	EXPECT_NO_THROW(list.begin()++);
	EXPECT_ANY_THROW(list.end()++);

	string expectRes1 = "2";
	EXPECT_NO_THROW(*(++list.begin()) == expectRes1);
	auto it = list.begin();
	EXPECT_TRUE(*(++it) == expectRes1);
	EXPECT_TRUE(*it == expectRes1);
}

TEST(TestOperatorPostMinusMinus, OperatorPostMinusMinus)
{
	CMyList<string> list;
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");

	EXPECT_NO_THROW(list.end()--);
	EXPECT_ANY_THROW(list.begin()--);

	string expectRes2 = "3";
	EXPECT_NO_THROW((list.end()--));
	auto it = list.end();
	EXPECT_TRUE((it--) == list.end());
	EXPECT_TRUE(*it == expectRes2);
}

TEST(TestOperatorPrefMinusMinus, OperatorPrefMinusMinus)
{
	CMyList<string> list;
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");
	EXPECT_THROW(--list.begin(), std::out_of_range);
	EXPECT_NO_THROW(--list.end());

	string expectRes1 = "3";
	EXPECT_NO_THROW(*(--list.end()));
	auto it = list.end();
	EXPECT_TRUE(*(--it) == expectRes1);
}

TEST(TestOperatorEqualIterator, operatorEqualItertor)
{
	CMyList<string> list;
	list.push_front("1");
	list.push_front("2");
	list.push_front("3");
	EXPECT_NO_THROW(list.begin() == list.end());
	EXPECT_FALSE(list.begin() == list.end());
	EXPECT_FALSE(list.begin() == list.end());
	EXPECT_TRUE(list.begin() == list.begin());
}

TEST(TestOperatorNotEqualIterator, operatorNotEqualIterator)
{
	CMyList<string> list;
	list.push_front("1");
	list.push_front("2");
	list.push_front("3");
	EXPECT_NO_THROW(list.begin() != list.end());
	EXPECT_TRUE(list.begin() != list.end());
	EXPECT_TRUE(list.begin() != list.end());
	EXPECT_FALSE(list.begin() != list.begin());
}