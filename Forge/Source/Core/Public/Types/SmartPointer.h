#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "Core/Public/RTTI/RefCounter.h"

#include "Core/Public/CoreFwd.h"

#include "Core/Public/Debug/Debug.h"

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

using namespace Forge::Common;

namespace Forge {
	namespace RTTI
	{
		/**
		 * @brief Manages the storage of raw pointers, provides garbage-collection,
		 * and allows multiple TSharedPtr to share management of the same pointer.
		 * This ultimatly prevents accidental memory leaks and helps in monitoring
		 * shared memory locations.
		 * 
		 * Objects of TSharedPtr have the ability of taking ownership of a pointer
		 * and sharing that ownership. Upon taking ownership, a reference counter 
		 * is incremented indicating the number of TSharedPtr objects managing the
		 * pointer. 
		 * 
		 * When a TSharedPtr is destroyed the reference counter is decremented.
		 * A TSharedPtr becomes responsible for the deletion of the stored pointer
		 * when it is the last object to release ownership.
		 * 
		 * @author Karim Hisham
		 */
		template<typename T>
		class TSharedPtr
		{
		private:
			using ValueType         = T;
			using ValueTypeRef      = T&;
			using ValueTypePtr      = T*;
			using ConstValueType    = const T;
			using ConstValueTypeRef = const T&;
 			using ConstValueTypePtr = const T*;

		private:
			using DeleterCallback = Void(*)(ValueTypePtr);

		private:
			ValueTypePtr    m_raw_ptr;
			DeleterCallback m_deleter_callback;

		public:
			TSharedPtr(void)
				: m_raw_ptr(nullptr) 
			{
				m_deleter_callback = [](ValueTypePtr ptr) -> Void
				{
					// delete ptr;
					return;
				};
			}
			TSharedPtr(ValueTypePtr ptr)
				: m_raw_ptr(ptr)
			{
				

				m_deleter_callback = [](ValueTypePtr ptr) -> Void
				{
					// delete ptr;
					return;
				};
			}
			TSharedPtr(ValueTypePtr ptr, DeleterCallback del)
				: m_raw_ptr(nullptr), m_deleter_callback(del) 
			{
				
			}
		   
		public:
			TSharedPtr(TWeakPtr<ValueType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;
			}
			TSharedPtr(TSharedPtr<ValueType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;
			}
			TSharedPtr(const TWeakPtr<ValueType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
			}
			TSharedPtr(const TSharedPtr<ValueType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
			}

		public:
			~TSharedPtr()
			{
				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);
			}

		public:
			TSharedPtr<ValueType>& operator =(ValueTypePtr ptr)
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
			TSharedPtr<ValueType>& operator =(TWeakPtr<ValueType>&& rhs)
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
			TSharedPtr<ValueType>& operator =(TSharedPtr<ValueType>&& rhs)
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
			TSharedPtr<ValueType>& operator =(const TWeakPtr<ValueType>& rhs)
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
			TSharedPtr<ValueType>& operator =(const TSharedPtr<ValueType>& rhs)
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
			ValueTypeRef operator *()
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/

				return *m_raw_ptr;
			}

		public:
			ValueTypePtr operator ->()
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/

