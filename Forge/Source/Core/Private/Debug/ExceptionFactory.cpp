#include "Core/Public/Debug/Exception/ExceptionFactory.h"

#include "Core/Public/RTTI/SmartPointer.h"

namespace Forge {
	namespace Debug
	{
		Void ExceptionFactory::ThrowException(Exception::EXCEPTION_CODE code, ConstCharPtr line, ConstCharPtr func, ConstCharPtr file)
		{
			switch (code)
			{
				case Exception::ERR_IO_EXCEPTION:				    throw IOException(line, func, file);
				case Exception::ERR_TIMEOUT_EXCEPTION:              throw TimeoutException(line, func, file);
				case Exception::ERR_DIVIDE_BY_ZERO_EXCEPTION:       throw DivideByZeroException(line, func, file);
				case Exception::ERR_FILE_NOT_FOUND_EXCEPTION:	    throw FileNotFoundException(line, func, file);
				case Exception::ERR_BAD_ALLOCATION_EXCEPTION:       throw BadAllocationException(line, func, file);
				case Exception::ERR_INDEX_OUT_RANGE_EXCEPTION:	    throw IndexOutOfRangeException(line, func, file);
				case Exception::ERR_INVALID_OPERATION_EXCEPTION:    throw InvalidOperationException(line, func, file);
				case Exception::ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION: throw MemoryOutOfBoundsException(line, func, file);
				default:                                            throw Exception(line, func, file, "An exception has occured");
			}
		}
		Void ExceptionFactory::ThrowException(Exception::EXCEPTION_CODE code, ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr add_info)
		{
			switch (code)
			{
				case Exception::ERR_IO_EXCEPTION:				    throw IOException(line, func, file, add_info);
				case Exception::ERR_TIMEOUT_EXCEPTION:              throw TimeoutException(line, func, file, add_info);
				case Exception::ERR_DIVIDE_BY_ZERO_EXCEPTION:       throw DivideByZeroException(line, func, file, add_info);
				case Exception::ERR_FILE_NOT_FOUND_EXCEPTION:	    throw FileNotFoundException(line, func, file, add_info);
				case Exception::ERR_BAD_ALLOCATION_EXCEPTION:       throw BadAllocationException(line, func, file, add_info);
				case Exception::ERR_INDEX_OUT_RANGE_EXCEPTION:	    throw IndexOutOfRangeException(line, func, file, add_info);
				case Exception::ERR_INVALID_OPERATION_EXCEPTION:    throw InvalidOperationException(line, func, file, add_info);
				case Exception::ERR_MEMORY_OUT_OF_BOUNDS_EXCEPTION: throw MemoryOutOfBoundsException(line, func, file, add_info);
				default:                                            throw Exception(line, func, file, "An exception has occured", add_info);
			}
		}
	}
}