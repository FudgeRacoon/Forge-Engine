#include "gtest/gtest.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Containers/TDynamicStack.h"

using namespace Forge;
using namespace Forge::Containers;

namespace UnitTest
{
	TEST(TDynamicStackConstructorTest, DefaultConstructorTest)
	{
		TDynamicStack<I32> dynamic_stack;

		EXPECT_EQ(true, dynamic_stack.IsEmpty());
	}

	TEST(TDynamicStackConstructorTest, CopyConstructorTest)
	{
		TDynamicStack<I32> dynamic_stack_1;

		dynamic_stack_1.Push(12);
		dynamic_stack_1.Push(24);
		dynamic_stack_1.Push(56);

		TDynamicStack<I32> dynamic_stack_2 = dynamic_stack_1;

		I32* dynamic_stack_array_1 = dynamic_stack_1.ToArray();
		I32* dynamic_stack_array_2 = dynamic_stack_2.ToArray();

		for (int i = 0; i < 3; i++)
			EXPECT_EQ(dynamic_stack_array_1[i], dynamic_stack_array_2[i]);
	}


	TEST(TDynamicStackOperatorTest, AssignmentOperatorTest)
	{
		TDynamicStack<I32> dynamic_stack_1;
		TDynamicStack<I32> dynamic_stack_2;

		dynamic_stack_1.Push(12);
		dynamic_stack_1.Push(24);
		dynamic_stack_1.Push(56);

		dynamic_stack_2 = dynamic_stack_1;

		I32* dynamic_stack_array_1 = dynamic_stack_1.ToArray();
		I32* dynamic_stack_array_2 = dynamic_stack_2.ToArray();

		for (int i = 0; i < 3; i++)
			EXPECT_EQ(dynamic_stack_array_1[i], dynamic_stack_array_2[i]);
	}


	TEST(TDynamicStackModifierTest, PushModifierTest)
	{
		TDynamicStack<I32> dynamic_stack;

		dynamic_stack.Push(0);
		dynamic_stack.Push(1);
		dynamic_stack.Push(2);
		dynamic_stack.Push(3);
		dynamic_stack.Push(4);
		dynamic_stack.Push(5);

		I32* dynamic_stack_array = dynamic_stack.ToArray();

		for (int i = 0; i < 6; i++)
			EXPECT_EQ(i, dynamic_stack_array[i]);

		EXPECT_EQ(6, dynamic_stack.GetSize());

		EXPECT_EQ(false, dynamic_stack.IsEmpty());
	}

	TEST(TDynamicStackModifierTest, PopModifierTest)
	{
		TDynamicStack<I32> dynamic_stack;

		dynamic_stack.Push(0);
		dynamic_stack.Push(1);
		dynamic_stack.Push(2);
		dynamic_stack.Push(3);
		dynamic_stack.Push(4);
		dynamic_stack.Push(5);

		dynamic_stack.Pop();

		I32* dynamic_stack_array = dynamic_stack.ToArray();

		for (int i = 0; i < 5; i++)
			EXPECT_EQ(i, dynamic_stack_array[i]);

		EXPECT_EQ(5, dynamic_stack.GetSize());

		EXPECT_EQ(false, dynamic_stack.IsEmpty());
	}

	TEST(TDynamicStackModifierTest, PeekModifierTest)
	{
		TDynamicStack<I32> dynamic_stack;

		dynamic_stack.Push(0);
		dynamic_stack.Push(1);
		dynamic_stack.Push(2);
		dynamic_stack.Push(3);
		dynamic_stack.Push(4);
		dynamic_stack.Push(5);

		EXPECT_EQ(5, dynamic_stack.Peek());
	}

	TEST(TDynamicStackModifierTest, ContainsModifierTest)
	{
		TDynamicStack<I32> dynamic_stack;

		dynamic_stack.Push(0);
		dynamic_stack.Push(1);
		dynamic_stack.Push(2);
		dynamic_stack.Push(3);
		dynamic_stack.Push(4);
		dynamic_stack.Push(5);

		EXPECT_EQ(true, dynamic_stack.Contains(5));
	}

	TEST(TDynamicStackModifierTest, ClearModifierTest)
	{
		TDynamicStack<I32> dynamic_stack;

		dynamic_stack.Push(0);
		dynamic_stack.Push(1);
		dynamic_stack.Push(2);
		dynamic_stack.Push(3);
		dynamic_stack.Push(4);
		dynamic_stack.Push(5);

		dynamic_stack.Clear();

		EXPECT_EQ(0, dynamic_stack.GetSize());

		EXPECT_EQ(true, dynamic_stack.IsEmpty());
	}
}
