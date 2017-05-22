#include <bitset>
#include <iostream>
#include <cstdint>
// prints bits in memory order
template<typename T>
void print_binary(std::ostream& os, const T& data){
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&data);
	for (unsigned i = 0; i != sizeof(data); ++i){
		const std::bitset<8> currentByte(*bytes++);
		for (unsigned j = 0; j != 8; ++j)	// normalize order, bitsets default is reverse
			os << std::noboolalpha << currentByte[j];
	}
}
// prints bit in reverse memory order
template<typename T>
void print_binary_reverse(std::ostream& os, const T& data){
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&data);
	bytes += sizeof(data)-1; // start at the end
	for (unsigned i = 0; i != sizeof(data); ++i)
		os << std::bitset<8>(*bytes--);
}
// test with double
int main(){
	float value = 128;	// may change and value for this test 
	std::cout << "printing " << 8* sizeof(decltype(value)) << " bits:" <<  std::endl;
	print_binary(std::cout, value);
	std::cout << std::endl;
	print_binary_reverse(std::cout, value);
}