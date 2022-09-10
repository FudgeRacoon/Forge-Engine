#ifndef REF_COUNTER_H
#define REF_COUNTER_H

#include "Core/Public/Common/Common.h"
#include "Core/Public/Memory/Memory.h"

namespace Forge {
	namespace RTTI
	{
		using RefCounterRef      = RefCounter&;
		using RefCounterPtr      = RefCounter*;
		using ConstRefCounter    = const RefCounter;
		using ConstRefCounterRef = const RefCounter&;
		using ConstRefCounterPtr = const RefCounter*;

		struct RefCounter
		{
			Size m_ref = 0;
			Size m_weak_ref = 0;
		};

		/// @brief Base class for reference-counted objects. These are non-copyable.
		class FORGE_API RefCounted
		{
		FORGE_CLASS_NONCOPYABLE(RefCounted)

		private:
			RefCounterPtr m_ref_counter;

		public:
			RefCounted();
			virtual ~RefCounted();

		public:
			/// @brief Gets number of object references.
			ConstSize GetRefCount(void) const;

			/// @brief Gets number of object weak references.
			ConstSize GetWeakRefCount(void) const;

		public:
			/// @brief Increments number of object references.
			Void IncrementRef(void);

			/// @brief Decrements number of object references. If zero, deletes itself.
			Void DecrementRef(void);

			/// @brief Increments number of object weak references.
			Void IncrementWeakRef(void);

			/// @brief Decrements number of object weak references.
			Void DecrementWeakRef(void);
		};
	}
}

#endif // REF_COUNTER_H
