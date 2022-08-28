#ifndef TIMEOUT_EXCEPTION_H
#define TIMEOUT_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class TimeoutException : public Exception
		{
		public:
			TimeoutException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Current operation has timed out") {}

			TimeoutException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Current operation has timed out", add_info) {}
		};
	}
}

#endif // TIMEOUT_EXCEPTION_H
