#include <iostream>
#include <stdexcept>
template <typename T> void reset(T& object){
	object = T();
}
template <typename T> void destruct(T& object){
	delete (&object); //ugly, shouldn't use
}

int main(){
	int test;
	if (std::cin >> test){
		std::cout << "deleting content ..." << std::endl;
		destruct(test);
		try{
			std::cout << test << std::endl; //error, test doesn't exist
		} catch (std::exception err){
			std::cerr << "can't output deleted variable" << std::endl;
		}
	}
}