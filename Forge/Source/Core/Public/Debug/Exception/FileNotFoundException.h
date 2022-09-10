#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class FileNotFoundException : public Exception
		{
		public:
			FileNotFoundException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
				: Exception(line, func, file, "Failed to find file") {}
			FileNotFoundException(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
				: Exception(line, func, file, "Failed to find file", add_info) {}
		};
	}
}

#endif // FILE_NOT_FOUND_EXCEPTION_H
