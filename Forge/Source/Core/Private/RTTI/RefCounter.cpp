#include "Core/Public/RTTI/RefCounter.h"

namespace Forge {
	namespace RTTI
	{
		RefCounted::RefCounted()
			: m_ref_counter(new RefCounter()) {}
		RefCounted::~RefCounted()
		{
			delete m_ref_counter;
		}

		ConstSize RefCounted::GetRefCount(void) const
		{
			return m_ref_counter->m_ref;
		}
		ConstSize RefCounted::GetWeakRefCount(void) const
		{
			return m_ref_counter->m_weak_ref;
		}

		Void RefCounted::IncrementRef(void)
		{
			FORGE_ASSERT(m_ref_counter->m_ref >= 0, "Reference number must be a positive integer")
			m_ref_counter->m_ref++;
		}
		Void RefCounted::DecrementRef(void)
		{
			FORGE_ASSERT(m_ref_counter->m_ref >= 0, "Reference number must be a positive integer")
			m_ref_counter->m_ref--;
		}
	
		Void RefCounted::IncrementWeakRef(void)
		{
			FORGE_ASSERT(m_ref_counter->m_weak_ref >= 0, "Weak reference number must be a positive integer")
			m_ref_counter->m_weak_ref++;
		}
		Void RefCounted::DecrementWeakRef(void)
		{
			FORGE_ASSERT(m_ref_counter->m_weak_ref >= 0, "Weak reference number must be a positive integer")
			m_ref_counter->m_weak_ref--;
		}
	}
}
