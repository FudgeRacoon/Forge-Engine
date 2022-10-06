#ifndef IO_EXCEPTION_H
#define IO_EXCEPTION_H

#include "../Exception.h"

namespace Forge {
	namespace Debug
	{
		class IOException : public Exception
		{
		public:
			IOException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file) 
				: Exception(line, func, file, "Failed to perform I/O operation") {}
			IOException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Failed to perform I/O operation", add_info) {}
		};
	}
}

#endif // IO_EXCEPTION_H
