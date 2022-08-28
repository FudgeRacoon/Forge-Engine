#ifndef MEMORY_OUT_OF_BOUNDS_EXCEPTION_H
#define MEMORY_OUT_OF_BOUNDS_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class MemoryOutOfBoundsException : public Exception
		{
		public:
			MemoryOutOfBoundsException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Memory address is out of bounds") {}

			MemoryOutOfBoundsException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Memory address is out of bounds", add_info) {}
		};
	}
}

#endif // MEMORY_OUT_OF_BOUNDS_EXCEPTION_H