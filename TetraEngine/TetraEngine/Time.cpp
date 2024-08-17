#include "Time.h"
#include <GLFW/glfw3.h>

float Time::time = 0;
float Time::prevTime = 0;
float Time::deltaTime;
float Time::fps = 0;
void Time::Update()
{
	prevTime = time;
	time = glfwGetTime();
	deltaTime = time - prevTime;
	fps = (fps + 3 / deltaTime) / 4;
}