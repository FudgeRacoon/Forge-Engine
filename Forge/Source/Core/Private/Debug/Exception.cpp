#include "Core/Public/Debug/Exception/Exception.h"

#include <sstream>

#include "Core/Public/RTTI/SmartPointer.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Debug
	{
		Exception::Exception(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr desc)
			: m_line(line), m_func(func), m_file(file), m_additional_info(nullptr)
		{
			ConstCharPtr type_name = GetTypeInfo()->GetTypeName();

			std::stringstream ss;
			ss << "type_name" << ": " << desc << " in '" << func << "' at '" << file << "' (line " << line << ").";
			
			Memory::MemoryCopy(m_description, const_cast<CharPtr>(ss.str().c_str()), ss.str().size());
		}
		Exception::Exception(ConstCharPtr line, ConstCharPtr func, ConstCharPtr file, ConstCharPtr desc, ConstCharPtr add_info)
			: m_line(line), m_file(file), m_func(func), m_additional_info(add_info)
		{
			ConstCharPtr type_name = GetTypeInfo()->GetTypeName();

			std::stringstream ss;
			ss << "type_name" << ": " << desc << " in '" << func << "' at '" << file << "' (line " << line << "). " << m_additional_info << ".";

			Memory::MemoryCopy(m_description, const_cast<CharPtr>(ss.str().c_str()), ss.str().size());
		}
	
		TSharedPtr<Object> Exception::Clone(void)
		{
			return TSharedPtr<Object>();
		}
		TSharedPtr<Object> Exception::Clone(AbstractAllocator* allocator)
		{
			return TSharedPtr<Object>();
		}
	}
}