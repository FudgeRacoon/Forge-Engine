#ifndef IS_ARITHMETIC_H
#define IS_ARITHMETIC_H

#include "../TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		/// @brief Test whether typename is arithmetic.
		template<typename T>
		struct TIsArithmetic { enum { Value = false }; };

		template<> struct TIsArithmetic<Char> { enum { Value = true }; };

		template<> struct TIsArithmetic<U8>   { enum { Value = true }; };
		template<> struct TIsArithmetic<U16>  { enum { Value = true }; };
		template<> struct TIsArithmetic<U32>  { enum { Value = true }; };
		template<> struct TIsArithmetic<U64>  { enum { Value = true }; };

		template<> struct TIsArithmetic<I8>   { enum { Value = true }; };
		template<> struct TIsArithmetic<I16>  { enum { Value = true }; };
		template<> struct TIsArithmetic<I32>  { enum { Value = true }; };
		template<> struct TIsArithmetic<I64>  { enum { Value = true }; };

		template<> struct TIsArithmetic<F32>  { enum { Value = true }; };
		template<> struct TIsArithmetic<F64>  { enum { Value = true }; };

		template<typename T>
		struct TIsArithmetic<const T> { enum { Value = TIsArithmetic<T>::Value }; };
	}
}

#endif // IS_ARITHMETIC_H
