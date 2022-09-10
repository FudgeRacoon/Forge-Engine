#ifndef OBJECT_H
#define OBJECT_H

#include "TypeInfo.h"
#include "RefCounter.h"

#include "Core/Public/Common/Common.h"
#include "Core/Public/Memory/Memory.h"

using namespace Forge::Memory;

namespace Forge {
	namespace RTTI
	{
		using ObjectRef		 = Object&;
		using ObjectPtr      = Object*;
		using ConstObject    = const Object;
		using ConstObjectRef = const Object&;
		using ConstObjectPtr = const Object*;

		/// @brief Base class for classes with run-time type information. This class is reference-counted.
		class FORGE_API Object : public RefCounted
		{
		private:
			Object() = default;
		   ~Object() = default;
		
		public:
			/// @brief Gets the run-time type info of this object.
			/// 
			/// @returns Const raw pointer to the class type information.
			static ConstTypeInfoPtr GetTypeInfo(void);

		public:
			/// @brief Creates and returns a copy of this object.
			///
			/// @returns Raw pointer to the cloned object.
			virtual ObjectPtr Clone(void) = 0;

			/// @brief Creates and returns a copy of this object using an allocator.
			/// 
			/// @returns Raw pointer to the cloned object.
			virtual ObjectPtr Clone(AbstractAllocator& allocator) = 0;

		public:
			/// @brief Check whether the current type is of specified type.
			Bool IsInstanceOf(ConstStringHash type_id) const;

			/// @brief Check whether the current type is of specified type.
			Bool IsInstanceOf(ConstTypeInfoPtr type_info) const;

		public:
			/// @brief Casts the object to the class specified staticly.
			/// 
			/// @returns Raw pointer to the class specified.
			template<typename T> 
			T* StaticCast(void)
			{
				return (T*)this;
			}

			/// @brief Casts the object to the class specified dynamically.
			/// 
			/// @returns Raw pointer to the class specified, or nullptr if not derived from it.
			template<typename T> 
			T* DynamicCast(void)
			{
				if (this->IsInstanceOf(T::GetTypeInfoStatic()))
					return (T*)this;
				
				return nullptr;
			}

			/// @brief Casts the object to the class specified staticly.
			/// 
			/// @returns Const raw pointer to the class specified.
			template<typename T> 
			const T* StaticCastConst(void)
			{
				return (const T*)this;
			}

			/// @brief Casts the object to the class specified dynamically.
			/// 
			/// @returns Const raw pointer to the class specified, or nullptr if not derived from it.
			template<typename T> 
			const T* DynamicCastConst(void)
			{
				if (this->IsInstanceOf(T::GetTypeInfoStatic()))
					return (const T*)this;

				return nullptr;
			}
		};

		#define FORGE_DECLARE_TYPEINFO(__TYPENAME__, __BASE_TYPENAME__)	\
			using ClassName     = __TYPENAME__;							\
			using BaseClassName = __BASE_TYPENAME__;					\
			static ConstTypeInfoPtr GetTypeInfo(void) { static TypeInfo static_type_info(#__TYPENAME__, sizeof(ClassName), BaseClassName::GetTypeInfoStatic()); return &static_type_info; }	
	}
}

#endif // OBJECT_H
