// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

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
int main()
{
	std::shared_ptr<A> shared(new A(2));
	collection.push_back(shared);
	//A* aa = new A(10);

	ptr = static_cast<void*>(&shared);

	std::shared_ptr<A>* copy = static_cast<std::shared_ptr<A>*>(ptr);
	copy->reset();
	ptr = nullptr;

	return 0;
}
