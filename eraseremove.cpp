#include <iostream>
#include <vector>
#include <algorithm>

struct Foo{
	int first;
	std::string second;
};
int main(){
	std::vector<int> test {1,3,4,5,3,1,3};
	// remove all '3' from vector
	test.erase(std::remove(test.begin(),test.end(),3), test.end());
	typedef std::vector<int>::const_iterator myIterator;
	for (myIterator it = test.begin(); it != test.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;

	std::vector<Foo> next  {{0,"a"},{1,"b"},{0,"c"}};
	int to_erase = 1;
	next.erase(std::remove_if(next.begin(),next.end(),[&](Foo x){return x.first == to_erase;}), next.end());
	typedef std::vector<Foo>::const_iterator myFooIterator;
	for (myFooIterator it = next.begin(); it != next.end(); ++it)
		std::cout << it->second;
	std::cout << std::endl;
}