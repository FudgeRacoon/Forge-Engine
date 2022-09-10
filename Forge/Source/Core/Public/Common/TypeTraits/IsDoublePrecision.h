#ifndef IS_DOUBLE_PRECISION_H
#define IS_DOUBLE_PRECISION_H

#include "../TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		/// @brief Checks whether typename is double.
		template<typename T>
		struct TIsDoublePrecision { enum { Value = false }; };

		template<> struct TIsDoublePrecision<F64> { enum { Value = true }; };

		template<typename T>
		struct TIsDoublePrecision<const T> { enum { Value = TIsDouble<T>::Value }; };
	}
}

#endif // IS_DOUBLE_PRECISION_H
