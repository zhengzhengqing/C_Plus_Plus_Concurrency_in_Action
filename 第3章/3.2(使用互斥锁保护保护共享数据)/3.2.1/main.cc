#include <thread>
#include <functional>

#include "Test_Mutex.h"

int main()
{
    Test_Mutex test_mutex;
    std::thread t_1(std::bind(&Test_Mutex::add_value, &test_mutex));
    std::thread t_2(std::bind(&Test_Mutex::print_size, &test_mutex));
    t_1.join();
    t_2.join();
    return 0;
}
