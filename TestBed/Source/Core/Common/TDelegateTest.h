#ifndef T_DELEGATE_TEST_H
#define T_DELEGATE_TEST_H

#include <gtest/gtest.h>

#include "Core/Public/Common/TDelegate.h"

using namespace Forge::Common;

namespace DelegateUnitTest
{
	namespace Internal
	{
		int TestFunc(int value) { return value; }

		struct TestClass 
		{ 
			int TestMemberFunc(int value) { return value; } 
			int ConstTestMemberFunc(int value) const { return value; }
		};
	}

	/**
	 * Tests the default constructor of a delegate object.
	 */
	TEST(DelegateTest, DefaultConstructor)
	{
		TDelegate<void(void)> d;

		EXPECT_EQ(d.IsValid(), false);
	}

	/**
	 * Tests the invokable constructor of a delegate object, if passed a lambda
	 * function with no capture clause.
	 */
	TEST(DelegateTest, NoCaptureLambdaContructor)
	{
		TDelegate<int(int)> d = [](int value) -> int { return value; };

		EXPECT_EQ(d.IsValid(), true);

		EXPECT_EQ(d.Invoke(1), 1);
		EXPECT_EQ(d.Invoke(2), 2);
		EXPECT_EQ(d.Invoke(3), 3);
		EXPECT_EQ(d.Invoke(4), 4);
		EXPECT_EQ(d.Invoke(5), 5);
	}

	/**
	 * Tests the invokable constructor of a delegate object, if passed a lambda
	 * function with a capture clause.
	 */
	TEST(DelegateTest, CaptureLambdaConstructor)
	{
		int num = 0;

		TDelegate<void()> d = [&num]() { ++num; };

		EXPECT_EQ(d.IsValid(), true);

		d.Invoke(); EXPECT_EQ(num, 1);
		d.Invoke(); EXPECT_EQ(num, 2);
		d.Invoke(); EXPECT_EQ(num, 3);
		d.Invoke(); EXPECT_EQ(num, 4);
		d.Invoke(); EXPECT_EQ(num, 5);
	}

	/**
	 * Tests the invokable constructor of a delegate object, if passed a global
	 * function.
	 */
	TEST(DelegateTest, GlobalFunctionConstructor)
	{
		TDelegate<int(int)> d = Internal::TestFunc;

		EXPECT_EQ(d.IsValid(), true);

		EXPECT_EQ(d.Invoke(1), 1);
		EXPECT_EQ(d.Invoke(2), 2);
		EXPECT_EQ(d.Invoke(3), 3);
		EXPECT_EQ(d.Invoke(4), 4);
		EXPECT_EQ(d.Invoke(5), 5);
	}

	/**
	 * Tests the member function constructor of a delegate object.
	 */
	TEST(DelegateTest, MemberFunctionConstructor)
	{
		Internal::TestClass instance;

		TDelegate<int(int)> d = TDelegate<int(int)>(&Internal::TestClass::TestMemberFunc, &instance);

		EXPECT_EQ(d.IsValid(), true);

		EXPECT_EQ(d.Invoke(1), 1);
		EXPECT_EQ(d.Invoke(2), 2);
		EXPECT_EQ(d.Invoke(3), 3);
		EXPECT_EQ(d.Invoke(4), 4);
		EXPECT_EQ(d.Invoke(5), 5);
	}

	/**
	 * Tests the const member function constructor of a delegate object.
	 */
	TEST(DelegateTest, ConstMemberFunctionConstructor)
	{
		const Internal::TestClass instance;

		TDelegate<int(int)> d = TDelegate<int(int)>(&Internal::TestClass::ConstTestMemberFunc, &instance);

		EXPECT_EQ(d.IsValid(), true);

		EXPECT_EQ(d.Invoke(1), 1);
		EXPECT_EQ(d.Invoke(2), 2);
		EXPECT_EQ(d.Invoke(3), 3);
		EXPECT_EQ(d.Invoke(4), 4);
		EXPECT_EQ(d.Invoke(5), 5);
	}

	/**
	 * Tests the move constructor of a delegate object.
	 */
	TEST(DelegateTest, MoveConstructor)
	{
		TDelegate<int(int)> d1 = [](int value) -> int { return value; };
		TDelegate<int(int)> d2 = std::move(d1);

		EXPECT_EQ(d1.IsValid(), false);
		EXPECT_EQ(d2.IsValid(), true);

		EXPECT_EQ(d2.Invoke(1), 1);
		EXPECT_EQ(d2.Invoke(2), 2);
		EXPECT_EQ(d2.Invoke(3), 3);
		EXPECT_EQ(d2.Invoke(4), 4);
		EXPECT_EQ(d2.Invoke(5), 5);
	}

	/**
	 * Tests the copy constructor of a delegate object.
	 */
	TEST(DelegateTest, CopyConstructor)
	{
		TDelegate<int(int)> d1 = [](int value) -> int { return value; };
		TDelegate<int(int)> d2 = d1;

		EXPECT_EQ(d1.IsValid(), true);
		EXPECT_EQ(d2.IsValid(), true);

		EXPECT_EQ(d2.Invoke(1), 1);
		EXPECT_EQ(d2.Invoke(2), 2);
		EXPECT_EQ(d2.Invoke(3), 3);
		EXPECT_EQ(d2.Invoke(4), 4);
		EXPECT_EQ(d2.Invoke(5), 5);
	}

	/**
	 * Tests the IsEqual member function of a delegate object with a global
	 * invokable.
	 */
	TEST(DelegateTest, GlobalInvokableIsEqual)
	{
		TDelegate<int(int)> d1 = Internal::TestFunc;
		TDelegate<int(int)> d2 = Internal::TestFunc;

		EXPECT_EQ(d1.IsEqual(d2), true);
	}

	/**
	 * Tests the IsEqual member function of a delegate object with a member
	 * function.
	 */
	TEST(DelegateTest, MemberFunctionIsEqual)
	{
		{
			const Internal::TestClass instance;

			TDelegate<int(int)> d1 = TDelegate<int(int)>(&Internal::TestClass::ConstTestMemberFunc, &instance);
			TDelegate<int(int)> d2 = TDelegate<int(int)>(&Internal::TestClass::ConstTestMemberFunc, &instance);

			EXPECT_EQ(d1.IsEqual(d2), true);
		}

		{
			const Internal::TestClass instance_1;
			const Internal::TestClass instance_2;

			TDelegate<int(int)> d1 = TDelegate<int(int)>(&Internal::TestClass::ConstTestMemberFunc, &instance_1);
			TDelegate<int(int)> d2 = TDelegate<int(int)>(&Internal::TestClass::ConstTestMemberFunc, &instance_2);

			EXPECT_EQ(d1.IsEqual(d2), false);
		}
	}

	/**
	 * Tests the Invalidate member function of a delegate object.
	 */
	TEST(DelegateTest, Invalidate)
	{
		TDelegate<int(int)> d = Internal::TestFunc;

		EXPECT_EQ(d.IsValid(), true);

		d.Invalidate();

		EXPECT_EQ(d.IsValid(), false);
	}
}

#endif // T_DELEGATE_TEST_H


