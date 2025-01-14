// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
class Event
{

private:
	T type;
	std::string name;
	bool handled = false;
protected:
	virtual bool Handled() const { return handled; };
public:
	std::string GetName() const { return name; };
	inline T GetType() const { return type; }
	Event(T eventType, std::string eventName = "new event") : name(eventName), type(eventType) {};
};

class EventDispatcher
{
	using func = std::function<void(const Event<int>&)>;
	std::map<int, std::vector<func>> listeners;
public:
	void AddListener(int type, const func& function)
	{
		listeners[type].push_back(function);
	};
	void RemoveListener(int type, const func& function) {
		if (listeners.find(type) == listeners.end()) return;

		auto loc = std::find(listeners[type].begin(), listeners[type].end(), &function);
		if (loc == listeners[type].end()) return;

		listeners[type].erase(loc);
	}
	void Invoke(const Event<int>& event)
	{
		auto qualifier = event.GetType();
		if (listeners.find(event.GetType()) == listeners.end()) return;

		for (auto&& listener : listeners.at(event.GetType())) {
			listener(event);
		}
	}
};

class A {
public:
	int a = 0;
	A(int i = 1) {
		a = i;
	}
	~A() {
		std::cout << a;
	}
};
void* ptr;
std::vector<std::shared_ptr<A>> collection;

void foo(Event<int> ev)
{
	std::cout << ev.GetType();
}

int main()
{
	EventDispatcher dispatcher;
	Event<int> myEvent (1);
	dispatcher.AddListener(1, foo);
	dispatcher.Invoke(myEvent);
}
