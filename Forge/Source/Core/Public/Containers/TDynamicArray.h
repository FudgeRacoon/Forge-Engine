#ifndef T_DYNAMIC_ARRAY_H
#define T_DYNAMIC_ARRAY_H

#include <initializer_list>

#include "AbstractList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		template<typename InElementType>
		class TDynamicArray : public AbstractList<InElementType>
		{

		};
	}
}

#endif // T_DYNAMIC_ARRAY_H
