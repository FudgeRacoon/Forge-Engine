#ifndef T_DYNAMIC_QUEUE_TEST_H
#define T_DYNAMIC_QUEUE_TEST_H

#include <gtest/gtest.h>

#include "Core/Public/Containers/TDynamicQueue.h"

using namespace Forge::Containers;

namespace DynamicQueueTest
{
	/**
	 * Tests the default constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, DefaultConstructor)
	{
		TDynamicQueue<int> ll;

		EXPECT_EQ(ll.GetCount(), 0);
		EXPECT_EQ(ll.IsEmpty(), true);
	}

	/**
	 * Tests the move element constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, MoveElementConstructor)
	{
		int value = 10;

		TDynamicQueue<int> ll(std::move(value), 10);

		EXPECT_EQ(ll.GetCount(), 10);
		EXPECT_EQ(ll.IsEmpty(), false);

		ll.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the copy element constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, CopyElementConstructor)
	{
		int value = 10;

		TDynamicQueue<int> ll(value, 10);

		EXPECT_EQ(ll.GetCount(), 10);
		EXPECT_EQ(ll.IsEmpty(), false);

		ll.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the initializer list constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, InitializerListConstructor)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll.GetCount(), 5);
		EXPECT_EQ(ll.IsEmpty(), false);

		int value = 1;

		ll.ForEach([&value](int& element)
			{
				EXPECT_EQ(element, value++);
			}
		);
	}

	/**
	 * Tests the move constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, MoveConstructor)
	{
		TDynamicQueue<int> ll1 = TDynamicQueue<int>(10, 10);
		TDynamicQueue<int> ll2 = std::move(ll1);

		EXPECT_EQ(ll1.GetCount(), 0);
		EXPECT_EQ(ll1.IsEmpty(), true);

		EXPECT_EQ(ll2.GetCount(), 10);
		EXPECT_EQ(ll2.IsEmpty(), false);

		ll2.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the copy constructor of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, CopyConstructor)
	{
		TDynamicQueue<int> ll1 = TDynamicQueue<int>(10, 10);
		TDynamicQueue<int> ll2 = ll1;

		EXPECT_EQ(ll1.GetCount(), 10);
		EXPECT_EQ(ll1.IsEmpty(), false);

		EXPECT_EQ(ll2.GetCount(), 10);
		EXPECT_EQ(ll2.IsEmpty(), false);

		ll2.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the move assignment of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, MoveAssignment)
	{
		TDynamicQueue<int> ll1 = TDynamicQueue<int>(10, 10);
		TDynamicQueue<int> ll2;

		ll2 = std::move(ll1);

		EXPECT_EQ(ll1.GetCount(), 0);
		EXPECT_EQ(ll1.IsEmpty(), true);

		EXPECT_EQ(ll2.GetCount(), 10);
		EXPECT_EQ(ll2.IsEmpty(), false);

		ll2.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the copy assignment of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, CopyAssignment)
	{
		TDynamicQueue<int> ll1 = TDynamicQueue<int>(10, 10);
		TDynamicQueue<int> ll2;

		ll2 = ll1;

		EXPECT_EQ(ll1.GetCount(), 10);
		EXPECT_EQ(ll1.IsEmpty(), false);

		EXPECT_EQ(ll2.GetCount(), 10);
		EXPECT_EQ(ll2.IsEmpty(), false);

		ll2.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the IsEqual member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, IsEqual)
	{
		TDynamicQueue<int> ll1 = { 1, 2, 3, 4, 5 };
		TDynamicQueue<int> ll2 = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll1.IsEqual(ll2), true);

		ll1.Push(6);

		EXPECT_EQ(ll1.IsEqual(ll2), false);
	}

	/**
	 * Tests the ToArray member function of a dynamic stack object.
	 */
	TEST(DynamicQueueTest, ToArray)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		int* array_ptr = ll.ToArray();

		int j = 1;

		for (int i = 0; i < 5; i++, j++)
			EXPECT_EQ(array_ptr[i], j);

		free(array_ptr);
	}

	/**
	 * Tests the FirstIndexOf member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, FirstIndexOf)
	{
		TDynamicQueue<int> ll(10, 10);

		EXPECT_EQ(ll.FirstIndexOf(10), 0);
	}

	/**
	 * Tests the LastIndexOf member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, LastIndexOf)
	{
		TDynamicQueue<int> ll(10, 10);

		EXPECT_EQ(ll.LastIndexOf(10), 9);
	}

	/**
	 * Tests the PeekBack member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, Peek)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll.Peek(), 1);
	}

	/**
	 * Tests the PushBack member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, Push)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		ll.Push(6);

		EXPECT_EQ(ll.GetCount(), 6);
		EXPECT_EQ(ll.Peek(), 1);

		ll.Push(7);

		EXPECT_EQ(ll.GetCount(), 7);
		EXPECT_EQ(ll.Peek(), 1);

		ll.Push(8);

		EXPECT_EQ(ll.GetCount(), 8);
		EXPECT_EQ(ll.Peek(), 1);
	}

	/**
	 * Tests the PopBack member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, Pop)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		ll.Pop();

		EXPECT_EQ(ll.GetCount(), 4);
		EXPECT_EQ(ll.Peek(), 2);

		ll.Pop();

		EXPECT_EQ(ll.GetCount(), 3);
		EXPECT_EQ(ll.Peek(), 3);

		ll.Pop();

		EXPECT_EQ(ll.GetCount(), 2);
		EXPECT_EQ(ll.Peek(), 4);
	}

	/**
	 * Tests the Contains member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, Contains)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		for (int i = 1; i <= ll.GetCount(); i++)
			EXPECT_EQ(ll.Contains(i), true);
	}

	/**
	 * Tests the InsertAll member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, InsertAll)
	{
		TDynamicQueue<int> ll1 = { 1, 2, 3, 4, 5 };
		TDynamicQueue<int> ll2 = { 6, 7, 8, 9, 10 };

		ll1.InsertAll(ll2);

		EXPECT_EQ(ll1.GetCount(), 10);

		int value = 1;

		ll1.ForEach([&value](int& element)
			{
				EXPECT_EQ(element, value++);
			}
		);
	}

	/**
	 * Tests the ContainsAll member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, ContainsAll)
	{
		TDynamicQueue<int> ll1 = { 1, 2, 3, 2, 5 };
		TDynamicQueue<int> ll2 = { 1, 2, 3, 5 };

		EXPECT_EQ(ll1.ContainsAll(ll2), true);

		ll1.Push(6);

		EXPECT_EQ(ll1.ContainsAll(ll2), false);
	}

	/**
	 * Tests the Clear member function of a dynamic queue object.
	 */
	TEST(DynamicQueueTest, Clear)
	{
		TDynamicQueue<int> ll = { 1, 2, 3, 4, 5 };

		ll.Clear();

		EXPECT_EQ(ll.GetCount(), 0);
		EXPECT_EQ(ll.IsEmpty(), true);
	}
}

#endif // T_DYNAMIC_QUEUE_TEST_H

