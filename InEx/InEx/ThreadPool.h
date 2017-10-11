#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <random>
#include <windows.h>
#include <mutex>

std::mutex	g_mutex;
std::condition_variable g_cond_var;
bool g_thread_in_progress = false;

void lockCondition()
{
	std::unique_lock<std::mutex> lock(g_mutex);
	while (!g_thread_in_progress)
		g_cond_var.wait(lock);
}

void unlockCondition()
{
	std::unique_lock<std::mutex> lock(g_mutex);
	g_thread_in_progress = true;
	g_cond_var.notify_all();
}

void startTask()
{
	std::random_device rd;
	lockCondition();

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(50, 100000);

	std::cout << "Sleeping... \n" << "Thread id: " << std::this_thread::get_id() << std::endl;
	Sleep(dis(gen));
}

class ThreadPool
{
public:
	static ThreadPool& getInstance()
	{
		static ThreadPool instance;
		return instance;
	}

	void generateThreadTaskQueue(int i_amount) 
	{
		for (int i = 0; i < i_amount; ++i)
		{
			std::cout << "##################################" << std::endl;
			
			std::thread* thread = new std::thread(startTask);
			m_thread_pool.push_back(thread);
			
			std::cout << "Thread was added to queue, thread id: " << thread->get_id() << std::endl;
		}
	}

	void processThreadQueue()
	{
		unlockCondition();
		
		for (auto thread = m_thread_pool.begin(); thread != m_thread_pool.end(); ++thread)
		{
			(*thread)->join();
		}
	}

	void deleteThreadQueue()
	{	
		std::cout << "Thread queue size before cleaning: " << m_thread_pool.size() << std::endl;

		m_thread_pool.clear();
		std::cout << "Thread queue size after cleaning: " << m_thread_pool.size() << std::endl;
	}

private:

	std::deque<std::thread*> m_thread_pool;
	std::queue<std::function<void()>> m_task_pool;
	
private:
	ThreadPool() {};
	~ThreadPool() {};
	ThreadPool(const ThreadPool&) {};
	ThreadPool& operator=(const ThreadPool&) {};

};

#endif // !THREAD_POOL_H
