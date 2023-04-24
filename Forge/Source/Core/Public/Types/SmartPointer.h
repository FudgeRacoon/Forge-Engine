#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "Core/Public/RTTI/RefCounter.h"

#include "Core/Public/CoreFwd.h"

#include <Core/Public/Debug/Debug.h>
#include <Core/Public/Common/Common.h>
#include <Core/Public/Types/TDelegate.h>
#include <Core/Public/Algorithm/GeneralUtilities.h>

using namespace Forge::Common;
using namespace Forge::Algorithm;

namespace Forge {
	namespace Common
	{
		/**
		 * @brief Manages the storage of raw pointers, provides garbage-collection,
		 * and allows multiple TSharedPtr to share management of the same pointer.
		 * This ultimatly prevents accidental memory leaks and helps in monitoring
		 * shared memory locations.
		 * 
		 * Objects of TSharedPtr have the ability of taking ownership of a pointer
		 * and share that ownership. Upon taking ownership, a reference counter 
		 * is incremented indicating the number of TSharedPtr objects managing the
		 * pointer. 
		 * 
		 * When a TSharedPtr is destroyed the reference counter is decremented.
		 * A TSharedPtr becomes responsible for the deletion of the stored pointer
		 * when it is the last object to release ownership.
		 * 
		 * @author Karim Hisham
		 */
		template<typename InType>
		class TSharedPtr final
		{
		public:
			using Type         = InType;
			using TypePtr      = InType*;
			using TypeRef      = InType&;
			using TypeMoveRef  = InType&&;
			using ConstType    = const InType;
			using ConstTypeRef = const InType&;
 			using ConstTypePtr = const InType*;

		private:
			using SelfType         = TSharedPtr<Type>;
			using SelfTypePtr      = TSharedPtr<Type>*;
			using SelfTypeRef      = TSharedPtr<Type>&;
			using SelfTypeMoveRef  = TSharedPtr<Type>&&;
			using ConstSelfType    = const TSharedPtr<Type>;
			using ConstSelfTypeRef = const TSharedPtr<Type>&;
			using ConstSelfTypePtr = const TSharedPtr<Type>*;

		private:
			TypePtr m_raw_ptr;

		private:
			TDelegate<Void(TypePtr)> m_deleter_callback;

		public:
			/**
			 * @brief Default constructor.
			 */
			TSharedPtr(Void)
				: m_raw_ptr(nullptr) 
			{
				m_deleter_callback = [](TypePtr ptr) -> Void
				{
					delete ptr;
					return;
				};
			}

			/**
			 * @brief Pointer constructor.
			 */
			TSharedPtr(TypePtr ptr)
				: m_raw_ptr(ptr)
			{
				m_deleter_callback = [](ValueTypePtr ptr) -> Void
				{
					delete ptr;
					return;
				};
			}
			
			/**
			 * @brief Pointer and Deleter constructor.
			 */
			TSharedPtr(TypePtr ptr, TDelegate<Void(TypePtr)> del)
				: m_raw_ptr(ptr), m_deleter_callback(del) {}
		   
		public:
			/**
			 * @brief Shared pointer move constructor.
			 */
			TSharedPtr(SelfTypeMoveRef rhs)
			{
				*this = Move(rhs);
			}

			/**
			 * @brief Shared pointer copy constructor.
			 */
			TSharedPtr(ConstSelfTypeRef rhs)
			{
				*this = rhs;
			}

			/**
			 * @brief Weak pointer move constructor.
			 */
			TSharedPtr(TWeakPtr<Type>&& rhs)
			{
				*this = Move(rhs);
			}

			/**
			 * @brief Weak pointer copy constructor.
			 */
			TSharedPtr(const TWeakPtr<Type>& rhs)
			{
				*this = rhs;
			}
			
		public:
			/**
			 * @brief Default constructor.
			 */
			~TSharedPtr(Void)
			{
				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);
			}

		public:
			/**
			 * @brief Pointer copy assigment.
			 */
			SelfTypeRef operator =(TypePtr ptr)
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
			
			/**
			 * @brief Shared pointer move assigment.
			 */
			SelfTypeRef operator =(SelfTypeMoveRef rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}
			
			/**
			 * @brief Shared pointer copy assigment.
			 */
			SelfTypeRef operator =(ConstSelfTypeRef rhs)
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

			/**
			 * @brief Weak pointer move assigment.
			 */
			SelfTypeRef operator =(TWeakPtr<Type>&& rhs)
			{
				if (m_raw_ptr == rhs.m_raw_ptr)
					return *this;

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = rhs.m_raw_ptr;
				rhs.m_raw_ptr = nullptr;

				return *this;
			}

