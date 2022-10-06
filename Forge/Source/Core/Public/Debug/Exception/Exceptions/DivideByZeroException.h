#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include "../Exception.h"

namespace Forge {
	namespace Debug
	{
		class DivideByZeroException : public Exception
		{
		public:
			DivideByZeroException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Cannot divide by zero") {}
			DivideByZeroException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Cannot divide by zero", add_info) {}
		};
	}
}

#endif // DIVIDE_BY_ZERO_EXCEPTION_H