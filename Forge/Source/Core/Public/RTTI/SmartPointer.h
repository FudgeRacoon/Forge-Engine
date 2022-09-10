#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "Object.h"

#include "Core/Public/Common/Common.h"

#include "Core/Public/Memory/Memory.h"

#include "Core/Public/Debug/Exception/ExceptionFactory.h"

namespace Forge {
	namespace RTTI
	{
		template<typename T, Bool IsObject = Common::IsBaseOf<T, Object>::Value>
		class FORGE_API TSharedPtr {};

		template<typename T>
		class FORGE_API TSharedPtr<T, true>
		{
		private:
			using ObjectType         = T;
			using ObjectTypeRef      = T&;
			using ObjectTypePtr      = T*;
			using ConstObjectType    = const T;
			using ConstObjectTypeRef = const T&;
 			using ConstObjectTypePtr = const T*;

		private:
			using DeleterCallback = Void(*)(ObjectTypePtr);

		private:
			ObjectTypePtr   m_raw_ptr;
			DeleterCallback m_deleter_callback;

		public:
			TSharedPtr(void);
			TSharedPtr(ObjectTypePtr ptr);
			TSharedPtr(ObjectTypePtr ptr, DeleterCallback del);
		   
		public:
			TSharedPtr(TWeakPtr<ObjectType>&& rhs);
			TSharedPtr(TSharedPtr<ObjectType>&& rhs);
			TSharedPtr(const TWeakPtr<ObjectType>& rhs);
			TSharedPtr(const TSharedPtr<ObjectType>& rhs);

		public:
			~TSharedPtr();

		public:
			TSharedPtr<ObjectType>& operator =(ObjectTypePtr ptr)
			{
				if (m_raw_ptr == ptr)
					return *this;

				if (ptr)
					ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = ptr;

				return *this;
			}
			TSharedPtr<ObjectType>& operator =(TWeakPtr<ObjectType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
				{
					rhs.m_raw_ptr->IncrementRef();
					rhs.m_raw_ptr->DecrementWeakRef();
				}

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}
			TSharedPtr<ObjectType>& operator =(TSharedPtr<ObjectType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}
			TSharedPtr<ObjectType>& operator =(const TWeakPtr<ObjectType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
				{
					rhs.m_raw_ptr->IncrementRef();
					rhs.m_raw_ptr->DecrementWeakRef();
				}

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;

				return *this;
			}
			TSharedPtr<ObjectType>& operator =(const TSharedPtr<ObjectType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				
				return *this;
			}

		public:
			ObjectTypeRef operator *()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")

				return *m_raw_ptr;
			}
			ObjectTypePtr operator ->()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")

				return m_raw_ptr;
			}
		
		public:
			/// @brief Returns the number of shared pointers that share 
			/// ownership over the same stored pointer including itself.
			ConstSize GetRefCount(void);

			/// @brief Gets the stored pointer owned by the shared pointer.
			ObjectTypePtr GetRawPtr(void);

		public:
			/// @brief Checks whether the shared pointer does not share ownership 
			/// over its pointer with other shared pointers.
			Bool IsUnique(void);

			/// @brief Checks whether the stored pointer is not anull pointer.
			Bool IsNotNull(void);

		public:
			/// @brief Exchanges the contents of the shared pointer with the other,
			/// without altering the reference count of either.
			Void Swap(TSharedPtr<ObjectType>& other);

			/// @brief Resets the raw pointer to null by default, or sets a new
			/// ownership of the pointer passed and deletes reference to the old pointer.
			Void Reset(ObjectTypePtr ptr = nullptr);
		};

		template<typename T, Bool IsObject = Common::IsBaseOf<T, Object>::Value>
		class FORGE_API TWeakPtr {};

		template<typename T>
		class FORGE_API TWeakPtr<T, true>
		{
		private:
			using ObjectType = T;
			using ObjectTypeRef = T&;
			using ObjectTypePtr = T*;
			using ConstObjectType = const T;
			using ConstObjectTypeRef = const T&;
			using ConstObjectTypePtr = const T*;

		private:
			using DeleterCallback = Void(*)(ObjectTypePtr);

		private:
			ObjectTypePtr m_raw_ptr;

		public:
			TWeakPtr(void);
			TWeakPtr(ObjectTypePtr ptr);

		public:
			TWeakPtr(TWeakPtr<ObjectType>&& rhs);
			TWeakPtr(TSharedPtr<ObjectType>&& rhs);
			TWeakPtr(const TWeakPtr<ObjectType>& rhs);
			TWeakPtr(const TSharedPtr<ObjectType>& rhs);

		public:
			~TWeakPtr();

		public:
			TWeakPtr<ObjectType>& operator =(ObjectTypePtr ptr)
			{
				if (m_raw_ptr == ptr)
					return *this;

				if (ptr)
					ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = ptr;

				return *this;
			}
			TWeakPtr<ObjectType>& operator =(TWeakPtr<ObjectType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();
				
				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}
			TWeakPtr<ObjectType>& operator =(TSharedPtr<ObjectType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}
			TWeakPtr<ObjectType>& operator =(const TWeakPtr<ObjectType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;

				return *this;
			}
			TWeakPtr<ObjectType>& operator =(const TSharedPtr<ObjectType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;

				return *this;
			}

		public:
			ObjectTypeRef operator *()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")

				return *m_raw_ptr;
			}
			ObjectTypePtr operator ->()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")

				return m_raw_ptr;
			}

		public:
			/// @brief Returns the number of weak pointers that share 
			/// ownership over the same stored pointer including itself.
			ConstSize GetRefCount(void);

		public:
			/// @brief Checks whether no shared pointer share ownership 
			/// over the stored pointer anymore.
			Bool IsExpired(void);

			/// @brief Checks whether the stored pointer is not a null pointer.
			Bool IsNotNull(void);

		public:
			/// @brief Exchanges the contents of the shared pointer with the other,
			/// without altering the reference count of either.
			Void Swap(TSharedPtr<ObjectType>& other);

			/// @brief Resets the stored pointer to null by default, or sets a new
			/// ownership of the pointer passed and deletes reference to the old pointer.
			Void Reset(ObjectTypePtr ptr = nullptr);
		};
	}
}

#endif // SMART_POINTER_H
