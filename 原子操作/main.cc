#include <iostream>
#include <atomic>
#include <thread>
using namespace std;


int main()
{

  std::atomic<int> count(0);
  std::thread t1(
	[&] {
			for(int i = 0; i < 10000 ; i++)
			{
				count += i;
			}
		});
  	
  std::thread t2(
	[&] {
			for(int i = 0; i < 10000 ; i++)
			{
				count += i;
			}
  		});

  
  t1.join();
  t2.join();
  
  return 0;
}
