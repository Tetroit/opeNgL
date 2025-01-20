#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef TETRA_GLFW
#define TETRA_GLFW
#endif // !TETRA_GLFW

class InputManager;

class GLFWContext
{
private:

	static GLFWContext* current;

public:


	union KeyInfo
	{
	public:

		uint16_t raw;
		struct {
			uint16_t key : 9;
			uint16_t action : 2;
			uint16_t any : 1;
			uint16_t _unused : 4;
		} bits;

		KeyInfo(int key, int action)
		{
			bits.key = key & 0b111111111;
			bits.action = action & 0b11;
			bits.any = 0;
			bits._unused = 0;
		};
		KeyInfo(int action)
		{
			bits.key = 0;
			bits.action = action & 0b11;
			bits.any = 0;
			bits._unused = 0;
		};
		bool operator <(const KeyInfo& other) const { return raw < other.raw; }
		bool operator ==(const KeyInfo& other) const { return raw == other.raw; }
		operator int() const { return raw; }
	};


	bool captureMouse = true;
	bool captureKeyboard = true;
	bool captureMouseClick = true;
	
	GLFWwindow* window = nullptr;
	InputManager* inputManager = nullptr;

	bool cursorEnabled = false;

	unsigned int width = 1920, height = 1080;
	float lastMouseX = 0, lastMouseY = 0;

	GLFWContext(int width, int height);
	~GLFWContext();
	static const GLFWContext* get() { return current; };

	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

