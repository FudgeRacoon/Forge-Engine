#ifndef BAD_ALLOCATION_EXCEPTION_H
#define BAD_ALLOCATION_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class BadAllocationException : public Exception
		{
		public:
			BadAllocationException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Failed to perform allocation storage") {}
			BadAllocationException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Failed to perform allocation storage", add_info) {}
		};
	}
}

#endif // BAD_ALLOCATION_EXCEPTION_H
