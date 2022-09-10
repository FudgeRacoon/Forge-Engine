#ifndef IS_CONST_H
#define IS_CONST_H

namespace Forge {
	namespace Common
	{
		/// @brief Tests whether typename is const.
		template<typename T>
		struct TIsConst { enum { Value = false }; };

		template<typename T>
		struct TIsConst<const T> { enum { Value = true }; };
	}
}

#endif // IS_CONST_H
