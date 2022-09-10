#ifndef IS_POINTER_H
#define IS_POINTER_H

namespace Forge {
	namespace Common
	{
		/// @brief Tests wether typename is pointer.
		template<typename T>
		struct TIsPointer { enum { Value = false }; };

		template<typename T>
		struct TIsPointer<T*> { enum { Value = true }; };
	}
}

#endif // IS_POINTER_H