			/**
			 * @brief Weak pointer copy assigment.
			 */
			SelfTypeRef operator =(const TWeakPtr<Type>& rhs)
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
			/**
			 * @brief Dereference operator.
			 */
			TypeRef operator *()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(ExceptionType::FORGE_INVALID_OPERATION, "Shared pointer is storing a null pointer")

				return *m_raw_ptr;
			}

		public:
			/**
			 * @brief Arrow operator.
			 */
			TypePtr operator ->()
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(ExceptionType::FORGE_INVALID_OPERATION, "Shared pointer is storing a null pointer")

				return m_raw_ptr;
			}
		
		public:
			/**
			 * @brief Gets the number of TSharedPtr objects that share ownership
			 * over the same stored pointer including itself.
			 * 
			 * @returns ConstSize storing the number of refrences to the stored
			 * pointer.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			ConstSize GetRefCount(Void) const
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(ExceptionType::FORGE_INVALID_OPERATION, "Shared pointer is storing a null pointer")
				
				return m_raw_ptr->GetRefCount();
			}

			/**
			 * @brief Gets the stored pointer owned by the TSharedPtr object. 
			 * 
			 * Avoid manually deleting the stored pointer as this may cause
			 * undefined behaviour. 
			 * 
			 * @returns TypePtr storing the address of the stored pointer.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			TypePtr GetRawPtr(Void)
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(ExceptionType::FORGE_INVALID_OPERATION, "Shared pointer is storing a null pointer")

				return m_raw_ptr;
			}

		public:
			/**
			 * @brief Checks whether the stored pointer is a null pointer.
			 *
			 * @returns True if the stored pointer is null, otherwise false.
			 */
			Bool IsNull(Void) const
			{
				if (!m_raw_ptr)
					return FORGE_TRUE;

				return FORGE_FALSE;
			}

			/**
			 * @brief Checks whether the shared pointer does not share ownership
			 * over its pointer with other shared pointers.
			 *
			 * @returns True if the TShartedPtr object is unique, otherwise false.
			 * 
			 * @throws InvalidOperationException if the stored pointer is null.
			 */
			Bool IsUnique(Void) const
			{
				if (!m_raw_ptr)
					FORGE_EXCEPT(ExceptionType::FORGE_INVALID_OPERATION, "Shared pointer is storing a null pointer")

				return FORGE_TRUE ? m_raw_ptr->GetRefCount() == 1 : FORGE_FALSE;
			}

		public:
			/**
			 * @brief Swaps the content of the TSharedPtr object with the other,
			 * without altering the reference count of either or destroying them.
			 * 
			 * @param[in] other The TSharedPtr object to swap content with.
			 */
			Void Swap(SelfTypeRef other)
			{
				Algorithm::Swap(this, other);
			}

			/**
			 * @brief Resets the raw pointer to null by default, or sets a new ownership of 
			 * the pointer passed and releases ownership of the old pointer.
			 * 
			 * @param[in] ptr The new pointer that will be owned by the TSharedPtr object.
			 */
			Void Reset(TypePtr ptr = nullptr)
			{
				if (ptr)
					ptr->IncrementRef();

				m_raw_ptr->DecrementRef();

				if (!m_raw_ptr->GetRefCount())
					m_deleter_callback(m_raw_ptr);

				m_raw_ptr = ptr;
			}
		};

		FORGE_TYPEDEF_TEMPLATE_DECL(TSharedPtr)

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
		template<typename InType>
		class TWeakPtr final
		{
		public:
			using Type         = InType;
			using TypePtr      = InType*;
			using TypeRef      = InType&;
			using TypeMoveRef  = InType&&;
			using ConstType    = const InType;
			using ConstTypeRef = const InType&;
			using ConstTypePtr = const InType*;

		private:
			using SelfType         = TWeakPtr<Type>;
			using SelfTypePtr      = TWeakPtr<Type>*;
			using SelfTypeRef      = TWeakPtr<Type>&;
			using SelfTypeMoveRef  = TWeakPtr<Type>&&;
			using ConstSelfType    = const TWeakPtr<Type>;
			using ConstSelfTypeRef = const TWeakPtr<Type>&;
			using ConstSelfTypePtr = const TWeakPtr<Type>*;

		private:
			TypePtr m_raw_ptr;

		public:
			TWeakPtr(Void)
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
			ConstSize GetRefCount(Void)
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
			Bool IsExpired(Void)
			{
				return !m_raw_ptr || GetRefCount() == 0;
			}

			/**
			 * @brief Checks whether the stored pointer is not a null pointer.
			 *
			 * @return True if the stored pointer is not null.
			 */
			Bool IsNotNull(Void)
			{
				if (m_raw_ptr)
					return FORGE_TRUE;

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
			TSharedPtr<ValueType> Lock(Void)
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
