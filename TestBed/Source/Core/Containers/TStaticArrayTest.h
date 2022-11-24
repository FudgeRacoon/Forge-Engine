#ifndef T_STATIC_ARRAY_TEST_H
#define T_STATIC_ARRAY_TEST_H

#include <gtest/gtest.h>

#include "Core/Public/Containers/TStaticArray.h"

using namespace Forge::Containers;

namespace TStaticArrayTest
{
	/**  
	 * Tests the defualt constructor of a static array object.
	 */
	TEST(TStaticArrayTest, DefaultConstructor)
	{
		TStaticArray<int, 10> a;

		EXPECT_EQ(a.GetCount(), 0);
		EXPECT_EQ(a.IsEmpty(), true);
		EXPECT_EQ(a.GetMaxCapacity(), 10);
	}

	/**
	 * Tests the move element constructor of a static array object.
	 */
	TEST(TStaticArrayTest, MoveElementConstructor)
	{
		int value = 10;

		TStaticArray<int, 10> a(std::move(value), 10);

		EXPECT_EQ(a.GetCount(), 10);
		EXPECT_EQ(a.IsEmpty(), false);
		EXPECT_EQ(a.GetMaxCapacity(), 10);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a[i], 10);
	}

	/**
	 * Tests the copy element constructor of a static array object.
	 */
	TEST(TStaticArrayTest, CopyElementConstructor)
	{
		int value = 10;

		TStaticArray<int, 10> a(value, 10);

		EXPECT_EQ(a.GetCount(), 10);
		EXPECT_EQ(a.IsEmpty(), false);
		EXPECT_EQ(a.GetMaxCapacity(), 10);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(a[i], 10);
	}

	/**
	 * Tests the move constructor of a static array object.
	 */
	TEST(TStaticArrayTest, MoveConstructor)
	{
		TStaticArray<int, 10> a1(10, 10);
		TStaticArray<int, 10> a2 = std::move(a1);

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
	TEST(TStaticArrayTest, CopyConstructor)
	{
		TStaticArray<int, 10> a1(10, 10);
		TStaticArray<int, 10> a2 = a1;

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
	TEST(TStaticArrayTest, MoveAssignment)
	{
		TStaticArray<int, 10> a1(10, 10);
		TStaticArray<int, 10> a2;
			
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
	TEST(TStaticArrayTest, CopyAssignment)
	{
		TStaticArray<int, 10> a1(10, 10);
		TStaticArray<int, 10> a2 = a1;

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
	TEST(TStaticArrayTest, GetRawData)
	{
		TStaticArray<int, 10> a(10, 10);
		
		const int* ptr = a.GetRawData();

		for (int i = 0; i < a.GetCount(); i++)
			EXPECT_EQ(ptr[i], 10);
	}

	/**
	 * Tests the IsEqual member function of a static array object.
	 */
	TEST(TStaticArrayTest, IsEqual)
	{
		TStaticArray<int, 10> a1 = { 1, 2, 3, 4, 5 };
		TStaticArray<int, 10> a2 = { 1, 2, 3, 4, 5 };
	
		EXPECT_EQ(a1.IsEqual(a2), true);

		a1.PushBack(6);

		EXPECT_EQ(a1.IsEqual(a2), false);
	}
	
	/**
	 * Tests the ToArray member function of a static array object.
	 */
	TEST(TStaticArrayTest, ToArray)
	{
		TStaticArray<int, 5> a = { 1, 2, 3, 4, 5 };

		int* array_ptr = a.ToArray();

		int j = 1;

		for (int i = 0; i < 5; i++, j++)
			EXPECT_EQ(array_ptr[i], j);

		free(array_ptr);
	}

	/**
	 * Tests the FirstIndexOf member function of a static array object.
	 */
	TEST(TStaticArrayTest, FirstIndexOf)
	{
		TStaticArray<int, 10> a(10, 10);

		EXPECT_EQ(a.FirstIndexOf(10), 0);
	}

	/**
	 * Tests the LastIndexOf member function of a static array object.
	 */
	TEST(TStaticArrayTest, LastIndexOf)
	{
		TStaticArray<int, 10> a(10, 10);

		EXPECT_EQ(a.LastIndexOf(10), 9);
	}

	/**
	 * Tests the PeekBack member function of a static array object.
	 */
	TEST(TStaticArrayTest, PeekBack)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(a.PeekBack(), 5);
	}

	/**
	 * Tests the PeekFront member function of a static array object.
	 */
	TEST(TStaticArrayTest, PeekFront)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

		EXPECT_EQ(a.PeekFront(), 1);
	}

	/**
	 * Tests the PushBack member function of a static array object.
	 */
	TEST(TStaticArrayTest, PushBack)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, PushFront)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, PopBack)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, PopFront)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, InsertAt)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, RemoveAt)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, Remove)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

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
	TEST(TStaticArrayTest, Contains)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

		for (int i = 1; i <= a.GetCount(); i++)
			EXPECT_EQ(a.Contains(i), true);
	}

	/**
	 * Tests the InsertAll member function of a static array object.
	 */
	TEST(TStaticArrayTest, InsertAll)
	{
		TStaticArray<int, 10> a1 = { 1, 2, 3, 4, 5 };
		TStaticArray<int, 10> a2 = { 6, 7, 8, 9, 10 };

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
	TEST(TStaticArrayTest, RemoveAll)
	{
		TStaticArray<int, 10> a1 = { 1, 2, 3, 2, 5 };
		TStaticArray<int, 10> a2 = { 2, 3 };

		a1.RemoveAll(a2);

		EXPECT_EQ(a1.GetCount(), 2);
		EXPECT_EQ(a1.Contains(2), false);
		EXPECT_EQ(a1.Contains(3), false);
	}

	/**
	 * Tests the ContainsAll member function of a static array object.
	 */
	TEST(TStaticArrayTest, ContainsAll)
	{
		TStaticArray<int, 10> a1 = { 1, 2, 3, 2, 5 };
		TStaticArray<int, 10> a2 = { 1, 2, 3, 5 };

		EXPECT_EQ(a1.ContainsAll(a2), true);

		a1.PushBack(6);

		EXPECT_EQ(a1.ContainsAll(a2), false);
	}

	/**
	 * Tests the Clear member function of a static array object.
	 */
	TEST(TStaticArrayTest, Clear)
	{
		TStaticArray<int, 10> a = { 1, 2, 3, 4, 5 };

		a.Clear();

		EXPECT_EQ(a.GetCount(), 0);
		EXPECT_EQ(a.IsEmpty(), true);
	}
}

#endif
