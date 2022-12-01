#ifndef T_UNIQUE_PTR_H
#define T_UNIQUE_PTR_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Containers
	{
		namespace Internal
		{
			template<typename InDataType>
			Void UnqiuePtrDeleter(InDataType* raw_ptr) { delete raw_ptr; raw_ptr = nullptr; }
		}

		template<typename InDataType, typename DeleterCallback = Void(*)(InDataType*)>
		class TUniquePtr
		{
		private:
			using DataType         = InDataType;
			using DataTypeRef      = InDataType&;
			using DataTypePtr      = InDataType*;
			using ConstDataType    = const InDataType;
			using ConstDataTypeRef = const InDataType&;
			using ConstDataTypePtr = const InDataType*;

		private:
			DataTypePtr m_raw_ptr;
			DeleterCallback m_deleter;

		public:
			TUniquePtr(void)
				: m_raw_ptr(nullptr), m_deleter(Internal::UnqiuePtrDeleter) {}
			TUniquePtr(DataTypePtr raw_ptr)
				: m_raw_ptr(raw_ptr), m_deleter(Internal::UnqiuePtrDeleter) {}
			TUniquePtr(DataTypePtr raw_ptr, DeleterCallback deleter)
				: m_raw_ptr(raw_ptr), m_deleter(deleter) {}

		public:
			TUniquePtr(TUniquePtr<DataType>&& rhs)
			{
				rhs.Swap(*this);
			}
			TUniquePtr(const TUniquePtr<DataType>& rhs)
			{
				rhs.Swap(*this);
			}

		public:
			template<typename OtherDataType>
			TUniquePtr(TUniquePtr<OtherDataType>&& rhs)
			{
				DataTypePtr temp = rhs.m_raw_ptr;
			}
			template<typename OtherDataType>
			TUniquePtr(const TUniquePtr<OtherDataType>& rhs)
			{

			}
		
		public:
			~TUniquePtr()
			{
				this->m_deleter(this->m_raw_ptr);
			}
		
		public:
			TUniquePtr<DataType>& operator =(TUniquePtr<DataType>&& rhs)
			{
				rhs.Swap(*this);

				return *this;
			}
			TUniquePtr<DataType>& operator =(const TUniquePtr<DataType>& rhs)
			{
				rhs.Swap(*this);

				return *this;
			}
		
		public:
			DataTypeRef operator *()
			{
				return *(this->m_raw_ptr);
			}
			
		public:
			DataTypePtr operator ->()
			{
				return this->m_raw_ptr;
			}

		public:
			Bool operator <(const TUniquePtr<DataType>& rhs) const
			{

			}
			Bool operator >(const TUniquePtr<DataType>& rhs) const
			{

			}
			Bool operator <=(const TUniquePtr<DataType>& rhs) const
			{

			}
			Bool operator >=(const TUniquePtr<DataType>& rhs) const
			{

			}
			Bool operator ==(const TUniquePtr<DataType>& rhs) const
			{

			}
			Bool operator !=(const TUniquePtr<DataType>& rhs) const
			{

			}

		public:
			DataTypePtr GetRawPtr(void) const
			{
				return this->m_raw_ptr;
			}

		public:
			/**
			 * @brief Swaps the content of the TUniquePtr object with the other,
			 * transferring ownership of the managed pointers between them without
			 * destroying either.
			 *
			 * @param[in] other The TSharedPtr object to swap content with.
			 */
			Void Swap(TUniquePtr<DataType>& other)
			{
				DataTypePtr temp = other.m_raw_ptr;
				other.m_raw_ptr = this->m_raw_ptr;
				this->m_raw_ptr = temp;
			}

			/**
			 * @brief Resets the TUniquePtr object to a new ownership of the
			 * pointer passed and deletes the previously owned pointer.
			 *
			 * @param[in] ptr The new pointer that will be owned by the TUniquePtr
			 * object.
			 *
			 * @throws InvalidArgumentException if the passed pointer is null.
			 */
			Void Reset(DataTypePtr ptr)
			{
				if (!ptr); // Throw Exception

				this->m_deleter(this->m_raw_ptr);

				this->m_raw_ptr = ptr;
			}

			/**
			 * @brief Releases ownership of the of the stored pointer, by
			 * returning its value and setting it to null.
			 * 
			 * This operation does not delete the previously stored pointer,
			 * but the TUniquePtr object is released from the responsibility to
			 * delete it, therefore another entity must take responsibility of
			 * deleting it.
			 * 
			 * @return DataTypePtr storing the previously stored pointer.
			 */
			DataTypePtr Release(void)
			{
				DataTypePtr temp = this->m_raw_ptr;

				this->m_raw_ptr = nullptr;

				return temp;
			}
		};
	}
}

#endif // T_UNIQUE_PTR_H
