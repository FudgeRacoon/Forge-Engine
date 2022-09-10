#include "Core/Public/RTTI/TypeInfo.h"

namespace Forge {
	namespace RTTI
	{
		TypeInfo::TypeInfo(ConstCharPtr type_name, Size type_size, TypeInfoPtr base_type_info)
			: m_type_name(m_type_name), m_type_size(type_size), m_base_type_info(base_type_info)
		{
			/// Compute type ID
		}

		Bool TypeInfo::IsSameAs(ConstStringHash& type_id)
		{
			return false;
		}
		Bool TypeInfo::IsDerivedFrom(ConstStringHash& type_id)
		{
			return false;
		}
		Bool TypeInfo::IsSameAs(ConstTypeInfoPtr type_info)
		{
			return this == type_info;
		}
		Bool TypeInfo::IsDerivedFrom(ConstTypeInfoPtr type_info)
		{
			if (!type_info)
				return false;

			ConstTypeInfoPtr current = this;
			
			while (current)
			{
				if (current == type_info)
					return true;

				current = current->m_base_type_info;
			}

			return false;
		}
	}
}
