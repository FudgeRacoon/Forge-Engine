#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class DivideByZeroException : public Exception
		{
		public:
			DivideByZeroException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Cannot divide by zero") {}

			DivideByZeroException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Cannot divide by zero", add_info) {}
		};
	}
}

#endif // DIVIDE_BY_ZERO_EXCEPTION_H