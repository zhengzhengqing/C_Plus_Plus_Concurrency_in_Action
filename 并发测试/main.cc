#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
#include <mutex>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;
static mutex exclusive;

void worker(int min, int max)
{
    double tmp_sum = 0;
    for (int i = min; i <= max; i++) {
        tmp_sum += sqrt(i); // 
    }
    
    exclusive.lock(); // 
    sum += tmp_sum;
    exclusive.unlock();
}


// one thread
void serial_task(int min, int max) { 
  auto start_time = chrono::steady_clock::now();
  sum = 0;
  worker(0, MAX);
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

// multi thread
void concurrent_task(int min, int max) {
  auto start_time = chrono::steady_clock::now();

  unsigned concurrent_count = thread::hardware_concurrency(); // ①
  cout << "hardware_concurrency: " << concurrent_count << endl;
  vector<thread> threads;
  min = 0;
  sum = 0;
  for (int t = 0; t < concurrent_count; t++) 
  { // ②
    int range = max / concurrent_count * (t + 1);
    threads.push_back(thread(worker, min, range)); // ③
    min = range + 1;
  }
  for (auto& t : threads) 
  {
    t.join(); //
  }

  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
  cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

 int main()
 {
    //serial_task(0, 0);
    concurrent_task(0, MAX);
 }