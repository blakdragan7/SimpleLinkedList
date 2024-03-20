#include <gtest/gtest.h>
#include "SimpleLinkedList.hpp"

struct double_linked_list_tests : testing::Test
{
	std::unique_ptr <custom_linked_list::double_linked_list<int>> list;

	double_linked_list_tests() : list(new custom_linked_list::double_linked_list<int>())
	{
	}
};

TEST_F(double_linked_list_tests, TestPushBackIntoEmpty)
{
	EXPECT_EQ(list->size(), 0);
	list->push_back(10);
	EXPECT_EQ(list->size(), 1);
	EXPECT_EQ(list->pop_back(), 10);
	EXPECT_EQ(list->size(), 0);
};

TEST_F(double_linked_list_tests, TestPushFrontIntoEmpty)
{
	EXPECT_EQ(list->size(), 0);
	list->push_front(10);
	EXPECT_EQ(list->size(), 1);
	EXPECT_EQ(list->pop_front(), 10);
	EXPECT_EQ(list->size(), 0);
};

TEST_F(double_linked_list_tests, TestIndexOnEmptyShouldThrow)
{
	EXPECT_THROW((*list)[5], std::out_of_range);
}

TEST_F(double_linked_list_tests, TestIndexToLargeShouldThrow)
{
	list->push_back(0);
	EXPECT_THROW((*list)[1], std::out_of_range);
}

TEST_F(double_linked_list_tests, TestPopOnEmptyShouldThrow)
{
	EXPECT_EQ(list->size(), 0);
	EXPECT_THROW(list->pop_back(), std::out_of_range);
	EXPECT_THROW(list->pop_front(), std::out_of_range);
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& obj)
{
	os << "{";
	for(const auto i : obj)
	{
		os << i << ",";
	}
	os << "}";
	return os;
}

struct push_object_state
{
	std::vector<int> data_to_push_front;
	std::vector<int> data_to_push_back;

	friend std::ostream& operator<<(std::ostream& os, const push_object_state& obj)
	{
		return os
			<< "data_to_push_front: " << obj.data_to_push_front
			<< "data_to_push_back: " << obj.data_to_push_back;
	}
};

struct acces_object_state
{
	std::vector<int> data_to_push;
	unsigned index;
	unsigned expected_value;

	friend std::ostream& operator<<(std::ostream& os, const acces_object_state& obj)
	{
		return os
			<< "data_to_push_front: " << obj.data_to_push
			<< " index: " << obj.index
		    << " expected_value: " << obj.expected_value;
	}
};

struct push_many_tests : double_linked_list_tests, testing::WithParamInterface<push_object_state>
{
};

struct access_tests : double_linked_list_tests, testing::WithParamInterface<acces_object_state>
{
};

TEST_P(push_many_tests, TestPushManyValuesBackThenFront)
{
	const auto as = GetParam();
	for(const auto i : as.data_to_push_back)
	{
		list->push_back(i);
	}

	EXPECT_EQ(list->size(), as.data_to_push_back.size());

	for (const auto i : as.data_to_push_front)
	{
		list->push_front(i);
	}


	EXPECT_EQ(list->size(), as.data_to_push_back.size() + as.data_to_push_front.size());

	for (auto iterator = as.data_to_push_back.rbegin();
		iterator != as.data_to_push_back.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_back(), *iterator);
	}

	for (auto iterator = as.data_to_push_front.rbegin();
		iterator != as.data_to_push_front.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_front(), *iterator);
	}
}

TEST_P(push_many_tests, TestPushManyValuesFrontThenBack)
{
	const auto as = GetParam();

	for (const auto i : as.data_to_push_front)
	{
		list->push_front(i);
	}

	EXPECT_EQ(list->size(), as.data_to_push_front.size());

	for (const auto i : as.data_to_push_back)
	{
		list->push_back(i);
	}

	EXPECT_EQ(list->size(), as.data_to_push_back.size() + as.data_to_push_front.size());

	for (auto iterator = as.data_to_push_back.rbegin();
		iterator != as.data_to_push_back.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_back(), *iterator);
	}

	for (auto iterator = as.data_to_push_front.rbegin();
		iterator != as.data_to_push_front.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_front(), *iterator);
	}

	EXPECT_EQ(list->size(), 0);
}

TEST_P(push_many_tests, TestPushManyValuesMixFrontAndBack)
{
	const auto as = GetParam();

	const auto max_size = std::max(as.data_to_push_back.size(), as.data_to_push_front.size());

	for(auto i=0ul;i<max_size;i++)
	{
		if(i < as.data_to_push_back.size())
		{
			list->push_back(as.data_to_push_back[i]);
		}

		if (i < as.data_to_push_front.size())
		{
			list->push_front(as.data_to_push_front[i]);
		}
	}

	EXPECT_EQ(list->size(), as.data_to_push_back.size() + as.data_to_push_front.size());

	for (auto iterator = as.data_to_push_back.rbegin();
		iterator != as.data_to_push_back.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_back(), *iterator);
	}

	for (auto iterator = as.data_to_push_front.rbegin();
		iterator != as.data_to_push_front.rend(); ++iterator)
	{
		EXPECT_EQ(list->pop_front(), *iterator);
	}

	EXPECT_EQ(list->size(), 0);
}

TEST_P(access_tests, access_push_back)
{
	const auto as = GetParam();
	for (const auto i : as.data_to_push)
	{
		list->push_back(i);
	}

	EXPECT_EQ(list->size(), as.data_to_push.size());

	EXPECT_EQ((*list)[as.index], as.expected_value);
}

TEST_P(access_tests, access_push_front)
{
	const auto as = GetParam();

	for (auto iterator = as.data_to_push.rbegin();
		iterator != as.data_to_push.rend(); ++iterator)
	{
		list->push_front(*iterator);
	}

	EXPECT_EQ(list->size(), as.data_to_push.size());

	EXPECT_EQ((*list)[as.index], as.expected_value);
}

INSTANTIATE_TEST_SUITE_P(Default, push_many_tests, testing::Values(
	push_object_state{ {10}, {1}},
	push_object_state{ {10 ,50, 10, 20, 40}, {1} },
	push_object_state{ {10}, {1, 50, 10 ,6, 8 ,4 ,2} },
	push_object_state{ {10, 1 ,2 ,2, 6}, {1, 4, 6, 8 ,7} },
	push_object_state{ {1000, 12654, 121987654, 2344 ,54897, 4, 54, 9, 8, 65, 4, 67, 6, 5, 4, 6, 57, 657, 65, 7,65 ,4, 654, 65, 4, 654 ,654, 654},{1, 654, 78, 999, 100} }
));

INSTANTIATE_TEST_SUITE_P(Default, access_tests, testing::Values(
	acces_object_state{ {1,2,3,4,5,6,7}, 1, 2 },
	acces_object_state{ {1,2,3,4,5,6,7}, 6, 7 },
	acces_object_state{ {1,2,3,4,5,6,7}, 5, 6 },
	acces_object_state{ {1,2,3,4,5,6,7}, 4, 5 },
	acces_object_state{ {1000, 12654, 121987654, 2344 ,54897, 4, 54, 9, 8, 65, 4, 67, 6, 5, 4, 6, 57, 657, 65, 7,65 ,4, 654, 65, 4, 654 ,654, 654}, 3, 2344 }
));