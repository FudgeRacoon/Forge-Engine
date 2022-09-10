#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include "Core/Public/Common/Common.h"

#include "Core/Public/Math/StringHash.h"

using namespace Forge::Math;

namespace Forge {
	namespace RTTI
	{
		using TypeInfoRef	   = TypeInfo&;
		using TypeInfoPtr      = TypeInfo*;
		using ConstTypeInfo    = const TypeInfo;
		using ConstTypeInfoRef = const TypeInfo&;
		using ConstTypeInfoPtr = const TypeInfo*;

		/// @brief The type info class stores meta-information about classes.
		class FORGE_API TypeInfo
		{
		private:
			ConstSize		  m_type_size;
			ConstCharPtr      m_type_name;
			ConstStringHash	  m_type_hash_id;
			ConstTypeInfoPtr  m_base_type_info;
		
		public:
			TypeInfo(ConstCharPtr type_name, Size type_Size, TypeInfoPtr base_type_info);
		   ~TypeInfo() = default;

		public:
			/// @brief Get the Size of the type in bytes.
			ConstSize GetTypeSize(void);

			/// @brief Get the name of the type.
			ConstCharPtr GetTypeName(void);

			/// @brief Get the ID of the type.
			ConstStringHash GetTypeId(void);

			/// @brief Get the base type of the type, nullptr if has no base type.
			ConstTypeInfoPtr GetBaseTypeInfo(void);

		public:
			/// @brief Check whether the current type is of specified type.
			Bool IsSameAs(ConstStringHash& type_id);

			/// @brief Check wether the current type is derived from the specified type.
			Bool IsDerivedFrom(ConstStringHash& type_id);
			
			/// @brief Check whether the current type is of specified type.
			Bool IsSameAs(ConstTypeInfoPtr type_info);

			/// @brief Check wether the current type is derived from the specified type.
			Bool IsDerivedFrom(ConstTypeInfoPtr type_info);
		};

		FORGE_FORCE_INLINE ConstSize TypeInfo::GetTypeSize(void)            { return m_type_size; }
		FORGE_FORCE_INLINE ConstCharPtr TypeInfo::GetTypeName(void)         { return m_type_name; }
		FORGE_FORCE_INLINE ConstStringHash TypeInfo::GetTypeId(void)		{ return m_type_hash_id; }
		FORGE_FORCE_INLINE ConstTypeInfoPtr TypeInfo::GetBaseTypeInfo(void) { return m_base_type_info; }
	}
}

#endif // TYPE_INFO_H
