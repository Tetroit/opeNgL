// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>



void foo(int i)
{
	std::cout << i << " #1\n";
}
void foo2(int i)
{
	std::cout << i << " #2\n";
}

class MyClass {
public:
	void foo(int i)
	{
		std::cout << i * 2 << " #2\n";
	}
	void foo2(int i)
	{
		std::cout << i * 2 << " #3\n";
	}

};

struct AbstractTest
{
	virtual void test(int i) {};
};
struct AbstractTestImpl : public AbstractTest
{
	void test(int i) override
	{ std::cout << i; };
};
int main()
{
	std::unique_ptr<AbstractTest> ptr = std::make_unique<AbstractTestImpl>();
	std::vector<std::unique_ptr<AbstractTest>> vec;
	std::map<int, std::vector<std::unique_ptr<AbstractTest>>> map;

	vec.begin();
	map.emplace(1, std::move(vec));

	return 0;
}
