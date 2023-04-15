#ifndef T_MEMORY_REGION_H
#define T_MEMORY_REGION_H

#include <Core/Public/Common/Common.h>
#include <Core/Public/Algorithm/GeneralUtilities.h>

namespace Forge {
	namespace Common
	{
		/**
		 * @brief Represents a contiguous region of arbitrary memory.
		 * 
		 * @author Karim Hisham
		 */
		template<typename InType>
		class TMemoryRegion
		{
		public:
			using Type         = InType;
			using TypePtr      = InType*;
			using TypeRef      = InType&;
			using TypeMoveRef  = InType&&;
			using ConstType    = const InType;
			using ConstTypeRef = const InType&;
			using ConstTypePtr = const InType*;

		public:
			using SelfType         = TMemoryRegion<InType>;
			using SelfTypePtr      = TMemoryRegion<InType>*;
			using SelfTypeRef      = TMemoryRegion<InType>&;
			using SelfTypeMoveRef  = TMemoryRegion<InType>&&;
			using ConstSelfType    = const TMemoryRegion<InType>;
			using ConstSelfTypeRef = const TMemoryRegion<InType>&;
			using ConstSelfTypePtr = const TMemoryRegion<InType>*;

		private:
			TypePtr m_data;

		private:
			Size m_size;
			Size m_count;

		public:
			/**
			 * @brief Default constructor.
			 */
			TMemoryRegion(Void)
				: m_data(data), m_size(0), m_count(count) {}

			/**
			 * @brief Move data constructor.
			 */
			TMemoryRegion(TypeMoveRef data, Size count)
				: m_data(data), m_size(count * sizeof(InType)), m_count(count)
			{
				data = nullptr;
			}

			/**
			 * @brief Copy data constructor.
			 */
			TMemoryRegion(ConstTypeRef data, Size count)
				: m_data(data), m_size(count * sizeof(InType)), m_count(count) {}
			
		public:
			/**
			 * @brief Move constructor.
			 */
			TMemoryRegion(SelfTypeMoveRef other)
			{
				*this = Algorithm::Move(other);
			}

			/**
			 * @brief Copy constructor.
			 */
			TMemoryRegion(ConstSelfTypeRef other)
			{
				*this = other;
			}

		public:
			
			/**
			 * @brief Copy assignment.
			 */
			FORGE_FORCE_INLINE TypeRef operator =(SelfTypeMoveRef other)
			{
				m_data = other.m_data;
				m_count = other.m_count;

				other.Clear();

				return *this;
			}

			/**
			 * @brief Move assignment.
			 */
			FORGE_FORCE_INLINE TypeRef operator =(ConstSelfTypeRef other)
			{
				m_data = other.m_data;
				m_count = other.m_count;

				return *this;
			}

		public:
			/**
			 * @brief Element Accessor.
			 */
			FORGE_FORCE_INLINE TypeRef operator[](U32 index)
			{
				FORGE_ASSERT(index >= 0 && index < m_count);

				return m_data[index];
			}

			/**
			 * @brief Element Accessor.
			 */
			FORGE_FORCE_INLINE ConstTypeRef operator[](U32 index) const
			{
				FORGE_ASSERT(index >= 0 && index < m_count);

				return m_data[index];
			}

		public:
			/**
			 * @brief Checks wether the stored pointer is empty or not.
			 * 
			 * @returns True if the stored pointer is empty, otherwise false.
			 */
			FORGE_FORCE_INLINE Bool IsEmpty(Void) const
			{
				return m_count
			}

			/**
			 * @brief Checks wether the stored pointer is valid or not.
			 * 
			 * @returns True if the the stored pointer is valid, otherwise
			 * false. 
			 */
			FORGE_FORCE_INLINE Bool IsValid(Void) const
			{
				return m_data != nullptr;
			}

			/**
			 * @brief Checks wether the stored pointer is invalid or not.
			 *
			 * @returns True if the the stored pointer is invalid, otherwise
			 * false.
			 */
			FORGE_FORCE_INLINE Bool IsInvalid(Void) const
			{
				return m_data == nullptr;
			}

		public:
			/**
			 * @brief Gets the total size of the memory region. in bytes.
			 *
			 * @returns Size storing the size of the memory region in bytes.
			 */
			FORGE_FORCE_INLINE Size GetSize(Void)
			{
				return m_size;
			}

			/**
			 * @brief Gets the count of elements in the memory region.
			 * 
			 * @returns Size storing the length of the memory region.
			 */
			FORGE_FORCE_INLINE Size GetCount(Void) const
			{
				return m_count;
			}

			/**
			 * @brief Gets the start address of the memory region.
			 * 
			 * @returns TypePtr storing the start address of the memory
			 * region.
			 */
			FORGE_FORCE_INLINE TypePtr GetPointer(Void)
			{
				return m_data;
			}

			/**
			 * @brief Gets the end address of the memory region.
			 *
			 * @returns TypePtr storing the end address of the memory
			 * region.
			 */
			FORGE_FORCE_INLINE TypePtr GetEndPointer(Void)
			{
				return m_data + (m_count - 1);
			}

			/**
			 * @brief Gets the starts address of the memory region.
			 * 
			 * @returns ConstTypePtr storing the start address of the memory
			 * region.
			 */
			FORGE_FORCE_INLINE ConstTypePtr GetConstPointer(Void) const
			{
				return m_data;
			}

			/**
			 * @brief Gets the end address of the memory region.
			 *
			 * @returns ConstTypePtr storing the end address of the memory
			 * region.
			 */
			FORGE_FORCE_INLINE ConstTypePtr GetConstEndPointer(Void) const
			{
				return m_data + (m_count - 1);
			}

		public:
			/**
			 * @brief Gets a sub memory of the memory region.
			 * 
			 * @param offset THe start address of the sub memory.
			 * @param length THe length of the sub memory.
			 * 
			 * @returns TMemoryRegion storing the starting address of the sub
			 * memory.
			 */
			FORGE_FORCE_INLINE SelfType GetSubMemory(Size offset, Size length)
			{
				return TMemoryRegion<Type>(m_ptr + offset, length);
			}

			/**
			 * @brief Gets a sub memory of the memory region.
			 *
			 * @param offset THe start address of the sub memory.
			 * @param length THe length of the sub memory.
			 *
			 * @returns const TMemoryRegion storing the starting address of the sub
			 * memory.
			 */
			FORGE_FORCE_INLINE ConstSelfType GetConstSubMemory(Size offset, Size length) const
			{
				return TMemoryRegion<Type>(m_ptr + offset, length);
			}

		public:
			/**
			 * @brief Converts the memory region to a byte array.
			 * 
			 * @returns TMemoryRegion storing the the data in contiguous bytes.
			 */
			FORGE_FORCE_INLINE TMemoryRegion<Byte> ConvertToByteArray(Void)
			{
				return TMemoryRegion<Byte>(reinterpret_cast<BytePtr>(m_data), m_count);
			}

			/**
			 * @brief Converts the memory region to a byte array.
			 *
			 * @returns TMemoryRegion storing the the data in contiguous bytes.
			 */
			FORGE_FORCE_INLINE const TMemoryRegion<Byte> ConvertToConstByteArray(Void) const
			{
				return TMemoryRegion<Byte>(reinterpret_cast<BytePtr>(m_data), m_count);
			}

		public:
			/**
			 * @brief Invalidates the data pointer and resets the memory region
			 * state.
			 */
			FORGE_FORCE_INLINE Void Clear(Void)
			{
				m_data = nullptr;
				m_count = 0;
			}
		};
	}
}

#endif
