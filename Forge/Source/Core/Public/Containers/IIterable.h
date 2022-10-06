#ifndef I_ITERABLE_H
#define I_ITERABLE_H

#include "AbstractIterator.h"

#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace Containers
	{
		template<typename T>
		class IIterable
		{
		private:
			using ValueType         = T;
			using ValueTypeRef      = T&;
			using ValueTypePtr      = T*;
			using ConstValueType    = const T;
			using ConstValueTypeRef = const T&;
			using ConstValueTypePtr = const T*;

		public:
			/**
			 * @brief Returns a forward iterator pointing to the first element in
			 * the iterable collection.
			 * 
			 * @return ForwardIterator pointing to the first element.
			 */
			virtual AbstractIterator<ValueType>& GetForwardStartItr(void) = 0;

			/**
			 * @brief Returns a forward iterator pointing to the past-end element
			 * in the iterable collection.
			 *
			 * @return ForwardIterator pointing to the past-end element element.
			 */
			virtual AbstractIterator<ValueType>& GetForwardEndItr(void) = 0;

			/**
			 * @brief Returns a backward iterator pointing to the last element in
			 * the iterable collection.
			 *
			 * The backward iterator moves in the reverse direction.
			 * 
			 * @return BackwardIterator pointing to the last element.
			 */
			virtual AbstractIterator<ValueType>& GetBackwardStartItr(void) = 0;

			/**
			 * @brief Returns a backward iterator pointing to the first element in
			 * the iterable collection.
			 * 
			 * The backward iterator moves in the reverse direction.
			 *
			 * @return BackwardIterator pointing to the first element.
			 */
			virtual AbstractIterator<ValueType>& GetBackwardEndItr(void) = 0;
		};
	}
}

#endif // I_ITERABLE_H
