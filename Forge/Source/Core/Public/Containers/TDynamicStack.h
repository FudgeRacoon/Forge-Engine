#ifndef T_DYNAMIC_STACK_H
#define T_DYNAMIC_STACK_H

#include <utility>
#include <stdlib.h>
#include <initializer_list>

#include "AbstractList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/PoolAllocator.h"
#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class TDynamicStack : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		public:

		};
	}
}

#endif // T_DYNAMIC_STACK_H
