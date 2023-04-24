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
			/**
			 * @brief Default constructor.
			 */
			ExceptionFactory(Void) = default;

		public:
			/**
			 * @brief Default destructor.
			 */
		   ~ExceptionFactory(Void) = default;

		public:
			/**
			 * @brief Constructs an exception object, records the location of
			 * where it was called and then throws it.
			 * 
			 * @param type[in]     The type of exception to throw.
			 * @param line[in]     The line where this function was called.
			 * @param file[in]     The file where this function was called.
			 * @param function[in] The function where this function was called.
			 */
			static Void ThrowException(ExceptionType type, ConstCharPtr line, ConstCharPtr file, ConstCharPtr function);

			/**
			 * @brief Constructs an exception object, records the location of
			 * where it was called and then throws it.
			 *
			 * @param type[in]     The type of exception to throw.
			 * @param line[in]     The line where this function was called.
			 * @param file[in]     The file where this function was called.
			 * @param function[in] The function where this function was called.
			 * @param info[in]     The additional info to add to the exception.
			 */
			static Void ThrowException(ExceptionType type, ConstCharPtr line, ConstCharPtr file, ConstCharPtr function, ConstCharPtr info);
		};

		#define FORGE_EXCEPT_1(__TYPE__) \
			Debug::ExceptionFactory::ThrowException(__TYPE__, FORGE_LINE_LITERAL, FORGE_FILE_LITERAL, FORGE_FUNC_LITERAL); 

		#define FORGE_EXCEPT_2(__TYPE__, __INFO__) \
			Debug::ExceptionFactory::ThrowException(__TYPE__, FORGE_LINE_LITERAL, FORGE_FILE_LITERAL, FORGE_FUNC_LITERAL, __INFO__); 

		#define FORGE_EXCEPT_CHOOSER(__ARG_1__, __ARG_2__, __NAME__, ...) __NAME__

		#define FORGE_EXCEPT_EXPAND(x) x

		#define FORGE_EXCEPT(...) FORGE_EXCEPT_EXPAND(FORGE_EXCEPT_CHOOSER(__VA_ARGS__, FORGE_EXCEPT_2, FORGE_EXCEPT_1) (__VA_ARGS__))

	}
}

#endif // EXCEPTION_FACTORY_H
