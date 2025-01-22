#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>

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
struct EventListenerTemplate
{
	EventListenerTemplate<T>(bool isStatic) : isStatic(isStatic) {};
	virtual std::function<void(const Event<T>&)> GetFunction() const { return NULL; };
	virtual void operator()(const Event<T>& ev) { GetFunction()(ev); };

	template <typename ListenerType>
	inline ListenerType ToType() const {
		return static_cast<const ListenerType&> (*this);
	}
	bool IsStatic() { return isStatic; };
private:
	bool isStatic = false;
};

template <typename T>
struct EventListener : public EventListenerTemplate<T>
{
	void(* function)(const Event<T>&);
	//void (*function) (const Event<T>&);

	EventListener(void(*function)(const Event<T>&)) : EventListenerTemplate<T>(true), function(function) { };

	std::function<void(const Event<T>&)> GetFunction() const override {
		return std::function(function);
	}
	bool operator== (const EventListener& other) const { 
		return function == other.function; };
};

template <typename T, class Sender>
struct EventListenerNonStatic : public EventListenerTemplate<T>
{
	void(Sender::*function)(const Event<T>&);
	const Sender& obj;
	//void (*function) (const Event<T>&);

	EventListenerNonStatic(void(Sender::*function)(const Event<T>&), const Sender& obj) : EventListenerTemplate<T>(false), function(function), obj(obj) { };

	std::function<void(const Event<T>&)> GetFunction() const override {

		return std::function<void(const Event<T>&)>(std::bind(function, obj, std::placeholders::_1));
	}
	bool operator== (const EventListenerNonStatic& other) const {
		return (function == other.function && &obj == &(other.obj));
	};
};

//template <typename T>
//struct EventListenerHasher
//{
//	std::size_t operator()(const EventListenerTemplate<T>& listener) const {
//		return std::hash<void*>()(reinterpret_cast<void*>(listener.GetFunction()));
//	}
//};

template <typename T>
class EventDispatcher
{
	using func = EventListenerTemplate<T>;
	//using funcHasher = EventListenerHasher<T>;

	std::map<T, std::vector<std::unique_ptr<func>>> calls;

private:

	//int AddListener(T type, const func& function)
	//{
	//	calls[type].push_back((std::unique_ptr<func>)std::move(function));
	//	int handle = calls[type].size() - 1;
	//	return handle;
	//};

public:

	template <class Sender>
	int AddListener(T type, void (Sender::* function)(const Event<T>&), const Sender& obj)
	{
		std::unique_ptr<EventListenerNonStatic<T, Sender>> created = std::make_unique<EventListenerNonStatic<T, Sender>>(function, obj);
		calls[type].push_back(std::move(created));
		return calls[type].size() - 1;
	};

	int AddListener(T type, void (* function)(const Event<T>&))
	{
		std::unique_ptr<EventListener<T>> created = std::make_unique<EventListener<T>>(function);
		calls[type].push_back(std::move(created));
		return calls[type].size() - 1;
	};

	std::vector<std::unique_ptr<func>>::iterator Find(T type, void (*function)(const Event<T>&))
	{
		EventListener<T> target(function);
		auto loc = calls[type].begin();
		for (; loc < calls[type].end(); loc++)
		{
			if ((*loc)->IsStatic())
			{
				EventListener<T> ptr = (*loc)->ToType<EventListener<T>>();
				if (target == ptr)
					return loc;
			}
		}
		return calls[type].end();
	}
	template <class Sender>
	std::vector<std::unique_ptr<func>>::iterator Find(T type, void (Sender::*function)(const Event<T>&), const Sender& obj)
	{
		EventListenerNonStatic<T,Sender> target(function, obj);
		auto loc = calls[type].begin();
		for (; loc < calls[type].end(); loc++)
		{
			if (!(*loc)->IsStatic())
			{
				EventListenerNonStatic<T,Sender> ptr = (*loc)->ToType<EventListenerNonStatic<T,Sender>>();
				if (target == ptr)
					return loc;
			}
		}
		return calls[type].end();
	}

	bool RemoveListener(T type, void (*function)(const Event<T>&))
	{
		auto loc = Find(type, function);
		if (loc == calls[type].end())
		{
			std::cout << "couldn't find listener\n";
			return false;
		}
		calls[type].erase(loc);
		return true;
	}

	template <class Sender>
	bool RemoveListener(T type, void (Sender::* function)(const Event<T>&), const Sender& obj)
	{
		auto loc = Find<Sender>(type, function, obj);
		if (loc == calls[type].end())
		{
			std::cout << "couldn't find nonstatic listener\n";
			return false;
		}
		calls[type].erase(loc);
		return true;
	}

	void Invoke(const Event<T>& event)
	{
		auto qualifier = event.GetType();
		if (calls.find(event.GetType()) == calls.end()) return;

		for (std::unique_ptr<func>& listener : calls.at(event.GetType())) {
			(*listener)(event);
		}
	}
};
