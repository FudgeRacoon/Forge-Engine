#ifndef ABSTRACT_HARDWARE_BUFFER_H
#define ABSTRACT_HARDWARE_BUFFER_H

#include <Core/Public/Common/Common.h>
#include <Core/Public/Types/TMemoryRegion.h>

using namespace Forge::Common;

namespace Forge {
	namespace Graphics
	{
		class AbstractHardwareBuffer
		{
		public:
			enum class LockModeMask : Byte
			{
				FORGE_ENUM_DECL(FORGE_DISCARD,    0x0)

				FORGE_ENUM_DECL(FORGE_READ_ONLY,  0x1)

				FORGE_ENUM_DECL(FORGE_WRITE_ONLY, 0x2)

				FORGE_ENUM_DECL(FORGE_READ_WRITE, 0x3)

				MAX
			};

			enum class UsageModeMask : Byte
			{

			};

		protected:
			Size m_size;
			Size m_lock_offset;
			Size m_lock_length;

		protected:
			Bool m_is_locked;
			Bool m_is_shadowed;

		protected:
			UsageModeMask m_usage_mode;

		protected:
			TMemoryRegion<Byte> m_shadow_buffer;

		public:
			AbstractHardwareBuffer(UsageModeMask usage, Bool is_shadowed)
				: m_size(0), 
				  m_lock_offset(0), 
				  m_lock_length(0), 
				  m_is_locked(false), 
				  m_is_shadowed(is_shadowed)
			{

			}

		public:
			virtual ~AbstractHardwareBuffer(Void) = default;

		public:
			Size GetSize(Void)
			{
				return m_size;
			}

			UsageModeMask GetUsageMode(Void)
			{
				return m_usage_mode;
			}

			TMemoryRegion<Byte> GetShadowBuffer(Void)
			{
				return m_shadow_buffer;
			}

		public:
			Bool IsLocked(Void)
			{
				return m_is_locked;
			}

			Bool IsShadowed(Void)
			{
				return m_is_shadowed;
			}

		public:
			virtual VoidPtr Lock(LockModeMask lock_mode) = 0;

			virtual VoidPtr Lock(LockModeMask lock_mode, Size offset, Size length) = 0;

			virtual Void Unlock(Void) = 0;
		};
	}
}

#endif
