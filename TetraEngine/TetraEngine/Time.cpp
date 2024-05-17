#include "Time.h"
#include <GLFW/glfw3.h>

float Time::time = 0;
float Time::prevTime = 0;
float Time::deltaTime;
void Time::Update()
{
	prevTime = time;
	time = glfwGetTime();
	deltaTime = time - prevTime;
}
float Time::GetFPS() {
	if (deltaTime > 0)
		return 1 / deltaTime;
	else
		return 0;
}