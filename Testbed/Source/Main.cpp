#include "CustomAllocatorsTest.h"

int main(int argc, char** args)
{
	StackAllocator stack_alloc(32);

	PVOID address_1 = stack_alloc.Allocate(4);
	PVOID address_2 = stack_alloc.Allocate(4);
	PVOID address_3 = stack_alloc.Allocate(4);

	try 
	{
		stack_alloc.Deallocate(address_2);
	}
	catch (Debug::Exception& e)
	{
		printf("%s", e.GetDescripton());
	}
}