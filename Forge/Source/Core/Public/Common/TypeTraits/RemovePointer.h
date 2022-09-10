#ifndef REMOVE_POINTER_H
#define REMOVE_POINTER_H

namespace Forge {
	namespace Common
	{
		/// @brief Removes pointer qualifier from typename.
		template<typename T>
		struct TRemovePointer { using Type = T; };

		template<typename T>
		struct TRemovePointer<T*> { using Type = T; };
	}
}

#endif // REMOVE_POINTER_H

