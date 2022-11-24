#include <gtest/gtest.h>

#include "Source/Core/Common/TDelegateTest.h"

#include "Source/Core/Containers/TLinkedListTest.h"
#include "Source/Core/Containers/TStaticArrayTest.h"
#include "Source/Core/Containers/TDynamicStackTest.h"
#include "Source/Core/Containers/TDynamicQueueTest.h"

int main(int argc, char** args)
{
	testing::InitGoogleTest(&argc, args);
	return RUN_ALL_TESTS();
}
