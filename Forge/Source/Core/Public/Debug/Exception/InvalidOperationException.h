#ifndef INVALID_OPERATION_EXCEPTION_H
#define INVALID_OPERATION_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class InvalidOperationException : public Exception
		{
		public:
			InvalidOperationException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Failed to perform operation on object") {}
			InvalidOperationException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Failed to perform operation on object", add_info) {}
		};
	}
}

#endif // INVALID_OPERATION_EXCEPTION_H
