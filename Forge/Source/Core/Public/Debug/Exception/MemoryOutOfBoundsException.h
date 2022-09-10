#ifndef MEMORY_OUT_OF_BOUNDS_EXCEPTION_H
#define MEMORY_OUT_OF_BOUNDS_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class MemoryOutOfBoundsException : public Exception
		{
		public:
			MemoryOutOfBoundsException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Memory address is out of bounds") {}
			MemoryOutOfBoundsException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Memory address is out of bounds", add_info) {}
		};
	}
}

#endif // MEMORY_OUT_OF_BOUNDS_EXCEPTION_H