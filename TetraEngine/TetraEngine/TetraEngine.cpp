
#include "Core.h"
#include "MyApplication.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	if (Core::Initialize() != 0)
		return -1;

	Core::CreateApplication<MyApplication>();

	std::thread consoleThread(Core::processConsole);

	while (!glfwWindowShouldClose(Core::glfwContext->window))
	{
		//layers
		Core::Update();
		Core::UpdateOverlay();
		Core::AfterUpdate();
	}
	consoleThread.detach();
	consoleThread.~thread();
	Core::CleanUp();

	return 0;
}
