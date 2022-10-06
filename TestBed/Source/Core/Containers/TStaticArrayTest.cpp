#include "gtest/gtest.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Containers/TStaticArray.h"

using namespace Forge;
using namespace Forge::Containers;

namespace UnitTest
{
	TEST(TStaticArrayConstructorTests, DefaultConstructorTest)
	{
		TStaticArray<I32, 10> static_array;

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(0, static_array[i]);
	}

	TEST(TStaticArrayConstructorTests, DataPointerConstructorTest)
	{
		I32 data_ptr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		TStaticArray<I32, 10> static_array(data_ptr, 10);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(i, static_array[i]);
	}

	TEST(TStaticArrayConstructorTests, InitalizerListConstructorTest)
	{
		TStaticArray<I32, 10> static_array = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(i, static_array[i]);
	}

	TEST(TStaticArrayConstructorTests, MoveConstructorTest)
	{
		I32 data_ptr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		TStaticArray<I32, 10> static_array = TStaticArray<I32, 10>(data_ptr, 10);

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(i, static_array[i]);
	}

	TEST(TStaticArrayConstructorTests, CopyConstructorTest)
	{
		TStaticArray<I32, 10> static_array_1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		TStaticArray<I32, 10> static_array_2 = static_array_1;

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(i, static_array_2[i]);
	}

	TEST(TStaticArrayOperatorTests, AssignmentOperatorTest)
	{
		TStaticArray<I32, 10> static_array_1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		TStaticArray<I32, 10> static_array_2;

		static_array_2 = static_array_1;

		for (int i = 0; i < 10; i++)
			EXPECT_EQ(i, static_array_2[i]);
	}

	TEST(TStaticArrayOperatorTests, IndexOperatorTest)
	{
		TStaticArray<I32, 10> static_array = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		static_array[1] = 120;

		I32 test_val = static_array[5];

		EXPECT_EQ(120, static_array[1]);
		EXPECT_EQ(5, test_val);
	}


	struct TStaticArrayIteratorTests : public testing::Test
	{
	protected:
		TStaticArray<I32, 10> static_array;

	protected:
		void SetUp() override
		{
			for (int i = 0; i < 10; i++)
				static_array[i] = i;
		}
	};

	TEST_F(TStaticArrayIteratorTests, ForwardIteratorIncrementTest)
	{
		TStaticArray<I32, 10>::ForwardIterator itr = static_array.GetForwardStartItr();

		for (int i = 0; itr != static_array.GetForwardEndItr(); itr++, i++)
			EXPECT_EQ(*itr, static_array[i]);
	}

	TEST_F(TStaticArrayIteratorTests, ForwardIteratorDecrementTest)
	{
		TStaticArray<I32, 10>::ForwardIterator itr = static_array.GetForwardEndItr();
		itr--;

		for (int i = 9; i >= 0; itr--, i--)
			EXPECT_EQ(*itr, static_array[i]);
	}

	TEST_F(TStaticArrayIteratorTests, ForwardIteratorEqualityTest)
	{
		TStaticArray<I32, 10>::ForwardIterator start_itr = static_array.GetForwardStartItr();
		TStaticArray<I32, 10>::ForwardIterator end_itr = static_array.GetForwardEndItr();

		EXPECT_EQ(true, start_itr != end_itr);
	}

	TEST_F(TStaticArrayIteratorTests, ForwardIteratorDerefrenceTest)
	{
		TStaticArray<I32, 10>::ForwardIterator itr = static_array.GetForwardStartItr();

		*itr = 10;
		itr++;

		*itr = 20;
		itr++;

		*itr = 30;
		itr++;

		EXPECT_EQ(10, static_array[0]);
		EXPECT_EQ(20, static_array[1]);
		EXPECT_EQ(30, static_array[2]);
	}

	
	struct TStaticArrayModifierTests : public testing::Test
	{
	protected:
		TStaticArray<I32, 10> static_array;

	protected:
		void SetUp() override
		{
			static_array[0] = 7;
			static_array[1] = 4;
			static_array[2] = 7;
			static_array[3] = 1;
			static_array[4] = 5;
			static_array[5] = 7;
			static_array[6] = 9;
			static_array[7] = 2;
			static_array[8] = 8;
			static_array[9] = 9;
		}
	};

	TEST_F(TStaticArrayModifierTests, FirstIndexOfTest)
	{
		Size index = static_array.FirstIndexOf(9);

		EXPECT_EQ(6, index);
	}

	TEST_F(TStaticArrayModifierTests, LastIndexOfTest)
	{
		Size index = static_array.LastIndexOf(7);

		EXPECT_EQ(5, index);
	}
}