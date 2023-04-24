#include <Platform/Public/Platform.h>
#include <GraphicsDevice/Public/OpenGL/GLGraphicsContext.h>
#include <GraphicsDevice/Public/OpenGL/GLGraphicsContextState.h>

#include "../ThirdParty/GL/glew.h"

#pragma comment (lib, "opengl32.lib")

using namespace Forge::Platform;
using namespace Forge::Graphics;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Platform::GetInstance().Initialize(hInstance);

	WindowPtr wnd = Platform::GetInstance().ConstructWindow("Forge Engine");

	GLGraphicsContextPtr gc = new GLGraphicsContext(wnd, 3, 3, GLContextProfileMask::FORGE_CORE, GLContextFlags::FORGE_NONE);
	gc->Initialize();

	GLGraphicsContextState gcs(gc);

	gcs.SetColorClear(1.0, 0.0, 0.0, 1.0);

	while (!wnd->IsClosing())
	{
		Platform::GetInstance().PumpMessages();

		glClear(GL_COLOR_BUFFER_BIT);

		gc->SwapBuffers(1);
	}
}


