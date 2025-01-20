#include "InputManager.h"
#include <functional>

InputManager::InputManager()
{
	for (int i = 0; i < 1024; i++)
		keys[i] = false;

	//MyClass test;
	//EventListener<KeyInfo> listener(std::bind(& MyClass::handleEvent, test, std::placeholders::_1));
	//keyDispatcher.AddListener<MyClass>(KeyInfo(GLFW_KEY_P, GLFW_PRESS), &MyClass::handleEvent, test);
}

InputManager::~InputManager()
{
}

void InputManager::OnKeyDown(int key)
{
	DispatchKeyEvent(KeyInfo(key, GLFW_PRESS));
	keys[key] = true;
}

void InputManager::OnKeyUp(int key)
{
	DispatchKeyEvent(KeyInfo(key, GLFW_RELEASE));
	keys[key] = false;
}

void InputManager::OnKeyPressed(int key)
{
	DispatchKeyEvent(KeyInfo(key, GLFW_REPEAT));
}
void InputManager::UpdateKeys()
{
	anyPressed = false;
	for (int i = 0; i < 1024; i++)
	{
		if (keys[i])
		{
			OnKeyPressed(KeyInfo(keys[i], GLFW_PRESS));
			anyPressed = true;
		}
	}
}
void InputManager::DispatchKeyEvent(KeyInfo info)
{
	std::string name = std::to_string(info.bits.key);
	switch (info.bits.action)
	{
	case 0:
		name += " released"; break;
	case 1:
		name += " pressed"; break;
	case 2:
		name += " held"; break;
	}
	keyDispatcher.Invoke(KeyEvent(info.bits.key, info.bits.action, name));
	keyDispatcher.Invoke(AnyKeyEvent(info.bits.key, info.bits.action, name));

	std::cout << name << '\n';
}

void InputManager::foo(const Event<KeyInfo>& ev)
{
	std::cout << ev.GetName() << '\n';
	std::cout << (int)ev.GetType().bits.key << '\n';
};
