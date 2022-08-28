#ifndef INVALID_OPERATION_EXCEPTION_H
#define INVALID_OPERATION_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class InvalidOperationException : public Exception
		{
		public:
			InvalidOperationException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Failed to perform operation on object") {}

			InvalidOperationException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Failed to perform operation on object", add_info) {}
		};
	}
}

#endif // INVALID_OPERATION_EXCEPTION_H
