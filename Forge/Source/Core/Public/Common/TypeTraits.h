#ifndef TYPETRAITS_H
#define TYPETRAITS_H

#include "TypeDefinitions.h"

namespace Forge {
	namespace TypeTraits
	{
		/// TODO: Implement IsConstructible, IsDestructible and IsCopyable tests

		/// Tests whether the predicate is true, if so returns the typename
		template<BOOL predicate, typename Result>
		struct TEnableIf { };
		template<typename Result>
		struct TEnableIf<true, Result> { using Type = Result; };

		/// Tests whether two typenames are the same
		template<typename A, typename B>
		struct TAreSameType { enum { Value = false }; };
		template<typename T>
		struct TAreSameType<T, T> { enum { Value = true }; };

		/// Tests whether typename is const
		template<typename T>
		struct TIsConst { enum { Value = false }; };
		template<typename T>
		struct TIsConst<const T> { enum { Value = true }; };

		/// Tests whether typename is lvalue reference
		template<typename T>
		struct TIsLValueReference { enum { Value = false }; };
		template<typename T>
		struct TIsLValueReference<T&> { enum { Value = true }; };

		/// Tests whether typename is rvalue reference
		template<typename T>
		struct TIsRValueReference { enum { Value = false }; };
		template<typename T>
		struct TIsRValueReference<T&&> { enum { Value = true }; };

		/// Tests whether typename is floating point
		template<typename T>
		struct TIsFloatingPoint { enum { Value = false }; };
		template<> struct TIsFloatingPoint<F32> { enum { Value = true }; };
		template<> struct TIsFloatingPoint<F64> { enum { Value = true }; };
		template<typename T>
		struct TIsFloatingPoint<const T> { enum { Value = TIsFloatingPoint<T>::Value }; };

		/// Tests whether typename is double
		template<typename T>
		struct TIsDoublePrecision { enum { Value = false }; };
		template<> struct TIsDoublePrecision<F64> { enum { Value = true }; };
		template<typename T>
		struct TIsDoublePrecision<const T> { enum { Value = TIsDouble<T>::Value }; };

		/// Tests wether typename is signed 
		template<typename T>
		struct TIsSigned { enum { Value = false }; };
		template<> struct TIsSigned<I8>  { enum { Value = true }; };
		template<> struct TIsSigned<I16> { enum { Value = true }; };
		template<> struct TIsSigned<I32> { enum { Value = true }; };
		template<> struct TIsSigned<I64> { enum { Value = true }; };
		template<> struct TIsSigned<F32> { enum { Value = true }; };
		template<> struct TIsSigned<F64> { enum { Value = true }; };
		template<typename T>
		struct TIsSigned<const T> { enum { Value = TIsSigned<T>::Value }; };

		/// Test whether typename is arithmetic
		template<typename T>
		struct TIsArithmetic { enum { Value = false }; };
		template<> struct TIsArithmetic<CHAR> { enum { Value = true }; };
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

		/// Tests wether typename is pointer
		template<typename T>
		struct TIsPointer { enum { Value = false }; };
		template<typename T>
		struct TIsPointer<T*> { enum { Value = true }; };

		/// Removes constant qualifiers from typename
		template<typename T>
		struct TRemoveConst { using Type = T; };
		template<typename T>
		struct TRemoveConst<const T> { using Type = T; };

		/// Removes reference qualifiers from typename
		template<typename T>
		struct TRemoveRefernce { using Type = T; };
		template<typename T>
		struct TRemoveRefernce<T&> { using Type = T; };
		template<typename T>
		struct TRemoveRefernce<T&&> { using Type = T; };

		/// Removes pointer qualifier from typename
		template<typename T>
		struct TRemovePointer { using Type = T; };
		template<typename T>
		struct TRemovePointer<T*> { using Type = T; };
	}
}

#endif // TYPETRAITS_H
