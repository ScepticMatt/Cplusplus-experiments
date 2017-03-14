#include <chrono>
#include <iostream>
using namespace std::chrono;

// test gcc for inlining, does that automatically with -O2, -O1 with keyword, -O0 never inlines
inline void count(size_t& value){
	++value;
}
int main(){
	auto t1 = high_resolution_clock::now();
	// count in main
	size_t cnt = 0;
	while (++cnt < 1234567890);
	std::cout << count << std::endl;
	auto t2 = high_resolution_clock::now();
	// count using function
	size_t cnt2 = 0;
	while (count(cnt2), cnt2 < 1234567890);
	std::cout << cnt2 << std::endl;
	auto t3 = high_resolution_clock::now();

	//duration<double> time_span = duration_cast<duration<double>>(t2-t1);
 	std::chrono::duration<double, std::milli> without_register = t2 - t1;
 	std::chrono::duration<double, std::milli> with_register = t3 - t2;
 	std::cout << "counting without register took " << without_register.count() << " ms" << std::endl;
 	std::cout << "counting with register took " << with_register.count() << " ms" << std::endl;
}