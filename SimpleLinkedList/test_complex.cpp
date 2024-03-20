#include <gtest/gtest.h>
#include "SimpleLinkedList.hpp"

struct complex_object
{
	int x;
	float b;
	std::string name;

	bool operator==(const complex_object& other)const
	{
		return x == other.x && b == other.b && name == other.name;
	}
};


struct double_linked_list_tests_complex_obj : testing::Test
{
	std::unique_ptr <custom_linked_list::double_linked_list<complex_object>> list;

	double_linked_list_tests_complex_obj() : list(new custom_linked_list::double_linked_list<complex_object>())
	{
	}
};

TEST_F(double_linked_list_tests_complex_obj, TestPushBackIntoEmpty)
{
	const complex_object test_obj = { 10 , 0.5, "name" };

	EXPECT_EQ(list->size(), 0);
	list->push_back(test_obj);
	EXPECT_EQ(list->size(), 1);
	EXPECT_EQ(list->pop_back(), test_obj);
	EXPECT_EQ(list->size(), 0);
};

TEST_F(double_linked_list_tests_complex_obj, TestPushFrontIntoEmpty)
{
	const complex_object test_obj = { 10 , 0.5, "name" };
	EXPECT_EQ(list->size(), 0);
	list->push_front(test_obj);
	EXPECT_EQ(list->size(), 1);
	EXPECT_EQ(list->pop_front(), test_obj);
	EXPECT_EQ(list->size(), 0);
};

TEST_F(double_linked_list_tests_complex_obj, TestIndexOnEmptyShouldThrow)
{
	EXPECT_THROW((*list)[5], std::out_of_range);
}

TEST_F(double_linked_list_tests_complex_obj, TestIndexToLargeShouldThrow)
{
	const complex_object test_obj = { 10 , 0.5, "name" };
	list->push_back(test_obj);
	EXPECT_THROW((*list)[1], std::out_of_range);
}

TEST_F(double_linked_list_tests_complex_obj, TestPopOnEmptyShouldThrow)
{
	EXPECT_EQ(list->size(), 0);
	EXPECT_THROW(list->pop_back(), std::out_of_range);
	EXPECT_THROW(list->pop_front(), std::out_of_range);
};
