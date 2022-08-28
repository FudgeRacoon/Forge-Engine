#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H

#include "Exception.h"

namespace Forge {
	namespace Debug
	{
		class FileNotFoundException : public Exception
		{
		public:
			FileNotFoundException(PCCHAR line, PCCHAR func, PCCHAR file)
				: Exception(line, func, file, "Failed to find file") {}

			FileNotFoundException(PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info)
				: Exception(line, func, file, "Failed to find file", add_info) {}
		};
	}
}

#endif // FILE_NOT_FOUND_EXCEPTION_H
