// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

	template <typename EventType>
	inline EventType ToType() const {
		if (std::is_base_of<Event<T>, EventType>::value)
			return static_cast<const EventType&> (*this);
		else
			throw std::invalid_argument("wrong event type");
	}
	Event(T eventType, std::string eventName = "new event") : name(eventName), type(eventType) {};
};

template <typename T>
struct EventListener
{
	void (*function) (const Event<T>&);

	EventListener(void (*function) (const Event<T>&)) : function(function) { };

	void operator()(const Event<T>& ev) { function(ev); };
	bool operator== (const EventListener& other) const { return (function == other.function); };
};

template <typename T>
struct EventListenerHasher
{
	std::size_t operator()(const EventListener<T>& listener) const {
		return std::hash<void*>()(reinterpret_cast<void*>(listener.function));
	}
};

template <typename T>
class EventDispatcher
{
	using func = EventListener<T>;
	using funcHasher = EventListenerHasher<T>;
	using funcIter = typename std::vector<func>::iterator;

	std::map<T, std::vector<func>> calls;
	std::unordered_map<func, T, funcHasher> listeners;

public:
	funcIter AddListener(T type, const func& function)
	{
		calls[type].push_back(function);
		int handle = calls[type].size() - 1;
		listeners.emplace(function, type);
		return calls[type].begin() + handle;
	};

	bool RemoveListener(T type, const func& function)
	{
		auto loc = std::find(calls[type].begin(), calls[type].end(), function);
		if (loc == calls[type].end()) {
			std::cout<<"no listener found for type\n";
			return false;
		}
		calls[type].erase(loc);
		return true;
	}
	bool RemoveListener(const func& function)
	{
		auto loc = listeners.find(function);
		if (loc == listeners.end()) {
			std::cout << "no listener found\n"; 
			return false;
		}
		return RemoveListener(loc->second, loc->first);
	}
	void Invoke(const Event<T>& event)
	{
		auto qualifier = event.GetType();
		if (calls.find(event.GetType()) == calls.end()) return;

		for (auto&& listener : calls.at(event.GetType())) {
			listener(event);
		}
	}
};

enum Act {
	PRESS,
	HOWER
};

class KeyEvent : public Event<Act> {
public:
	int key;
	KeyEvent(Act act, int key) : Event<Act>(act, "Key Event"), key(key) {};
};

void foo(const Event<Act>& ev)
{
	KeyEvent keyEv = ev.ToType<KeyEvent>();
	std::cout << keyEv.key << "\n";
}
void foo2(const Event<Act>& ev)
{
	std::cout << ev.GetType() << " e\n";
}

KeyEvent myEvent(PRESS, 2);

int main()
{
	EventDispatcher<Act> dispatcher;
	dispatcher.AddListener(PRESS, foo2);
	dispatcher.AddListener(PRESS, foo);
	dispatcher.Invoke(myEvent);
	return 0;
}
