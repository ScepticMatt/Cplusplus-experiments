#include <iostream>

// requires C++14
template <typename T> constexpr T sumsum(T value){
	T sumsum{};
	for (T it{}; it != value; ++it)
		sumsum += it;
	return sumsum;
}
int main(){
	constexpr unsigned long long test_value = 1234567ULL;
	std::cout << sumsum(test_value) << std::endl;
	return 0;
}