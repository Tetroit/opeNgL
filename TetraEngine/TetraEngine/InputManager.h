#pragma once
#include "Event.h"
#include "GLFWContext.h"

#ifdef TETRA_GLFW
typedef GLFWContext::KeyInfo KeyInfo;
#endif // TETRA_GLFW

class KeyEvent : public Event<KeyInfo> {
public:
	KeyEvent(int key, int mode, std::string name) : Event<KeyInfo>(KeyInfo(key, mode), name) {};
};
class AnyKeyEvent : public Event<KeyInfo>
{
public:
	int key;
	AnyKeyEvent(int key, int mode, std::string name) : Event<KeyInfo>(KeyInfo(mode), name), key(key) {};
};

class InputManager
{
private:

	void DispatchKeyEvent(KeyInfo info);

public:

	bool anyPressed = false;
	bool keys[1024];
	EventDispatcher<KeyInfo> keyDispatcher;

	InputManager();
	~InputManager();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void OnKeyPressed(int key);
	void UpdateKeys();

	void foo(const Event<KeyInfo>& ev);
};

