#ifndef IS_FLOATING_POINT_H
#define IS_FLOATING_POINT_H

#include "../TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		/// @brief Tests whether typename is floating point.
		template<typename T>
		struct TIsFloatingPoint { enum { Value = false }; };

		template<> struct TIsFloatingPoint<F32> { enum { Value = true }; };
		template<> struct TIsFloatingPoint<F64> { enum { Value = true }; };
		
		template<typename T>
		struct TIsFloatingPoint<const T> { enum { Value = TIsFloatingPoint<T>::Value }; };
	}
}

#endif // IS_FLOATING_POINT_H
