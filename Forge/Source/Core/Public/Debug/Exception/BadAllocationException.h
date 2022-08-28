#ifndef BAD_ALLOCATION_EXCEPTION_H
#define BAD_ALLOCATION_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class BadAllocationException : public Exception
		{
		public:
			BadAllocationException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Failed to perform allocation storage") {}

			BadAllocationException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Failed to perform allocation storage", add_info) {}
		};
	}
}

#endif // BAD_ALLOCATION_EXCEPTION_H
