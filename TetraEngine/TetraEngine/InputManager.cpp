#include "InputManager.h"

EventDispatcher<InputManager::KeyEvents> InputManager::keyDispatcher;

void InputManager::OnKeyDown(int i)
{
	keyDispatcher.Invoke(KeyEvent(KeyDown, i));
}
void InputManager::OnKeyUp(int i)
{
	keyDispatcher.Invoke(KeyEvent(KeyUp, i));
}