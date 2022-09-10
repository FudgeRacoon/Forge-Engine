#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

#include "Core//Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Debug
	{
		/// @brief An exception is used to provide information about
		/// errors that occured in the engine.
		class FORGE_API Exception
		{
		protected:
			ConstCharPtr m_line;
			ConstCharPtr m_func;
			ConstCharPtr m_file;
			ConstCharPtr m_additional_info;

		protected:
			Char m_description[256] = { 0 };

		public:
			enum EXCEPTION_CODE
			{
				ERR_IO_EXCEPTION,
				ERR_TIMEOUT_EXCEPTION,
				ERR_ARGUMENT_EXCEPTION,
				ERR_ARGUMENT_NULL_EXCEPTION,
				ERR_DIVIDE_BY_ZERO_EXCEPTION,
				ERR_FILE_NOT_FOUND_EXCEPTION,
				ERR_BAD_ALLOCATION_EXCEPTION,
				ERR_INDEX_OUT_RANGE_EXCEPTION,
				ERR_INVALID_OPERATION_EXCEPTION,
				ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION
			};

		public:
			Exception(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr desc);
			Exception(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr desc, ConstCharPtr add_info);
			virtual ~Exception() = default;

		public:
			/// @brief Gets the source line number.
			ConstCharPtr GetLine();

			/// @brief Gets the source function name.
			ConstCharPtr GetFunc();

			/// @brief Gets the source file name.
			ConstCharPtr GetFile();

			/// @brief Gets additional information about the exception.
			ConstCharPtr GetAdditionalInfo();

		public:
			/// @brief Gets the description of the exception.
			/// 
			/// The description contains the cause, the line number, 
			/// file name, what function threw the error and additional
			/// information if provided by the user.
			ConstCharPtr GetDescripton();
		};

		FORGE_FORCE_INLINE ConstCharPtr Exception::GetLine()           { return m_line; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetFunc()           { return m_func; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetFile()           { return m_file; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetAdditionalInfo() { return m_additional_info; }

		FORGE_FORCE_INLINE ConstCharPtr Exception::GetDescripton() { return m_description; }
	}
}

#endif // EXCEPTION_H
