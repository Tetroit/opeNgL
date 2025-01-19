#pragma once

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

	std::map<T, std::vector<func>> calls;
	std::unordered_map<func, T, funcHasher> listeners;

public:

	void AddListener(T type, const func& function)
	{
		calls[type].push_back(function);
		int handle = calls[type].size() - 1;
		listeners.emplace(function, type);
	};

	bool RemoveListener(T type, const func& function)
	{
		auto loc = std::find(calls[type].begin(), calls[type].end(), function);
		if (loc == calls[type].end()) {
			std::cout << "no listener found for type\n";
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