				return m_raw_ptr;
			}
		
		public:
			/**
			 * @brief Gets the number of TSharedPtr objects that share ownership
			 * over the same stored pointer including itself.
			 * 
			 * @return Number of refrences to the stored pointer.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			ConstSize GetRefCount(void)
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/
				
				return m_raw_ptr->GetRefCount();
			}

			/**
			 * @brief Gets the stored pointer owned by the TSharedPtr object. Avoid
			 * manually deleting the stored pointer as this will causes errors. 
			 * 
			 * @return Address of the stored pointer.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			ValueTypePtr GetRawPtr(void)
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/

				return m_raw_ptr;
			}

		public:
			/**
			 * @brief Checks whether the shared pointer does not share ownership
			 * over its pointer with other shared pointers.
			 *
			 * @return True if the TShartedPtr object is unique.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			Bool IsUnique(void)
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/

				return true ? m_raw_ptr->GetRefCount() == 1 : false;
			}

			/**
			 * @brief Checks whether the stored pointer is not a null pointer.
			 * 
			 * @return True if the stored pointer is not null.
			 */
			Bool IsNotNull(void)
			{
				if (m_raw_ptr)
					return true;

				return false;
			}

		public:
			/**
			 * @brief Exchanges the contents of the TSharedPtr object with the other,
			 * without altering the reference count of either or destroying them.
			 * 
			 * @param[in] other The TSharedPtr object to swap content with.
			 */
			Void Swap(TSharedPtr<ValueType>& other)
			{
				ValueTypePtr temp = other.m_raw_ptr;
				other.m_raw_ptr = m_raw_ptr;
				m_raw_ptr = temp;
			}

			/**
			 * @brief Resets the raw pointer to null by default, or sets a new ownership of 
			 * the pointer passed and releases ownership of the old pointer.
			 * 
			 * @param[in] ptr The new pointer that will be owned by the TSharedPtr object.
			 */
			Void Reset(ValueTypePtr ptr = nullptr)
			{
				if (ptr)
					ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = ptr;
			}
		};

		/**
		 * @brief Manages the storage of raw pointers, by holding non-owning 
		 * "weak" references to data managed by TSharedPtr. Unlike TSharedPtr it 
		 * does not provide garabge-collection. 
		 * 
		 * TWeakPtr models temporary ownership, allowing data to be accessed only 
		 * if it exists, and may be deleted at any time. 
		 * 
		 * TWeakPtr is used to track the object, and is converted to TSharedPtr 
		 * to assume temporary ownership and access the data. If the original 
		 * TSharedPtr object is destroyed at this time, the object's lifetime 
		 * is extended until the temporary TSharedPtr is destroyed as well.
		 * 
		 * @author Karim Hisham
		 */
		template<typename T>
		class TWeakPtr
		{
		private:
			using ValueType         = T;
			using ValueTypeRef      = T&;
			using ValueTypePtr      = T*;
			using ConstValueType    = const T;
			using ConstValueTypeRef = const T&;
			using ConstValueTypePtr = const T*;

		private:
			ValueTypePtr m_raw_ptr;

		public:
			TWeakPtr(void)
				: m_raw_ptr(nullptr) 
			{
				
			}
			TWeakPtr(ValueTypePtr ptr)
				: m_raw_ptr(ptr) 
			{
				
			}

		public:
			TWeakPtr(TWeakPtr<ValueType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;
			}
			TWeakPtr(TSharedPtr<ValueType>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;
			}
			TWeakPtr(const TWeakPtr<ValueType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
			}
			TWeakPtr(const TSharedPtr<ValueType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;
			}

		public:
			~TWeakPtr()
			{
				m_raw_ptr->DecrementWeakRef();
			}

		public:
			TWeakPtr<ValueType>& operator =(ValueTypePtr ptr)
			{
				if (m_raw_ptr == ptr)
					return *this;

				if (ptr)
					ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = ptr;

				return *this;
			}
			TWeakPtr<ValueType>& operator =(TWeakPtr<ValueType>&& rhs)
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
			TWeakPtr<ValueType>& operator =(TSharedPtr<ValueType>&& rhs)
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
			TWeakPtr<ValueType>& operator =(const TWeakPtr<ValueType>& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				if (rhs.m_raw_ptr)
					rhs.m_raw_ptr->IncrementWeakRef();

				m_raw_ptr->DecrementWeakRef();

				m_raw_ptr = rhs.m_raw_ptr;

				return *this;
			}
			TWeakPtr<ValueType>& operator =(const TSharedPtr<ValueType>& rhs)
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
			/**
			 * @brief Gets the number of TSharedPtr objects that share ownership
			 * over the same stored pointer. TWeakPtr objects are not counted.
			 *
			 * @return Number of refrences to the stored pointer.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			ConstSize GetRefCount(void)
			{
				/*if (!m_raw_ptr)
					FORGE_EXCEPT(Debug::Exception::ERR_INVALID_OPERATION_EXCEPTION, "Shared pointer is storing a null pointer")*/

				return m_raw_ptr->GetRefCount();
			}

		public:
			/**
			 * @brief Checks whether the TWeakPtr object is either empty or there
			 * are no more TSharedPtr referencing the stored pointer.
			 * 
			 * @return True if no more TSharedPtr are referencing the stored 
			 * pointer and has been deallocated or the TWeakPtr object is empty.
			 */
			Bool IsExpired(void)
			{
				return !m_raw_ptr || GetRefCount() == 0;
			}

			/**
			 * @brief Checks whether the stored pointer is not a null pointer.
			 *
			 * @return True if the stored pointer is not null.
			 */
			Bool IsNotNull(void)
			{
				if (m_raw_ptr)
					return true;

				return false;
			}

		public:
			/**
			 * @brief Locks the stored pointer and prevents it from being released.
			 * 
			 * @return TSharedPtr with the information preserved by the TWeakPtr
			 * object if it is not expired. If the TWeakPtr object has expired, 
			 * the function returns an empty TSharedPtr.
			 */
			TSharedPtr<ValueType> Lock(void)
			{
				if (IsExpired())
					return TSharedPtr<ValueType>();
				
				return TSharedPtr<ValueType>(m_raw_ptr);
			}

		public:
			/**
			 * @brief Exchanges the contents of the TWeakPtr object with the other,
			 * without altering the weak reference count of either or destroying them.
			 *
			 * @param[in] other The TWeakPtr object to swap content with.
			 */
			Void Swap(TWeakPtr<ValueType>& other)
			{
				ValueTypePtr temp = other.m_raw_ptr;
				other.m_raw_ptr = m_raw_ptr;
				m_raw_ptr = temp;
			}

			/**
			 * @brief Resets the TWeakPtr and makes it empty.
			 */
			Void Reset()
			{
				m_raw_ptr = nullptr;
			}
		};
	}
}

#endif // SMART_POINTER_H
