#ifndef T_LINKED_LIST_TEST_H
#define T_LINKED_LIST_TEST_H

#include <gtest/gtest.h>

#include "Core/Public/Containers/TLinkedList.h"

using namespace Forge::Containers;

namespace LinkedListTest
{
	/**
	 * Tests the default constructor of a linked list object.
	 */
	TEST(LinkedListTest, DefaultConstructor)
	{
		TLinkedList<int> ll;

		EXPECT_EQ(ll.GetCount(), 0);
		EXPECT_EQ(ll.IsEmpty(), true);
	}

	/**
	 * Tests the move element constructor of a linked list object.
	 */
	TEST(LinkedListTest, MoveElementConstructor)
	{
		int value = 10;

		TLinkedList<int> ll(std::move(value), 10);

		EXPECT_EQ(ll.GetCount(), 10);
		EXPECT_EQ(ll.IsEmpty(), false);
		
		ll.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the copy element constructor of a linked list object.
	 */
	TEST(LinkedListTest, CopyElementConstructor)
	{
		int value = 10;

		TLinkedList<int> ll(value, 10);

		EXPECT_EQ(ll.GetCount(), 10);
		EXPECT_EQ(ll.IsEmpty(), false);

		ll.ForEach([](int& element)
			{
				EXPECT_EQ(element, 10);
			}
		);
	}

	/**
	 * Tests the initializer list constructor of a linked list object.
	 */
	TEST(LinkedListTest, InitializerListConstructor)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

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
	 * Tests the move constructor of a linked list object. 
	 */
	TEST(LinkedListTest, MoveConstructor)
	{
		TLinkedList<int> ll1 = TLinkedList<int>(10, 10);
		TLinkedList<int> ll2 = std::move(ll1);

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
	 * Tests the copy constructor of a linked list object.
	 */
	TEST(LinkedListTest, CopyConstructor)
	{
		TLinkedList<int> ll1 = TLinkedList<int>(10, 10);
		TLinkedList<int> ll2 = ll1;

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
	 * Tests the move assignment of a linked list object.
	 */
	TEST(LinkedListTest, MoveAssignment)
	{
		TLinkedList<int> ll1 = TLinkedList<int>(10, 10);
		TLinkedList<int> ll2; 
		
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
	 * Tests the copy assignment of a linked list object.
	 */
	TEST(LinkedListTest, CopyAssignment)
	{
		TLinkedList<int> ll1 = TLinkedList<int>(10, 10);
		TLinkedList<int> ll2; 
		
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
	 * Tests the IsEqual member function of a linked list object.
	 */
	TEST(LinkedListTest, IsEqual)
	{
		TLinkedList<int> ll1 = { 1, 2, 3, 4, 5 };
		TLinkedList<int> ll2 = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll1.IsEqual(ll2), true);

		ll1.PushBack(6);

		EXPECT_EQ(ll1.IsEqual(ll2), false);
	}

	/**
	 * Tests the ToArray member function of a linked list object.
	 */
	TEST(LinkedListTest, ToArray)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		int* array_ptr = ll.ToArray();

		int j = 1;

		for (int i = 0; i < 5; i++, j++)
			EXPECT_EQ(array_ptr[i], j);

		free(array_ptr);
	}

	/**
	 * Tests the FirstIndexOf member function of a linked list object.
	 */
	TEST(LinkedListTest, FirstIndexOf)
	{
		TLinkedList<int> ll(10, 10);

		EXPECT_EQ(ll.FirstIndexOf(10), 0);
	}

	/**
	 * Tests the LastIndexOf member function of a linked list object.
	 */
	TEST(LinkedListTest, LastIndexOf)
	{
		TLinkedList<int> ll(10, 10);

		EXPECT_EQ(ll.LastIndexOf(10), 9);
	}

	/**
	 * Tests the PeekBack member function of a linked list object.
	 */
	TEST(LinkedListTest, PeekBack)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll.PeekBack(), 5);
	}

	/**
	 * Tests the PeekFront member function of a linked list object.
	 */
	TEST(LinkedListTest, PeekFront)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(ll.PeekFront(), 1);
	}

	/**
	 * Tests the PushBack member function of a linked list object.
	 */
	TEST(LinkedListTest, PushBack)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.PushBack(6);

		EXPECT_EQ(ll.GetCount(), 6);
		EXPECT_EQ(ll.PeekBack(), 6);

		ll.PushBack(7);

		EXPECT_EQ(ll.GetCount(), 7);
		EXPECT_EQ(ll.PeekBack(), 7);

		ll.PushBack(8);

