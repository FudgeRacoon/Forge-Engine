#ifndef TIMEOUT_EXCEPTION_H
#define TIMEOUT_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class TimeoutException : public Exception
		{
		public:
			TimeoutException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Current operation has timed out") {}
			TimeoutException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Current operation has timed out", add_info) {}
		};
	}
}

#endif // TIMEOUT_EXCEPTION_H
