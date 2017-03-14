#include <iostream>
#include <ratio>
#include <chrono> // provides high_resolution_clock
#include <climits>  
using namespace std::chrono;

// testing time difference between prefix and postfix iteration
int main ()
{
  
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (int i = 0; i < INT_MAX; i++);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  for (int j = 0; j < INT_MAX; ++j);
  high_resolution_clock::time_point t3 = high_resolution_clock::now();
  // calculating time
  duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
  duration<double> time_span2 = duration_cast<duration<double>>(t3 - t2);
  double percentage = (time_span1 - time_span2)/(time_span1 + time_span2);
  std::cout << "time1: " << time_span1.count() << " seconds." << std::endl;;
  std::cout << "time2: " << time_span2.count() << " seconds." << std::endl;
  std::cout << "time diff" << 100*percentage << " \%" << std::endl;
  std::cout << std::endl;

  return 0;
}
