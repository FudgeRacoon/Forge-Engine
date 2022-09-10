#ifndef IS_BASE_OF_H
#define IS_BASE_OF_H

#include <type_traits>

namespace Forge {
	namespace Common
	{
		/// @brief Checks whether class is derived from base.
		template<typename Derived, typename Base>
		struct IsBaseOf { enum { Value = std::is_base_of<Base, Derived>::value }; };
	}
}

#endif
