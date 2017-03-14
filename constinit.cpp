#include <iostream>

int main(){
	const int buffSize = []() -> int {int temp; std::cin >> temp; return temp;}();
	std::cout << buffSize << std::endl;
}