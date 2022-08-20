#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdlib.h>

#include "MemoryUtilities.h"
#include "AbstractAllocator.h"

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Memory
	{
		class FORGE_API LinearAllocator : public AbstractAllocator
		{
		private:
			PVOID m_offset_ptr;

		public:
			LinearAllocator(SIZE total_size);
			LinearAllocator(PVOID start, SIZE total_size);
		   ~LinearAllocator();

		public:
			PVOID Allocate(SIZE size, BYTE alignment = 4) override;
			VOID  Deallocate(PVOID address) override;
			VOID  Clear() override;
		};
	}
}

#endif // LINEAR_ALLOCATOR_H
