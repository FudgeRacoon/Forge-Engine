#ifndef IS_SIGNED_H
#define IS_SIGNED_H

#include "../TypeDefinitions.h"

namespace Forge {
	namespace Common
	{
		/// @brief Tests wether typename is signed.
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
	}
}

#endif // IS_SIGNED_H