#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <type_traits>

#include "TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		template<I32 Value>
		struct TTraitInt
		{
			enum { Value = Value };
		};

		using TypeIsPod = TTraitInt<1>;
		using TypeIsClass = TTraitInt<0>;

		/**
		 * @brief Tests if a type is pod (plain old data).
		 */
		template<typename _Type>
		struct TIsPod { enum { Value = __is_pod(_Type) }; };
		
		/**
		 * @brief Tests if two types are assignable.
		 */
		template<typename _Type_1, typename _Type_2> 
		struct TIsAssignable { enum { Value = std::is_assignable<_Type_1, _Type_2>::value }; };

		/**
		 * @brief Tests if a type has a default constructor.
		 */
		template<typename _Type>
		struct TIsTriviallyConstructible { enum { Value = __has_trivial_constructor(_Type) }; };

		/**
		 * @brief Tests if a type has a default destructor.
		 */
		template<typename _Type>
		struct TIsTriviallyDestructible { enum { Value = __has_trivial_destructor(_Type) }; };

		/**
		 * @brief Tests if a type has a default copy constructor.
		 */
		template<typename _Type>
		struct TIsTriviallyCopyConstructible { enum { Value = __has_trivial_copy(_Type) }; };

		/**
		 * @brief Tests if a type has a default assignment operator.
		 */
		template<typename _Type>
		struct TIsTriviallyCopyAssignable { enum { Value = __has_trivial_assign(_Type) }; };

		/**
		 * @brief Tests whether two typenames are the same.
		 */
		template<typename Type_1, typename Type_2>
		struct TAreSameType { enum { Value = false }; };

		template<typename _Type>
		struct TAreSameType<_Type, _Type> { enum { Value = true }; };

		/**
		 * @brief Tests whether the predicate is true, if so returns the type.
		 */
		template<Bool Predicate, typename Result>
		struct TEnableIf { };

		template<typename Result>
		struct TEnableIf<true, Result> { using Type = Result; };

		/**
		 * @brief Tests whether class is derived from base.
		 */
		template<typename Derived, typename Base>
		struct IsBaseOf { enum { Value = __is_base_of(Base, Derived) }; };

		/**
		 * @brief Tests whether a type is const.
		 */
		template<typename Type>
		struct TIsConst { enum { Value = false }; };

		template<typename _Type>
		struct TIsConst<const _Type> { enum { Value = true }; };

		/**
		 * @brief Tests wether a type is pointer.
		 */
		template<typename _Type>
		struct TIsPointer { enum { Value = false }; };

		template<typename _Type>
		struct TIsPointer<_Type*> { enum { Value = true }; };

		/**
		 * @brief Tests whether a type is l-value reference.
		 */
		template<typename Type>
		struct TIsLValueReference { enum { Value = false }; };

		template<typename _Type>
		struct TIsLValueReference<_Type&> { enum { Value = true }; };

		/**
		 * @brief Tests whether a type is r-value reference.
		 */
		template<typename _Type>
		struct TIsRValueReference { enum { Value = false }; };

		template<typename _Type>
		struct TIsRValueReference<_Type&&> { enum { Value = true }; };

		/**
		 * @brief Test whether a type is arithmetic.
		 */
		template<typename _Type>
		struct TIsArithmetic { enum { Value = false }; };

		template<> struct TIsArithmetic<Char> { enum { Value = true }; };

		template<> struct TIsArithmetic<U8>  { enum { Value = true }; };
		template<> struct TIsArithmetic<U16> { enum { Value = true }; };
		template<> struct TIsArithmetic<U32> { enum { Value = true }; };
		template<> struct TIsArithmetic<U64> { enum { Value = true }; };

		template<> struct TIsArithmetic<I8>  { enum { Value = true }; };
		template<> struct TIsArithmetic<I16> { enum { Value = true }; };
		template<> struct TIsArithmetic<I32> { enum { Value = true }; };
		template<> struct TIsArithmetic<I64> { enum { Value = true }; };

		template<> struct TIsArithmetic<F32> { enum { Value = true }; };
		template<> struct TIsArithmetic<F64> { enum { Value = true }; };

		template<typename _Type>
		struct TIsArithmetic<const _Type> { enum { Value = TIsArithmetic<_Type>::Value }; };

		/**
		 * @brief Tests wether a type is signed.
		 */
		template<typename _Type>
		struct TIsSigned { enum { Value = false }; };

		template<> struct TIsSigned<I8>  { enum { Value = true }; };
		template<> struct TIsSigned<I16> { enum { Value = true }; };
		template<> struct TIsSigned<I32> { enum { Value = true }; };
		template<> struct TIsSigned<I64> { enum { Value = true }; };

		template<> struct TIsSigned<F32> { enum { Value = true }; };
		template<> struct TIsSigned<F64> { enum { Value = true }; };

		template<typename _Type>
		struct TIsSigned<const _Type> { enum { Value = TIsSigned<_Type>::Value }; };

		/**
		 * @brief Tests whether typename is floating point.
		 */
		template<typename _Type>
		struct TIsFloatingPoint { enum { Value = false }; };

		template<> struct TIsFloatingPoint<F32> { enum { Value = true }; };
		template<> struct TIsFloatingPoint<F64> { enum { Value = true }; };

		template<typename _Type>
		struct TIsFloatingPoint<const _Type> { enum { Value = TIsFloatingPoint<_Type>::Value }; };

		/**
		 * @brief Checks whether a type is double precision.
		 */
		template<typename _Type>
		struct TIsDoublePrecision { enum { Value = false }; };

		template<> struct TIsDoublePrecision<F64> { enum { Value = true }; };

		template<typename _Type>
		struct TIsDoublePrecision<const _Type> { enum { Value = TIsDouble<_Type>::Value }; };

		/**
		 * @brief Removes constant qualifiers from a type.
		 */
		template<typename _Type>
		struct TRemoveConst { using Type = _Type; };

		template<typename _Type>
		struct TRemoveConst<const _Type> { using Type = _Type; };

		/**
		 * @brief Removes pointer qualifier from a type.
		 */
		template<typename _Type>
		struct TRemovePointer { using Type = _Type; };

		template<typename _Type>
		struct TRemovePointer<_Type*> { using Type = _Type; };

		/**
		 * @brief Removes reference qualifiers from a type.
		 */
		template<typename _Type>
		struct TRemoveRefernce { using Type = _Type; };

		template<typename _Type>
		struct TRemoveRefernce<_Type&> { using Type = _Type; };

		template<typename _Type>
		struct TRemoveRefernce<_Type&&> { using Type = _Type; };
	}
}

#endif // TYPE_TRAITS_H
