#include "pch.h"
#include "../../lab6/StringLust/CStringList.h"
#include "../../lab6/StringLust/CStringList.cpp"



TEST(TestEmptyList, EmptyList) 
{
	CStringList list;
	EXPECT_NO_THROW(CStringList list);
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_TRUE(list.GetSize() != 1);
}

TEST(TestNotEmptyList, NotEmptyList) 
{
	CStringList list;
	list.Push_back("1");
	EXPECT_EQ(list.GetSize(), 1);
	EXPECT_TRUE(list.GetSize() != 2);
	list.Push_back("1asdasdasdsa");
	EXPECT_EQ(list.GetSize(), 2);
	EXPECT_TRUE(list.GetSize() != 3);
}

TEST(TestPushBack, PushBack)
{
	CStringList list;
	std::string str = "hello world";
	list.Push_back(str);
	EXPECT_TRUE(*list.Cbegin() == str);
	EXPECT_NO_THROW(list.Push_back(str));
}

TEST(TestPushFront, PushBack)
{
	CStringList list;
	std::string str = "hello world";
	list.Push_front(str);
	EXPECT_TRUE(*list.Cbegin() == str);
	EXPECT_NO_THROW(list.Push_front(str));
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

TEST(TestClearEmptyListNoThrow, ClearEmptyListNoThrow)
{
	CStringList list;
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_NO_THROW(list.Clear());
	EXPECT_TRUE(list.IsEmpty());
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
