// #include <list> 使用vector 替换文章中的list
#pragma once
#include <iostream>
#include <mutex>
#include <vector>
#include <algorithm>
#include <unistd.h>


using namespace std;


class Test_Mutex
{
    public:
    	Test_Mutex()
    	{
    	    add_count_ = 0;
    	    abord_count_ = 0;
    	}
    	~Test_Mutex() = default;
    	
    	void add_value()
    	{
    	    while(add_count_ <= 100)
    	    {
    	        sleep(1); // 1s
	    	{
	    	    std::lock_guard<std::mutex> guard(mutex_) ; // lock
	    	    vector_.emplace_back(add_count_++);
	    	}
	    	cout <<"add a num to vector_, thread_id = "<<std::this_thread::get_id() <<endl;
    	    }
    	}
    	
    	void print_size()
    	{
    	    while(abord_count_ <= 100)
    	    {
    	        sleep(1); // 1s
    	    	std::lock_guard<std::mutex> guard(mutex_) ; // lock
    	    	cout <<"vector.size = " << vector_.size() << " thread_id = " << std::this_thread::get_id() <<endl;
    	    }
    	}
    	
    private:
        vector<int> vector_;
        std::mutex mutex_;
        int add_count_;
        int abord_count_;
};
