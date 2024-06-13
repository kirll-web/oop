#include "pch.h"
#include "../CMyList/CMyList.h"
#include <vector>



TEST(TestEmptyList, EmptyList) 
{
	CMyList list;
	EXPECT_NO_THROW(CMyList list);
	EXPECT_EQ(list.GetSize(), 0);
	EXPECT_TRUE(list.GetSize() != 1);
}

//TEST(TestNotEmptyListAndPushBack, NotEmptyListAndPushBack)
//{
//	CStringList list;
//	list.push_back("1");
//	EXPECT_EQ(list.GetSize(), 1);
//	EXPECT_TRUE(list.GetSize() != 2);
//	list.push_back("1asdasdasdsa");
//	EXPECT_EQ(list.GetSize(), 2);
//	EXPECT_TRUE(list.GetSize() != 3);
//	list.push_back("1asdasdasdsa1");
//	list.push_back("1asdasdasdsa2");
//	list.push_back("1asdasdasdsa3");
//	EXPECT_EQ(list.GetSize(), 5);
//	EXPECT_TRUE(list.GetSize() != 3);
//}
//
//TEST(TestNotEmptyListAndPushFront, NotEmptyListAndPushFront)
//{
//	CStringList list;
//	list.push_back("1");
//	EXPECT_EQ(list.GetSize(), 1);
//	EXPECT_TRUE(list.GetSize() != 2);
//	list.push_back("1asdasdasdsa");
//	EXPECT_EQ(list.GetSize(), 2);
//	EXPECT_TRUE(list.GetSize() != 3);
//	list.push_back("1asdasdasdsa1");
//	list.push_back("1asdasdasdsa2");
//	list.push_back("1asdasdasdsa3");
//	EXPECT_EQ(list.GetSize(), 5);
//	EXPECT_TRUE(list.GetSize() != 3);
//}
//
//
//TEST(TestIsEmpty, IsEmpty)
//{
//	CStringList list;
//	EXPECT_TRUE(list.IsEmpty());
//	std::string str = "hello world";
//	list.push_front(str);
//	EXPECT_TRUE(!list.IsEmpty());
//}
//
//TEST(TestIsNotEmpty, IsNotEmpty)
//{
//	CStringList list;
//	std::string str = "hello world";
//	list.push_front(str);
//	EXPECT_TRUE(list.IsNotEmpty());
//	EXPECT_NO_THROW(list.IsNotEmpty());
//}
//
//void TestIteratorForRange()
//{
//	CStringList list;
//	std::vector <std::string> vec{"1","2","3", "4"};
//	list.push_back("1");
//	list.push_back("2");
//	list.push_back("3");
//	list.push_back("4");
//	int index = 0;
//	for (auto it = list.begin(); it != list.end(); it++)
//	{
//		EXPECT_TRUE(*it == vec[index]);
//		++index;
//	}
//}
//
//TEST(TestForRange, ForRange)
//{
//	EXPECT_NO_THROW(TestIteratorForRange());
//}
//
//void TestConstIteratorForRange()
//{
//	CStringList list;
//	std::vector <std::string> vec{ "1","2","3", "4" };
//	list.push_back("1");
//	list.push_back("2");
//	list.push_back("3");
//	list.push_back("4");
//	int index = 0;
//	for (auto it = list.cbegin(); it != list.cend(); it++)
//	{
//		EXPECT_TRUE(*it == vec[index]);
//		++index;
//	}
//}
//
//TEST(TestConstIteratorForConst, ConstIteratorForRange)
//{
//	EXPECT_NO_THROW(TestConstIteratorForRange());
//}
//
//TEST(TestClearList, ClearList) 
//{
//	CStringList list;
//	std::string str = "hello world";
//	list.push_back(str);
//	list.push_back("asdasdasdsadsa");
//	list.push_back("str");
//	list.push_back(str);
//	EXPECT_TRUE(list.IsNotEmpty());
//	EXPECT_NO_THROW(list.Clear());
//	EXPECT_TRUE(list.IsEmpty());
//	EXPECT_NO_THROW(list.Clear());
//	EXPECT_TRUE(list.IsEmpty());
//}
//
//TEST(TestBegin, TestBegin)
//{
//	CStringList list;
//	std::string str = "hello world";
//	list.push_back(str);
//	EXPECT_TRUE(*list.begin() == str);
//	EXPECT_NO_THROW(list.Clear());
//	EXPECT_TRUE(list.IsEmpty());
//	EXPECT_ANY_THROW(*list.begin());
//}
//
//TEST(TestInsert, Insert) 
//{
//	CStringList list;
//	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
//	list.push_back("1");
//	list.push_back("2");
//	list.push_back("3");
//	EXPECT_NO_THROW(list.Insert(list.begin(), vec[0]));
//	EXPECT_NO_THROW(list.Insert(list.begin() + 1, vec[1]));
//	EXPECT_TRUE(list.IsNotEmpty());
//	EXPECT_TRUE(!list.IsEmpty());
//	EXPECT_TRUE(*list.begin() ==vec[0]);
//	EXPECT_TRUE(*(list.begin() + 1) == vec[1]);
//	EXPECT_TRUE(!list.IsEmpty());
//	EXPECT_TRUE(*list.cbegin() == vec[0]);
//	EXPECT_TRUE(*(list.begin() + 1) == vec[1]);
//	EXPECT_NO_THROW(list.Clear());
//	EXPECT_TRUE(list.IsEmpty());
//	EXPECT_NO_THROW(list.Insert(list.begin(), vec[1]));
//	EXPECT_NO_THROW(list.Insert(list.end(), vec[1]));
//	EXPECT_NO_THROW(list.Clear());
//	list.push_back("1");
//	list.push_back("2");
//	list.push_back("3");
//	EXPECT_ANY_THROW(list.Insert(list.begin() + 4, vec[1]));
//	EXPECT_ANY_THROW(list.Insert(list.end() + 4, vec[1]));
//}
//
//TEST(TestErase, Erase)
//{
//	CStringList list;
//	std::vector<std::string> vec = { "12asd", "asdasd", "asdasd" };
//	for (int i = 0; i < vec.size(); i++)
//	{
//		list.push_back(vec[i]);
//	}
//	EXPECT_TRUE(list.IsNotEmpty());
//	EXPECT_NO_THROW(list.Erase(list.begin()));
//	EXPECT_TRUE(list.GetSize() == 2);
//	EXPECT_NO_THROW(list.Clear());
//	EXPECT_ANY_THROW(list.Erase(list.end()));
//	EXPECT_TRUE(list.IsEmpty());
//}
//
//
//void TestReverseIteratorForRange()
//{
//	CStringList list;
//	std::vector <std::string> vec{ "1","2","3", "4" };
//	std::vector <std::string> vecExpect{  "4","3","2", "1", };
//	list.push_back("1");
//	list.push_back("2");
//	list.push_back("3");
//	list.push_back("4");
//	int index = 0;
//	for (auto it = list.rbegin(); it != list.rend(); it++)
//	{
//		EXPECT_TRUE(*it == vecExpect[index]);
//		++index;
//	}
//}
//
//TEST(TestReverseIterator, ReverseIterator)
//{
//	EXPECT_NO_THROW(TestReverseIteratorForRange());
//}
//
//
//TEST(TestTransform, Transform)
//{
//	CStringList list;
//	CStringList list2;
//	list.push_front("1");
//	list.push_front("2");
//	list.push_front("3");
//	list.push_front("4");
//
//	auto it = std::transform(list.begin(), list.end(), std::back_inserter(list2), [](std::string n)
//		{ return n + "a"; });
//
//	std::vector <std::string> vecExpect{ "1a","2a","3a", "4a"};
//	int index = 0;
//	EXPECT_NO_THROW(for (auto it = list2.rbegin(); it != list2.rend(); it++)
//	{
//		EXPECT_TRUE(*it == vecExpect[index]);
//		++index;
//	});
//}
//
//TEST(TestFind, Find)
//{
//	CStringList list;
//	list.push_front("1");
//	list.push_front("2");
//	list.push_front("3");
//
//
//	CStringList::CIterator find = std::find(list.begin(), list.end(), "2");
//
//	EXPECT_TRUE(*find == "2");
//}


