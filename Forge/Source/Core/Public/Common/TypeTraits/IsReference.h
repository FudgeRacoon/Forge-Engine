#ifndef IS_REFERENCE_H
#define IS_REFERENCE_H

namespace Forge {
	namespace Common
	{
		/// @brief Tests whether typename is l-value reference.
		template<typename T>
		struct TIsLValueReference { enum { Value = false }; };

		template<typename T>
		struct TIsLValueReference<T&> { enum { Value = true }; };

		/// @brief Tests whether typename is r-value reference
		template<typename T>
		struct TIsRValueReference { enum { Value = false }; };

		template<typename T>
		struct TIsRValueReference<T&&> { enum { Value = true }; };
	}
}

#endif // IS_REFERENCE_H
