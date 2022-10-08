#ifndef T_STATIC_ARRAY_H
#define T_STATIC_ARRAY_H

#include <initializer_list>

#include "AbstractList.h"

#include "Core/Public/Common/TypeDefinitions.h"
#include "Core/Public/Common/PreprocessorUtilities.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Containers
	{
		/**
		 * @brief A fixed-size linear container that holds a specific number of
		 * elements in a contigous memory block.
		 * 
		 * The static array has a fixed-size and does not manage the allocation of
		 * its elements through the memory allocators, instead the memory block is
		 * constructed at compile time. Therefore, it cannot be expanded dynamiclly
		 * at run-time.
		 * 
		 *  @author Karim Hisham
		 */
		template<typename InElementType, Size InMaxSize>
		class TStaticArray : public AbstractList<InElementType>
		{
		private:
			using ElementType         = InElementType;
			using ElementTypeRef      = InElementType&;
			using ElementTypePtr      = InElementType*;
			using ConstElementType    = const InElementType;
			using ConstElementTypeRef = const InElementType&;
			using ConstElementTypePtr = const InElementType*;

		private:
			ElementType m_mem_block[InMaxSize];
		
		public:
			class ForwardIterator : public AbstractIterator<ElementType>
			{
			public:
				ForwardIterator(ElementTypePtr ptr)
					: AbstractIterator<ElementType>(ptr) {}

			public:
				ForwardIterator& operator ++(void) override
				{
					++this->m_raw_ptr;

					ForwardIterator itr(this->m_raw_ptr);
					return itr;
				}
				ForwardIterator& operator ++(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr++;

					ForwardIterator itr(temp);
					return itr;
				}

			public:
				ForwardIterator& operator --(void) override
				{
					ForwardIterator itr(--this->m_raw_ptr);
					return itr;
				}
				ForwardIterator& operator --(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr--;

					ForwardIterator itr(temp);
					return itr;
				}
			};
			
			class BackwardIterator : public AbstractIterator<ElementType>
			{
			public:
				BackwardIterator(ElementTypePtr ptr)
					: AbstractIterator<ElementType>(ptr) {}

			public:
				BackwardIterator& operator ++(void) override
				{
					BackwardIterator itr(--this->m_raw_ptr);
					return itr;
				}
				BackwardIterator& operator ++(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr--;

					BackwardIterator itr(temp);
					return itr;
				}

			public:
				BackwardIterator& operator --(void) override
				{
					BackwardIterator itr(++this->m_raw_ptr);
					return itr;
				}
				BackwardIterator& operator --(I32 junk) override
				{
					ElementTypePtr temp = this->m_raw_ptr++;

					BackwardIterator itr(temp);
					return itr;
				}
			};

		public:
			/**
			 * @brief Constructs an empty array with no elements.
			 */
			TStaticArray() 
				: AbstractList<ElementType>(0, InMaxSize)
			{
				FORGE_ASSERT(this->m_capacity != 0 && this->m_size <= this->m_capacity, "Array size is not large enough to store the data.")

				Memory::MemorySet(m_mem_block, 0, sizeof(ElementType) * this->m_capacity);
			}
			
			/**
			 * @brief Constructs an array filled with the elements inside the
			 * memory block.
			 * 
			 * @param[in] data_ptr The memory block containing the elements to fill.
			 * @param[in] size     The number of elements inside the memory block.
			 */
			TStaticArray(ElementTypePtr data_ptr, Size size)
				: AbstractList<ElementType>(size, InMaxSize)
			{
				FORGE_ASSERT(this->m_capacity != 0 && this->m_size <= this->m_capacity, "Array size is not large enough to store the data.")

				Memory::MemoryCopy(m_mem_block, data_ptr, sizeof(ElementType) * this->m_size);
			}
			
			/**
			 * @brief Constructs an array filled with the elements inside a C++
			 * standard initializer list.
			 * 
			 * @param[in] init_list The initializer list containing the elements
			 * to fill.
			 */
			TStaticArray(std::initializer_list<ElementType> init_list)
				: AbstractList<ElementType>(init_list.size(), InMaxSize)
			{
				FORGE_ASSERT(this->m_capacity != 0 && this->m_size <= this->m_capacity, "Array size is not large enough to store the data.")

				Memory::MemoryCopy(m_mem_block, const_cast<ElementTypePtr>(init_list.begin()), sizeof(ElementType) * this->m_size);
			}
			
		public:
			TStaticArray(TStaticArray<ElementType, InMaxSize>&& rhs)
				: AbstractList<ElementType>(rhs)
			{
				this->m_size = rhs.m_size;
				this->m_mem_block = rhs.m_mem_block;

				rhs.m_mem_block = nullptr;
			}
			TStaticArray(const TStaticArray<ElementType, InMaxSize>& rhs)
				: AbstractList<ElementType>(rhs)
			{
				this->m_size = rhs.m_size;

				Memory::MemoryCopy(m_mem_block, const_cast<ElementTypePtr>(rhs.m_mem_block), sizeof(ElementType) * this->m_size);
			}

		public:
			~TStaticArray() = default;

		public:
			TStaticArray<ElementType, InMaxSize>& operator =(TStaticArray&& rhs)
			{
				this->m_size = rhs.m_size;

				this->m_mem_block = rhs.m_mem_block;
				rhs.m_mem_block = nullptr;

				return *this;
			}
			TStaticArray<ElementType, InMaxSize>& operator =(const TStaticArray& rhs)
			{
				this->m_size = rhs.m_size;

				Memory::MemoryCopy(this->m_mem_block, const_cast<ElementTypePtr>(rhs.m_mem_block), sizeof(ElementType) * this->m_size);

				return *this;
			}

		public:
			ElementTypeRef operator [](Size index) override
			{
				FORGE_ASSERT(index >= 0 && index < this->m_capacity, "Index is out of range.")

				return *(this->m_mem_block + index);
			}

		public:
			/**
			 * @brief Returns a forward iterator pointing to the first element in
			 * the static array.
			 *
			 * @return ForwardIterator pointing to the first element.
			 */
			ForwardIterator& GetForwardStartItr(void) override
			{
				static ForwardIterator itr(this->m_mem_block);
				return itr;
			}

			/**
			 * @brief Returns a forward iterator pointing to the past-end element
			 * in the static array.
			 *
			 * @return ForwardIterator pointing to the past-end element element.
			 */
			ForwardIterator& GetForwardEndItr(void) override
			{
				static ForwardIterator itr(this->m_mem_block + InMaxSize);
				return itr;
			}

			/**
			 * @brief Returns a backward iterator pointing to the last element in
			 * the static array.
			 *
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the last element.
			 */
			BackwardIterator& GetBackwardStartItr(void) override
			{
				static BackwardIterator itr(this->m_mem_block + InMaxSize - 1);
				return itr;
			}

			/**
			 * @brief Returns a backward iterator pointing to the first element in
			 * the static array.
			 *
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the first element.
			 */
			BackwardIterator& GetBackwardEndItr(void) override
			{
				static BackwardIterator itr(this->m_mem_block);
				return itr;
			}

		public:
			/**
			 * @brief Gets a direct pointer to the memory array managed by this
			 * collection.
			 *
			 * Elements in the memory array are guranteed to be stored in contiguous
			 * memory locations. This allows the pointer to be offsetted to access
			 * different elements.
			 *
			 * @return Const pointer storing address of the memory array.
			 */
			ConstElementTypePtr GetRawData() const override
			{
				return this->m_mem_block;
			}

		public:
			/**
			 * @brief Checks whether the static array is equal to the specified
			 * collection.
			 *
			 * Equality between collections is governed by their size, the order
			 * of the elements in the collection and the eqaulity of the elements
			 * they store.
			 *
			 * @param[in] collection The collection to be compared with this
			 * collection.
			 *
			 * @return True if the specified collection is equal to this collection.
			 */
			Bool IsEqual(const AbstractCollection<ElementType>& collection) const override
			{
				return true;
			}

		public:
			/**
			 * @brief Returns an array containing all the elements stored in the
			 * static array.
			 *
			 * The length of the array is equal to the number of elements stored in
			 * the static array. The array returned also stores the elements in the 
			 * same order that it is stored in the static array and contains deep 
			 * copies of the elements.
			 *
			 * @return ElementTypePtr storing the address of the new array.
			 */
			ElementTypePtr ToArray(void) const override
			{
				ElementTypePtr array_ptr = new ElementType[this->m_size];

				Memory::MemoryCopy(array_ptr, const_cast<ElementTypePtr>(m_mem_block), sizeof(ElementType) * this->m_size);

				return array_ptr;
			}

			/**
			 * @brief Fills the passed array with all the elements stored in the
			 * static array.
			 *
			 * The length of the passed array must be equal to the number of 
			 * elements stored in the static array. The array passed will store the
			 * elements in the same order that it is stored in the static array and
			 * will contain deep copies of the elements.
			 *
			 * @param[out] array_ptr The array to fill with elements from this 
			 * array's memory block.
			 * 
			 * @return ElementTypePtr storing the address of the passed array.
			 */
			ElementTypePtr ToArray(ElementTypePtr array_ptr) const override
			{
				Memory::MemoryCopy(array_ptr, const_cast<ElementTypePtr>(m_mem_block), sizeof(ElementType) * this->m_size);

				return array_ptr;
			}

		public:
			/**
			 * @brief Returns the index of the first occurence of the specified
			 * element in the static array, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] value The element to search for the first occurence.
			 *
			 * @return Size storing the index of the first occurrence of the
			 * specified element, or -1 if the static array does not contain the
			 * element or it is empty.
			 */
			I64 FirstIndexOf(ElementType value) const override
			{
				if (this->m_capacity > 0)
				{
					ConstElementTypePtr start = this->m_mem_block;
					ConstElementTypePtr end = start + this->m_capacity;

					for (ConstElementTypePtr ptr = start; ptr != end; ptr++)
					{
						if (*ptr == value)
							return reinterpret_cast<I64>(Memory::SubAddress(ptr, start)) / sizeof(ElementType);
					}
				}

				return -1;
			}
			
			/**
			 * @brief Returns the index of the last occurence of the specified
			 * element in the static array, or -1 if it does not contain the
			 * element or it is empty.
			 *
			 * @param[in] value The element to search for the last occurence.
			 *
			 * @return Size storing the index of the last occurrence of the
			 * specified element, or -1 if the static array does not contain the
			 * element or it is empty.
			 */
			I64 LastIndexOf(ElementType value) const override
			{
				if (this->m_capacity > 0)
				{
					ConstElementTypePtr start = this->m_mem_block - 1;
					ConstElementTypePtr end = start + InMaxSize;

					for (ConstElementTypePtr ptr = end; ptr != start; ptr--)
					{
						if (*ptr == value)
							return reinterpret_cast<I64>(Memory::SubAddress(ptr, start + 1)) / sizeof(ElementType);
					}
				}

				return -1;
			}

		public:	
			/**
			* @brief Inserts the specified element after the element in the
			* specified position in the static array.
			*
			* This function overwrites the memory where the specified element will
			* be inserted.
			*
			* @param[in] index   The numerical index to insert the element at.
			* @param[in] element The element to insert in the static array.
			*
			* @throw IndexOutOfRangeException if position is out of range of the
			* static array.
			*/
			Void InsertAt(Size index, ElementType element) override
			{
				FORGE_ASSERT(index >= 0 && index < InMaxSize, "Index is out of range.")

				this->m_size++;

				*(this->m_mem_block + index + 1) = element;
			}

			/**
			 * @brief Inserts the specified element after the element in the
			 * specified position in the static array.
			 *
			 * This function overwrites the memory where the specified element will
			 * be inserted.
			 *
			 * @param[in] index   The iterator position to insert the element at.
			 * @param[in] element The element to insert in the static array.
			 *
			 * @throw IndexOutOfRangeException if position is out of range of the
			 * static array.
			 */
			Void InsertAt(AbstractIterator<ElementType>& index, ElementType element) override
			{
				FORGE_ASSERT(index != this->GetForwardEndItr(), "Index is out of range.")

				this->m_size++;

				*(++index) = element;
			}

			/**
			 * @brief Removes the specified element after the element in the
			 * specified position in the list.
			 *
			 * This effectively decreases the list size by one, and destroys the
			 * element but does not deallocate the memory the element was stored
			 * at.
			 *
			 * @param[in] index The numerical index to remove the element at.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			Void RemoveAt(Size index) override
			{
				FORGE_ASSERT(index >= 0 && index < InMaxSize, "Index is out of range.")

				this->m_size--;

				*(this->m_mem_block + index + 1) = 0;
			}

			/**
			 * @brief Removes the specified element after the element in the
			 * specified position in the list.
			 *
			 * This effectively decreases the list size by one, and destroys the
			 * element but does not deallocate the memory the element was stored
			 * at.
			 *
			 * @param[in] position  The iterator position to remove the element at.
			 *
			 * @throw InvalidOperationException if operation not supported by
			 * this collection.
			 */
			Void RemoveAt(AbstractIterator<ElementType>& index) override
			{
				FORGE_ASSERT(index != this->GetForwardEndItr(), "Index is out of range.")

				this->m_size--;

				*(++index) = 0;
			}

		public:
			/**
			 * @brief Inserts the specified element after the last element inserted
			 * in the static array.
			 *
			 * @param[in] element ElementType to insert in the static array.
			 *
			 * @return True if insertion was successful and array is not yet full.
			 */
			Bool Insert(ElementType element) override
			{
				if (this->m_index_ptr >= InMaxSize)
					return false;

				this->m_size++;

				InsertAt(this->m_index_ptr++, element);
				 
				return true;
			}

			/**
			 * @brief Removes the first occurance of the specified element from the
			 * static array.
			 *
			 * This operation explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 * 
			 * @param[in] element ElementType to remove from the static array.
			 *
			 * @return True if removal was successful and the element was found.
			 */
			Bool Remove(ElementType element) override
			{
				Size index = FirstIndexOf(element);

				if (index == -1)
					return false;

				RemoveAt(index);

				return true;
			}

			/**
			 * @brief Searches the static array for the specified element.
			 *
			 * @param[in] element ElementType to search for in the static array.
			 *
			 * @return True if the specified element was found in the static array.
			 */
			Bool Contains(ElementType element) override
			{
				Size index = FirstIndexOf(element);

				return index != -1;
			}

		public:
			/**
			 * @brief Inserts all the elements in the specified collection to the
			 * static array. 
			 * 
			 * The order in which the elements are inserted into the static array
			 * depends on how the specified collection is iterated on.
			 *
			 * @param[in] collection The collection containing elements to be added
			 * to the static array.
			 *
			 * @return True if insertion was succesfull and array is not yet full.
			 */
			Bool InsertAll(const AbstractCollection<ElementType>& collection) override
			{
				return true;
			}

			/**
			 * @brief Removes all the elements in the specified collection from the
			 * static array.
			 *
			 * This operation explicitly calls the destructor of the element
			 * but does not deallocate the memory it was stored at.
			 * 
			 * @param[in] collection The collection containing elements to be
			 * removed from the static array.
			 *
			 * @return True if removal was successful and the elements were found.
			 */
			Bool RemoveAll(const AbstractCollection<ElementType>& collection) override
			{
				return true;
			}

			/**
			 * @brief Searches for all the elements in the specified collection in
			 * the static array.
			 *
			 * @param[in] collection The collection containing elements to be
			 * search for in the static array.
			 *
			 * @return True if the specified elements were found in the static array.
			 */
			Bool ContainsAll(const AbstractCollection<ElementType>& collection) override
			{
				return true;
			}
	
		public:
			/**
			 * @brief Removes all the elements from the static array.
			 *
			 * The static array will be empty after this operation.
			 */
			Void Clear(void) override
			{
				this->m_size = 0;
				
				Memory::MemorySet(m_mem_block, 0, sizeof(ElementType) * InMaxSize);
			}
		};
	}
}

#endif // T_STATIC_ARRAY_H
