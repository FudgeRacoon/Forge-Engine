#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Core/Public/CoreFwd.h"

#include "Core/Public/RTTI/Object.h"

#include "Core/Public/Common/Common.h"

using namespace Forge::RTTI;

namespace Forge {
	namespace Debug
	{
		/**
		 * @brief Provides information about errors that occured in the engine.
		 * 
		 * Forge throws exceptions whenever an error occures, this is the object
		 * that stores the source of the problem and information regarding why the
		 * problem has occured.
		 * 
		 * The user application is advised to always wrap Forge functions within 
		 * try {} catch(Exception& e) {} blocks in order to gracefully handle these
		 * errors.
		 * 
		 * @author Karim Hisham
         */		
		class FORGE_API Exception : public Object
		{
		public:
			FORGE_DECLARE_TYPEINFO(Exception, Object)

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

		public:
			virtual ~Exception() = default;

		public:
			/**
			 * @brief Performs a deep-copy of the object and returns the new
			 * instance.
			 *
			 * @return TSharedPtr object to the cloned object.
			 */
			TSharedPtr<Object> Clone(void) override;

			/**
			 * @brief Performs a deep-copy of the object and returns the new
			 * instance using an allocator.
			 *
			 * @param[in] allocator The allocator used to construct the new object.
			 *
			 * @return TSharedPtr object to the cloned object.
			 */
			TSharedPtr<Object> Clone(AbstractAllocator* allocator) override;

		public:
			/**
			 * @brief Gets the number of the source line where the exception was
			 * thrown.
			 * 
			 * @return ConstCharPtr storing the number of the source line.
			 */
			ConstCharPtr GetLine();

			/**
			 * @brief Gets the name of the source function where the exception was 
			 * thrown.
			 * 
			 * @return ConstCharPtr storing the name of the source function.
			 */
			ConstCharPtr GetFunc();

			/**
			 * @brief Gets the name of the source file where the exception was 
			 * thrown.
			 * 
			 * @return ConstCharPtr storing the name of the source file.
			 */
			ConstCharPtr GetFile();

			/**
			 * @brief Gets additional information about the exception if provided.
			 * 
			 * @return ConstCharPtr storing additional information about the 
			 * exception, or null if no additional information provided. 
			 */
			ConstCharPtr GetAdditionalInfo();

		public:
			/**
			 * @brief Gets the full description of the exception.
			 * 
			 * The description contains the cause, the line number, file name, what
			 * function threw the error and additional information if provided.
			 */
			ConstCharPtr GetDescripton();
		};

		FORGE_FORCE_INLINE ConstCharPtr Exception::GetLine()           { return m_line; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetFunc()           { return m_func; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetFile()           { return m_file; }
		FORGE_FORCE_INLINE ConstCharPtr Exception::GetAdditionalInfo() { if (m_additional_info) return m_additional_info; return nullptr; }

		FORGE_FORCE_INLINE ConstCharPtr Exception::GetDescripton() { return m_description; }
	}
}

#endif // EXCEPTION_H
