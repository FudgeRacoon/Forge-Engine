#ifndef EXCEPTION_FACTORY_H
#define EXCEPTION_FACTORY_H

#include "Exceptions/IOException.h"
#include "Exceptions/TimeoutException.h"
#include "Exceptions/FileNotFoundException.h"
#include "Exceptions/DivideByZeroException.h"
#include "Exceptions/BadAllocationException.h"
#include "Exceptions/IndexOutOfRangeException.h"
#include "Exceptions/InvalidOperationException.h"
#include "Exceptions/MemoryOutOfBoundsException.h"

#include "Core/Public/CoreFwd.h"

#include "Core/Public/RTTI/Object.h"

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Debug
	{
		class FORGE_API ExceptionFactory
		{
		public:
			ExceptionFactory() = default;
		   ~ExceptionFactory() = default;

		public:
			Void ThrowException(Exception::EXCEPTION_CODE code, ConstCharPtr line, ConstCharPtr func, ConstCharPtr file);
			Void ThrowException(Exception::EXCEPTION_CODE code, ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info);
		};

		#define FORGE_EXCEPT_1(__CODE__) static Debug::ExceptionFactory e; \
			e.ThrowException(__CODE__, FORGE_LINE_LITERAL, FORGE_FUNC_LITERAL, FORGE_FILE_LITERAL); 
		#define FORGE_EXCEPT_2(__CODE__, __ADD_INFO__) static Debug::ExceptionFactory e; \
			e.ThrowException(__CODE__, FORGE_LINE_LITERAL, FORGE_FUNC_LITERAL, FORGE_FILE_LITERAL, __ADD_INFO__);

		#define FORGE_EXCEPT_CHOOSER(__ARG_1__, __ARG_2__, __NAME__, ...) __NAME__

		#define FORGE_EXCEPT_EXPAND(x) x
		#define FORGE_EXCEPT(...) FORGE_EXCEPT_EXPAND(FORGE_EXCEPT_CHOOSER(__VA_ARGS__, FORGE_EXCEPT_2, FORGE_EXCEPT_1) (__VA_ARGS__))
	}
}

#endif // EXCEPTION_FACTORY_H