		EXPECT_EQ(ll.GetCount(), 8);
		EXPECT_EQ(ll.PeekBack(), 8);
	}

	/**
	 * Tests the PushFront member function of a linked list object.
	 */
	TEST(LinkedListTest, PushFront)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.PushFront(0);

		EXPECT_EQ(ll.GetCount(), 6);
		EXPECT_EQ(ll.PeekFront(), 0);

		ll.PushFront(-1);

		EXPECT_EQ(ll.GetCount(), 7);
		EXPECT_EQ(ll.PeekFront(), -1);

		ll.PushFront(-2);

		EXPECT_EQ(ll.GetCount(), 8);
		EXPECT_EQ(ll.PeekFront(), -2);
	}

	/**
	 * Tests the PopBack member function of a linked list object.
	 */
	TEST(LinkedListTest, PopBack)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.PopBack();

		EXPECT_EQ(ll.GetCount(), 4);
		EXPECT_EQ(ll.PeekBack(), 4);

		ll.PopBack();

		EXPECT_EQ(ll.GetCount(), 3);
		EXPECT_EQ(ll.PeekBack(), 3);

		ll.PopBack();

		EXPECT_EQ(ll.GetCount(), 2);
		EXPECT_EQ(ll.PeekBack(), 2);
	}

	/**
	 * Tests the PopFront member function of a linked list object.
	 */
	TEST(LinkedListTest, PopFront)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.PopFront();

		EXPECT_EQ(ll.GetCount(), 4);
		EXPECT_EQ(ll.PeekFront(), 2);

		ll.PopFront();

		EXPECT_EQ(ll.GetCount(), 3);
		EXPECT_EQ(ll.PeekFront(), 3);

		ll.PopFront();

		EXPECT_EQ(ll.GetCount(), 2);
		EXPECT_EQ(ll.PeekFront(), 4);
	}

	/**
	 * Tests the InsertAt member function of a linked list object.
	 */
	TEST(LinkedListTest, InsertAt)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.InsertAt(2, 15);

		EXPECT_EQ(ll.GetCount(), 6);
		EXPECT_EQ(ll.Contains(15), true);
		EXPECT_EQ(ll.FirstIndexOf(15), 2);

		ll.InsertAt(5, 25);

		EXPECT_EQ(ll.GetCount(), 7);
		EXPECT_EQ(ll.Contains(25), true);
		EXPECT_EQ(ll.FirstIndexOf(25), 5);

		ll.InsertAt(4, 30);

		EXPECT_EQ(ll.GetCount(), 8);
		EXPECT_EQ(ll.Contains(30), true);
		EXPECT_EQ(ll.FirstIndexOf(30), 4);
	}

	/**
	 * Tests the RemoveAt member function of a linked list object.
	 */
	TEST(LinkedListTest, RemoveAt)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.RemoveAt(2);

		EXPECT_EQ(ll.GetCount(), 4);
		EXPECT_EQ(ll.Contains(3), false);

		ll.RemoveAt(1);

		EXPECT_EQ(ll.GetCount(), 3);
		EXPECT_EQ(ll.Contains(2), false);

		ll.RemoveAt(2);

		EXPECT_EQ(ll.GetCount(), 2);
		EXPECT_EQ(ll.Contains(5), false);
	}

	/**
	 * Tests the Remove member function of a linked list object.
	 */
	TEST(LinkedListTest, Remove)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.Remove(4);

		EXPECT_EQ(ll.GetCount(), 4);
		EXPECT_EQ(ll.Contains(4), false);

		ll.Remove(3);

		EXPECT_EQ(ll.GetCount(), 3);
		EXPECT_EQ(ll.Contains(3), false);

		ll.Remove(1);

		EXPECT_EQ(ll.GetCount(), 2);
		EXPECT_EQ(ll.Contains(1), false);
	}

	/**
	 * Tests the Contains member function of a linked list object.
	 */
	TEST(LinkedListTest, Contains)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		for (int i = 1; i <= ll.GetCount(); i++)
			EXPECT_EQ(ll.Contains(i), true);
	}

	/**
	 * Tests the InsertAll member function of a linked list object.
	 */
	TEST(LinkedListTest, InsertAll)
	{
		TLinkedList<int> ll1 = { 1, 2, 3, 4, 5 };
		TLinkedList<int> ll2 = { 6, 7, 8, 9, 10 };

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
	 * Tests the RemoveAll member function of a linked list object.
	 */
	TEST(LinkedListTest, RemoveAll)
	{
		TLinkedList<int> ll1 = { 1, 2, 3, 2, 5 };
		TLinkedList<int> ll2 = { 2, 3 };

		ll1.RemoveAll(ll2);

		EXPECT_EQ(ll1.GetCount(), 2);
		EXPECT_EQ(ll1.Contains(2), false);
		EXPECT_EQ(ll1.Contains(3), false);
	}

	/**
	 * Tests the ContainsAll member function of a linked list object.
	 */
	TEST(LinkedListTest, ContainsAll)
	{
		TLinkedList<int> ll1 = { 1, 2, 3, 2, 5 };
		TLinkedList<int> ll2 = { 1, 2, 3, 5 };

		EXPECT_EQ(ll1.ContainsAll(ll2), true);

		ll1.PushBack(6);

		EXPECT_EQ(ll1.ContainsAll(ll2), false);
	}

	/**
	 * Tests the Clear member function of a linked list object.
	 */
	TEST(LinkedListTest, Clear)
	{
		TLinkedList<int> ll = { 1, 2, 3, 4, 5 };

		ll.Clear();

		EXPECT_EQ(ll.GetCount(), 0);
		EXPECT_EQ(ll.IsEmpty(), true);
	}
}

#endif // T_LINKED_LIST_H
