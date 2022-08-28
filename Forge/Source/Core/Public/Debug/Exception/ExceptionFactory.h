#ifndef EXCEPTION_FACTORY_H
#define EXCEPTION_FACTORY_H

#include "Exceptions.h"

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Debug
	{
		class FORGE_API ExceptionFactory
		{
		public:
			ExceptionFactory() = default;
		   ~ExceptionFactory() = default;

		public:
			VOID ThrowException(Exception::EXCEPTION_CODE code, PCCHAR line, PCCHAR func, PCCHAR file);
			VOID ThrowException(Exception::EXCEPTION_CODE code, PCCHAR line, PCCHAR func, PCCHAR file, PCCHAR add_info);
		};
	}
}

#endif // EXCEPTION_FACTORY_H
