#pragma once
#include "Event.h"


static class InputManager
{
public:
	enum KeyEvents {
		KeyDown,
		KeyUp
	};
	
	class KeyEvent : public Event<KeyEvents> {

	public:
		KeyEvent(KeyEvents ev, int key, std::string name = "Key event") : Event<KeyEvents>(ev, name), key(key) {}
		int key;
	};

	static EventDispatcher<KeyEvents> keyDispatcher;

	static void OnKeyDown(int i);
	static void OnKeyUp(int i);
};

