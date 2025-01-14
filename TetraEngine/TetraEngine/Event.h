#pragma once

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
	std::map<int, std::vector<func>> calls;
public:
	void AddListener(int type, const func& function)
	{
		calls[type].push_back(function);
	};
	void RemoveListener(int type, const func& function) {
		if (calls.find(type) == calls.end()) return;

		auto loc = std::find(calls[type].begin(), calls[type].end(), function);
		if (loc == calls[type].end()) return;

		calls[type].erase(loc);
	}
	void Invoke(const Event<int>& event)
	{
		auto qualifier = event.GetType();
		if (calls.find(event.GetType()) == calls.end()) return;

		for (auto&& listener : calls.at(event.GetType())) {
			listener(event);
		}
	}
};
