#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include "Core/Public/Common/Common.h"

namespace Forge {
	namespace Graphics
	{
		class FORGE_API GraphicsContext
		{
		public:
			GraphicsContext(Void) = default;
		
			virtual ~GraphicsContext(Void) = default;

		public:
			virtual Void SetCurrent(Void) = 0;

			virtual Void EndCurrent(Void) = 0;

		public:
			virtual Void ReleaseContext(Void) = 0;
		};

		FORGE_TYPEDEF_DECL(GraphicsContext, GraphicsContext)
	}
}

#endif
