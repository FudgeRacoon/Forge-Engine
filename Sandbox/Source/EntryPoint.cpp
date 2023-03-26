#include <Platform/Public/Platform.h>
#include <GraphicsDevice/Public/GraphicsContext.h>

#include "../ThirdParty/GL/glew.h"

#pragma comment (lib, "opengl32.lib")

using namespace Forge::Platform;
using namespace Forge::Graphics;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Platform::GetInstance().Initialize(hInstance);

	WindowPtr wnd = Platform::GetInstance().ConstructWindow("Forge Engine");

	GraphicsContextPtr gc = wnd->ConstructContext(3, 3, GLContextProfile::FORGE_CORE, GLContextFlags::FORGE_NONE);

	while (!wnd->IsClosing())
	{
		Platform::GetInstance().PumpMessages();

		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		gc->SwapBuffers(1);
	}
}


