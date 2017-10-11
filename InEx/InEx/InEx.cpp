// InEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ThreadPool.h"
#include <windows.h>
#include <random>

#define Pool ThreadPool::getInstance()

class Func 
{
public:
	void foo()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1000);
		std::cout << "\nSleeping... \t"<< "Thread id: \t" <<std::this_thread::get_id()<< std::endl;
		Sleep(dis(gen));
	}
};

void main()
{
	std::function<void()> callfunc = std::bind(&Func::foo, Func());

	for (int counter = 0; counter < 10; ++counter)
	{
		std::thread tmp_thread(callfunc);
		Pool.processThreadQueue(&tmp_thread);
	}

	Pool.deleteThreadQueue();
	system("pause");
}