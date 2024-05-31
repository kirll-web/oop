#include "pch.h"
#include "../../lab6/StringLust/CStringList.h"
#include "../../lab6/StringLust/CStringList.cpp"
#include <vector>


TEST(TestEmptyList, EmptyList) 
{
	CStringList list;
	EXPECT_NO_THROW(CStringList list);
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_TRUE(list.GetSize() != 1);
}

TEST(TestNotEmptyListAndPushBack, NotEmptyListAndPushBack)
{
	CStringList list;
	list.Push_back("1");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_TRUE(list.GetSize() != 2);
	list.Push_back("1asdasdasdsa");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_TRUE(list.GetSize() != 3);
	list.Push_back("1asdasdasdsa1");
	list.Push_back("1asdasdasdsa2");
	list.Push_back("1asdasdasdsa3");
	EXPECT_EQ(list.GetSize(), 5);
	EXPECT_TRUE(list.GetSize() != 3);
}

TEST(TestNotEmptyListAndPushFront, NotEmptyListAndPushFront)
{
	CStringList list;
	list.Push_back("1");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_TRUE(list.GetSize() != 2);
	list.Push_back("1asdasdasdsa");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_TRUE(list.GetSize() != 3);
	list.Push_back("1asdasdasdsa1");
	list.Push_back("1asdasdasdsa2");
	list.Push_back("1asdasdasdsa3");
	EXPECT_EQ(list.GetSize(), 5);
	EXPECT_TRUE(list.GetSize() != 3);
}


TEST(TestIsEmpty, IsEmpty)
{
	CStringList list;
	EXPECT_TRUE(list.IsEmpty());
	std::string str = "hello world";
	list.Push_front(str);
	EXPECT_TRUE(!list.IsEmpty());
}

TEST(TestIsNotEmpty, IsNotEmpty)
{
	CStringList list;
	std::string str = "hello world";
	list.Push_front(str);
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_NO_THROW(list.IsNotEmpty());
}

void TestIteratorForRange()
{
	CStringList list;
	std::vector <std::string> vec{"1","2","3", "4"};
	list.Push_back("1");
	list.Push_back("2");
	list.Push_back("3");
	list.Push_back("4");
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
	CStringList list;
	std::vector <std::string> vec{ "1","2","3", "4" };
	list.Push_back("1");
	list.Push_back("2");
	list.Push_back("3");
	list.Push_back("4");
	int index = 0;
	for (auto it = list.Cbegin(); it != list.Cend(); it++)
	{
		EXPECT_TRUE(*it == vec[index]);
		++index;
	}
}

TEST(TestConstIteratorForConst, ConstIteratorForRange)
{
	EXPECT_NO_THROW(TestConstIteratorForRange());
}


TEST(TestClearList, ClearList) 
{
	CStringList list;
	std::string str = "hello world";
	list.Push_back(str);
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
}

TEST(TestBegin, TestBegin)
{
	CStringList list;
	std::string str = "hello world";
	list.Push_back(str);
	EXPECT_TRUE(*list.begin() == str);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_ANY_THROW(*list.begin());
}

TEST(TestInsert, Insert) 
{
	CStringList list;
	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
	list.Push_back("1");
	list.Push_back("2");
	list.Push_back("3");
	EXPECT_NO_THROW(list.Insert(list.begin(), vec[0]));
	EXPECT_NO_THROW(list.Insert(list.begin() + 1, vec[1]));
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_TRUE(!list.IsEmpty());
	EXPECT_TRUE(*list.begin() ==vec[0]);
	EXPECT_TRUE(*(list.begin() + 1) == vec[1]);
	EXPECT_TRUE(!list.IsEmpty());
	EXPECT_TRUE(*list.Cbegin() == vec[0]);
	EXPECT_TRUE(*(list.begin() + 1) == vec[1]);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_NO_THROW(list.Insert(list.begin(), vec[1]));
	EXPECT_NO_THROW(list.Insert(list.end(), vec[1]));
	EXPECT_NO_THROW(list.Clear());
	list.Push_back("1");
	list.Push_back("2");
	list.Push_back("3");
	EXPECT_ANY_THROW(list.Insert(list.begin() + 4, vec[1]));
	EXPECT_ANY_THROW(list.Insert(list.end() + 4, vec[1]));
}

TEST(TestErase, Erase)
{
	CStringList list;
	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
	for (int i = 0; i < vec.size(); i++)
	{
		list.Push_back(vec[i]);
	}
	EXPECT_TRUE(list.IsNotEmpty());
	EXPECT_NO_THROW(list.Erase(list.begin()));
	EXPECT_TRUE(list.GetSize() == 2);
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
}


TEST(TestStl, Erase)
{
	CStringList list;
	std::vector<std::string> vec = { "3", "2", "1" };
	std::vector<std::string> exceptVec = { "1", "2", "3" };
	list.Push_back(vec[0]);
	list.Push_back(vec[1]);
	list.Push_back(vec[2]);
	std::sort(list.begin(), list.end());
	int index = 0;
	for (auto it = list.begin(); it != list.end(); it++)
	{
		EXPECT_TRUE(*it == exceptVec[index]);
		++index;
	}
}
