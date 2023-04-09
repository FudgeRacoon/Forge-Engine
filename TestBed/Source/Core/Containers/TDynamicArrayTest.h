#ifndef T_DYNAMIC_ARRAY_TEST_H
#define T_DYNAMIC_ARRAY_TEST_H

#include <gtest/gtest.h>

#include "Core/Public/Containers/TDynamicArray.h"

using namespace Forge::Containers;

namespace TDynamicArrayTest
{
	/**
	 * Tests the defualt constructor of a static array object.
	 */
	TEST(TDynamicArrayTest, DefaultConstructor)
	{
		TDynamicArray<int> a;

		EXPECT_EQ(a.GetCount(), 0);
		EXPECT_EQ(a.IsEmpty(), true);
	}

	/**
	 * Tests the move element constructor of a static array object.
	 */
	TEST(TDynamicArrayTest, MoveElementConstructor)
	{
		int value = 10;

		TDynamicArray<int> a(std::move(value), 10);

		EXPECT_EQ(a.GetCount(), 10);
		EXPECT_EQ(a.IsEmpty(), false);
		
		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a[i], 10);
	}

	/**
	 * Tests the copy element constructor of a static array object.
	 */
	TEST(TDynamicArrayTest, CopyElementConstructor)
	{
		int value = 10;

		TDynamicArray<int> a(value, 10);

		EXPECT_EQ(a.GetCount(), 10);
		EXPECT_EQ(a.IsEmpty(), false);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a[i], 10);
	}

	/**
	 * Tests the move constructor of a static array object.
	 */
	TEST(TDynamicArrayTest, MoveConstructor)
	{
		TDynamicArray<int> a1(10, 10);
		TDynamicArray<int> a2 = std::move(a1);

		EXPECT_EQ(a1.GetCount(), 0);
		EXPECT_EQ(a1.IsEmpty(), true);

		EXPECT_EQ(a2.GetCount(), 10);
		EXPECT_EQ(a2.IsEmpty(), false);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a2[i], 10);
	}

	/**
	 * Tests the copy constructor of a static array object.
	 */
	TEST(TDynamicArrayTest, CopyConstructor)
	{
		TDynamicArray<int> a1(10, 10);
		TDynamicArray<int> a2 = a1;

		EXPECT_EQ(a1.GetCount(), 10);
		EXPECT_EQ(a1.IsEmpty(), false);

		EXPECT_EQ(a2.GetCount(), 10);
		EXPECT_EQ(a2.IsEmpty(), false);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a2[i], 10);
	}

	/**
	 * Tests the move assignment of a static array object.
	 */
	TEST(TDynamicArrayTest, MoveAssignment)
	{
		TDynamicArray<int> a1(10, 10);
		TDynamicArray<int> a2;

		a2 = std::move(a1);

		EXPECT_EQ(a1.GetCount(), 0);
		EXPECT_EQ(a1.IsEmpty(), true);

		EXPECT_EQ(a2.GetCount(), 10);
		EXPECT_EQ(a2.IsEmpty(), false);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a2[i], 10);
	}

	/**
	 * Tests the copy assignment of a static array object.
	 */
	TEST(TDynamicArrayTest, CopyAssignment)
	{
		TDynamicArray<int> a1(10, 10);
		TDynamicArray<int> a2 = a1;

		EXPECT_EQ(a1.GetCount(), 10);
		EXPECT_EQ(a1.IsEmpty(), false);

		EXPECT_EQ(a2.GetCount(), 10);
		EXPECT_EQ(a2.IsEmpty(), false);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a2[i], 10);
	}

	/**
	 * Tests the GetRawData member function of a static array object.
	 */
	TEST(TDynamicArrayTest, GetRawData)
	{
		TDynamicArray<int> a(10, 10);

		const int* ptr = a.GetRawData();

		for (int i = 0; i < a.GetCount(); i++)
			EXPECT_EQ(ptr[i], 10);
	}

	/**
	 * Tests the IsEqual member function of a static array object.
	 */
	TEST(TDynamicArrayTest, IsEqual)
	{
		TDynamicArray<int> a1 = { 1, 2, 3, 4, 5 };
		TDynamicArray<int> a2 = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(a1.IsEqual(a2), true);

		a1.PushBack(6);

		EXPECT_EQ(a1.IsEqual(a2), false);
	}

	/**
	 * Tests the ToArray member function of a static array object.
	 */
	TEST(TDynamicArrayTest, ToArray)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		int* array_ptr = a.ToArray();

		int j = 1;

		for (int i = 0; i < 5; i++, j++)
			EXPECT_EQ(array_ptr[i], j);

		free(array_ptr);
	}

	/**
	 * Tests the FirstIndexOf member function of a static array object.
	 */
	TEST(TDynamicArrayTest, FirstIndexOf)
	{
		TDynamicArray<int> a(10, 10);

		EXPECT_EQ(a.FirstIndexOf(10), 0);
	}

	/**
	 * Tests the LastIndexOf member function of a static array object.
	 */
	TEST(TDynamicArrayTest, LastIndexOf)
	{
		TDynamicArray<int> a(10, 10);

		EXPECT_EQ(a.LastIndexOf(10), 9);
	}

	/**
	 * Tests the PeekBack member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PeekBack)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(a.PeekBack(), 5);
	}

	/**
	 * Tests the PeekFront member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PeekFront)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(a.PeekFront(), 1);
	}

	/**
	 * Tests the PushBack member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PushBack)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.PushBack(6);

		EXPECT_EQ(a.GetCount(), 6);
		EXPECT_EQ(a.PeekBack(), 6);

		a.PushBack(7);

		EXPECT_EQ(a.GetCount(), 7);
		EXPECT_EQ(a.PeekBack(), 7);

		a.PushBack(8);

		EXPECT_EQ(a.GetCount(), 8);
		EXPECT_EQ(a.PeekBack(), 8);
	}

	/**
	 * Tests the PushFront member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PushFront)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.PushFront(0);

		EXPECT_EQ(a.GetCount(), 6);
		EXPECT_EQ(a.PeekFront(), 0);

		a.PushFront(-1);

		EXPECT_EQ(a.GetCount(), 7);
		EXPECT_EQ(a.PeekFront(), -1);

		a.PushFront(-2);

		EXPECT_EQ(a.GetCount(), 8);
		EXPECT_EQ(a.PeekFront(), -2);
	}

	/**
	 * Tests the PopBack member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PopBack)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.PopBack();

		EXPECT_EQ(a.GetCount(), 4);
		EXPECT_EQ(a.PeekBack(), 4);

		a.PopBack();

		EXPECT_EQ(a.GetCount(), 3);
		EXPECT_EQ(a.PeekBack(), 3);

		a.PopBack();

		EXPECT_EQ(a.GetCount(), 2);
		EXPECT_EQ(a.PeekBack(), 2);
	}

	/**
	 * Tests the PopFront member function of a static array object.
	 */
	TEST(TDynamicArrayTest, PopFront)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.PopFront();

		EXPECT_EQ(a.GetCount(), 4);
		EXPECT_EQ(a.PeekFront(), 2);

		a.PopFront();

		EXPECT_EQ(a.GetCount(), 3);
		EXPECT_EQ(a.PeekFront(), 3);

		a.PopFront();

		EXPECT_EQ(a.GetCount(), 2);
		EXPECT_EQ(a.PeekFront(), 4);
	}

	/**
	 * Tests the InsertAt member function of a static array object.
	 */
	TEST(TDynamicArrayTest, InsertAt)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.InsertAt(2, 15);

		EXPECT_EQ(a.GetCount(), 6);
		EXPECT_EQ(a.Contains(15), true);
		EXPECT_EQ(a.FirstIndexOf(15), 2);

		a.InsertAt(5, 25);

		EXPECT_EQ(a.GetCount(), 7);
		EXPECT_EQ(a.Contains(25), true);
		EXPECT_EQ(a.FirstIndexOf(25), 5);

		a.InsertAt(4, 30);

		EXPECT_EQ(a.GetCount(), 8);
		EXPECT_EQ(a.Contains(30), true);
		EXPECT_EQ(a.FirstIndexOf(30), 4);
	}

	/**
	 * Tests the RemoveAt member function of a static array object.
	 */
	TEST(TDynamicArrayTest, RemoveAt)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.RemoveAt(2);

		EXPECT_EQ(a.GetCount(), 4);
		EXPECT_EQ(a.Contains(3), false);

		a.RemoveAt(1);

		EXPECT_EQ(a.GetCount(), 3);
		EXPECT_EQ(a.Contains(2), false);

		a.RemoveAt(2);

		EXPECT_EQ(a.GetCount(), 2);
		EXPECT_EQ(a.Contains(5), false);
	}

	/**
	 * Tests the Remove member function of a static array object.
	 */
	TEST(TDynamicArrayTest, Remove)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.Remove(4);

		EXPECT_EQ(a.GetCount(), 4);
		EXPECT_EQ(a.Contains(4), false);

		a.Remove(3);

		EXPECT_EQ(a.GetCount(), 3);
		EXPECT_EQ(a.Contains(3), false);

		a.Remove(1);

		EXPECT_EQ(a.GetCount(), 2);
		EXPECT_EQ(a.Contains(1), false);
	}

	/**
	 * Tests the Contains member function of a static array object.
	 */
	TEST(TDynamicArrayTest, Contains)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		for (int i = 1; i <= a.GetCount(); i++)
			EXPECT_EQ(a.Contains(i), true);
	}

	/**
	 * Tests the InsertAll member function of a static array object.
	 */
	TEST(TDynamicArrayTest, InsertAll)
	{
		TDynamicArray<int> a1 = { 1, 2, 3, 4, 5 };
		TDynamicArray<int> a2 = { 6, 7, 8, 9, 10 };

		a1.InsertAll(a2);

		EXPECT_EQ(a1.GetCount(), 10);

		int value = 1;

		a1.ForEach([&value](int& element)
			{
				EXPECT_EQ(element, value++);
			}
		);
	}

	/**
	 * Tests the RemoveAll member function of a static array object.
	 */
	TEST(TDynamicArrayTest, RemoveAll)
	{
		TDynamicArray<int> a1 = { 1, 2, 3, 2, 5 };
		TDynamicArray<int> a2 = { 2, 3 };

		a1.RemoveAll(a2);

		EXPECT_EQ(a1.GetCount(), 2);
		EXPECT_EQ(a1.Contains(2), false);
		EXPECT_EQ(a1.Contains(3), false);
	}

	/**
	 * Tests the ContainsAll member function of a static array object.
	 */
	TEST(TDynamicArrayTest, ContainsAll)
	{
		TDynamicArray<int> a1 = { 1, 2, 3, 2, 5 };
		TDynamicArray<int> a2 = { 1, 2, 3, 5 };

		EXPECT_EQ(a1.ContainsAll(a2), true);

		a1.PushBack(6);

		EXPECT_EQ(a1.ContainsAll(a2), false);
	}

	/**
	 * Tests the Clear member function of a static array object.
	 */
	TEST(TDynamicArrayTest, Clear)
	{
		TDynamicArray<int> a = { 1, 2, 3, 4, 5 };

		a.Clear();

		EXPECT_EQ(a.GetCount(), 0);
		EXPECT_EQ(a.IsEmpty(), true);
	}
}

#endif

