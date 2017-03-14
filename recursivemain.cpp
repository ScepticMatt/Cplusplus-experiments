#include <iostream>

int main(){
	static size_t count = 0;
	count++;
	if (count == 100){
		std::cout << "done" << std::endl;
		return 0;
	}
	else {
		std::cout << count << std::endl;
		main();	// illegal, but still works?
	}
		
}