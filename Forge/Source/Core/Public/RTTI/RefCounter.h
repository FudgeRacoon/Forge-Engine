#ifndef REF_COUNTER_H
#define REF_COUNTER_H

#include "Core/Public/Common/Compiler.h"
#include "Core/Public/Common/TypeDefinitions.h"

namespace Forge {
	namespace RTTI
	{
		/**
		 * @brief Manages reference-counting on objects and prevents copying.
		 * 
		 * @author Karim Hisham
		 */
		class FORGE_API RefCounted
		{
		FORGE_CLASS_NONCOPYABLE(RefCounted)

		private:
			struct RefCounter
			{
				Size m_ref;
				Size m_weak_ref;
			} *m_ref_counter;

		public:
			RefCounted();
			virtual ~RefCounted();

		public:
			/**
			 * @brief Gets number of object references.
			 * 
			 * @return ConstSize storing number of references. 
			 */
			ConstSize GetRefCount(void) const;

			/**
			 * @brief Gets number of object weak references.
			 *
			 * @return ConstSize storing number of weak references. 
			 */
			ConstSize GetWeakRefCount(void) const;

		public:
			/**
			 * @brief Increments number of object references.
			 */
			Void IncrementRef(void);

			/**
			 * @brief Decrements number of object references.
			 */
			Void DecrementRef(void);

			/**
			 * @brief Increments number of object weak references.
			 */
			Void IncrementWeakRef(void);

			/**
			 * @brief Decrements number of object weak references.
			 */
			Void DecrementWeakRef(void);
		};
	}
}

#endif // REF_COUNTER_H
